import os,re
import matplotlib.pyplot as plt
# dir_path = '/home/samra/Documents/CS411/Project1/nonblocking_files/'

# filename_list = os.listdir(dir_path)
# print filename_list

# with open('result_nb.txt', 'w') as outfile:
#     for fname in filename_list:
#         with open(fname) as infile:
#             for line in infile:
#                 outfile.write(line)

# parsing the result_nb file where all files are appended
nest_dict = {0: {}, 1:{}}
with open('result_nb.txt') as readfile:
        for line in readfile:
            temp_list = list(map(int, re.findall(r"[\w']+", line)))
            senderORrequest = nest_dict.get(temp_list[0])
            if senderORrequest.get(temp_list[2]) == None:
                senderORrequest[temp_list[2]] = [temp_list[1]]
            else:
                senderORrequest.get(temp_list[2]).append(temp_list[1])

## reciever
def receiverPlot():
    num_bytes_list =[]
    avg_time_list=[]
    for num_bytes, time_list in sorted(nest_dict.get(0).items()):
        avg_time = sum(time_list)/len(time_list)
        # make two lists of num_bytes and avg_time simaltaneously
        num_bytes_list.append(num_bytes)
        avg_time_list.append(avg_time)

    plt.plot(avg_time_list, num_bytes_list)
    plt.savefig('receiverPlot.png')
    plt.close()
 ## sender
def senderPlot():
    num_bytes_list =[]
    avg_time_list=[]
    for num_bytes, time_list in sorted(nest_dict.get(1).items()):
        avg_time = sum(time_list)/len(time_list)
        num_bytes_list.append(num_bytes)
        avg_time_list.append(avg_time)
    plt.plot(avg_time_list, num_bytes_list)
    plt.savefig('senderPlot.png')
    plt.close()



receiverPlot()
senderPlot()