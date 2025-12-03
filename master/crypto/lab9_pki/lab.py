import json
import hashlib
import os
from datetime import datetime
from cryptography.hazmat.primitives.asymmetric import rsa, padding
from cryptography.hazmat.primitives import hashes, serialization
from cryptography.hazmat.backends import default_backend


class CertificationAuthority:
    """Класс для представления Центра Сертификации"""
    
    def __init__(self, name, private_key=None, public_key=None):
        self.name = name
        if private_key is None:
            # Генерируем новую пару ключей
            self.private_key = rsa.generate_private_key(
                public_exponent=65537,
                key_size=2048,
                backend=default_backend()
            )
            self.public_key = self.private_key.public_key()
        else:
            self.private_key = private_key
            self.public_key = public_key
    
    def sign_data(self, data):
        """Подписывает данные приватным ключом"""
        signature = self.private_key.sign(
            data.encode('utf-8'),
            padding.PSS(
                mgf=padding.MGF1(hashes.SHA256()),
                salt_length=padding.PSS.MAX_LENGTH
            ),
            hashes.SHA256()
        )
        return signature
    
    def verify_signature(self, data, signature, public_key):
        """Проверяет подпись с использованием публичного ключа"""
        try:
            public_key.verify(
                signature,
                data.encode('utf-8'),
                padding.PSS(
                    mgf=padding.MGF1(hashes.SHA256()),
                    salt_length=padding.PSS.MAX_LENGTH
                ),
                hashes.SHA256()
            )
            return True
        except:
            return False


class Certificate:
    """Класс для представления сертификата"""
    
    def __init__(self, owner_name, public_key, issuer_name, signature):
        self.owner_name = owner_name
        self.public_key = public_key
        self.issuer_name = issuer_name
        self.signature = signature
        self.timestamp = datetime.now().isoformat()
    
    def to_dict(self):
        """Конвертирует сертификат в словарь для сохранения"""
        public_pem = self.public_key.public_bytes(
            encoding=serialization.Encoding.PEM,
            format=serialization.PublicFormat.SubjectPublicKeyInfo
        ).decode('utf-8')
        
        return {
            'owner_name': self.owner_name,
            'public_key': public_pem,
            'issuer_name': self.issuer_name,
            'signature': self.signature.hex(),
            'timestamp': self.timestamp
        }
    
    @staticmethod
    def from_dict(data):
        """Создает сертификат из словаря"""
        public_key = serialization.load_pem_public_key(
            data['public_key'].encode('utf-8'),
            backend=default_backend()
        )
        signature = bytes.fromhex(data['signature'])
        
        cert = Certificate(
            data['owner_name'],
            public_key,
            data['issuer_name'],
            signature
        )
        cert.timestamp = data['timestamp']
        return cert
    
    def get_signed_data(self):
        """Возвращает данные, которые были подписаны"""
        public_pem = self.public_key.public_bytes(
            encoding=serialization.Encoding.PEM,
            format=serialization.PublicFormat.SubjectPublicKeyInfo
        ).decode('utf-8')
        return f"{self.owner_name}|{public_pem}"


