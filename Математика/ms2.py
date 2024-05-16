import numpy as np
import scipy.stats as st
import pandas as pd
import statsmodels.api as sm
import statsmodels.formula.api as smf
import seaborn as sns
import matplotlib.pyplot as plt

df = pd.read_excel("мат2.xlsx")

print(np.corrcoef([df.y, df.x1, df.x2, df.x3, df.x4]))  #матрица корреляций


# через scipy (даёт значение коэффициента корреляции и p-значение)
print(st.pearsonr(df.x1, df.y))
print(st.spearmanr(df.x1, df.y))
print(st.kendalltau(df.x1, df.y), '\n')
print(st.pearsonr(df.x2, df.y))
print(st.spearmanr(df.x2, df.y))
print(st.kendalltau(df.x2, df.y), '\n')
print(st.pearsonr(df.x3, df.y))
print(st.spearmanr(df.x3, df.y))
print(st.kendalltau(df.x3, df.y), '\n')


print(df.corr())      # парный линейный коэффициент корреляции Пирсона в виде матрицы
print(df.corr(method='spearman'))          # коэффициент корреляции Спирмена в виде матрицы
print(df.corr(method='kendall'))   # коэффициент корреляции Кендала в виде матрицы

sns.pairplot(data=df, kind = 'reg')    # графическое представление парной регрессии ЗП и НП, гистограммы каж-дого признака
plt.show()

# График парной линейной корреляции
sns.set(style='whitegrid', rc={'figure.figsize' : (10,5)}) 
sns.regplot(x = 'x1', y = 'y', data = df)
plt.title('Поле корреляции (облако)')
plt.xlabel('Ось х1')
plt.ylabel('Ось у')
plt.show()

# Уравнение множественной линейной регрессии через формулу
results = smf.ols('y ~ x1 + x2 + x3', data= df).fit()
print(results.summary())

