def is_prime(n):
    if n < 2:
        return False
    for i in range(2, int(n**0.5) + 1):
        if n % i == 0:
            return False
    return True


def mod_inverse(a, p):
    if a < 0:
        a = (a % p + p) % p
    
    def extended_gcd(a, b):
        if a == 0:
            return b, 0, 1
        gcd, x1, y1 = extended_gcd(b % a, a)
        x = y1 - (b // a) * x1
        y = x1
        return gcd, x, y
    
    gcd, x, _ = extended_gcd(a % p, p)
    if gcd != 1:
        return None
    return (x % p + p) % p


def multiplication_table(p):
    if not is_prime(p):
        print(f"Ошибка: {p} не является простым числом!")
        return
    elements = list(range(1, p))
    
    print(f"\n{'=' * 60}")
    print(f"ТАБЛИЦА УМНОЖЕНИЯ В ГРУППЕ Z_{p}*")
    print(f"{'=' * 60}\n")
    
    # Заголовок
    print(f"{'×':>4}", end="")
    for e in elements:
        print(f"{e:>4}", end="")
    print()
    print("-" * (4 + 4 * len(elements)))
    
    # Строки таблицы
    for a in elements:
        print(f"{a:>4}", end="")
        for b in elements:
            result = (a * b) % p
            print(f"{result:>4}", end="")
        print()


def element_order_table(p):
    if not is_prime(p):
        print(f"Ошибка: {p} не является простым числом!")
        return
    
    elements = list(range(1, p))
    max_power = p - 1  # Максимальная степень для проверки
    
    print(f"\n{'=' * 80}")
    print(f"ТАБЛИЦА ПОРЯДКОВ ЭЛЕМЕНТОВ В ГРУППЕ Z_{p}*")
    print(f"{'=' * 80}\n")
    
    print(f"{'Элемент':>8}", end="")
    for power in range(1, max_power + 1):
        print(f"{power:>4}", end="")
    print(f"{'Порядок':>10}")
    print("-" * (8 + 4 * max_power + 10))
    
    generators = []
    
    for elem in elements:
        print(f"{elem:>8}", end="")
        order = 0
        
        for power in range(1, max_power + 1):
            result = pow(elem, power, p)
            
            print(f"{result:>4}", end="")
            order = power
            
            if result == 1:
                break
        
        for _ in range(power + 1, max_power + 1):
            print(f"{'—':>4}", end="")
        
        print(f"{order:>10}", end="")
        
        if order == p - 1:
            print(" ← ГЕНЕРАТОР", end="")
            generators.append(elem)
        
        print()
    
    print(f"\nГенераторы группы Z_{p}*: {generators}")
    print(f"Количество генераторов: {len(generators)}")


class EllipticCurve:
    
    def __init__(self, a, b, p):
        self.a = a % p
        self.b = b % p
        self.p = p
        
        if not is_prime(p):
            raise ValueError(f"{p} не является простым числом!")
        
        discriminant = (4 * a**3 + 27 * b**2) % p
        if discriminant == 0:
            raise ValueError("Кривая сингулярна (дискриминант = 0)!")
    
    def is_on_curve(self, point):
        if point is None:  # Точка в бесконечности
            return True
        
        x, y = point
        left = (y * y) % self.p
        right = (x**3 + self.a * x + self.b) % self.p
        return left == right
    
    def add_points(self, P1, P2):
        if P1 is None:
            return P2
        if P2 is None:
            return P1
        
        x1, y1 = P1
        x2, y2 = P2
        
        if x1 == x2 and (y1 + y2) % self.p == 0:
            return None  # Результат - точка в бесконечности
        
        if x1 == x2 and y1 == y2:
            if y1 == 0:
                return None
            numerator = (3 * x1 * x1 + self.a) % self.p
            denominator = (2 * y1) % self.p
        else:
            numerator = (y2 - y1) % self.p
            denominator = (x2 - x1) % self.p
        
        inv = mod_inverse(denominator, self.p)
        if inv is None:
            return None
        
        lambda_val = (numerator * inv) % self.p
        
        x3 = (lambda_val * lambda_val - x1 - x2) % self.p
        y3 = (lambda_val * (x1 - x3) - y1) % self.p
        
        return (x3, y3)
    
    def multiply_point(self, point, m):
        """M-кратная композиция точки (P + P + ... + P, m раз)"""
        if m == 0:
            return None  # Точка в бесконечности
        
        if m < 0:
            point = self.negate_point(point)
            m = -m
        
        result = None
        addend = point
        
        while m > 0:
            if m & 1:
                result = self.add_points(result, addend)
            addend = self.add_points(addend, addend)
            m >>= 1
        
        return result
    
    def negate_point(self, point):
        if point is None:
            return None
        x, y = point
        return (x, (-y) % self.p)
    
    def get_all_points(self):
        points = [None]  # Начинаем с точки в бесконечности
        
        for x in range(self.p):
            y_squared = (x**3 + self.a * x + self.b) % self.p
            
            for y in range(self.p):
                if (y * y) % self.p == y_squared:
                    points.append((x, y))
        
        return points
    
    def point_to_str(self, point):
        if point is None:
            return "O"
        return f"({point[0]},{point[1]})"


def m_fold_composition(a, b, p, point, m):
    curve = EllipticCurve(a, b, p)
    
    if not curve.is_on_curve(point):
        print(f"Ошибка: точка {point} не принадлежит кривой!")
        return
    
    print(f"\n{'=' * 60}")
    print(f"M-КРАТНАЯ КОМПОЗИЦИЯ ТОЧКИ НА КРИВОЙ")
    print(f"Кривая: y² = x³ + {a}x + {b} (mod {p})")
    print(f"Точка: {curve.point_to_str(point)}")
    print(f"M = {m}")
    print(f"{'=' * 60}\n")
    
    print("Используется алгоритм быстрого возведения в степень:\n")
    
    binary = bin(m)[2:]  # Убираем префикс '0b'
    print(f"M = {m} = {binary}₂ (двоичное представление)\n")
    
    result = None
    addend = point
    step = 0
    
    print("Шаги алгоритма:")
    print(f"{'Шаг':>4} {'Бит':>4} {'Удвоение':>15} {'Результат':>30}")
    print("-" * 65)
    
    for i, bit in enumerate(reversed(binary)):
        step += 1
        action = ""
        
        if bit == '1':
            result = curve.add_points(result, addend)
            action = f"добавить {curve.point_to_str(addend)}"
        else:
            action = "пропустить"
        
        print(f"{step:>4} {bit:>4} {curve.point_to_str(addend):>15} {action:>30}")
        
        if i < len(binary) - 1:
            addend = curve.add_points(addend, addend)
    
    print("\n" + "=" * 60)
    print(f"РЕЗУЛЬТАТ: {m} × {curve.point_to_str(point)} = {curve.point_to_str(result)}")
    print("=" * 60)

    return result

def elliptic_curve_addition_table(a, b, p):
    curve = EllipticCurve(a, b, p)
    points = curve.get_all_points()
    
    print(f"\n{'=' * 80}")
    print(f"ТАБЛИЦА СЛОЖЕНИЯ ТОЧЕК НА КРИВОЙ y² = x³ + {a}x + {b} (mod {p})")
    print(f"Всего точек на кривой: {len(points)}")
    print(f"{'=' * 80}\n")
    
    if len(points) > 20:
        print("Слишком много точек для отображения полной таблицы.")
        print(f"Показаны первые 15 точек из {len(points)}:\n")
        display_points = points[:15]
    else:
        display_points = points
    
    col_width = 8
    print(f"{'+':>{col_width}}", end="")
    for P in display_points:
        print(f"{curve.point_to_str(P):>{col_width}}", end="")
    print()
    print("-" * (col_width + col_width * len(display_points)))
    
    for P1 in display_points:
        print(f"{curve.point_to_str(P1):>{col_width}}", end="")
        for P2 in display_points:
            result = curve.add_points(P1, P2)
            print(f"{curve.point_to_str(result):>{col_width}}", end="")
        print()


def elliptic_curve_order_table(a, b, p):
    curve = EllipticCurve(a, b, p)
    points = curve.get_all_points()
    
    print(f"\n{'=' * 80}")
    print(f"ТАБЛИЦА ПОРЯДКОВ ТОЧЕК НА КРИВОЙ y² = x³ + {a}x + {b} (mod {p})")
    print(f"Всего точек на кривой: {len(points)}")
    print(f"{'=' * 80}\n")
    
    max_m = len(points)
    
    col_width = 8
    print(f"{'Точка':>{col_width}}", end="")
    for m in range(1, min(max_m + 1, 16)):
        print(f"{m:>{col_width}}", end="")
    if max_m > 15:
        print(f"{'...':>{col_width}}", end="")
    print(f"{'Порядок':>{col_width}}")
    print("-" * (col_width * (min(max_m, 15) + 3)))
    
    generators = []
    
    for point in points:
        print(f"{curve.point_to_str(point):>{col_width}}", end="")
        
        order = 0
        result = point
        
        for m in range(1, max_m + 1):
            result = curve.multiply_point(point, m)
            result_str = curve.point_to_str(result)
            
            if m <= 15:
                print(f"{result_str:>{col_width}}", end="")
            order = m
            
            if result is None:
                break
        
        for _ in range(order + 1, max_m + 1):
            print(f"{'—':>{col_width}}", end="")
        
        if max_m > 15:
            print(f"{'':>{col_width}}", end="")
        
        print(f"{order:>{col_width}}", end="")
        
        if order == len(points):
            print(" ← ГЕНЕРАТОР", end="")
            generators.append(point)
        
        print()
    
    print(f"\nГенераторы группы: {[curve.point_to_str(p) for p in generators]}")
    print(f"Количество генераторов: {len(generators)}")


def main():
    while True:
        print("\n" + "=" * 60)
        print("ПРОГРАММА ДЛЯ РАБОТЫ С ГРУППАМИ И ЭЛЛИПТИЧЕСКИМИ КРИВЫМИ")
        print("=" * 60)
        print("\n1. Таблица умножения в группе остатков Z_p*")
        print("2. Порядки элементов в группе остатков Z_p*")
        print("3. M-кратная композиция точки на эллиптической кривой")
        print("4. Таблица сложения точек на эллиптической кривой")
        print("5. Порядки точек на эллиптической кривой")
        print("0. Выход")
        
        choice = input("\nВыберите задачу (0-5): ").strip()
        
        if choice == "0":
            print("Выход из программы.")
            break
        
        elif choice == "1":
            try:
                p = int(input("Введите простое число p: "))
                multiplication_table(p)
            except ValueError:
                print("Ошибка: введите корректное число!")
        
        elif choice == "2":
            try:
                p = int(input("Введите простое число p: "))
                element_order_table(p)
            except ValueError:
                print("Ошибка: введите корректное число!")
        
        elif choice == "3":
            try:
                a = int(input("Введите коэффициент a: "))
                b = int(input("Введите коэффициент b: "))
                p = int(input("Введите простое число p: "))
                x = int(input("Введите координату x точки: "))
                y = int(input("Введите координату y точки: "))
                m = int(input("Введите значение M (кратность композиции): "))
                m_fold_composition(a, b, p, (x, y), m)
            except (ValueError, Exception) as e:
                print(f"Ошибка: {e}")
        
        elif choice == "4":
            try:
                a = int(input("Введите коэффициент a: "))
                b = int(input("Введите коэффициент b: "))
                p = int(input("Введите простое число p: "))
                elliptic_curve_addition_table(a, b, p)
            except (ValueError, Exception) as e:
                print(f"Ошибка: {e}")
        
        elif choice == "5":
            try:
                a = int(input("Введите коэффициент a: "))
                b = int(input("Введите коэффициент b: "))
                p = int(input("Введите простое число p: "))
                elliptic_curve_order_table(a, b, p)
            except (ValueError, Exception) as e:
                print(f"Ошибка: {e}")
        
        else:
            print("Неверный выбор! Попробуйте снова.")
        
        input("\nНажмите Enter для продолжения...")


if __name__ == "__main__":
    main()