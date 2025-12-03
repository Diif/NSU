#!/usr/bin/env python3

import argparse
import base64
import getpass
import glob
import hashlib
import hmac
import json
import os
import sys
import time
from typing import Dict, Optional

CHUNK_SIZE = 8192
DEFAULT_MANIFEST = "mac_manifest.json"


def derive_key(password: str, salt: bytes, iterations: int = 100_000, dklen: int = 32) -> bytes:
    return hashlib.pbkdf2_hmac("sha256", password.encode("utf-8"), salt, iterations, dklen)


def compute_hmac_file(path: str, key: bytes) -> str:
    h = hmac.new(key, digestmod=hashlib.sha256)
    with open(path, "rb") as f:
        while True:
            chunk = f.read(CHUNK_SIZE)
            if not chunk:
                break
            h.update(chunk)
    return h.hexdigest()


def load_manifest(path: str) -> Dict:
    if not os.path.exists(path):
        return {}
    with open(path, "r", encoding="utf-8") as f:
        return json.load(f)


def save_manifest(path: str, data: Dict) -> None:
    with open(path, "w", encoding="utf-8") as f:
        json.dump(data, f, indent=2, ensure_ascii=False)


def resolve_paths(patterns):
    out = []
    for p in patterns:
        for match in glob.glob(p):
            ab = os.path.abspath(match)
            if os.path.isfile(ab):
                out.append(ab)
    seen = set()
    uniq = []
    for x in out:
        if x not in seen:
            uniq.append(x)
            seen.add(x)
    return uniq


def init_manifest(manifest_path: str, file_patterns, iterations: int):
    files = resolve_paths(file_patterns)
    if not files:
        print("No files found to initialize. Provide filenames or glob patterns.")
        return

    password = getpass.getpass("Enter new password (will derive key): ")
    password2 = getpass.getpass("Confirm password: ")
    if password != password2:
        print("Passwords do not match; aborting.")
        return

    salt = os.urandom(16)
    key = derive_key(password, salt, iterations)

    manifest = {
        "kdf": "pbkdf2_sha256",
        "salt": base64.b64encode(salt).decode("ascii"),
        "iterations": iterations,
        "files": {}
    }

    for p in files:
        try:
            mac = compute_hmac_file(p, key)
            manifest["files"][p] = {
                "mac": mac,
                "size": os.path.getsize(p),
                "mtime": os.path.getmtime(p)
            }
            print(f"Added: {p}")
        except Exception as e:
            print(f"Failed to add {p}: {e}")

    save_manifest(manifest_path, manifest)
    print(f"Manifest saved to {manifest_path}")


def ask_password_and_key(manifest: Dict) -> Optional[bytes]:
    if not manifest or "salt" not in manifest or "iterations" not in manifest:
        print("Manifest missing KDF parameters. Are you sure this is a valid manifest?")
        return None
    salt = base64.b64decode(manifest["salt"])
    iterations = int(manifest["iterations"])
    password = getpass.getpass("Enter password: ")
    return derive_key(password, salt, iterations)


def add_files(manifest_path: str, file_patterns):
    manifest = load_manifest(manifest_path)
    if not manifest:
        print("Manifest not found or empty. Use 'init' to create one first.")
        return
    key = ask_password_and_key(manifest)
    if key is None:
        return
    files = resolve_paths(file_patterns)
    if not files:
        print("No files matched given patterns.")
        return
    changed = False
    for p in files:
        try:
            mac = compute_hmac_file(p, key)
            manifest.setdefault("files", {})[p] = {
                "mac": mac,
                "size": os.path.getsize(p),
                "mtime": os.path.getmtime(p)
            }
            print(f"Added/Updated: {p}")
            changed = True
        except Exception as e:
            print(f"Failed to add {p}: {e}")
    if changed:
        save_manifest(manifest_path, manifest)
        print(f"Manifest updated: {manifest_path}")


def verify_manifest(manifest_path: str, check_new_files: bool = True):
    manifest = load_manifest(manifest_path)
    if not manifest:
        print("Manifest not found or empty.")
        return
    key = ask_password_and_key(manifest)
    if key is None:
        return
    recorded = manifest.get("files", {})

    ok = []
    modified = []
    missing = []
    for path, meta in recorded.items():
        if not os.path.exists(path):
            missing.append(path)
            continue
        try:
            mac = compute_hmac_file(path, key)
            if hmac.compare_digest(mac, meta["mac"]):
                ok.append(path)
            else:
                modified.append(path)
        except Exception as e:
            print(f"Error checking {path}: {e}")

    new_files = []
    if check_new_files:
        dirs = set(os.path.dirname(p) for p in recorded.keys())
        for d in dirs:
            try:
                for fname in os.listdir(d):
                    full = os.path.abspath(os.path.join(d, fname))
                    if os.path.isfile(full) and full not in recorded:
                        new_files.append(full)
            except Exception:
                continue

    print("\nVerification result:")
    print(f"  OK: {len(ok)}")
    print(f"  Modified: {len(modified)}")
    print(f"  Missing: {len(missing)}")
    if check_new_files:
        print(f"  New (not in manifest): {len(new_files)}")

    if ok:
        print("\nOK files:")
        for p in ok:
            print("  ", p)
    if modified:
        print("\nModified files:")
        for p in modified:
            print("  ", p)
    if missing:
        print("\nMissing files:")
        for p in missing:
            print("  ", p)
    if check_new_files and new_files:
        print("\nNew files (present but not recorded):")
        for p in new_files:
            print("  ", p)