class NetworkPKI:
    """Сетевая (Mesh) PKI - граф доверия"""
    
    def __init__(self):
        self.cas = {}  # Словарь ЦС: {имя: CA объект}
        self.trust_graph = {}  # Граф доверия: {имя_ЦС: [список_доверенных_ЦС]}
        self.certificates = {}  # Сертификаты пользователей: {имя: Certificate}
        
        # Создаем корневой ЦС
        root_ca = CertificationAuthority("RootCA")
        self.cas["RootCA"] = root_ca
        self.trust_graph["RootCA"] = []
        self.trust_graph["RootCA"].append("RootCA")
        print("✓ Создан корневой центр сертификации: RootCA")
    
    def add_ca(self, new_ca_name, signer_ca_name):
        """Добавляет новый ЦС, подписанный существующим"""
        if signer_ca_name not in self.cas:
            print(f"✗ Ошибка: ЦС '{signer_ca_name}' не существует")
            return False
        
        if new_ca_name in self.cas:
            print(f"✗ Ошибка: ЦС '{new_ca_name}' уже существует")
            return False
        
        # Создаем новый ЦС
        new_ca = CertificationAuthority(new_ca_name)
        self.cas[new_ca_name] = new_ca
        
        # Добавляем связь доверия
        if signer_ca_name not in self.trust_graph:
            self.trust_graph[signer_ca_name] = []
        self.trust_graph[signer_ca_name].append(new_ca_name)
        
        if new_ca_name not in self.trust_graph:
            self.trust_graph[new_ca_name] = []
        self.trust_graph[new_ca_name].append(signer_ca_name)
        self.trust_graph[new_ca_name].append(new_ca_name)
        
        print(f"✓ ЦС '{new_ca_name}' создан и подписан '{signer_ca_name}'")
        return True
    
    def issue_certificate(self, user_name, ca_name):
        """Выпускает сертификат для пользователя"""
        if ca_name not in self.cas:
            print(f"✗ Ошибка: ЦС '{ca_name}' не существует")
            return None
        
        # Генерируем ключи для пользователя
        private_key = rsa.generate_private_key(
            public_exponent=65537,
            key_size=2048,
            backend=default_backend()
        )
        public_key = private_key.public_key()
        
        # Создаем данные для подписи
        public_pem = public_key.public_bytes(
            encoding=serialization.Encoding.PEM,
            format=serialization.PublicFormat.SubjectPublicKeyInfo
        ).decode('utf-8')

        data_to_sign = f"{user_name}|{public_pem}"
        
        # Подписываем ЦС
        ca = self.cas[ca_name]
        signature = ca.sign_data(data_to_sign)
        
        # Создаем сертификат
        certificate = Certificate(user_name, public_key, ca_name, signature)
        self.certificates[user_name] = certificate
        
        return private_key, public_key, certificate
    
    def build_trust_chain(self, from_ca, to_ca, visited=None):
        """Строит цепочку доверия от from_ca до to_ca (BFS)"""
        if visited is None:
            visited = set()
        
        if from_ca == to_ca:
            return [from_ca]
        
        if from_ca in visited:
            return None
        
        visited.add(from_ca)
        
        # Поиск в ширину
        queue = [(from_ca, [from_ca])]
        explored = {from_ca}
        
        while queue:
            current, path = queue.pop(0)
            
            if current == to_ca:
                return path
            
            # Проверяем всех, кому доверяет текущий ЦС
            if current in self.trust_graph:
                for neighbor in self.trust_graph[current]:
                    if neighbor not in explored:
                        explored.add(neighbor)
                        queue.append((neighbor, path + [neighbor]))
        
        return None
    
    def verify_certificate(self, cert_file):
        """Проверяет сертификат пользователя"""
        try:
            with open(cert_file, 'r') as f:
                cert_data = json.load(f)
            
            certificate = Certificate.from_dict(cert_data)
            
            print(f"\n=== Проверка сертификата ===")
            print(f"Владелец: {certificate.owner_name}")
            print(f"Выпущен: {certificate.issuer_name}")
            print(f"Дата: {certificate.timestamp}")
            
            # Проверяем, что издатель существует
            if certificate.issuer_name not in self.cas:
                print(f"✗ Издатель '{certificate.issuer_name}' не найден")
                return False
            
            # Проверяем подпись
            issuer_ca = self.cas[certificate.issuer_name]
            data = certificate.get_signed_data()
            
            if not issuer_ca.verify_signature(data, certificate.signature, issuer_ca.public_key):
                print("✗ Подпись сертификата недействительна")
                return False
            
            print("✓ Подпись сертификата действительна")
            
            # Строим цепочку доверия до RootCA
            chain = self.build_trust_chain("RootCA", certificate.issuer_name)
            
            if chain:
                print(f"✓ Цепочка доверия найдена: {' -> '.join(chain)}")
                return True
            else:
                print(f"✗ Цепочка доверия до RootCA не найдена")
                return False
                
        except Exception as e:
            print(f"✗ Ошибка при проверке сертификата: {e}")
            return False
    
    def show_trust_graph(self):
        """Отображает граф доверия"""
        print("\n=== Граф доверия (матрица смежности) ===")
        ca_list = sorted(self.cas.keys())
        
        # Заголовок
        print(f"{'':12}", end="")
        for ca in ca_list:
            print(f"{ca:12}", end="")
        print()
        
        # Строки матрицы
        for ca1 in ca_list:
            print(f"{ca1:12}", end="")
            for ca2 in ca_list:
                if ca2 in self.trust_graph.get(ca1, []):
                    print(f"{'1':12}", end="")
                else:
                    print(f"{'0':12}", end="")
            print()


