import numpy as np
import matplotlib.pyplot as plt

spikes = np.genfromtxt('spikes.txt', delimiter='	')
nbSpikes = np.genfromtxt('nbSpikes.txt', delimiter='	')

time1 = spikes[:,][:,0]
neurons_spiking = spikes[:,][:,1]
time2 = nbSpikes[:,][:,0]
nb_spikes = nbSpikes[:,][:,1]

#plot
fig1 = plt.subplot(2, 1, 1)
plt.scatter(time1, neurons_spiking, s=1, c='b')
fig1.set_title('Neurons that spiked at time t')
fig1.set_ylabel('Neuron ID')
fig1.set_ylim(0, 50)

fig2 = plt.subplot(2, 1, 0, sharex=fig1)
fig2.plot(time2, nb_spikes, c='r')
fig2.set_title('Number of spikes that occured in the network at time t')
fig2.set_xlabel('t (in ms)')
fig2.set_xlim(50, 250)
fig2.set_ylim(0, 200)

plt.savefig('plot.png')
plt.show()
