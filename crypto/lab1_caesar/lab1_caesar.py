import re
import enchant

def caesar_encrypt(text, key):
    result = ""
    for ch in text:
        if ch.isalpha():
            # Determine the base code ('A' for uppercase, 'a' for lowercase)
            base = ord('A') if ch.isupper() else ord('a')
            # Shift the character by the key with wrap-around
            result += chr((ord(ch) - base + key) % 26 + base)
        else:
            result += ch
    return result

def caesar_decrypt(text, key):
    return caesar_encrypt(text, (-key) % 26)

def known_plaintext_attack(plaintext, ciphertext):
    for key in range(26):
        if caesar_encrypt(plaintext, key) == ciphertext:
            return key
    return None

def ciphertext_only_attack(ciphertext):
    results = []
    for key in range(26):
        decrypted = caesar_decrypt(ciphertext, key)
        results.append((key, decrypted))
    return results

def automatic_attack(ciphertext, threshold=0.5):
    english_dict = enchant.Dict("en_US")
    best_key = None
    best_ratio = 0
    best_decryption = ""
    
    for key in range(26):
        decrypted = caesar_decrypt(ciphertext, key)
        words = re.findall(r'\b[a-z]+\b', decrypted.lower())
        if not words:
            ratio = 0
        else:
            count = sum(1 for word in words if english_dict.check(word))
            ratio = count / len(words)
        if ratio > best_ratio:
            best_ratio = ratio
            best_key = key
            best_decryption = decrypted
            
    if best_ratio >= threshold:
        return best_key, best_decryption
    else:
        return None, None

def main():
    while True:
        print("Choose an option:")
        print("1. Encryption/Decryption (Caesar cipher)")
        print("2. Known-plaintext attack")
        print("3. Ciphertext-only attack (brute force all keys)")
        print("4. Automatic attack using pyenchant (detects meaningful text)")
        print("0. Exit")
        choice = input("Your choice: ")

        if choice == "1":
            mode = input("Enter 'e' for encryption or 'd' for decryption: ").lower()
            text = input("Enter the text: ")
            try:
                key = int(input("Enter the key (0-25): "))
            except ValueError:
                print("Invalid key. Please enter a number between 0 and 25.")
                continue

            if not (0 <= key <= 25):
                print("Key must be in the range 0-25.")
                continue


            if mode == "e":
                result = caesar_encrypt(text, key)
                print("Encrypted text:", result)
            elif mode == "d":
                result = caesar_decrypt(text, key)
                print("Decrypted text:", result)
            else:
                print("Invalid mode. Choose 'e' or 'd'.")
        
        elif choice == "2":
            plaintext = input("Enter the plaintext: ")
            ciphertext = input("Enter the ciphertext: ")
            key = known_plaintext_attack(plaintext, ciphertext)
            if key is not None:
                print("Determined encryption key:", key)
            else:
                print("Key not found. Please check your input.")
        
        elif choice == "3":
            ciphertext = input("Enter the ciphertext: ")
            print("Decryption options:")
            for key, decrypted in ciphertext_only_attack(ciphertext):
                print(f"Key {key}: {decrypted}")
        
        elif choice == "4":
            ciphertext = input("Enter the ciphertext: ")
            key, decryption = automatic_attack(ciphertext)
            if key is not None:
                print("Found encryption key:", key)
                print("Decrypted text:", decryption)
            else:
                print("Could not determine the key automatically.")
        
        elif choice == "0":
            print("Exiting the program.")
            break
        else:
            print("Invalid choice, please try again.")
        
        print("\n" + "-"*40 + "\n")

if __name__ == "__main__":
    main()
