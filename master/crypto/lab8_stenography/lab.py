from PIL import Image

def text_to_bits(text):
    return ''.join(f"{ord(c):08b}" for c in text)

def bits_to_text(bits):
    chars = [bits[i:i+8] for i in range(0, len(bits), 8)]
    return ''.join([chr(int(c, 2)) for c in chars])

def embed_lsb(image_path, output_path, secret_message):
    img = Image.open(image_path)
    if img.mode != 'RGB':
        img = img.convert('RGB')
    pixels = list(img.getdata())

    bits = text_to_bits(secret_message) + '00000000'  # маркер конца
    bit_index = 0
    new_pixels = []

    for r, g, b in pixels:
        if bit_index < len(bits):
            r = (r & ~1) | int(bits[bit_index])
            bit_index += 1
        if bit_index < len(bits):
            g = (g & ~1) | int(bits[bit_index])
            bit_index += 1
        if bit_index < len(bits):
            b = (b & ~1) | int(bits[bit_index])
            bit_index += 1
        new_pixels.append((r, g, b))

    img.putdata(new_pixels)
    img.save(output_path)
    print(f"Сообщение успешно внедрено и сохранено в '{output_path}'.")

def extract_lsb(image_path):
    img = Image.open(image_path)
    if img.mode != 'RGB':
        img = img.convert('RGB')
    pixels = list(img.getdata())

    bits = ''
    for r, g, b in pixels:
        bits += str(r & 1)
        bits += str(g & 1)
        bits += str(b & 1)

    # собираем байты и останавливаемся на маркере конца
    chars = [bits[i:i+8] for i in range(0, len(bits), 8)]
    result = ''
    for byte in chars:
        if byte == '00000000':
            break
        result += chr(int(byte, 2))
    return result

def main():
    while True:
        print("\nВыберите действие:")
        print("1) Внедрить сообщение")
        print("2) Извлечь сообщение")
        print("0) Выход")
        choice = input("Ваш выбор: ").strip()

        if choice == "1":
            input_path = input("Путь к исходному BMP-файлу: ").strip()
            output_path = input("Путь для сохранения результата: ").strip()
            message = input("Введите сообщение для внедрения: ")
            embed_lsb(input_path, output_path, message)

        elif choice == "2":
            input_path = input("Путь к BMP-файлу для извлечения: ").strip()
            secret = extract_lsb(input_path)
            print("Извлечённое сообщение:", secret)

        elif choice == "0":
            print("Выход.")
            break

        else:
            print("Неверный выбор, попробуйте снова.")

if __name__ == "__main__":
    main()
