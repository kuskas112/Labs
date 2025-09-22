import pandas as pd
import matplotlib as mpl
import matplotlib.pyplot as plt
import seaborn as sns
from scipy.stats import norm

data = pd.read_csv('''C:\\Users\\ivan\\Desktop\\Лекции\\Labs\\Машинное обучение\\dataset.csv''')

print('Посчитайте количество пропусков в каждом из столбцов.')
total_nans = data.isna().sum().sum()
print(total_nans)

print('Замените все пропуски дискретных признаков соответствующими медианами, непрерывных признаков - средними значениями.')
categorial_cols = [
    'Pregnancies',
    'Glucose',
    'BloodPressure',
    'SkinThickness',
    'Insulin',
    'Age'
]
numerical_cols = [
    'BMI',
    'DiabetesPedigreeFunction'
]
for col in categorial_cols:
    median = data[col].dropna().median()
    data[col] = data[col].fillna(median)

for col in numerical_cols:
    avg = data[col].dropna().mean()
    data[col] = data[col].fillna(avg)


print('Вычислите основные статистики (минимум, максимум, среднее, дисперсию, квантили) для всех столбцов.')
all_columns = [
    'Pregnancies',
    'Glucose',
    'BloodPressure',
    'SkinThickness',
    'Insulin',
    'Age',
    'BMI',
    'DiabetesPedigreeFunction',
    'Class'
]
for col in all_columns:
    minimum = data[col]
    maxium = data[col].max()
    mean = data[col].mean()
    disp = data[col].var()
    quant1 = data[col].quantile(0.25)
    quant2 = data[col].quantile(0.5)
    quant3 = data[col].quantile(0.75)
    print(f'col: {col}, min: , max: {maxium}, mean:{mean}, var: {disp},\n q1: {quant1}, q2: {quant2}, q3: {quant3}')

print('У скольких женщин старше 50 лет обнаружен диабет?')
condition = (data['Class'] == 1) & (data['Age'] > 50)
count = condition.sum()
print(count) 

print('Найдите трех женщин с наибольшим числом беременностей.')
top_values = data.nlargest(3, columns='Pregnancies')
print(top_values)

print('Сколько женщин возраста между 30 и 40 успело родить 3 или более детей?')
condition = (data['Age'] > 30) & (data['Age'] < 40) & (data['Pregnancies'] >= 3)
print(condition.sum())

print('Нормальным кровяным давлением будем считать давление в диапазоне [80-89]. У какого процента женщин давление нормальное?')
condition = (data['BloodPressure'] >= 80) & (data['BloodPressure'] <= 89)
normal_pressure_count = condition.sum()
total_count = data.shape[0]
print(f'Percentage: {normal_pressure_count / total_count * 100} %')

print('Считается, что BMI >= 30 - это признак ожирения. У скольких женщин с признаками ожирения кровяное давление выше среднего?')
mean_pressure = data['BloodPressure'].mean()
condition = (data['BloodPressure'] > mean_pressure) & (data['BMI'] >= 30)
print(condition.sum())

print('Сравните средние значения для признаков Glucose,	BloodPressure, Insulin среди тех, у кого обнаружен диабет, и тех, у кого его нет. ')
no_deb = data[data['Class'] == 0]
deb = data[data['Class'] == 1]

print(f'         Больные | Здоровые')
print(f'Глюкоза: {deb["Glucose"].mean()}, {no_deb["Glucose"].mean()}')
print(f'Давление: {deb["BloodPressure"].mean()}, {no_deb["BloodPressure"].mean()}')
print(f'Инсулин: {deb["Insulin"].mean()}, {no_deb["Insulin"].mean()}')

print('Постройте гистограммы для любых двух количественных признаков.')
gist1 = data['Insulin']
plt.hist(gist1, bins=30)
plt.title('Инсулин')
#plt.show()

gist2 = data['BloodPressure']
plt.hist(gist2, bins=50)
plt.title('Кровяное давлени')
#plt.show()

print('Постройте круговую диаграмму для признака __Class__.')
freq = data['Class'].value_counts()
plt.pie(freq, labels=freq.index, autopct='%1.1f%%')
plt.title('Больные диабетом')
#plt.show()

import random
print('Постройте распределения для признаков __Age__ и __BloodPressure__ и сравните оба распределения с нормальным.')
ageSort = data.sort_values(by='Age')
freqsAge = ageSort['Age'].value_counts().sort_index()
unique_values = freqsAge.index
freqs = freqsAge.values



print(ageSort)
# minAge = ageSort.min()
# maxAge = ageSort.max()
# normalAge = []
# for i in range(100):
#     normalAge.append(random.randint(minAge, maxAge))
# normalAge = sorted(normalAge)
plt.close()
plt.hist(ageSort, color='pink', edgecolor='black', bins=50)
#plt.hist(normalAge, color='black', edgecolor='black')
plt.show()

