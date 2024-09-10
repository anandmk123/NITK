import numpy as np
import matplotlib.pyplot as plt

# Load data from the first file
data1 = np.loadtxt('./time/DescendBubbleTime')
x1 = data1[:, 0]
y1 = data1[:, 1]

# Load data from the second file
data2 = np.loadtxt('./time/DescendInsertionTime')
x2 = data2[:, 0]
y2 = data2[:, 1]

data3 = np.loadtxt('./time/RandomMergeTime')
x3 = data3[:, 0]
y3 = data3[:, 1]

data4 = np.loadtxt('./time/RandomQuickPivotMedianTime')
x4 = data4[:, 0]
y4 = data4[:, 1]

data5 = np.loadtxt('./time/RandomHeapTime')
x5 = data5[:, 0]
y5 = data5[:, 1]

data6 = np.loadtxt('./time/SortedRadixTime')
x6 = data6[:, 0]
y6 = data6[:, 1]

# Create a plot
plt.figure(figsize=(10, 6))

# Plot the first dataset
# plt.plot(x1, y1, marker='o', linestyle='-', color='g', label='Bubble Sort')

# Plot the second dataset
# plt.plot(x2, y2, marker='x', linestyle='--', color='r', label='Insertion Sort')

plt.plot(x3, y3, marker='x', linestyle=':', color='b', label='Merge Sort')

plt.plot(x4, y4, marker='x', linestyle=':', color='orange', label='Quick Sort Pivot-Median')

plt.plot(x5, y5, marker='x', linestyle=':', color='m', label='Heap Sort')

plt.plot(x6, y6, marker='x', linestyle=':', color='black', label='Radix Sort')


# Add labels and title
plt.xlabel('Number of Inputs(n)')
plt.ylabel('Time in millisecond')
plt.title('Analysis of Number of comparisons for Sorted list in increasing order')
plt.legend()

#
#Best Case Analysis of All Six Sorting Algorithms- Magnified view (Without Bubble Sort)
# Show the plot
plt.grid(True)
plt.show()