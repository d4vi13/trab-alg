import pandas as pd 
import numpy as np
import math
from matplotlib import pyplot as plt

columns = ["ind","temp"]


"""
df = pd.read_csv("merge.csv",usecols=columns)
df1 = pd.read_csv("testsig.csv",usecols=columns)
df2 = pd.read_csv("testl.csv",usecols=columns)
"""
x = np.linspace(1,2**17)
n_log = np.vectorize(math.log)
q = np.vectorize(math.pow)

df = pd.read_csv("dados/compBB.csv",usecols=columns)
df2 = pd.read_csv("dados/compBS.csv",usecols=columns)

#print(df)


plt.figure(figsize=(9,4))
plt.rcParams['font.size'] = '16'
plt.rcParams["axes.formatter.limits"] = [-2,4]

plt.grid()
plt.title("Tempo necessario para achar um elemento")
plt.ylabel("Tempo(s)")
plt.xlabel("Indices")

plt.plot(df.ind,df.temp)
plt.plot(df2.ind,df2.temp)


#plt.plot(x[::-1],pow(x,2))


plt.legend(["busca binaria","busca sequencial"])


plt.show()
