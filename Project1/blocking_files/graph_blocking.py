import numpy as np
import matplotlib.pyplot as plt

DATA_PATH = './blocking_files/outALL.txt'
NET_DATA = {0:{}, 1:{}} # 0 = recv, 1 = send
RECV = 0
SEND = 1

def load_data():
    """
    loads network data collectd
    """
    network_data_file = open(DATA_PATH, 'r')

    for line in network_data_file:
        rank, time, msg_size = line.split(',')

        if not NET_DATA[int(rank)].get(int(msg_size), False):
            NET_DATA[int(rank)][int(msg_size)] = []

        NET_DATA[int(rank)][int(msg_size)].append(int(time))

def recv_graph():
    """
    creates recv graph
    """
    x_msg_size = []
    y_time_avg = []
    y_time_stddev = []

    for msg_size, times in NET_DATA[RECV].items():
        x_msg_size.append(msg_size)
        y_time_avg.append(np.average(times))
        y_time_stddev.append(np.std(times))
    plt.title('Blocking Recv Times vs. Message Size')
    plt.xlabel('message size (bytes)')
    plt.ylabel('recv time (microseconds)')
    plt.errorbar(x_msg_size, y_time_avg, yerr=y_time_stddev, fmt='-o')

def send_graph():
    """
    creates send graph
    """
    x_msg_size = []
    y_time_avg = []
    y_time_stddev = []

    for msg_size, times in NET_DATA[SEND].items():
        x_msg_size.append(msg_size)
        y_time_avg.append(np.average(times))
        y_time_stddev.append(np.std(times))
    plt.title('Blocking Send Times vs. Message Size')
    plt.xlabel('message size (bytes)')
    plt.ylabel('send time (microseconds)')
    plt.errorbar(x_msg_size, y_time_avg, yerr=y_time_stddev, fmt='-o')

if __name__ == '__main__':
    load_data()
    send_graph()
    recv_graph()
