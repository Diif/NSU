# lab_house_prices.py

import pandas as pd
import numpy as np
from sklearn.ensemble import GradientBoostingClassifier
from sklearn.model_selection import train_test_split, GridSearchCV
from sklearn.linear_model import LinearRegression
from sklearn.model_selection import KFold
from sklearn.preprocessing import StandardScaler
from sklearn.ensemble import GradientBoostingRegressor
from sklearn.metrics import mean_squared_error, r2_score
from sklearn.preprocessing import OneHotEncoder
from sklearn.impute import SimpleImputer
from sklearn.decomposition import PCA
import matplotlib.pyplot as plt

rand_seed = 111
threshold = 0.4

# House Prices - Advanced Regression Techniques
df = pd.read_csv('train.csv')

df['MasVnrType'] = df['MasVnrType'].fillna('NoMas')
median_lot_frontage = df['LotFrontage'].median()
df['LotFrontage'] = df['LotFrontage'].fillna(median_lot_frontage)

# Считаем долю пропусков в каждом столбце
missing_frac = df.isnull().mean()

# Отбираем столбцы, доля пропусков в которых не превышает 50%
good_columns = missing_frac[missing_frac <= threshold].index

# Оставляем только эти столбцы
df_clean = df[good_columns]

# Теряем где-то 100 строк из 1400
df_clean = df_clean.dropna()
df_clean = df_clean.drop(columns = ['Id'])

# привело к ухудшению модели
# df_clean['SalePrice'] = np.log1p(df_clean['SalePrice'])

# ====== 2 Linear Regression on numerical features only ======
df_numerical = df_clean.select_dtypes(include=[np.number])
X_num = df_numerical.drop(columns=['SalePrice'])
y = df_numerical['SalePrice']

cv = KFold(n_splits=5, shuffle=True, random_state=rand_seed)

rmse_lr_list = []
rmse_gb_list = []

# param_grid = {
#     'n_estimators': [2000, 3000, 4000, 5000],
#     'max_depth': [1, 3, 5],
#     'learning_rate': [0.05, 0.02, 0.01]
# }
# gbr = GridSearchCV(GradientBoostingRegressor(random_state=rand_seed),
#                    param_grid, cv=cv, scoring='neg_mean_squared_error', n_jobs=-1)
# gbr.fit(X_num, y)
# best_gbr = gbr.best_estimator_
# y_pred_gb = best_gbr.predict(X_test)
# print("Best params:", gbr.best_params_)
# Best params: {'learning_rate': 0.02, 'max_depth': 3, 'n_estimators': 4000}

gbr = GradientBoostingRegressor(random_state=rand_seed, learning_rate= 0.02, max_depth = 3, n_estimators = 4000)
for fold, (train_idx, test_idx) in enumerate(cv.split(X_num), 1):
    X_tr, X_te = X_num.iloc[train_idx], X_num.iloc[test_idx]
    y_tr, y_te = y.iloc[train_idx],    y.iloc[test_idx]

    lr = LinearRegression().fit(X_tr, y_tr)
    gbr.fit(X_tr, y_tr);

    y_pred_lr = lr.predict(X_te)
    y_pred_gbm = gbr.predict(X_te)

    # rmse_lr = np.sqrt(mean_squared_error(np.expm1(y_te), np.expm1(y_pred_lr)))
    rmse_lr = np.sqrt(mean_squared_error((y_te), (y_pred_lr)))
    rmse_gb = np.sqrt(mean_squared_error((y_te), (y_pred_gbm)))
    rmse_lr_list.append(rmse_lr)
    rmse_gb_list.append(rmse_gb)
    print(f"added mean RMSE: {rmse_gb:.4f}")

print(f"LR mean RMSE: {np.mean(rmse_lr_list):.4f}")
print(f"GB mean RMSE: {np.mean(rmse_gb_list):.4f}")
# LR mean RMSE: 38293.9021
# GB mean RMSE: 27622.3006

cat_cols = df_clean.select_dtypes(include=['object']).columns

# ====== PART 3: Encoding categorical features ======
df_ohe = pd.get_dummies(df_clean, columns=cat_cols, drop_first=True)

X_num = df_ohe.drop(columns=['SalePrice'])

