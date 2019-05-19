from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import pandas as pd

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

df = pd.read_csv('result.txt')


x = list(df['counting'])
y = list(df['merging'])
z = list(df['best_time'])

ax.scatter(x, y, z)

ax.set_xlabel('Counting threads')
ax.set_ylabel('Merging threads')
ax.set_zlabel('Best time')


plt.show()
fig.savefig('plot.pdf')