from matplotlib import pyplot as plt
import numpy as np
RESULTS = './results_runtime.csv'
RESULTS_K = './results_parametric_k.csv'
RESULTS_D = './results_parametric_d.csv'
RUNTIME = 2

# graph sizes
# Google: nodes=875,713 edges=5,105,039
# BernStan: nodes=685,230 edges=7,600,595
# NotreDame: nodes=325,729 edges=1,497,134
# Facebook: nodes=? edges=?

def load_data(filename):
    in_file = open(filename, 'r')
    data = {}
    for line in in_file:
        #csv format: threads,damping,k,runtime,filename
        threads, damping, k, runtime, graphfile = line.split(',')

        if not data.get(graphfile, False):
            data[graphfile] = {}
        if not data[graphfile].get(int(threads), False):
            data[graphfile][int(threads)] = []
        data[graphfile][int(threads)].append((int(k), float(damping), float(runtime)))
    in_file.close()

    return data

def speed_up(serial_time, parallel_time):
    return serial_time / parallel_time

def efficiency(speedUp, procs):
    return speedUp / procs

def make_graphs_d(data):
    x_axis_line = [0.1, 0.3, 0.5, 0.7, 0.9] #d

    # Runtime Pagerank
    lines_parallel_time = {}
    for graph, procs_dict in sorted(data.items()):
        lines_parallel_time[graph] = []
        for time_tuple in procs_dict[8]:
            lines_parallel_time[graph].append(time_tuple[RUNTIME])

    # plot runtime time graph
    plt.figure(figsize=(8,6), dpi=100, facecolor='w', edgecolor='k')
    for graph, line in lines_parallel_time.items():
        plt.plot(x_axis_line, line, label=graph+" p=8")
    plt.legend(loc='upper left')
    plt.title("Pagerank Runtime vs D", fontsize=16, fontweight='bold')
    plt.xlabel("D: Damping Ratio")
    plt.ylabel("Runtime (milliseconds)")
    plt.xticks(x_axis_line)
    plt.savefig('./pagerank_parametric_d.png')
    plt.show()

def make_graphs_k(data):
    x_axis_line = [100, 200, 400, 800, 1600, 3200] #k

    # Runtime Pagerank
    lines_parallel_time = {}
    for graph, procs_dict in sorted(data.items()):
        lines_parallel_time[graph] = []
        for time_tuple in procs_dict[8]:
            lines_parallel_time[graph].append(time_tuple[RUNTIME])

    # plot runtime time graph
    plt.figure(figsize=(8,6), dpi=100, facecolor='w', edgecolor='k')
    for graph, line in lines_parallel_time.items():
        plt.plot(x_axis_line, line, label=graph+" p=8")
    plt.legend(loc='upper left')
    plt.title("Pagerank Runtime vs K", fontsize=16, fontweight='bold')
    plt.xlabel("K: Walk Length")
    plt.ylabel("Runtime (milliseconds)")
    plt.xticks(x_axis_line)
    plt.savefig('./pagerank_parametric_k.png')
    plt.show()


def make_graphs_runtime(data):

    x_axis_line = [1, 2, 4, 8]

    # Runtime Pagerank
    lines_parallel_time = {}
    lines_speedup_time = {}
    lines_efficiency_time = {}
    for graph, procs_dict in sorted(data.items()):
        lines_parallel_time[graph] = []
        lines_speedup_time[graph] = []
        lines_efficiency_time[graph] = []
        avg_best_time = np.average([time_tuple[RUNTIME] for time_tuple in data[graph][1]]) # 1 thread
        for num_procs, times in sorted(procs_dict.items()):
            avg_time = np.average([time_tuple[RUNTIME] for time_tuple in times])
            lines_parallel_time[graph].append(avg_time)
            speedup_score = speed_up(avg_best_time, avg_time)
            lines_speedup_time[graph].append(speedup_score)
            efficiency_score = efficiency(speedup_score, num_procs)
            lines_efficiency_time[graph].append(efficiency_score)

    # plot runtime time graph
    plt.figure(figsize=(8,6), dpi=100, facecolor='w', edgecolor='k')
    for graph, line in lines_parallel_time.items():
        plt.plot(x_axis_line, line, label=graph)
    plt.legend(loc='upper right')
    plt.title("Pagerank Runtime", fontsize=16, fontweight='bold')
    plt.xlabel("Number of Threads")
    plt.ylabel("Runtime (milliseconds)")
    plt.xticks(x_axis_line)
    plt.savefig('./pagerank_runtime.png')
    plt.show()

    # plot speed-up graph
    plt.figure(figsize=(8,6), dpi=100, facecolor='w', edgecolor='k')
    for graph, line in lines_speedup_time.items():
        plt.plot(x_axis_line, line, label=graph)
    plt.legend(loc='upper right')
    plt.title("Pagerank Speed Up", fontsize=16, fontweight='bold')
    plt.xlabel("Number of Threads")
    plt.ylabel("Speed Up Factor")
    plt.xticks(x_axis_line)
    plt.savefig('./pagerank_speedup.png')
    plt.show()

    # # plot efficiency graph
    plt.figure(figsize=(8,6), dpi=100, facecolor='w', edgecolor='k')
    for graph, line in lines_efficiency_time.items():
        plt.plot(x_axis_line, line, label=graph)
    plt.legend(loc='upper right')
    plt.title("Pagerank Efficiency", fontsize=16, fontweight='bold')
    plt.xlabel("Number of Threads")
    plt.ylabel("Efficiency (%)")
    plt.xticks(x_axis_line)
    plt.savefig('./pagerank_efficiency.png')
    plt.show()

if __name__ == '__main__':
    # data_runtime = load_data(RESULTS)
    # make_graphs_runtime(data_runtime)
    # data_k = load_data(RESULTS_K)
    # make_graphs_k(data)
    data_d = load_data(RESULTS_D)
    make_graphs_d(data_d)
    
    
# 8,0.1,500,80562.5,BerkStan
# 8,0.3,500,80921.6,BerkStan
# 8,0.5,500,80628.9,BerkStan
# 8,0.7,500,80783.4,BerkStan
# 8,0.9,500,81260.9,BerkStan
# 8,0.1,500,36880.9,NotreDame
# 8,0.3,500,37677.3,NotreDame
# 8,0.5,500,38045.4,NotreDame
# 8,0.7,500,38211.5,NotreDame
# 8,0.9,500,38633.5,NotreDame
# 8,0.1,500,451.664,Facebook
# 8,0.3,500,468.921,Facebook
# 8,0.5,500,474.907,Facebook
# 8,0.7,500,471.658,Facebook
# 8,0.9,500,467.422,Facebook
