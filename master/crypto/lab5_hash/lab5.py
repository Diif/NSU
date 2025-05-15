import os
import hashlib

# (salt: hex‑строка, pw_hash: hex‑строка)
users_db = {}

def hash_password(password: str, salt: bytes = None) -> tuple[bytes, bytes]:
    if salt is None:
        salt = os.urandom(16)
    pw_bytes = password.encode('utf-8')
    digest = hashlib.sha256(salt + pw_bytes).digest()
    return salt, digest

def register_user(username: str, password: str) -> bool:
    if username in users_db:
        print("Пользователь уже существует.")
        return False
    salt, pw_hash = hash_password(password)
    users_db[username] = (salt.hex(), pw_hash.hex())
    print(f"Пользователь '{username}' успешно зарегистрирован.")
    return True

def authenticate_user(username: str, password: str) -> bool:
    if username not in users_db:
        print("Пользователь не найден.")
        return False
    salt_hex, hash_hex = users_db[username]
    salt = bytes.fromhex(salt_hex)
    _, pw_hash = hash_password(password, salt)
    if pw_hash.hex() == hash_hex:
        print("Аутентификация успешна.")
        return True
    else:
        print("Неверный пароль.")
        return False

def show_users_db():
    print("\nТекущее содержимое базы пользователей:")
    if not users_db:
        print("(пусто)")
    else:
        for username, (salt, pw_hash) in users_db.items():
            print(f"- {username}:\n  Salt: {salt}\n  Hash: {pw_hash}")

def main():
    while True:
        print("\n1) Регистрация")
        print("2) Вход")
        print("3) Показать содержимое базы пользователей")
        print("0) Выход")
        print("==========")
        choice = input("Ваш выбор: ").strip()
        if choice == "1":
            u = input("Имя пользователя: ").strip()
            p = input("Пароль: ").strip()
            register_user(u, p)
        elif choice == "2":
            u = input("Имя пользователя: ").strip()
            p = input("Пароль: ").strip()
            authenticate_user(u, p)
        elif choice == "3":
            show_users_db()
        elif choice == "0":
            break
        else:
            print("Неверный выбор.")

if __name__ == "__main__":
    main()
