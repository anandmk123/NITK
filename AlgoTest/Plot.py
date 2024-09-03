import numpy as np
import matplotlib.pyplot as plt

# Load data from the first file
data1 = np.loadtxt('./Experiments/time 1/DescendQuickPivotFirstTime')
x1 = data1[:, 0]
y1 = data1[:, 1]

# Load data from the second file
data2 = np.loadtxt('./Experiments/time 1/DescendQuickPivotRandomTime')
x2 = data2[:, 0]
y2 = data2[:, 1]

data3 = np.loadtxt('./Experiments/time 3/DescendQuickPivotMedianTime')
x3 = data3[:, 0]
y3 = data3[:, 1]

# Create a plot
plt.figure(figsize=(10, 6))

# Plot the first dataset
# plt.plot(x1, y1, marker='o', linestyle='-', color='g', label='Pivot First')

# Plot the second dataset
plt.plot(x2, y2, marker='x', linestyle='--', color='r', label='Pivot Random')

plt.plot(x3, y3, marker='x', linestyle=':', color='b', label='Pivot Median')


# Add labels and title
plt.xlabel('Number of Inputs(n)')
plt.ylabel('Time in Milli Seconds')
plt.title('Average case running time of QuickSort(Magnified view: Version 2 vs Version 3)')
plt.legend()

#
#Worst case running time of QuickSort(Magnified view: Version 2 vs Version 3)
# Show the plot
plt.grid(True)
plt.show()