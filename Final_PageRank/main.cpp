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

map<int, node> load_graph(string filename)
{
    map<int, node> graph;
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
            graph[src_id] = node(src_id);

        if(graph.find(dest_id) == graph.end())
            graph[dest_id] = node(dest_id);

        graph[src_id].outlinks.push_back(dest_id);
    }

    graphfile.close();

    return graph;
}

bool coin_toss(double d)
{
    
    double coin;
    drand48_r(&randBuffer, &coin);

    // cout << "Coin Toss: " << coin << endl;

    if(coin <= d)
        return true; //jump
    return false; //dont jump
}

void travel(map<int, node>& graph, vector<int> keys, int node_id, int k, double d)
{
    
    for(int i = 0; i < k; i++)
    {
        graph[node_id].visit_count++;

        if(coin_toss(d)) // jump
        {
            node_id = graph[keys[rand() % keys.size()]].id;
            // cout << "Jumping" << endl;
        }
        else // pick neighbor
        {
            int index = rand() % (graph[node_id].outlinks.size() + 1);
            if(index != graph[node_id].outlinks.size())
            {
                node_id = graph[node_id].outlinks[index];
                // cout << "Picking neighbor" << endl;
            }
            else
            {
                // cout << "Reusing self" << endl;
            }
            
        }
    }
}

void page_rank(map<int, node>& graph, int k, double d)
{
    srand(time(0));
    vector<int> keys;
    priority_queue<node, vector<node>, LessThanByVisit> rankings;

    // get keys
    for(map<int, node>::iterator it = graph.begin(); it != graph.end(); it++)
    {
        keys.push_back(it->first);
    }

    for(int i=0; i< keys.size(); i++)
    {
        travel(graph, keys, keys[i], k, d);
    }

    for(map<int, node>::iterator it = graph.begin(); it != graph.end(); it++)
    {
        rankings.push(it->second);
    }

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
    double d;
    string filename;
    map<int, node> graph;
    srand48_r(time(0), &randBuffer);
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
        cout << " Procs: " << p;
        cout << " K: " << k;
        cout << " D: " << d << endl;
    }

    graph = load_graph(filename);
    // print_graph(graph);
    page_rank(graph, k, d);
    // omp_set_num_threads(p);

    // #pragma omp parallel
    // {
    //     assert(p==omp_get_num_threads());

    //     int rank = omp_get_thread_num();
    // }


}