class HierarchicalPKI:
    """Иерархическая PKI - дерево доверия"""
    
    def __init__(self):
        self.cas = {}  # Словарь ЦС: {имя: CA объект}
        self.hierarchy = {}  # Иерархия: {владелец: родительский_ЦС}
        self.certificates = {}  # Сертификаты пользователей
        
        # Создаем корневой ЦС
        root_ca = CertificationAuthority("RootCA")
        self.cas["RootCA"] = root_ca
        self.hierarchy["RootCA"] = None  # У корневого нет родителя
        print("✓ Создан корневой центр сертификации: RootCA")
    
    def add_ca(self, new_ca_name, parent_ca_name):
        """Добавляет новый ЦС в иерархию"""
        if parent_ca_name not in self.cas:
            print(f"✗ Ошибка: Родительский ЦС '{parent_ca_name}' не существует")
            return False
        
        if new_ca_name in self.cas:
            print(f"✗ Ошибка: ЦС '{new_ca_name}' уже существует")
            return False
        
        # Создаем новый ЦС
        new_ca = CertificationAuthority(new_ca_name)
        self.cas[new_ca_name] = new_ca
        self.hierarchy[new_ca_name] = parent_ca_name
        
        print(f"✓ ЦС '{new_ca_name}' создан под '{parent_ca_name}'")
        return True
    
    def issue_certificate(self, user_name, ca_name):
        """Выпускает сертификат для пользователя"""
        if ca_name not in self.cas:
            print(f"✗ Ошибка: ЦС '{ca_name}' не существует")
            return None
        
        # Генерируем ключи для пользователя
        private_key = rsa.generate_private_key(
            public_exponent=65537,
            key_size=2048,
            backend=default_backend()
        )
        public_key = private_key.public_key()
        
        # Создаем данные для подписи
        public_pem = public_key.public_bytes(
            encoding=serialization.Encoding.PEM,
            format=serialization.PublicFormat.SubjectPublicKeyInfo
        ).decode('utf-8')
        data_to_sign = f"{user_name}|{public_pem}"
        
        # Подписываем ЦС
        ca = self.cas[ca_name]
        signature = ca.sign_data(data_to_sign)
        
        # Создаем сертификат
        certificate = Certificate(user_name, public_key, ca_name, signature)
        self.certificates[user_name] = certificate
        self.hierarchy[user_name] = ca_name  # Добавляем в иерархию
        
        return private_key, public_key, certificate
    
    def build_trust_chain(self, entity_name):
        """Строит цепочку доверия от сущности до корня"""
        chain = []
        current = entity_name
        
        while current is not None:
            chain.append(current)
            current = self.hierarchy.get(current)
            
            # Защита от циклов
            if len(chain) > 100:
                return None
        
        return chain
    
    def verify_certificate(self, cert_file):
        """Проверяет сертификат пользователя"""
        try:
            with open(cert_file, 'r') as f:
                cert_data = json.load(f)
            
            certificate = Certificate.from_dict(cert_data)
            
            print(f"\n=== Проверка сертификата ===")
            print(f"Владелец: {certificate.owner_name}")
            print(f"Выпущен: {certificate.issuer_name}")
            print(f"Дата: {certificate.timestamp}")
            
            # Проверяем, что издатель существует
            if certificate.issuer_name not in self.cas:
                print(f"✗ Издатель '{certificate.issuer_name}' не найден")
                return False
            
            # Проверяем подпись
            issuer_ca = self.cas[certificate.issuer_name]
            data = certificate.get_signed_data()
            
            if not issuer_ca.verify_signature(data, certificate.signature, issuer_ca.public_key):
                print("✗ Подпись сертификата недействительна")
                return False
            
            print("✓ Подпись сертификата действительна")
            
            # Строим цепочку доверия
            chain = self.build_trust_chain(certificate.issuer_name)
            
            if chain and chain[-1] == "RootCA":
                print(f"✓ Цепочка доверия: {' -> '.join(reversed(chain))}")
                return True
            else:
                print(f"✗ Цепочка доверия до RootCA не найдена")
                return False
                
        except Exception as e:
            print(f"✗ Ошибка при проверке сертификата: {e}")
            return False
    
    def show_hierarchy(self):
        """Отображает иерархию"""
        print("\n=== Иерархия доверия ===")
        for entity, parent in sorted(self.hierarchy.items()):
            if parent is None:
                print(f"{entity} (корень)")
            else:
                print(f"{entity} <- {parent}")


