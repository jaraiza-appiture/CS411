import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression

DATA_PATH = './outAll.txt'
NET_DATA = {0:{}, 1:{}} # 0 = recv, 1 = send
RECV = 0
SEND = 1
OUT_F = open('results.txt', 'w')

def load_data():
    """
    loads network data collectd
    """
    network_data_file = open(DATA_PATH, 'r')

    for line in network_data_file:
        rank, time, msg_size = line.split(',')

        if not NET_DATA[int(rank)].get(int(msg_size), False):
            NET_DATA[int(rank)][int(msg_size)] = []
        if int(time) < 0:
            continue
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
    
    plt.figure(figsize=(8,6), dpi=100, facecolor='w', edgecolor='k')
    plt.title('Message Size vs. Blocking Recv Times')
    plt.xlabel('message size (bytes)')
    plt.ylabel('recv time (microseconds)')
    plt.errorbar(x_msg_size, y_time_avg, yerr=y_time_stddev, fmt='o-b', ecolor='r')
    plt.savefig('recv_plot.png')
    
    # split
    pre_time_avg = []
    pre_msg_size = []
    post_time_avg = []
    post_msg_size = []
    
    for i, size in enumerate(x_msg_size):
        if size < 256:
            pre_time_avg.append(y_time_avg[i])
            pre_msg_size.append(size)
        else:
            post_time_avg.append(y_time_avg[i])
            post_msg_size.append(size)
    post_msg_size = np.array(post_msg_size).reshape(-1, 1)
    post_time_avg = np.array(post_time_avg).reshape(-1, 1)
    latency = np.average(pre_time_avg)
    reg = LinearRegression().fit(post_msg_size, post_time_avg)
    print('Recv Latency:', latency, 'Recv Linear Regression slope:', reg.coef_, file=OUT_F)

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
    
    plt.figure(figsize=(8,6), dpi=100, facecolor='w', edgecolor='k')
    plt.title('Message Size vs. Blocking Send Times')
    plt.xlabel('message size (bytes)')
    plt.ylabel('send time (microseconds)')
    plt.errorbar(x_msg_size, y_time_avg, yerr=y_time_stddev, fmt='o-b', ecolor='r')
    plt.savefig('send_plt.png')
    
    latency = np.average(y_time_avg)
    print('Send latency:', latency, file=OUT_F)

if __name__ == '__main__':
    load_data()
    send_graph()
    recv_graph()
    OUT_F.close()