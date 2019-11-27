#include <fstream>
#include <iostream>
#include <map>
#include <omp.h>
#include <assert.h>
#include <vector>
#include <queue>
#include "node.h"

using std::cout;
using std::endl;
using std::string;
using std::map;
using std::ifstream;
using std::getline;
using std::vector;
using std::priority_queue;

struct drand48_data randBuffer;


// map<int, node> load_graph(string filename)
void print_graph(map<int, node> graph)
{
    map<int, node>::iterator it = graph.begin();
    vector<int>::iterator list_it;

    while(it != graph.end())
    {
        // int id = it->first;

        // cout << "src_id: " << id << " -> ";

        // for(list_it = graph[id].outlinks.begin(); list_it != graph[id].outlinks.end(); ++list_it)
        // {
        //     cout << list_it->first << " ";
        // }
        // cout << endl;

        // it++;
    }
}

void load_graph(string filename, map<int, node>& graph, vector<int>& keys)
{
    ifstream graphfile;
    char line[100];
    graphfile.open(filename);

    int src_id, dest_id;

    while(!graphfile.eof())
    {
        graphfile.getline(line, 100);
        
        if(line[0] == '#')
            continue;

        sscanf(line, "%d %d", &src_id, &dest_id);
        
        if(graph.find(src_id) == graph.end())
        {
            graph[src_id] = node(src_id);
            keys.push_back(src_id);
        }

        if(graph.find(dest_id) == graph.end())
        {
            graph[dest_id] = node(dest_id);
            keys.push_back(dest_id);
        }

        graph[src_id].outlinks.push_back(dest_id);
    }

    graphfile.close();
}

bool coin_toss(double d)
{
    double coin;
    drand48_r(&randBuffer, &coin);

    if(coin <= d)
        return true; //jump
    return false; //dont jump
}

void travel(map<int, node>& graph, vector<int>& keys, int node_id, int k, double d)
{
    
    for(int i = 0; i < k; i++)
    {
        #pragma omp atomic
            graph[node_id].visit_count += 1;

        if(coin_toss(d)) // jump
            node_id = graph[keys[rand() % keys.size()]].id;
        else // pick neighbor
        {
            int index = rand() % (graph[node_id].outlinks.size() + 1);
            if(index != graph[node_id].outlinks.size())
                node_id = graph[node_id].outlinks[index];
        }
    }
}

void page_rank(map<int, node>& graph, vector<int>& keys, int k, double d, double& time_elapsed)
{
    srand(time(0));
    
    priority_queue<node, vector<node>, LessThanByVisit> rankings;

    int i;
    time_elapsed = omp_get_wtime();
    #pragma omp parallel for schedule(static) shared(keys, graph) private(i)
    for(i=0; i< keys.size(); i++)
    {
        travel(graph, keys, keys[i], k, d);
    }
    time_elapsed = omp_get_wtime() - time_elapsed;

    for(map<int, node>::iterator it = graph.begin(); it != graph.end(); it++)
        rankings.push(it->second);

    cout << "Top 5 pages: " << endl;
    for(int i = 0; i < 5; i++)
    {
        cout << "id: " << rankings.top().id << " visit_count: " << rankings.top().visit_count << endl;
        rankings.pop();
    }
}

int main(int argc, char *argv[])
{
    int rank, k, p = 1;
    double d, time_elapsed;
    
    string filename;
    map<int, node> graph;
    vector<int> keys;

    srand48_r(time(NULL), &randBuffer);
    if(argc < 5)
    {
        cout << "Usage: pagerank graphfilename {k: length of walk} {d: damping ratio}";
        cout << " {p: num threads}" << endl;
        exit(1);
    }

    if(argc == 5)
    {
        k = atoi(argv[2]);
        d = atof(argv[3]);
        p = atoi(argv[4]);
        assert(p>=1);
        filename = argv[1];

        cout << "Filename: " << filename;
        cout << " K: " << k;
        cout << " D: " << d;
        cout << " Procs: " << p << endl;
    }

    omp_set_num_threads(p);

    #pragma omp parallel
    {
        assert(p==omp_get_num_threads());
        // int rank = omp_get_thread_num();
        // cout << "Rank=" << rank << "threads=" << p << endl;
    }

    load_graph(filename, graph, keys);

    page_rank(graph, keys, k, d, time_elapsed);

    cout << "Time: " << time_elapsed << endl;
}