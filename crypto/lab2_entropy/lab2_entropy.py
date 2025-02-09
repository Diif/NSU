import math
import collections
import os
import random

def compute_frequencies(file_path):
    try:
        with open(file_path, 'rb') as f:
            data = f.read()
    except IOError as e:
        print(f"Ошибка при чтении файла: {e}")
        return None, None

    total_symbols = len(data)
    freq = collections.Counter(data)
    probabilities = {byte: count / total_symbols for byte, count in freq.items()}
    return probabilities, total_symbols

def compute_entropy(probabilities):
    entropy = 0.0
    for p in probabilities.values():
        if p > 0:
            entropy -= p * math.log2(p)
    return entropy

def display_frequencies(probabilities, total_symbols):
    if probabilities is None:
        return
    print(f"\nОбщее количество символов: {total_symbols}")
    print("Частоты появления символов (в процентах):")
    for byte, prob in sorted(probabilities.items(), key=lambda item: item[1], reverse=True):
        try:
            char = bytes([byte]).decode('utf-8')
            if not char.isprintable():
                char = f"0x{byte:02x}"
        except UnicodeDecodeError:
            char = f"0x{byte:02x}"
        print(f"'{char}': {prob*100:.2f}%")

def file_entropy_menu():
    file_path = input("Введите путь к файлу: ")
    probabilities, total = compute_frequencies(file_path)
    if probabilities is None:
        return
    display_frequencies(probabilities, total)
    entropy = compute_entropy(probabilities)
    print(f"\nЭнтропия файла: {entropy:.4f} бит на символ")
    distinct_symbols = len(probabilities)
    if distinct_symbols > 0:
        max_entropy = math.log2(distinct_symbols)
        print(f"Максимальная энтропия для {distinct_symbols} различных символов: {max_entropy:.4f} бит на символ")
    else:
        print("Нет символов для вычисления максимальной энтропии.")

def generate_identical_file(file_path, symbol, size):
    try:
        with open(file_path, 'wb') as f:
            f.write(symbol * size)
        print(f"Файл '{file_path}' с {size} одинаковыми символами создан.")
    except IOError as e:
        print(f"Ошибка при записи файла: {e}")

def generate_random_binary_file(file_path, size):
    random_chars = [random.choice('01') for _ in range(size)]
    data = ''.join(random_chars).encode('utf-8')
    try:
        with open(file_path, 'wb') as f:
            f.write(data)
        print(f"Файл '{file_path}' с {size} случайными символами из '0' и '1' создан.")
    except IOError as e:
        print(f"Ошибка при записи файла: {e}")

def generate_random_bytes_file(file_path, size):
    data = os.urandom(size)
    try:
        with open(file_path, 'wb') as f:
            f.write(data)
        print(f"Файл '{file_path}' с {size} случайными байтами (0-255) создан.")
    except IOError as e:
        print(f"Ошибка при записи файла: {e}")

def generate_files_menu():
    print("\nВыберите тип файла для генерации:")
    print("1. Файл с одинаковыми символами")
    print("2. Файл с случайными символами из набора {'0', '1'}")
    print("3. Файл со случайными байтами (0-255)")
    choice = input("Ваш выбор: ")
    file_path = input("Введите путь для сохранения файла: ")
    try:
        size = int(input("Введите количество символов (размер файла): "))
    except ValueError:
        print("Неверное значение для размера файла.")
        return

    if choice == "1":
        symbol_input = input("Введите символ для заполнения файла: ")
        if not symbol_input:
            print("Символ не введён.")
            return
        # Берём первый символ и кодируем его в байты
        symbol = symbol_input[0].encode('utf-8')
        generate_identical_file(file_path, symbol, size)
    elif choice == "2":
        generate_random_binary_file(file_path, size)
    elif choice == "3":
        generate_random_bytes_file(file_path, size)
    else:
        print("Неверный выбор.")

def main():
    while True:
        print("\nМеню:")
        print("1. Вычислить частоты и энтропию файла")
        print("2. Сгенерировать тестовые файлы")
        print("0. Выход")
        choice = input("Ваш выбор: ")
        if choice == "1":
            file_entropy_menu()
        elif choice == "2":
            generate_files_menu()
        elif choice == "0":
            print("Выход из программы.")
            break
        else:
            print("Неверный выбор, попробуйте снова.")

if __name__ == "__main__":
    main()
