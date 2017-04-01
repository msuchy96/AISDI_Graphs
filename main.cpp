#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Graph.h"
#include <chrono>
#include <ctime>

int *permutationTab = nullptr;

void Isomorphic(int v,bool isIt)
{

    if(isIt)
    {
        std::cout << "Izomorficzne\n";
        for(int i=0; i<v; i++)
            std::cout << i << " --> " << permutationTab[i] << "\n";
    }

    else
        std::cout << "Nieizomorficzne\n";


    delete [] permutationTab;


}

void createPermutationTab(int v)
{
    permutationTab = new int[v];
    for(int i=0; i<v; i++)
        permutationTab[i]=i;

}

bool checkDegs(Graph &FirstGraph,Graph &SecondGraph)
{
    int degsFirstGraph[FirstGraph.v];
    int degsSecondGraph[SecondGraph.v];

    for(int i=0; i<FirstGraph.v; i++)
    {
        degsFirstGraph[i] = FirstGraph.vertexes[i].size();
        degsSecondGraph[i] = SecondGraph.vertexes[i].size();
    }
    std::sort(degsFirstGraph, degsFirstGraph+FirstGraph.v); /// Range of Tabs sort(first,last)
    std::sort(degsSecondGraph, degsSecondGraph+SecondGraph.v);

    for(int i=0; i<FirstGraph.v; i++)
        if(degsFirstGraph[i] != degsSecondGraph[i])  /// checking degrees of vertex
            return false;

    return true;
}

bool permutationTabOrder(int a, int b)
{
    return permutationTab[a] < permutationTab[b];
}

bool checkPermutation(Graph &FirstGraph,Graph &SecondGraph)
{

    for(int i=0; i<FirstGraph.v; i++)
    {
        if(FirstGraph.vertexes[i].size() != SecondGraph.vertexes[permutationTab[i]].size()) /// checking degree of vertex
            return false;

        std::sort(FirstGraph.vertexes[i].begin(), FirstGraph.vertexes[i].end(), permutationTabOrder);
        /// Sorting each record of Graph by permutationTabOrder

        for(int j=0; j<FirstGraph.vertexes[i].size(); j++)
            if( permutationTab[ FirstGraph.vertexes[i][j] ] != SecondGraph.vertexes[permutationTab[i]][j] )
                return false;

    }
    return true;


}

bool isItIsomorphic(Graph &FirstGraph,Graph &SecondGraph)
{
    if (FirstGraph.v != SecondGraph.v || FirstGraph.e != SecondGraph.e)
        return false;

    createPermutationTab(FirstGraph.v);

    for(int i=0; i<SecondGraph.v; i++)
        std::sort(SecondGraph.vertexes[i].begin(), SecondGraph.vertexes[i].end());

    if(!checkDegs(FirstGraph,SecondGraph))
       return false;

    do
    {
        if(checkPermutation(FirstGraph,SecondGraph))
            return true;


    }while(std::next_permutation(permutationTab,permutationTab+FirstGraph.v));


return false;

}


int main(int argc, char **argv)
{






    if (argc != 3)
    {
        std::cout << "Add files!" << std::endl;
        return 0;
    }
    Graph FirstGraph(argv[1]);
    Graph SecondGraph(argv[2]);

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    Isomorphic(FirstGraph.v,isItIsomorphic(FirstGraph, SecondGraph));

    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Finding Isomorphism: " << elapsed_seconds.count() << "s\n";

    return 0;
}
