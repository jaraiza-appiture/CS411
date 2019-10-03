
RESULTS = './results'

def load_data(filename):
    in_file = open(filename, 'r')
    data = {}
    for line in in_file:
        myreduce_time, mynaive_time, mpireduce_time, procs, elements, op_output = line.split(',')
        if not data.get(procs, False):
            data[procs] = {}
        if not data[procs].get(elements, False):
            data[procs][elements] = []
        data[procs][elements].append((myreduce_time, mynaive_time, mpireduce_time, op_output))
    in_file.close()
    
    return data

def speed_up(serial_time, parallel_time):
    pass

def efficiency(speedUp, procs):
    pass

def parallel_time():
    pass