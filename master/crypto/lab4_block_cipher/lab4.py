import os
import struct
import hashlib

BLOCK_SIZE = 8  # размер блока в байтах (64 бита)
TEA_ROUNDS = 32

def pkcs7_pad(data, block_size=BLOCK_SIZE):
    pad_len = block_size - (len(data) % block_size)
    return data + bytes([pad_len] * pad_len)

def pkcs7_unpad(data):
    pad_len = data[-1]
    if pad_len < 1 or pad_len > BLOCK_SIZE:
        raise ValueError("Неверное значение паддинга")
    if data[-pad_len:] != bytes([pad_len] * pad_len):
        raise ValueError("Неверный паддинг")
    return data[:-pad_len]

def derive_tea_key(key_string):
    key_hash = hashlib.md5(key_string.encode('utf-8')).digest()  # 16 байт
    key_words = struct.unpack(">4I", key_hash)  # 4 целых числа (32 бита каждое)
    return key_words

def tea_encrypt_block(block, key_words, rounds=TEA_ROUNDS):
    """
    Шифрует один 8-байтовый блок по алгоритму TEA.
    """
    y, z = struct.unpack(">II", block)
    delta = 0x9e3779b9
    sum = 0
    for _ in range(rounds):
        sum = (sum + delta) & 0xFFFFFFFF
        y = (y + (((z << 4) + key_words[0]) ^ (z + sum) ^ ((z >> 5) + key_words[1]))) & 0xFFFFFFFF
        z = (z + (((y << 4) + key_words[2]) ^ (y + sum) ^ ((y >> 5) + key_words[3]))) & 0xFFFFFFFF
    return struct.pack(">II", y, z)

def tea_decrypt_block(block, key_words, rounds=TEA_ROUNDS):
    """
    Дешифрует один 8-байтовый блок по алгоритму TEA.
    """
    y, z = struct.unpack(">II", block)
    delta = 0x9e3779b9
    sum = (delta * rounds) & 0xFFFFFFFF
    for _ in range(rounds):
        z = (z - (((y << 4) + key_words[2]) ^ (y + sum) ^ ((y >> 5) + key_words[3]))) & 0xFFFFFFFF
        y = (y - (((z << 4) + key_words[0]) ^ (z + sum) ^ ((z >> 5) + key_words[1]))) & 0xFFFFFFFF
        sum = (sum - delta) & 0xFFFFFFFF
    return struct.pack(">II", y, z)

def block_cipher_encrypt(data, key_words):
    padded_data = pkcs7_pad(data)
    ciphertext = bytearray()
    for i in range(0, len(padded_data), BLOCK_SIZE):
        block = padded_data[i:i+BLOCK_SIZE]
        ciphertext.extend(tea_encrypt_block(block, key_words))
    return bytes(ciphertext)

def block_cipher_decrypt(data, key_words):
    plaintext = bytearray()
    for i in range(0, len(data), BLOCK_SIZE):
        block = data[i:i+BLOCK_SIZE]
        plaintext.extend(tea_decrypt_block(block, key_words))
    return pkcs7_unpad(bytes(plaintext))

def encrypt_file(input_file, output_file, key_string):
    """Шифрует файл с использованием блочного шифра TEA."""
    key_words = derive_tea_key(key_string)
    with open(input_file, 'rb') as f:
        plaintext = f.read()
    ciphertext = block_cipher_encrypt(plaintext, key_words)
    with open(output_file, 'wb') as f:
        f.write(ciphertext)
    print(f"Файл '{input_file}' зашифрован и сохранён как '{output_file}'.")

def decrypt_file(input_file, output_file, key_string):
    """Расшифровывает файл с использованием блочного шифра TEA."""
    key_words = derive_tea_key(key_string)
    with open(input_file, 'rb') as f:
        ciphertext = f.read()
    plaintext = block_cipher_decrypt(ciphertext, key_words)
    with open(output_file, 'wb') as f:
        f.write(plaintext)
    print(f"Файл '{input_file}' расшифрован и сохранён как '{output_file}'.")

def main():
    print("Выберите действие:")
    print("1. Зашифровать файл")
    print("2. Расшифровать файл")
    choice = input("Ваш выбор: ")
    
    if choice == "1":
        input_file = input("Введите путь к исходному файлу: ")
        output_file = input("Введите путь для сохранения зашифрованного файла: ")
        key_string = input("Введите ключ (строка): ")
        encrypt_file(input_file, output_file, key_string)
    elif choice == "2":
        input_file = input("Введите путь к зашифрованному файлу: ")
        output_file = input("Введите путь для сохранения расшифрованного файла: ")
        key_string = input("Введите ключ (строка): ")
        decrypt_file(input_file, output_file, key_string)
    else:
        print("Бан.")

if __name__ == "__main__":
    main()
