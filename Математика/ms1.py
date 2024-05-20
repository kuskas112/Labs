import pandas as pd
import numpy as np
import scipy as ss
import scipy.stats
import seaborn as sns
import matplotlib.pyplot as plt
import pylab as py
from scipy.stats import chi2_contingency as chi
from scipy.stats import chisquare

data = pd.read_excel('C:\\Users\\Ольга\\Desktop\\Лекции\\2 курс\\2 семак\\Labs\\Математика\\мат.xlsx')

print("Основные характеристики:")
print(data.d_30.describe())
print("\n")

print("Мода:")
print(data.d_30.mode())
print("\n")

print("Медиана:")
print(data.d_30.median())
print("\n")

print("Размах")
print(np.percentile(data.d_30, [0, 100]))
print("\n")

print("Дисперсия:")
print(data.d_30.var())
print("\n")

print("Стандартная ошибка среднего:")
print(data.d_30.sem())
print("\n")

print("Доверительный интервал:")
print(
    ss.stats.t.interval(0.95, len(data.d_30) - 1,
                        loc=np.mean(data.d_30),
                        scale=ss.stats.sem(data.d_30)))
print("\n")

# Боксплот
plt.figure(figsize=(2, 16))
sns.boxplot(data.d_30)
plt.show()

# Гистограмма
AxesSubplot: 'Frequency'
plt.figure(figsize=(16, 6))
data.d_30.plot(kind="hist", bins=11, fontsize=8)
plt.show()

# QQ-plot
ss.stats.t.interval(0.95, len(data.d_30) - 1,
                    loc=np.mean(data.d_30),
                    scale=ss.stats.sem(data.d_30))
ss.stats.probplot(data.d_30, dist="norm", plot=py)
py.show()

#Полигон частот
n, bins, _ = plt.hist(data.d_30, bins=10, alpha=0, edgecolor='none')
tops = n
plt.fill_between(bins[:-1], tops, alpha=0.4, color='skyblue', step='mid')
plt.xlabel('Значения')
plt.ylabel('Частота')
plt.title('Полигон Частот')
plt.show()


n = len(data.d_30)
sr = sum(data.d_30)/len(data.d_30)
K = 10
h = (max(data.d_30) - min(data.d_30))/K
a = 0.1
minValue = min(data.d_30)

#a = scipy.stats.expon.cdf(x=5, scale=sr) - scipy.stats.expon.cdf(x=0, scale=sr)

class Interval:
    def __init__(self, left, right):
        self.left = left
        self.right = right
        self.freq = 0
        self.P = 0
    def __str__(self):
        return f"[{self.left}; {self.right}], freq = {self.freq}, P = {self.P}"

intervals=[Interval(minValue + h*x, minValue + h*(x+1)) for x in range(K)]
freqDict = {}
for val in sorted(data.d_30):
    if str(val) not in freqDict:
        freqDict[str(val)] = 0
    freqDict[str(val)] += 1

for val in freqDict:
    value = int(val)
    for i in range(len(intervals)):
        if intervals[i].left <= value <= intervals[i].right:
            intervals[i].freq += freqDict[val]

for interval in intervals:
    interval.P = scipy.stats.expon.cdf(x=interval.right, scale=sr) - scipy.stats.expon.cdf(x=interval.left, scale=sr)

print("Группированный статический ряд")
[print(x) for x in intervals]
print("\n")

while intervals[-1].freq < 5:
    intervals[-2].right = intervals[-1].right
    intervals[-2].freq += intervals[-1].freq
    intervals[-2].P += intervals[-1].P
    intervals.pop(-1)

Chi2 = sum([(x.freq - x.P*n)**2/(x.P*n) for x in intervals])
print("Хи квадрат наблюдаемое: ", Chi2, '\n')


chiFact = scipy.stats.chi2.ppf(q=1-a, df=len(intervals)-1-1)
print("Хи квадрат критическое: ", chiFact, '\n')

pValue = scipy.stats.chi2.sf(x=Chi2, df=len(intervals)-1-1)
print("p-value: ", pValue, '\n')
print("Уровень значимости: ", a, '\n')

