import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

df = pd.read_csv("result.csv", sep=';')
df['file'] = df['file'].map(lambda x: x[:-3])
df['seed'] = df['file'].map(lambda x: int(x.split('_')[0]))
df['size'] = df['file'].map(lambda x: int(x.split('_')[2]))

print(", ".join(df.columns))

print(df.groupby(['file'])['sa', 'timeSa', 'ls', 'timeLs'].agg(['min', 'max', 'mean', 'std', 'median', 'sum']))
print(df[df['size'] == 100])

# df.boxplot(by='file', column=['sa'], grid=False)
# bplot = sns.boxplot(y='sa', x='file', data=df[df['size'] == 100], width=0.5, palette='colorblind')
# plt.show()
# files = set(df['file'])
# print(files)

# for file in df['file']:
# for row in df[df.file == '11_npp_100.in']:
#     print(row)
