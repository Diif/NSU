# Импорт необходимых библиотек
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# Для моделирования
from sklearn.naive_bayes import CategoricalNB
from sklearn.linear_model import LogisticRegression
from sklearn.preprocessing import OrdinalEncoder
from sklearn.metrics import accuracy_score

# -----------------------------
# 1. Загрузка данных и визуализация распределений
# -----------------------------

# URL датасета "Mushroom" (данные без заголовка)
# data_url = "https://archive.ics.uci.edu/ml/machine-learning-databases/mushroom/agaricus-lepiota.data"
data_url = "./agaricus-lepiota.data"
# Задаём имена столбцов (согласно описанию UCI)
columns = [
    "class", "cap_shape", "cap_surface", "cap_color", "bruises", "odor",
    "gill_attachment", "gill_spacing", "gill_size", "gill_color",
    "stalk_shape", "stalk_root", "stalk_surface_above_ring", "stalk_surface_below_ring",
    "stalk_color_above_ring", "stalk_color_below_ring", "veil_type", "veil_color",
    "ring_number", "ring_type", "spore_print_color", "population", "habitat"
]

# Загружаем данные в DataFrame
df = pd.read_csv(data_url, header=None, names=columns)

# Вычисление распределения категориальных признаков по классам и визуализация
# Для каждого столбца (кроме 'class') будем строить столбчатую диаграмму распределения значений по классам
feature_cols = [col for col in df.columns if col != "class"]

# Количество графиков на одну фигуру
plots_per_fig = 11
n_total = len(feature_cols)  # общее число графиков (22)
n_figures = int(np.ceil(n_total / plots_per_fig))

# Используем прежнее значение для числа столбцов (4)
n_cols = 4

for fig in range(n_figures):
    start = fig * plots_per_fig
    end = min((fig + 1) * plots_per_fig, n_total)
    current_features = feature_cols[start:end]
    n_current = len(current_features)
    n_rows_current = int(np.ceil(n_current / n_cols))
    
    # Создаем новую фигуру для текущего набора графиков
    plt.figure(figsize=(4 * n_cols, 4 * n_rows_current))
    
    for j, col in enumerate(current_features):
        plt.subplot(n_rows_current, n_cols, j + 1)
        # Группировка: сначала по классу, затем value_counts для конкретного столбца
        dist = df.groupby(col)["class"].value_counts().unstack()
        dist.plot(kind="bar", ax=plt.gca())
        plt.title(col)
        plt.xlabel("Фича")
        plt.ylabel("Количество")
    
    plt.tight_layout()
    plt.show()



# -----------------------------
# 2. Построение решающей функции по каждой переменной (на основе частот)
# -----------------------------
# Для каждой категориальной переменной будем предсказывать класс как мажоритарный для данного значения признака.
# Рассчитаем точность такого "одно-переменного" классификатора.

def decision_function_accuracy(data, feature, target="class"):
    # Сначала находим для каждой категории признаки, какой класс встречается чаще
    mapping = data.groupby(feature)[target].agg(lambda x: x.value_counts().idxmax())
    # Делаем предсказание: для каждой строки берем значение признака и подставляем мажоритарный класс
    predictions = data[feature].map(mapping)
    acc = accuracy_score(data[target], predictions)
    return acc, mapping

accuracies = {}
mappings = {}
for col in feature_cols:
    acc, mapping = decision_function_accuracy(df, col)
    accuracies[col] = acc
    mappings[col] = mapping
    print(f"Точность для {col}: {acc:.4f}")

# Нахождение наиболее информативной переменной (с наименьшим числом ошибок)
best_feature = max(accuracies, key=accuracies.get)
print("\nНаиболее информативная переменная:", best_feature)
print("Точность:", accuracies[best_feature])

# -----------------------------
# 3. Наивный байесовский классификатор из sklearn (CategoricalNB)
# -----------------------------
# Для работы CategoricalNB необходимо преобразовать категориальные данные в числовые метки.
encoder = OrdinalEncoder()
X = encoder.fit_transform(df[feature_cols])
y = df["class"]

# Обучаем классификатор
nb_classifier = CategoricalNB()
nb_classifier.fit(X, y)
y_pred = nb_classifier.predict(X)
acc_nb = accuracy_score(y, y_pred)
print("\nТочность CategoricalNB:", acc_nb)

# -----------------------------
# 4. Реализация наивного байесовского классификатора самостоятельно
# -----------------------------