rmse_lr_list = []
rmse_gb_list = []
gbr = GradientBoostingRegressor(random_state=rand_seed, learning_rate= 0.02, max_depth = 3, n_estimators = 4000)
for fold, (train_idx, test_idx) in enumerate(cv.split(X_num), 1):
    X_tr, X_te = X_num.iloc[train_idx], X_num.iloc[test_idx]
    y_tr, y_te = y.iloc[train_idx],    y.iloc[test_idx]

    lr = LinearRegression().fit(X_tr, y_tr)
    gbr.fit(X_tr, y_tr);

    y_pred_lr = lr.predict(X_te)
    y_pred_gbm = gbr.predict(X_te)

    # rmse_lr = np.sqrt(mean_squared_error(np.expm1(y_te), np.expm1(y_pred_lr)))
    rmse_lr = np.sqrt(mean_squared_error((y_te), (y_pred_lr)))
    rmse_gb = np.sqrt(mean_squared_error((y_te), (y_pred_gbm)))
    rmse_lr_list.append(rmse_lr)
    rmse_gb_list.append(rmse_gb)
    print(f"added mean RMSE: {rmse_gb:.4f}")

print(f"LR mean RMSE: {np.mean(rmse_lr_list):.4f}")
print(f"GB mean RMSE: {np.mean(rmse_gb_list):.4f}")
# LR mean RMSE: 43848.4713
# GB mean RMSE: 26027.8603 

# --- Target Encoding ---
df_te = df_clean.copy()
for col in cat_cols:
    means = df_te.groupby(col)['SalePrice'].mean()
    df_te[col + '_te'] = df_te[col].map(means)

df_te = df_te.drop(columns=cat_cols)
X_num = df_te.drop(columns=['SalePrice'])

rmse_lr_list = []
rmse_gb_list = []
gbr = GradientBoostingRegressor(random_state=rand_seed, learning_rate= 0.02, max_depth = 3, n_estimators = 4000)
for fold, (train_idx, test_idx) in enumerate(cv.split(X_num), 1):
    X_tr, X_te = X_num.iloc[train_idx], X_num.iloc[test_idx]
    y_tr, y_te = y.iloc[train_idx],    y.iloc[test_idx]

    lr = LinearRegression().fit(X_tr, y_tr)
    gbr.fit(X_tr, y_tr);

    y_pred_lr = lr.predict(X_te)
    y_pred_gbm = gbr.predict(X_te)

    # rmse_lr = np.sqrt(mean_squared_error(np.expm1(y_te), np.expm1(y_pred_lr)))
    rmse_lr = np.sqrt(mean_squared_error((y_te), (y_pred_lr)))
    rmse_gb = np.sqrt(mean_squared_error((y_te), (y_pred_gbm)))
    rmse_lr_list.append(rmse_lr)
    rmse_gb_list.append(rmse_gb)
    print(f"added mean RMSE: {rmse_gb:.4f}")

print(f"LR mean RMSE: {np.mean(rmse_lr_list):.4f}")
print(f"GB mean RMSE: {np.mean(rmse_gb_list):.4f}")
# LR mean RMSE: 34679.9350
# GB mean RMSE: 24945.0610

# # ====== PART 4: PCA Visualization ======
scaler = StandardScaler()
X_scaled_num = scaler.fit_transform(X_num)

X_num = pd.DataFrame(
    X_scaled_num,
    index=X_num.index,
    columns=X_num.columns
)

# pca = PCA(n_components=2)
# pcs = pca.fit_transform(X_num)

# print("Доля объяснённой дисперсии (PC1, PC2):", pca.explained_variance_ratio_[:2])

# plt.figure(figsize=(8,6))
# sc = plt.scatter(pcs[:,0], pcs[:,1],
#                  c=y,
#                  cmap='viridis',
#                  s=20, alpha=0.7)
# plt.colorbar(sc, label='SalePrice')
# plt.xlabel('PC1')
# plt.ylabel('PC2')
# plt.title('Проекция на первые две главные компоненты')
# plt.grid(True)
# plt.show()

from mpl_toolkits.mplot3d import Axes3D

# 1. PCA с тремя компонентами
pca = PCA(n_components=3)
pcs = pca.fit_transform(X_num)

print("Доля объяснённой дисперсии (PC1, PC2, PC3):", pca.explained_variance_ratio_[:3])

# 3. Визуализация в 3D
fig = plt.figure(figsize=(10,8))
ax = fig.add_subplot(111, projection='3d')

sc = ax.scatter(pcs[:, 0], pcs[:, 1], pcs[:, 2],
                c=y, cmap='viridis', s=20, alpha=0.7)

ax.set_xlabel('PC1')
ax.set_ylabel('PC2')
ax.set_zlabel('PC3')
ax.set_title('3D проекция на первые три главные компоненты')

fig.colorbar(sc, ax=ax, label='SalePrice')
plt.show()