def save_certificate(certificate, private_key, filename):
    """Сохраняет сертификат и ключи в файлы"""
    # Сохраняем сертификат
    with open(filename, 'w') as f:
        json.dump(certificate.to_dict(), f, indent=2)
    
    # Сохраняем приватный ключ
    private_pem = private_key.private_bytes(
        encoding=serialization.Encoding.PEM,
        format=serialization.PrivateFormat.PKCS8,
        encryption_algorithm=serialization.NoEncryption()
    )
    
    with open(filename.replace('.cert', '_private.key'), 'wb') as f:
        f.write(private_pem)
    
    # Сохраняем публичный ключ
    public_pem = certificate.public_key.public_bytes(
        encoding=serialization.Encoding.PEM,
        format=serialization.PublicFormat.SubjectPublicKeyInfo
    )
    
    with open(filename.replace('.cert', '_public.key'), 'wb') as f:
        f.write(public_pem)


def main():
    print("=" * 60)
    print("   СИСТЕМА УПРАВЛЕНИЯ PKI")
    print("=" * 60)
    
    # Выбор режима
    print("\nВыберите режим работы:")
    print("1. Сетевая PKI (Mesh)")
    print("2. Иерархическая PKI")
    
    while True:
        mode = input("\nВведите номер режима (1 или 2): ").strip()
        if mode in ['1', '2']:
            break
        print("✗ Неверный выбор. Попробуйте снова.")
    
    # Создаем PKI
    if mode == '1':
        pki = NetworkPKI()
        mode_name = "Сетевая PKI"
    else:
        pki = HierarchicalPKI()
        mode_name = "Иерархическая PKI"
    
    print(f"\n✓ Запущен режим: {mode_name}\n")
    
    # Главный цикл
    while True:
        print("\n" + "=" * 60)
        print("МЕНЮ:")
        print("1. Создать новый ЦС")
        print("2. Выпустить сертификат пользователю")
        print("3. Проверить сертификат")
        print("4. Показать структуру доверия")
        print("5. Выход")
        print("=" * 60)
        
        choice = input("\nВыберите действие: ").strip()
        
        if choice == '1':
            # Создание нового ЦС
            new_ca = input("Введите название нового ЦС: ").strip()
            signer_ca = input("Введите название ЦС, который подпишет новый ЦС: ").strip()
            pki.add_ca(new_ca, signer_ca)
            
        elif choice == '2':
            # Выпуск сертификата
            user_name = input("Введите имя пользователя: ").strip()
            ca_name = input("Введите название ЦС, который выпустит сертификат: ").strip()
            
            result = pki.issue_certificate(user_name, ca_name)
            
            if result:
                private_key, public_key, certificate = result
                
                # Сохраняем в файлы
                filename = f"{user_name}_certificate.cert"
                save_certificate(certificate, private_key, filename)
                
                print(f"\n✓ Сертификат успешно создан!")
                print(f"  Сертификат сохранен: {filename}")
                print(f"  Приватный ключ: {filename.replace('.cert', '_private.key')}")
                print(f"  Публичный ключ: {filename.replace('.cert', '_public.key')}")
                
        elif choice == '3':
            # Проверка сертификата
            cert_file = input("Введите путь к файлу сертификата: ").strip()
            pki.verify_certificate(cert_file)
            
        elif choice == '4':
            # Показать структуру
            if mode == '1':
                pki.show_trust_graph()
            else:
                pki.show_hierarchy()
                
        elif choice == '5':
            print("\n✓ Завершение работы программы.")
            break
            
        else:
            print("✗ Неверный выбор. Попробуйте снова.")


if __name__ == "__main__":
    main()