class CustomNaiveBayes:
    def __init__(self, alpha=1.0):
        self.alpha = alpha
        self.classes_ = None
        self.prior_ = {}  # априорные вероятности
        self.feature_probs_ = {}  # условные вероятности: {feature: {class: {feature_value: prob}}}
    
    def fit(self, X, y):
        self.classes_ = np.unique(y)
        n_samples = len(y)
        # Вычисляем априорные вероятности
        for cls in self.classes_:
            self.prior_[cls] = np.sum(y == cls) / n_samples
        
        # Для каждого признака вычисляем условные вероятности
        self.feature_probs_ = {}
        X = pd.DataFrame(X, columns=feature_cols)
        X['class'] = y.values
        for col in feature_cols:
            self.feature_probs_[col] = {}
            # Определим все уникальные категории для признака
            categories = X[col].unique()
            for cls in self.classes_:
                cls_data = X[X['class'] == cls]
                total_count = len(cls_data)
                # Количество категорий в данном признаке
                n_categories = len(categories)
                # Вычисляем вероятности для каждого значения
                value_counts = cls_data[col].value_counts().to_dict()
                probs = {}
                for cat in categories:
                    count = value_counts.get(cat, 0)
                    probs[cat] = (count + self.alpha) / (total_count + self.alpha * n_categories)
                self.feature_probs_[col][cls] = probs
    
    def predict(self, X):
        X = pd.DataFrame(X, columns=feature_cols)
        predictions = []
        for idx, row in X.iterrows():
            class_scores = {}
            for cls in self.classes_:
                # Начинаем с априорной вероятности
                score = np.log(self.prior_[cls])
                # Прибавляем логарифмы условных вероятностей
                for col in feature_cols:
                    value = row[col]
                    prob = self.feature_probs_[col][cls].get(value, self.alpha / (self.alpha * len(self.feature_probs_[col][cls])))
                    score += np.log(prob)
                class_scores[cls] = score
            predictions.append(max(class_scores, key=class_scores.get))
        return np.array(predictions)

# Обучаем собственный классификатор
custom_nb = CustomNaiveBayes(alpha=1.0)
custom_nb.fit(df[feature_cols], df["class"])
y_pred_custom = custom_nb.predict(df[feature_cols])
acc_custom = accuracy_score(df["class"], y_pred_custom)
print("\nТочность собственного Naive Bayes:", acc_custom)
print(y_pred_custom)
# Сравнение с CategoricalNB
print("Разница в точности (CategoricalNB - Custom):", acc_nb - acc_custom)

# -----------------------------
# 5. Логистическая регрессия
# -----------------------------
# Для каждой категориальной переменной вычисляем оценку вероятности принадлежности к классу
# Затем применяем the inverse of the standard logistic function: log(p/(1-p)).
# Для вычисления вероятности применим Additive smoothing.

def compute_logit_encoding(data, feature, target="class", pos_class='e', alpha=1.0):
    # Группируем по значению признака и считаем количество положительных и общее количество
    grp = data.groupby(feature)[target].agg(
        pos=lambda x: np.sum(x == pos_class),
        total=lambda x: len(x)
    ).reset_index()
    # Вычисляем сглажённую вероятность
    grp['p'] = (grp['pos'] + alpha) / (grp['total'] + 2 * alpha)
    # Вычисляем logit
    grp['logit'] = np.log(grp['p'] / (1 - grp['p']))
    return grp[[feature, 'logit']].set_index(feature)

# Для каждого столбца создаём отображение: значение -> logit(prob)
logit_mappings = {}
for col in feature_cols:
    logit_map = compute_logit_encoding(df, col, target="class", pos_class='e', alpha=1.0)
    logit_mappings[col] = logit_map

# Преобразуем исходный DataFrame: заменяем каждое значение признака на соответствующий logit
df_encoded = pd.DataFrame()
for col in feature_cols:
    df_encoded[col] = df[col].map(logit_mappings[col]['logit']).fillna(0)

# Целевая переменная: преобразуем 'e' в 1, 'p' в 0
y_lr = (df["class"] == 'e').astype(int)

# Обучаем логистическую регрессию
lr = LogisticRegression(max_iter=100)
lr.fit(df_encoded, y_lr)
y_pred_lr = lr.predict(df_encoded)
acc_lr = accuracy_score(y_lr, y_pred_lr)
print("\nТочность логистической регрессии:", acc_lr)
