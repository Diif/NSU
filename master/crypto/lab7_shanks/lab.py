import math

def discrete_log_bruteforce(g, h, p):
    count = 0
    value = 1
    # x = 0
    if value == h % p:
        return 0, count
    # последующие x
    for x in range(1, p-1):
        value = (value * g) % p
        count += 1
        if value == h % p:
            return x, count
    return None, count

def discrete_log_bsgs(g, h, p):
    m = int(math.ceil(math.sqrt(p)) + 1)
    print(f"Используем m = ceil(sqrt(p))+1 = {m}")

    # 1) Baby steps: вычисляем g^j mod p для j = 0..m-1
    baby = {}
    count = 0
    val = 1
    print("\nБэби-степы:")
    for j in range(m):
        baby[val] = j
        print(f" j={str(j).rjust(2)} | g^{j:<2} mod p = {val}")
        # для следующего j
        val = (val * g) % p
        count += 1

    # 2) Предвычисляем g^(-m) mod p = g^(n-m) mod p
    inv = pow(g, - m, p)
    print(f"\nВычислено g^(-m) ≡ {inv} mod {p} (обратный элемент)")

    # 3) Giant steps: перебираем i = 0..m-1, вычисляем h * inv^i
    giant = h % p
    print("\nГигант-степы:")
    for i in range(m):
        print(f" i={str(i).rjust(2)} | h*(g^(-m))^{i:<2} mod p = {giant}")
        if giant in baby:
            j = baby[giant]
            x = i * m + j
            total_mults = count + i
            print(f"\nНайдено совпадение: i={i}, j={j} → x = {i}*{m} + {j} = {x}")
            print(f"Всего умножений: baby={m}, giant={i}, итого={total_mults}")
            return x, total_mults
        # шаг к следующему i
        giant = (giant * inv) % p
        count += 1

    print("Логарифм не найден.")
    return None, count

if __name__ == "__main__":
    p = 263        
    g = 79         

    test_xs = [989]
    for x in test_xs:
        # h = pow(g, x, p)
        h = 122
        print(f"\n=== Тест: p={p}, g={g}, x={x}, h={h} ===")
        print("1) Полный перебор:")
        bf_x, bf_mults = discrete_log_bruteforce(g, h, p)
        print(f" Результат x = {bf_x}, умножений = {bf_mults}\n")
        print("2) Метод младенца‑гиганта:")
        bs_x, bs_mults = discrete_log_bsgs(g, h, p)
        print(f"\nРезультат x = {bs_x}, умножений = {bs_mults}")

