from matplotlib import pyplot as plt
import numpy as np
RESULTS = './results.csv'
ALL_REDUCE = 0
NAIVE_REDUCE = 1
MPI_REDUCE = 2
def load_data(filename):
    in_file = open(filename, 'r')
    data = {}
    for line in in_file:
        myreduce_time, mynaive_time, mpireduce_time, procs, elements, op_output = line.split(',')
        if not data.get(int(elements), False):
            data[int(elements)] = {}
        if not data[int(elements)].get(int(procs), False):
            data[int(elements)][int(procs)] = []
        data[int(elements)][int(procs)].append((int(myreduce_time), int(mynaive_time), int(mpireduce_time), int(op_output)))
    in_file.close()
    
    return data

def speed_up(serial_time, parallel_time):
    return serial_time / parallel_time

def efficiency(speedUp, procs):
    return speedUp / procs

def make_graphs(data):
    
    x_axis_line = [1, 2, 4, 8, 16, 32, 64]
    
    # ALL REDUCE
    lines_parallel_time = {}
    lines_speedup_time = {}
    lines_efficiency_time = {}
    for num_elements, procs_dict in sorted(data.items()):
        lines_parallel_time[num_elements] = []
        lines_speedup_time[num_elements] = []
        lines_efficiency_time[num_elements] = []
        avg_best_serial_time = np.average([time_tuple[NAIVE_REDUCE] for time_tuple in data[num_elements][1]]) # 1 proc
        for num_procs, times in sorted(procs_dict.items()):
            avg_allreduce_time = np.average([time_tuple[ALL_REDUCE] for time_tuple in times])
            #avg_mpireduce_time = np.average([time_tuple[MPI_REDUCE] for time_tuple in times])
            lines_parallel_time[num_elements].append(avg_allreduce_time)
            speedup_score = speed_up(avg_best_serial_time, avg_allreduce_time)
            lines_speedup_time[num_elements].append(speedup_score)
            efficiency_score = efficiency(speedup_score, num_procs)
            lines_efficiency_time[num_elements].append(efficiency_score)
    
    # plot parallel time graph
    plt.figure(figsize=(8,6), dpi=100, facecolor='w', edgecolor='k')
    for num_elements, line in lines_parallel_time.items():
        plt.plot(x_axis_line, line, label="n = %d"%(num_elements))
    plt.legend(loc='upper right')
    plt.title("All Reduce Parallel Time", fontsize=16, fontweight='bold')
    plt.xlabel("Number of Processes")
    plt.ylabel("Parallel Time (microseconds)")
    plt.xticks(x_axis_line)
    plt.savefig('./all_reduce_parallel_time.png')
    plt.show()
    
    # plot speed-up graph
    plt.figure(figsize=(8,6), dpi=100, facecolor='w', edgecolor='k')
    for num_elements, line in lines_speedup_time.items():
        plt.plot(x_axis_line, line, label="n = %d"%(num_elements))
    plt.legend(loc='upper right')
    plt.title("All Reduce Speed Up", fontsize=16, fontweight='bold')
    plt.xlabel("Number of Processes")
    plt.ylabel("Speed Up Factor")
    plt.xticks(x_axis_line)
    plt.savefig('./all_reduce_speed_up.png')
    plt.show()
    
    # plot speed-up graph
    plt.figure(figsize=(8,6), dpi=100, facecolor='w', edgecolor='k')
    for num_elements, line in lines_efficiency_time.items():
        plt.plot(x_axis_line, line, label="n = %d"%(num_elements))
    plt.legend(loc='upper right')
    plt.title("All Reduce Efficiency", fontsize=16, fontweight='bold')
    plt.xlabel("Number of Processes")
    plt.ylabel("Efficiency (%)")
    plt.xticks(x_axis_line)
    plt.savefig('./all_reduce_efficiency.png')
    plt.show()
    
    # MPI REDUCE
    lines_parallel_time = {}
    lines_speedup_time = {}
    lines_efficiency_time = {}
    for num_elements, procs_dict in sorted(data.items()):
        lines_parallel_time[num_elements] = []
        lines_speedup_time[num_elements] = []
        lines_efficiency_time[num_elements] = []
        avg_best_serial_time = np.average([time_tuple[NAIVE_REDUCE] for time_tuple in data[num_elements][1]]) # 1 proc
        for num_procs, times in sorted(procs_dict.items()):
            #avg_allreduce_time = np.average([time_tuple[ALL_REDUCE] for time_tuple in times])
            avg_mpireduce_time = np.average([time_tuple[MPI_REDUCE] for time_tuple in times])
            lines_parallel_time[num_elements].append(avg_mpireduce_time)
            speedup_score = speed_up(avg_best_serial_time, avg_mpireduce_time)
            lines_speedup_time[num_elements].append(speedup_score)
            efficiency_score = efficiency(speedup_score, num_procs)
            lines_efficiency_time[num_elements].append(efficiency_score)
    
    # plot parallel time graph
    plt.figure(figsize=(8,6), dpi=100, facecolor='w', edgecolor='k')
    for num_elements, line in lines_parallel_time.items():
        plt.plot(x_axis_line, line, label="n = %d"%(num_elements))
    plt.legend(loc='upper right')
    plt.title("MPI All Reduce Parallel Time", fontsize=16, fontweight='bold')
    plt.xlabel("Number of Processes")
    plt.ylabel("Parallel Time (microseconds)")
    plt.xticks(x_axis_line)
    plt.savefig('./MPI_all_reduce_parallel_time.png')
    plt.show()
    
    # plot speed-up graph
    plt.figure(figsize=(8,6), dpi=100, facecolor='w', edgecolor='k')
    for num_elements, line in lines_speedup_time.items():
        plt.plot(x_axis_line, line, label="n = %d"%(num_elements))
    plt.legend(loc='upper right')
    plt.title("MPI All Reduce Speed Up", fontsize=16, fontweight='bold')
    plt.xlabel("Number of Processes")
    plt.ylabel("Speed Up Factor")
    plt.xticks(x_axis_line)
    plt.savefig('./MPI_all_reduce_speed_up.png')
    plt.show()
    
    # plot speed-up graph
    plt.figure(figsize=(8,6), dpi=100, facecolor='w', edgecolor='k')
    for num_elements, line in lines_efficiency_time.items():
        plt.plot(x_axis_line, line, label="n = %d"%(num_elements))
    plt.legend(loc='upper right')
    plt.title("MPI All Reduce Efficiency", fontsize=16, fontweight='bold')
    plt.xlabel("Number of Processes")
    plt.ylabel("Efficiency (%)")
    plt.xticks(x_axis_line)
    plt.savefig('./MPI_all_reduce_efficiency.png')
    plt.show()
    
    # NAIVE REDUCE
    lines_parallel_time = {}
    lines_speedup_time = {}
    lines_efficiency_time = {}
    for num_elements, procs_dict in sorted(data.items()):
        lines_parallel_time[num_elements] = []
        lines_speedup_time[num_elements] = []
        lines_efficiency_time[num_elements] = []
        avg_best_serial_time = np.average([time_tuple[NAIVE_REDUCE] for time_tuple in data[num_elements][1]]) # 1 proc
        for num_procs, times in sorted(procs_dict.items()):
            #avg_allreduce_time = np.average([time_tuple[ALL_REDUCE] for time_tuple in times])
            #avg_mpireduce_time = np.average([time_tuple[MPI_REDUCE] for time_tuple in times])
            avg_naivereduce_time = np.average([time_tuple[NAIVE_REDUCE] for time_tuple in times])
            lines_parallel_time[num_elements].append(avg_naivereduce_time)
            speedup_score = speed_up(avg_best_serial_time, avg_naivereduce_time)
            lines_speedup_time[num_elements].append(speedup_score)
            efficiency_score = efficiency(speedup_score, num_procs)
            lines_efficiency_time[num_elements].append(efficiency_score)
    
    # plot parallel time graph
    plt.figure(figsize=(8,6), dpi=100, facecolor='w', edgecolor='k')
    for num_elements, line in lines_parallel_time.items():
        plt.plot(x_axis_line, line, label="n = %d"%(num_elements))
    plt.legend(loc='upper right')
    plt.title("Naive Reduce Parallel Time", fontsize=16, fontweight='bold')
    plt.xlabel("Number of Processes")
    plt.ylabel("Parallel Time (microseconds)")
    plt.xticks(x_axis_line)
    plt.savefig('./naive_reduce_parallel_time.png')
    plt.show()
    
    # plot speed-up graph
    plt.figure(figsize=(8,6), dpi=100, facecolor='w', edgecolor='k')
    for num_elements, line in lines_speedup_time.items():
        plt.plot(x_axis_line, line, label="n = %d"%(num_elements))
    plt.legend(loc='upper right')
    plt.title("Naive Reduce Speed Up", fontsize=16, fontweight='bold')
    plt.xlabel("Number of Processes")
    plt.ylabel("Speed Up Factor")
    plt.xticks(x_axis_line)
    plt.savefig('./naive_reduce_speed_up.png')
    plt.show()
    
    # plot speed-up graph
    plt.figure(figsize=(8,6), dpi=100, facecolor='w', edgecolor='k')
    for num_elements, line in lines_efficiency_time.items():
        plt.plot(x_axis_line, line, label="n = %d"%(num_elements))
    plt.legend(loc='upper right')
    plt.title("Naive Reduce Efficiency", fontsize=16, fontweight='bold')
    plt.xlabel("Number of Processes")
    plt.ylabel("Efficiency (%)")
    plt.xticks(x_axis_line)
    plt.savefig('./naive_reduce_efficiency.png')
    plt.show()
    
    
if __name__ == '__main__':
    data = load_data(RESULTS)
    make_graphs(data)