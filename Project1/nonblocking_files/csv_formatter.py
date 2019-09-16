import os
import numpy as np
# filename_list = [f for f in os.listdir('nonblocking_files') if os.path.isfile(f)]
#set to the file extension of "to-be-merged" files
#set to your working directory
dir_path = '/home/samra/Documents/CS411/Project1/nonblocking_files/'
#set to the name of your output file
# results = 'nonblocking_merge.txt'

filename_list = os.listdir(dir_path)
print filename_list

with open('result_nb.txt', 'w') as outfile:
    for fname in filename_list:
        with open(fname) as infile:
            for line in infile:
                outfile.write(line)