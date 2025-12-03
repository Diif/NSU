#!/usr/bin/env python3

import secrets
import hashlib
import binascii
import sys

PBKDF2_ITER = 100_000
SESSION_KEY_LEN = 32  # bytes
MASTER_KEY_LEN = 32


def hexb(b: bytes) -> str:
    return binascii.hexlify(b).decode('ascii')


def xor_bytes(a: bytes, b: bytes) -> bytes:
    return bytes(x ^ y for x, y in zip(a, b))


# master_key == pwd, context == salt
def derive_keystream(master_key: bytes, context: bytes, length: int = SESSION_KEY_LEN, iterations: int = PBKDF2_ITER) -> bytes:
    return hashlib.pbkdf2_hmac('sha256', master_key, context, iterations, dklen=length)


class TTP:
    def __init__(self, n_users: int):
        self.n = n_users
        self.users = [f'User{i}' for i in range(1, n_users + 1)]
        # master keys (secret) for each user
        self.master_keys = {u: secrets.token_bytes(MASTER_KEY_LEN) for u in self.users}

    def show_users_table(self):
        print('\n=== Users and master keys ===')
        print(f"{'Index':>5} | {'User':<10} | {'Master key (hex)'}")
        print('-' * 60)
        for i, u in enumerate(self.users, start=1):
            print(f"{i:5} | {u:<10} | {hexb(self.master_keys[u])}")
        print()

    def generate_session_for(self, idx1: int, idx2: int):
        if idx1 < 1 or idx1 > self.n or idx2 < 1 or idx2 > self.n:
            raise ValueError('User index out of range')
        u1 = self.users[idx1 - 1]
        u2 = self.users[idx2 - 1]
        if u1 == u2:
            print('\nВыбраны одинаковые пользователи — общий ключ будет равен сессионному ключу, но это некорректный сценарий.')

        print(f"\n=== Генерация сессионного ключа для {u1} и {u2} ===")

        session_key = secrets.token_bytes(SESSION_KEY_LEN)
        print(f"[TTP] Сгенерирован Session Key (секрет): {hexb(session_key)}")

        context = f"{u1}:{u2}".encode('utf-8')
        print(f"[TTP] Контекст из ID клиентов (используется как salt): {context.decode('utf-8')}")

        results = {}
        for u in (u1, u2):
            mk = self.master_keys[u]
            print(f"\n[TTP] Для {u}:")
            print(f"  Master key (секрет, hex): {hexb(mk)}")
            ks = derive_keystream(mk, context)
            print(f"  Derived keystream (PBKDF2(...), hex): {hexb(ks)}")
            ciphertext = xor_bytes(session_key, ks)
            print(f"  Ciphertext (SessionKey XOR keystream), hex: {hexb(ciphertext)}")
            results[u] = {'mk': mk, 'ks': ks, 'ct': ciphertext}

        print('\n=== Восстановление Session Key пользователями ===')
        recovered = {}
        for u in (u1, u2):
            print(f"\n[{u}] Получил ciphertext: {hexb(results[u]['ct'])}")
            derived_ks = derive_keystream(self.master_keys[u], context)
            print(f"[{u}] Вычислил keystream из своего master key и context: {hexb(derived_ks)}")
            recovered_sk = xor_bytes(results[u]['ct'], derived_ks)
            print(f"[{u}] Восстановленный Session Key: {hexb(recovered_sk)}")
            recovered[u] = recovered_sk

        # Verify both recovered keys equal the original
        ok = True
        for u in (u1, u2):
            if recovered[u] != session_key:
                ok = False
        print('\n=== Проверка ===')
        if ok:
            print('Оба абонента корректно восстановили одинаковый Session Key.')
        else:
            print('Ошибка: восстановленные ключи не совпадают!')

        print(f"[TTP] Оригинальный Session Key (для проверки): {hexb(session_key)}\n")


def main():
    print('Модель распределения ключей с TTP')
    try:
        n = int(input('Введите количество пользователей: ').strip())
    except Exception:
        print('Неверный ввод, требуется целое число > 1')
        return
    if n < 2:
        print('Нужно минимум 2 пользователя')
        return

    ttp = TTP(n)
    ttp.show_users_table()

    while True:
        print("Выберите двух абонентов по номерам через пробел (или введите 'exit' для выхода):")
        s = input('> ').strip()
        if not s:
            continue
        if s.lower() in ('exit', 'quit', 'q'):
            print('Выход.')
            break
        parts = s.split()
        if len(parts) != 2:
            print('Ожидается два числа, например: 1 3')
            continue
        try:
            i1 = int(parts[0])
            i2 = int(parts[1])
        except ValueError:
            print('Ожидаются числовые индексы пользователей.')
            continue
        try:
            ttp.generate_session_for(i1, i2)
        except Exception as e:
            print(f'Ошибка: {e}')


if __name__ == '__main__':
    main()
