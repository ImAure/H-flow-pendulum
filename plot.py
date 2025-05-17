import pylab as pl
import numpy as np

filename = 'prova.txt'

data = np.loadtxt(filename, delimiter = ' ', usecols = [1, 2])
x, y = data[:, 0], data[:, 1]

pl.plot(x, y, linestyle = '-', linewidth = 0.5, color = 'black')

pl.xlabel('q')
pl.ylabel('p')
pl.title('Trajectory in the phase space\nfor a simple pendulum')
pl.grid(True)

pl.show()