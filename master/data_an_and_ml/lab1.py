import pandas as pd
import numpy as np
from sklearn import datasets
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis, QuadraticDiscriminantAnalysis
from sklearn.linear_model import LogisticRegression
from sklearn.svm import SVC
from sklearn.inspection import DecisionBoundaryDisplay

# 1. Загрузить таблицу Iris из репозитория UCI (можно из любого доступного источника: UCI, sklearn, kaggle). Поместить данные в объект DataFrame библиотеки pandas.
# Вычислить корреляции между признаками на всей таблице и отдельно по классам (использовать pd.groupby).
# Визуализировать распределения классов на всех парах переменных.

iris = datasets.load_iris()
df = pd.DataFrame(iris.data, columns=iris.feature_names)
df['class'] = iris.target

print(df.head())

correlation_all = df.corr(numeric_only=True)
print("Корреляция для всей таблицы:\n", correlation_all)

correlation_by_class = df.groupby('class').corr(numeric_only=True)
print("\nКорреляция по классам:\n", correlation_by_class)

sns.pairplot(df, hue='class')
plt.show()

# 2. Выбрать две переменные. Построить и визуализировать (показать разделяющую кривую) решения методами линейный и квадратичный дискриминант,
# логистическая регрессия, SVM (линейное и квадратичное ядро). Пример подходящей визуализации есть в sklearn.

x = df[['petal length (cm)', 'petal width (cm)']].values
y = df['class'].values

X_train, X_test, y_train, y_test = train_test_split(x, y, test_size=0.3, random_state=11)

scaler = StandardScaler()
X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)

models = {
    'Линейный дискриминант': LinearDiscriminantAnalysis(),
    'Квадратичный дискриминант': QuadraticDiscriminantAnalysis(),
    'Логистическая регрессия': LogisticRegression(max_iter=200),
    'SVM (линейное ядро)': SVC(kernel='linear'),
    'SVM (квадратичное ядро)': SVC(kernel='poly', degree=2)
}


fig, axes = plt.subplots(1, 5, figsize=(20, 4))

def color_rule(x):
    match x:
        case 0:
            return '#FFD6B0'
        case 1:
            return '#FF99CC'
        case 2:
            return '#A0A0A0'
        case _:
            return '#FFFFFF'

for ax, (name, model) in zip(axes, models.items()):
    model.fit(X_train, y_train)
    
    disp = DecisionBoundaryDisplay.from_estimator(
        model, X_train, response_method="predict",
        xlabel='Длина чашелистика (стандартизованная)', 
        ylabel='Ширина чашелистика (стандартизованная)',
        alpha=0.5, ax=ax
    )
    
    scatter = ax.scatter(X_train[:, 0], X_train[:, 1], c=[color_rule(x) for x in y_train], edgecolor='k', s=20)
    ax.set_title(name)

plt.tight_layout()
plt.show()

new_df = df[df['class'] != 0]
sns.pairplot(new_df, hue='class')
plt.show()

x = new_df[iris.feature_names].values
y = new_df['class'].values

X_train, X_test, y_train, y_test = train_test_split(x, y, test_size=0.3, random_state=11)
scaler = StandardScaler()
X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)

#3. Построить линейный дискриминант на всех переменных. Визуализировать ответы алгоритма (выделить, например, цветом)
# на обучающей выборке и классы объектов (выделить, например, формой маркеров) во всех двумерных подпространствах.
lda = LinearDiscriminantAnalysis()
lda.fit(X_train, y_train)

y_pred = lda.predict(X_test)

def plot_lda_predictions(ax, X, y_true, y_pred, feature1, feature2):
    markers = ['o', 's']  # Круг для класса 1, квадрат для класса 2
    for class_label, marker in zip([1, 2], markers):
        # Обучающие точки с предсказаниями (цвет по предсказанию)
        ax.scatter(X[(y_true == class_label) & (y_pred == class_label), feature1],
                   X[(y_true == class_label) & (y_pred == class_label), feature2],
                   marker=marker, label=f'True {class_label} (Correct)', alpha=0.7)
        ax.scatter(X[(y_true == class_label) & (y_pred != class_label), feature1],
                   X[(y_true == class_label) & (y_pred != class_label), feature2],
                   marker=marker, label=f'True {class_label} (Misclassified)', alpha=0.7, edgecolor='red')
    ax.set_xlabel(iris.feature_names[feature1])
    ax.set_ylabel(iris.feature_names[feature2])
    ax.legend()

n_features = 4
fig, axes = plt.subplots(n_features-1, n_features-1, figsize=(15, 15))

pairs = [(i, j) for i in range(n_features) for j in range(i+1, n_features)]

for idx, (i, j) in enumerate(pairs):
    row = idx // (n_features-1)  # Номер строки в сетке
    col = idx % (n_features-1)   # Номер столбца в сетке
    plot_lda_predictions(axes[row, col], X_test, y_test, y_pred, i, j)

for i in range(len(pairs), (n_features-1) * (n_features-1)):
    row = i // (n_features-1)
    col = i % (n_features-1)
    fig.delaxes(axes[row, col])

plt.tight_layout()
plt.show()



#4. На двух переменных из п2 вычислить квадратичную разделяющую функцию непосредственно по оценкам ковариационных матриц и средних 
# (самостоятельно реализовать метод, не используя готовый). Визуализировать её и сравнить с решением из п2.

x = df[['petal length (cm)', 'petal width (cm)']].values
y = df['class'].values
X_train, X_test, y_train, y_test = train_test_split(x, y, test_size=0.3, random_state=11)
scaler = StandardScaler()
X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)

class_labels = [0, 1, 2]
means = {}
covs = {}
for label in class_labels:
    X_class = X_train[y_train == label]
    means[label] = np.mean(X_class, axis=0)
    covs[label] = np.cov(X_class, rowvar=False)

def qda_predict(x, means, covs):
    scores = []
    for label in class_labels:
        mean = means[label]
        cov = covs[label]
        inv_cov = np.linalg.inv(cov)
        diff = x - mean
        score = -0.5 * np.dot(np.dot(diff, inv_cov), diff.T) - 0.5 * np.log(np.linalg.det(cov))
        scores.append(score)
    return class_labels[np.argmax(scores)]

x_min, x_max = X_train[:, 0].min() - 1, X_train[:, 0].max() + 1
y_min, y_max = X_train[:, 1].min() - 1, X_train[:, 1].max() + 1
xx, yy = np.meshgrid(np.arange(x_min, x_max, 0.1), np.arange(y_min, y_max, 0.1))

Z = np.array([qda_predict(np.array([x, y]), means, covs) for x, y in np.c_[xx.ravel(), yy.ravel()]])
Z = Z.reshape(xx.shape)

plt.figure(figsize=(6, 6))
plt.contourf(xx, yy, Z, alpha=0.5, cmap='coolwarm')
plt.scatter(X_train[:, 0], X_train[:, 1], c=y_train, edgecolor='k', s=20)
plt.xlabel('petal length (cm)')
plt.ylabel('petal width (cm)')
plt.title('QDA (Manual)')
plt.show()