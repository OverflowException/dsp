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

if len(sys.argv) != 3:
    print("Usage: python " + sys.argv[0] + " [sp | ce] spectdata")
    sys.exit()

beg_idx = -1
if sys.argv[1] == "sp":
    beg_idx = 0
elif sys.argv[1] == "ce":
    beg_idx = 1

if beg_idx == -1:
    sys.exit();
    
try:
    fd = open(sys.argv[2], 'r')
except IOError:
    print("Cannot open " + sys.argv[1])

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
    line_eles = line.split();
    for ele_idx in range(beg_idx, len(line_eles)):
        spect[line_idx].append(float(line_eles[ele_idx]))

            
            
rot_spect = zip(*spect[::-1])
spect = zip(*rot_spect[::-1])
rot_spect = zip(*spect[::-1])

plt.imshow(rot_spect, cmap='hot', interpolation='nearest')
plt.show()

fd.close()
