import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

from sklearn.model_selection import train_test_split, cross_val_score, StratifiedKFold
from sklearn.metrics import accuracy_score
from sklearn.preprocessing import LabelEncoder

from sklearn.tree import DecisionTreeClassifier, plot_tree
from sklearn.ensemble import GradientBoostingClassifier, RandomForestClassifier

RANDOM_SEED = 111

# 1. Загрузка и предобработка датасета Adult
url = "./adult.data"

# Задаем имена столбцов (согласно описанию датасета)
col_names = [
    'age', 'workclass', 'fnlwgt', 'education', 'education_num', 
    'marital_status', 'occupation', 'relationship', 'race', 'sex', 
    'capital_gain', 'capital_loss', 'hours_per_week', 'native_country', 'income'
]   

data = pd.read_csv(url, header=None, names=col_names, na_values=' ?')
print("Размер датасета до дропа:", data.shape)

# Убираем строки с пропущенными значениями
data.dropna(inplace=True)
print("Размер датасета после дропа:", data.shape)

# Преобразуем целевую переменную: '<=50K' -> 0, '>50K' -> 1
data['income'] = data['income'].apply(lambda x: 1 if x.strip() == '>50K' else 0)

# кодируем категориальные признаки (LabelEncoder для каждого)
cat_cols = data.select_dtypes(include=['object']).columns.tolist()
for col in cat_cols:
    le = LabelEncoder()
    data[col] = le.fit_transform(data[col].astype(str))
    # if (col == 'relationship'):
    #     print(le.classes_)

# Выбираем признаки и цель
features = data.drop('income', axis=1)
target = data['income']

X_train = features
y_train = target

# 1. Построить и визуализировать дерево решений (одиночное дерево)
tree_clf = DecisionTreeClassifier(max_depth=4, random_state=RANDOM_SEED)
tree_clf.fit(X_train, y_train)
plt.figure(figsize=(30, 20))
plot_tree(tree_clf,
          feature_names=X_train.columns,
          class_names=['<=50K', '>50K'],
          filled=True,
          rounded=True)

plt.show()

# 2. Градиентный бустинг: обучение, оценка значимости признаков, список построенных деревьев
gb_clf = GradientBoostingClassifier(n_estimators=100, max_depth=3,learning_rate=0.1, random_state=RANDOM_SEED)
gb_clf.fit(X_train, y_train)

# Вычисляем значимость признаков
feat_importance = pd.Series(gb_clf.feature_importances_, index=X_train.columns)
feat_importance.sort_values(ascending=False, inplace=True)

plt.figure(figsize=(10,6))
feat_importance.plot(kind='bar')
plt.title("Feature Importance - Gradient Boosting")
plt.ylabel("Importance")
plt.show()

for idx, estimator in enumerate(gb_clf.estimators_):
    print(f"Дерево {idx+1}: {estimator[0]}")

# 3. Зависимость качества решения (обучение и CV) от числа вершин для одиночного дерева.
depth_values = range(3,11)
results = []
N_SPLITS = 5
cv = StratifiedKFold(n_splits=N_SPLITS, shuffle=True, random_state=RANDOM_SEED)
for depth in depth_values:
    clf = DecisionTreeClassifier(max_depth=depth, random_state=RANDOM_SEED)
    clf.fit(X_train, y_train)
    train_acc = clf.score(X_train, y_train)
    cv_scores = cross_val_score(clf, X_train, y_train, cv=cv)
    cv_acc = np.min(cv_scores)
    results.append({'max_depth': depth, 'train_acc': train_acc, 'cv_acc': cv_acc})
    
results_df = pd.DataFrame(results)
print(results_df)

# Построим график зависимости точности от числа узлов (при разных глубинах)
plt.figure(figsize=(8,6))
plt.plot(results_df['max_depth'], results_df['train_acc'], label=f"Depth {depth} - Train")
plt.plot(results_df['max_depth'], results_df['cv_acc'], label=f"Depth {depth} - CV")
plt.xlabel("depth")
plt.ylabel("Accuracy")
plt.title("Accuracy vs. depth in Decision Tree")
plt.legend()
plt.show()

#4. Зависимость качества (обучение и CV) от числа деревьев для градиентного бустинга.
n_estimators_range = np.arange(20, 201, 20)  # от 10 до 200 деревьев

plt.figure(figsize=(12,8))

for d in depth_values:
    train_scores = []
    cv_scores = []
    gbm = GradientBoostingClassifier(n_estimators=max(n_estimators_range), max_depth=d, random_state=RANDOM_SEED)
    gbm.fit(X_train, y_train)
    predicted = np.array(list(gbm.staged_predict_proba(X_train)))

    for n_est in n_estimators_range:
        y_train_pred = (predicted[n_est-1][:,1] > 0.5).astype(int)
        train_scores.append(accuracy_score(y_train, y_train_pred))
# смотрим с помощью кросс-валидации 
    cur_split = 0
    cv_acc = np.zeros((len(n_estimators_range), N_SPLITS), dtype=np.float32)
    for train_index, val_index in cv.split(X_train, y_train):
        cv_train_x, cv_train_y = X_train.iloc[train_index], y_train.iloc[train_index]
        cv_test_x, cv_test_y = X_train.iloc[val_index], y_train.iloc[val_index]
        gbm.fit(cv_train_x, cv_train_y)
        predicted = np.array(list(gbm.staged_predict_proba(cv_test_x)))

        i = 0
        for n_est in n_estimators_range:
            y_train_pred = (predicted[n_est-1][:,1] > 0.5).astype(int)
            cv_acc[i][cur_split] = accuracy_score(cv_test_y, y_train_pred)
            i = i + 1

        cur_split = cur_split + 1

    i = 0
    for n_est in n_estimators_range:
        cv_scores.append(np.min(cv_acc[i]))
        i = i + 1

    plt.plot(n_estimators_range, train_scores, label=f"Depth {d} - Train")
    plt.plot(n_estimators_range, cv_scores, label=f"Depth {d} - CV", linestyle="--")

plt.xlabel("Number of Trees")
plt.ylabel("Accuracy")
plt.title("Gradient Boosting: Accuracy vs. Number of Trees for different Tree Depths")
plt.legend()
plt.show()

# 5. Аналогичный анализ для случайного леса.
# Будем варьировать число деревьев, а также сравним оценку out-of-bag (OOB) с результатом кросс-валидации.

plt.figure(figsize=(12,8))
for d in depth_values:
    rf_train_scores = []
    rf_cv_scores = []
    rf_oob_scores = []
    for n_est in n_estimators_range:
        rf = RandomForestClassifier(n_estimators=n_est, max_depth=d, oob_score=True, random_state=RANDOM_SEED, n_jobs=-1)
        rf.fit(X_train, y_train)
        rf_train_scores.append(rf.score(X_train, y_train))
        rf_cv_scores.append(np.mean(cross_val_score(rf, X_train, y_train, cv=cv)))
        rf_oob_scores.append(rf.oob_score_)

    plt.plot(n_estimators_range, rf_train_scores, label=f"Depth {d} - Train")
    plt.plot(n_estimators_range, rf_cv_scores, label=f"Depth {d} - CV", linestyle="--")
    plt.plot(n_estimators_range, rf_oob_scores, label=f"Depth {d} - OOB", linestyle=":")

plt.xlabel("Number of Trees")
plt.ylabel("Accuracy")
plt.title("Random forest: Accuracy vs. Number of Trees for different Tree Depths")
plt.legend()
plt.show()
