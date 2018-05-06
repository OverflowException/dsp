#!/usr/bin/python
###########################
#Author: liyao
#Python version: 2.7
#Dependency: matplotlib
#Usage: python plot_spectro.py [spectrogram file]
#Functionality: Visualize penalty value's effects on sentence correct rate, sentence correct rate, insertion error, deletion error.
###########################

import sys
import matplotlib.pyplot as plt
import math

if len(sys.argv) != 2:
    print("Usage: python plot_spectro.py [spectrogram file]")
    sys.exit()

try:
    fd = open(sys.argv[1], 'r')
except IOError:
    print("Cannot open " + sys.argv[1])

#Ignore 2 lines of header
for line_idx in range(0, 2):
    fd.readline();

#Read row number and column number

line = fd.readline();
if len(line) == 0:
    sys.exit()

size_info = line.split()
total_row = int(size_info[0])
total_col = int(size_info[1])
print("size = " + str(total_row) + " x " + str(total_col))

spect = []
for line_idx in range(0, total_row):
    line = fd.readline()
    spect.append([])
    for num in line.split():
        #spect[line_idx].append(math.log10(float(num)))
        spect[line_idx].append(float(num))

rot_spect = zip(*spect[::-1])
spect = zip(*rot_spect[::-1])
rot_spect = zip(*spect[::-1])

plt.imshow(rot_spect, cmap='hot', interpolation='nearest')
plt.show()

fd.close()
