from matplotlib import pyplot as plt
import numpy as np
RESULTS = './results_test_speed_up.txt'
RUNTIME = 1

def load_data(filename):
    in_file = open(filename, 'r')
    data = {}
    for line in in_file:
        #csv format: pi,samples,threads,runtime
        pi, samples, threads, runtime = line.split(',')
        
        if not data.get(int(samples), False):
            data[int(samples)] = {}
        if not data[int(samples)].get(int(threads), False):
            data[int(samples)][int(threads)] = []
        data[int(samples)][int(threads)].append((float(pi), float(runtime)))
    in_file.close()
    
    return data

def speed_up(serial_time, parallel_time):
    return serial_time / parallel_time

def efficiency(speedUp, procs):
    return speedUp / procs

def make_graphs(data):
    
    x_axis_line = [1, 2, 4, 8]
    
    # SERIAL MATRIX
    lines_parallel_time = {}
    lines_speedup_time = {}
    for num_elements, procs_dict in sorted(data.items()):
        lines_parallel_time[num_elements] = []
        lines_speedup_time[num_elements] = []
        # lines_efficiency_time[num_elements] = []
        avg_best_time = np.average([time_tuple[RUNTIME] for time_tuple in data[num_elements][1]]) # 1 thread
        for num_procs, times in sorted(procs_dict.items()):
            avg_time = np.average([time_tuple[RUNTIME] for time_tuple in times])
            lines_parallel_time[num_elements].append(avg_time)
            speedup_score = speed_up(avg_best_time, avg_time)
            lines_speedup_time[num_elements].append(speedup_score)
            # efficiency_score = efficiency(speedup_score, num_procs)
            # lines_efficiency_time[num_elements].append(efficiency_score)
    
    # plot parallel time graph
    # plt.figure(figsize=(8,6), dpi=100, facecolor='w', edgecolor='k')
    # for num_elements, line in lines_parallel_time.items():
    #     plt.plot(x_axis_line, line, label="n = %d"%(num_elements))
    # plt.legend(loc='upper right')
    # plt.title("Serial Matrix Time", fontsize=16, fontweight='bold')
    # plt.xlabel("Number of Processes")
    # plt.ylabel("Parallel Time (microseconds)")
    # plt.xticks(x_axis_line)
    # plt.savefig('./serial_matrix_time.png')
    # plt.show()
    
    # plot speed-up graph
    plt.figure(figsize=(8,6), dpi=100, facecolor='w', edgecolor='k')
    for num_elements, line in lines_speedup_time.items():
        plt.plot(x_axis_line, line, label="n = %d"%(num_elements))
    plt.legend(loc='upper right')
    plt.title("Speed Up", fontsize=16, fontweight='bold')
    plt.xlabel("Number of Threads")
    plt.ylabel("Speed Up Factor")
    plt.xticks(x_axis_line)
    plt.savefig('./serial_matrix_speed_up.png')
    plt.show()
    
    # # plot speed-up graph
    # plt.figure(figsize=(8,6), dpi=100, facecolor='w', edgecolor='k')
    # for num_elements, line in lines_efficiency_time.items():
    #     plt.plot(x_axis_line, line, label="n = %d"%(num_elements))
    # plt.legend(loc='upper right')
    # plt.title("Serial Matrix Efficiency", fontsize=16, fontweight='bold')
    # plt.xlabel("Number of Processes")
    # plt.ylabel("Efficiency (%)")
    # plt.xticks(x_axis_line)
    # plt.savefig('./serial_matrix_efficiency.png')
    # plt.show()
    
    # PARALLEL PREFIX
    # lines_parallel_time = {}
    # lines_speedup_time = {}
    # lines_efficiency_time = {}
    # for num_elements, procs_dict in sorted(data.items()):
    #     lines_parallel_time[num_elements] = []
    #     lines_speedup_time[num_elements] = []
    #     lines_efficiency_time[num_elements] = []
    #     avg_best_serial_time = np.average([time_tuple[SERIAL_BASELINE] for time_tuple in data[num_elements][2]]) # 1 proc
    #     for num_procs, times in sorted(procs_dict.items()):
    #         avg_parallel_prefix_time = np.average([time_tuple[PARALLEL_PREFIX] for time_tuple in times])
    #         lines_parallel_time[num_elements].append(avg_parallel_prefix_time)
    #         speedup_score = speed_up(avg_best_serial_time, avg_parallel_prefix_time)
    #         lines_speedup_time[num_elements].append(speedup_score)
    #         efficiency_score = efficiency(speedup_score, num_procs)
    #         lines_efficiency_time[num_elements].append(efficiency_score)
    
    # # plot parallel time graph
    # plt.figure(figsize=(8,6), dpi=100, facecolor='w', edgecolor='k')
    # for num_elements, line in lines_parallel_time.items():
    #     plt.plot(x_axis_line, line, label="n = %d"%(num_elements))
    # plt.legend(loc='upper right')
    # plt.title("Parallel Prefix Time", fontsize=16, fontweight='bold')
    # plt.xlabel("Number of Processes")
    # plt.ylabel("Parallel Time (microseconds)")
    # plt.xticks(x_axis_line)
    # plt.savefig('./parallel_prefix_time.png')
    # plt.show()
    
    # # plot speed-up graph
    # plt.figure(figsize=(8,6), dpi=100, facecolor='w', edgecolor='k')
    # for num_elements, line in lines_speedup_time.items():
    #     plt.plot(x_axis_line, line, label="n = %d"%(num_elements))
    # plt.legend(loc='upper right')
    # plt.title("Parallel Prefix Speed Up", fontsize=16, fontweight='bold')
    # plt.xlabel("Number of Processes")
    # plt.ylabel("Speed Up Factor")
    # plt.xticks(x_axis_line)
    # plt.savefig('./parallel_prefix_speed_up.png')
    # plt.show()
    
    # # plot speed-up graph
    # plt.figure(figsize=(8,6), dpi=100, facecolor='w', edgecolor='k')
    # for num_elements, line in lines_efficiency_time.items():
    #     plt.plot(x_axis_line, line, label="n = %d"%(num_elements))
    # plt.legend(loc='upper right')
    # plt.title("Parallel Prefix Efficiency", fontsize=16, fontweight='bold')
    # plt.xlabel("Number of Processes")
    # plt.ylabel("Efficiency (%)")
    # plt.xticks(x_axis_line)
    # plt.savefig('./parallel_prefix_efficiency.png')
    # plt.show()
    
    # # SERIAL BASELINE
    # lines_parallel_time = {}
    # lines_speedup_time = {}
    # lines_efficiency_time = {}
    # for num_elements, procs_dict in sorted(data.items()):
    #     lines_parallel_time[num_elements] = []
    #     lines_speedup_time[num_elements] = []
    #     lines_efficiency_time[num_elements] = []
    #     avg_best_serial_time = np.average([time_tuple[SERIAL_BASELINE] for time_tuple in data[num_elements][2]]) # 1 proc
    #     for num_procs, times in sorted(procs_dict.items()):
    #         avg_serial_baseline_time = np.average([time_tuple[SERIAL_BASELINE] for time_tuple in times])
    #         lines_parallel_time[num_elements].append(avg_serial_baseline_time)
    #         speedup_score = speed_up(avg_best_serial_time, avg_serial_baseline_time)
    #         lines_speedup_time[num_elements].append(speedup_score)
    #         efficiency_score = efficiency(speedup_score, num_procs)
    #         lines_efficiency_time[num_elements].append(efficiency_score)
    
    # # plot parallel time graph
    # plt.figure(figsize=(8,6), dpi=100, facecolor='w', edgecolor='k')
    # for num_elements, line in lines_parallel_time.items():
    #     plt.plot(x_axis_line, line, label="n = %d"%(num_elements))
    # plt.legend(loc='upper right')
    # plt.title("Serial Baseline Time", fontsize=16, fontweight='bold')
    # plt.xlabel("Number of Processes")
    # plt.ylabel("Parallel Time (microseconds)")
    # plt.xticks(x_axis_line)
    # plt.savefig('./serial_baseline_time.png')
    # plt.show()
    
    # # plot speed-up graph
    # plt.figure(figsize=(8,6), dpi=100, facecolor='w', edgecolor='k')
    # for num_elements, line in lines_speedup_time.items():
    #     plt.plot(x_axis_line, line, label="n = %d"%(num_elements))
    # plt.legend(loc='upper right')
    # plt.title("Serial Baseline Speed Up", fontsize=16, fontweight='bold')
    # plt.xlabel("Number of Processes")
    # plt.ylabel("Speed Up Factor")
    # plt.xticks(x_axis_line)
    # plt.savefig('./serial_baseline_speed_up.png')
    # plt.show()
    
    # # plot speed-up graph
    # plt.figure(figsize=(8,6), dpi=100, facecolor='w', edgecolor='k')
    # for num_elements, line in lines_efficiency_time.items():
    #     plt.plot(x_axis_line, line, label="n = %d"%(num_elements))
    # plt.legend(loc='upper right')
    # plt.title("Serial Baseline Efficiency", fontsize=16, fontweight='bold')
    # plt.xlabel("Number of Processes")
    # plt.ylabel("Efficiency (%)")
    # plt.xticks(x_axis_line)
    # plt.savefig('./serial_baseline_efficiency.png')
    # plt.show()
    
    
if __name__ == '__main__':
    data = load_data(RESULTS)
    make_graphs(data)