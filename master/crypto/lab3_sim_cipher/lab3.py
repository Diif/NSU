import os

def generate_random_key_file(file_path, size):
    random_bytes = os.urandom(size)
    with open(file_path, 'wb') as f:
        f.write(random_bytes)
    print(f"Ключевой файл '{file_path}' с размером {size} байт успешно создан.")

def vernam_cipher(input_file, key_file, output_file):
    with open(input_file, 'rb') as f:
        plaintext = f.read()
    with open(key_file, 'rb') as f:
        key = f.read()
    
    if len(key) < len(plaintext):
        raise ValueError("Ключевой файл короче файла с открытым текстом!")
    
    key = key[:len(plaintext)]
    
    ciphertext = bytes([p ^ k for p, k in zip(plaintext, key)])
    
    with open(output_file, 'wb') as f:
        f.write(ciphertext)
    print(f"Результат сохранён в файле '{output_file}'.")

def rc4(key, data):
    S = list(range(256))
    j = 0
    key_length = len(key)
    for i in range(256):
        j = (j + S[i] + key[i % key_length]) % 256
        S[i], S[j] = S[j], S[i]
    
    i = 0
    j = 0
    result = bytearray()
    for byte in data:
        i = (i + 1) % 256
        j = (j + S[i]) % 256
        S[i], S[j] = S[j], S[i]
        K = S[(S[i] + S[j]) % 256]
        result.append(byte ^ K)
    return bytes(result)

def rc4_encrypt_decrypt(input_file, key_string, output_file):
    key = key_string.encode('utf-8')
    with open(input_file, 'rb') as f:
        data = f.read()
    result = rc4(key, data)
    with open(output_file, 'wb') as f:
        f.write(result)
    print(f"RC4: Результат сохранён в файле '{output_file}'.")

def main():
    print("Выберите опцию:")
    print("1. Сгенерировать файл с случайными символами (ключ для шифра Вернама)")
    print("2. Шифр Вернама (зашифровать/расшифровать файл)")
    print("3. Поточный шифр RC4 (зашифровать/расшифровать файл)")
    choice = input("Ваш выбор: ")

    if choice == "1":
        file_path = input("Введите путь для сохранения ключевого файла: ")
        size = int(input("Введите размер файла (в байтах): "))
        generate_random_key_file(file_path, size)
    
    elif choice == "2":
        input_file = input("Введите путь к файлу: ")
        key_file = input("Введите путь к ключевому файлу: ")
        output_file = input("Введите путь для сохранения результата (зашифрованного/расшифрованного файла): ")
        vernam_cipher(input_file, key_file, output_file)
    
    elif choice == "3":
        input_file = input("Введите путь к входному файлу: ")
        key_string = input("Введите строковый ключ для RC4: ")
        output_file = input("Введите путь для сохранения результата: ")
        rc4_encrypt_decrypt(input_file, key_string, output_file)
    
    else:
        print("Неверный выбор. Завершение работы.")

if __name__ == "__main__":
    main()
