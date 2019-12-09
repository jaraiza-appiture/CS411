#include <fstream>
#include <iostream>
#include <unordered_map>
#include <omp.h>
#include <assert.h>
#include <vector>
#include <queue>
#include "node.h"

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::vector;
using std::priority_queue;
using std::unordered_map;

struct drand48_data randBuffer;
int debug = 0;

void load_graph(string filename, unordered_map<int, node>& graph, vector<int>& keys)
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

void travel(unordered_map<int, node>& graph, vector<int>& keys, int node_id, int k, double d)
{
    for(int i = 0; i < k; i++)
    {
        // atomic method:
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

void page_rank(unordered_map<int, node>& graph, vector<int>& keys, int k, double d, double& time_elapsed)
{
    srand(time(0));
    
    priority_queue<node, vector<node>, LTBVisit> rankings;
    int i;

    time_elapsed = omp_get_wtime();
    #pragma omp parallel for schedule(dynamic) shared(keys, graph) private(i)
    for(i=0; i< keys.size(); i++)
    {
        travel(graph, keys, keys[i], k, d);
    }
    time_elapsed = omp_get_wtime() - time_elapsed;

    for(unordered_map<int, node>::iterator it = graph.begin(); it != graph.end(); it++)
        rankings.push(it->second);

    if(debug)
    {
        cout << "Top 5 pages: " << endl;
        for(int i = 0; i < 5; i++)
        {
            cout << "id: " << rankings.top().id << " visit_count: " << rankings.top().visit_count << endl;
            rankings.pop();
        }
    }
}

int main(int argc, char *argv[])
{
    int rank, k, p = 1;
    double d, time_elapsed;
    
    string filename;
    unordered_map<int, node> graph;
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
        if (debug){
            cout << "Filename: " << filename;
            cout << " K: " << k;
            cout << " D: " << d;
            cout << " Procs: " << p << endl;
        }
    }

    omp_set_num_threads(p);

    #pragma omp parallel
    {
        assert(p==omp_get_num_threads());
    }

    if(debug)
        cout << "Loading graph..." << endl;
    load_graph(filename, graph, keys);
    
    if(debug)
        cout << "Ranking pages..." << endl;
    page_rank(graph, keys, k, d, time_elapsed);

    if(debug)
        cout << "Time (ms): " << time_elapsed*1000 << endl;
    // csv: p,d,k,runtime,filename
    cout << p << "," << d << "," << k << "," << time_elapsed*1000;
    cout << "," << filename << endl;
}