def update_files(manifest_path: str, file_patterns=None):
    manifest = load_manifest(manifest_path)
    if not manifest:
        print("Manifest not found or empty.")
        return
    key = ask_password_and_key(manifest)
    if key is None:
        return
    recorded = manifest.setdefault("files", {})
    targets = []
    if file_patterns:
        targets = resolve_paths(file_patterns)
    else:
        targets = list(recorded.keys())

    changed = False
    for p in targets:
        if not os.path.exists(p):
            print(f"Skipping missing file: {p}")
            continue
        try:
            mac = compute_hmac_file(p, key)
            recorded[p] = {"mac": mac, "size": os.path.getsize(p), "mtime": os.path.getmtime(p)}
            print(f"Updated: {p}")
            changed = True
        except Exception as e:
            print(f"Failed to update {p}: {e}")
    if changed:
        save_manifest(manifest_path, manifest)
        print("Manifest saved.")


def list_files(manifest_path: str):
    manifest = load_manifest(manifest_path)
    if not manifest:
        print("Manifest not found or empty.")
        return
    files = manifest.get("files", {})
    if not files:
        print("No files recorded.")
        return
    print(f"Files in manifest ({len(files)}):")
    for p, meta in files.items():
        print(f" - {p}\n    mac: {meta.get('mac')}\n    size: {meta.get('size')}\n    mtime: {time.ctime(meta.get('mtime', 0))}")


def remove_files(manifest_path: str, file_patterns):
    manifest = load_manifest(manifest_path)
    if not manifest:
        print("Manifest not found or empty.")
        return
    files = resolve_paths(file_patterns)
    changed = False
    for p in files:
        if p in manifest.get("files", {}):
            manifest["files"].pop(p)
            print(f"Removed: {p}")
            changed = True
        else:
            print(f"Not recorded: {p}")
    if changed:
        save_manifest(manifest_path, manifest)
        print("Manifest updated.")


def parse_args(argv=None):
    p = argparse.ArgumentParser(description="File integrity tool using HMAC-SHA256")
    p.add_argument("--manifest", "-m", default=DEFAULT_MANIFEST, help=f"manifest file (default: {DEFAULT_MANIFEST})")
    sub = p.add_subparsers(dest="cmd", required=True)

    sp_init = sub.add_parser("init", help="Create a new manifest from files")
    sp_init.add_argument("files", nargs="+", help="Files or glob patterns to include")
    sp_init.add_argument("--iterations", type=int, default=100_000, help="PBKDF2 iterations")

    sp_add = sub.add_parser("add", help="Add files to an existing manifest")
    sp_add.add_argument("files", nargs="+", help="Files or glob patterns to add")

    sp_verify = sub.add_parser("verify", help="Verify files in the manifest")
    sp_verify.add_argument("--no-new", dest="check_new", action="store_false", help="Do not look for new files on disk")

    sp_update = sub.add_parser("update", help="Recompute and store MACs for target files (or all if none specified)")
    sp_update.add_argument("files", nargs="*", help="Files or glob patterns to update (default: all recorded)")

    sp_list = sub.add_parser("list", help="List files in the manifest")

    sp_remove = sub.add_parser("remove", help="Remove files from the manifest")
    sp_remove.add_argument("files", nargs="+", help="Files or glob patterns to remove")

    return p.parse_args(argv)


def main(argv=None):
    args = parse_args(argv)
    manifest_path = args.manifest

    if args.cmd == "init":
        init_manifest(manifest_path, args.files, args.iterations)
    elif args.cmd == "add":
        add_files(manifest_path, args.files)
    elif args.cmd == "verify":
        verify_manifest(manifest_path, check_new_files=args.check_new)
    elif args.cmd == "update":
        patterns = args.files if args.files else None
        update_files(manifest_path, patterns)
    elif args.cmd == "list":
        list_files(manifest_path)
    elif args.cmd == "remove":
        remove_files(manifest_path, args.files)
    else:
        print("Unknown command")


if __name__ == "__main__":
    main()
