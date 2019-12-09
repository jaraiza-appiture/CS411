#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <omp.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
struct Node{
    int visits;
    int data;
    double rank;
    vector<int> neighbors;
}Node;

int compare(struct Node* sortedgraph , struct Node currNode)
{
    struct Node tempNode;
    struct Node swapNode;
    for (int i =0; i<5; i++)
    {  // printf("\nsortedgraph i rank %f:", sortedgraph[i].rank);
       // printf("\n currNode i rank %f:", currNode.rank);
       
        if (currNode.rank >= sortedgraph[i].rank)
        {
            
            tempNode = sortedgraph[i];
            sortedgraph[i]= currNode;

            for (int j=i+1; j< 5; j++)
            {
                swapNode= sortedgraph[j];
                sortedgraph[j] = tempNode;
                tempNode = swapNode;
            }
            break;
        }
        
    }
}
int main(int argc, char *argv[])
{

	omp_set_num_threads(atoi(argv[2]));

    ifstream infile;
    int lengthWalk, numNodes;
    std::string line;
    std::string file;
    std::string first_num, second_num;
    int currNode;
    int currFriend;
    double D = atof(argv[1]);    
    lengthWalk = atoi(argv[3]);
    int p = atoi(argv[2]);
    struct Node* sortedgraph  = (struct Node*)malloc(sizeof(struct Node)*5);
    struct Node* mygraph  = (struct Node*)malloc(sizeof(struct Node)*numNodes);


    int total_visits;
    double timeElapsed;

    infile.open("NotreDame.txt");

    if (!infile) 
    {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
    else
    {
        std::string line = "" ;
        getline(infile, line);
        numNodes = atoi(line.c_str());
        mygraph  = (struct Node*)malloc(sizeof(struct Node)*numNodes);


        // N= stoi(first);
        // K= stoi(second);
        // comp set thread com get thread
        for (int i =0 ; i < numNodes; i++)
        {
            mygraph[i].data = i;

        }
        while (!infile.eof()) {
            getline(infile, first_num, '\t');
            getline(infile, second_num);
            currNode= atoi(first_num.c_str());
            currFriend= atoi(second_num.c_str());
            // printf("This is me %d\n", currNode);
            // printf("This is my friend %d\n", currFriend);
            mygraph[currNode].visits = 0;
            // mygraph[currNode].data = currNode;
            mygraph[currNode].neighbors.push_back(currFriend);

        }

        //for each node 
        timeElapsed =  omp_get_wtime();
        #pragma omp parallel for schedule(static) 
        for (int eachNode=0; eachNode< numNodes; eachNode++)
        {
            int rank = omp_get_thread_num(); 
            // printf("I am the thread%d\n", rank);

            unsigned int seed = eachNode+rank;
            int prevNode = -1;
            int node= eachNode;
            //go the entire path 

            for (int one_step = 0; one_step<lengthWalk ; one_step++)
            {
		        if (prevNode != node)
                {
                #pragma omp atomic
                    mygraph[node].visits++;
                }
                //generate numbers between 0 and 1 to compare with D
                double coinToss = (double)rand_r(&seed)/(double)RAND_MAX;
                prevNode = node;

                if (coinToss > D) // if it is greater than D
                    {
                        //tails.. Go to a random neighbor

                        if(!mygraph[node].neighbors.empty()) // check if the neighbors are empty
                        {
                            //generate numbers between 0  and length of the neighbotrs-1
                            //neighbors.size() === number of edges
                            // seed+=node;
                            int rand_edge =  rand_r(&seed)%(mygraph[node].neighbors.size());
                            //choose the random neighbor
                            node =  mygraph[node].neighbors[rand_edge];
                        }
                    }
                else
                    {
                    //generate numbers between 0  and N-1
                    //head ... go to a random node in the graph
                        // seed +=node;
                        int rand_node =  rand_r(&seed)% numNodes;
                        //choose a random node
                        node =  rand_node;
                    }
                
                     
                
                
            }
        }
        timeElapsed = omp_get_wtime() - timeElapsed;
        printf("\ntime spent %f\n", timeElapsed);
    }
    int totallinks = 0;
    for (int i = 0; i< numNodes; i++)
    {
        totallinks += mygraph[i].visits;
    }
    for (int i = 0; i< numNodes; i++)
    {
        mygraph[i].rank = (double)mygraph[i].visits/(double)totallinks; 

    }



    printf("total visits: %d\n", totallinks);

    infile.close();


    
    for (int i=0; i < 5; i++)
    {
        sortedgraph[i].rank = -0.1;
    }
    for (int i = 0; i < numNodes ; i++) 
    { 
         compare(sortedgraph, mygraph[i]);
    }
    for (int i = 0; i < 5; i++)
    {
        printf("Node = %d\tVisits = %d\tRank = %f\tNeighbors = %d\n", sortedgraph[i].data, sortedgraph[i].visits, sortedgraph[i].rank, sortedgraph[i].neighbors.size());
    }
          

    return 0;
}
