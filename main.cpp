#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<int> *FirstGraph;  int v_f = 0;
std::vector<int> *SecondGraph; int v_s = 0;
int *permutationTab = nullptr;


bool checkBasicPropereties(int edge_counter_F,int edge_counter_S)
{
    if(v_f != v_s || edge_counter_F != edge_counter_S)
        return false;

 return true;

}

bool createGraph(int &a,int &b,int &counter,int &v, std::vector<int>*& Graph )
{
    if( a<0 || a >= v || b<0 || b >=v )
        return false;

    counter++;
    Graph[a].push_back(b);
    if( a != b )
        Graph[b].push_back(a);
    return true;

}

bool openFile(char* argv[])
{
    std::ifstream file;
    int edge_counter_F=0;
    int edge_counter_S=0;

    file.open( argv[1] );
    if (!file.good())
        return false;

    file >> v_f; /// n - liczba wierzecholkow
    FirstGraph = new std::vector<int>[v_f]; /// deklaracja tablicy wektorow
    int a,b;
    while( !file.eof() ) /// jedna funkcja w obu grafach
    {

        file >> a >> b;
        if(!createGraph(a,b,edge_counter_F,v_f,FirstGraph))
            return false;

    }
    file.close();


    file.open( argv[2] );
    if (!file.good()) {
        delete[] FirstGraph;
        return false;
    }


    file >> v_s;
    SecondGraph = new std::vector<int>[v_s];
    while( !file.eof() )  /// jedna funkcja w obu grafach
    {

        file >> a >> b;

        if(!createGraph(a,b,edge_counter_S,v_s,SecondGraph))
            return false;


    }
    file.close();


    return checkBasicPropereties(edge_counter_F, edge_counter_S);
    /// return (v_f==v_s && edge_counter_F == edge_counter_s);
}

void createPermutationTab()
{
    permutationTab = new int[v_f];
    for(int i=0; i<v_s; i++)
        permutationTab[i]=i;

}

void sortSecondGraph()
{
    for(int i=0; i<v_f; i++)
        std::sort(SecondGraph[i].begin(), SecondGraph[i].end());

}

bool checkDegsV()
{
    int degsFirstGraph[v_f];
    int degsSecondGraph[v_s];

    for(int i=0; i<v_f; i++)
    {
        degsFirstGraph[i] = FirstGraph[i].size();
        degsSecondGraph[i] = SecondGraph[i].size();
    }
    std::sort(degsFirstGraph, degsFirstGraph+v_f); /// Range of Tabs sort(first,last)
    std::sort(degsSecondGraph, degsSecondGraph+v_s);

    for(int i=0; i<v_f; i++)
        if(degsFirstGraph[i] != degsSecondGraph[i])  /// checking degrees of vertex
            return false;

    return true;
}

void printPermutation()
{

    for(int i=0; i<v_f; i++)
        std::cout << i << " --> " << permutationTab[i] << "\n";
}

void Isomorphic(bool isIt)
{
    if(isIt)
    {
        std::cout << "Izomorficzne\n";
        printPermutation();
    }

    else
        std::cout << "Nieizomorficzne\n";

    delete[] FirstGraph;
    delete[] SecondGraph;
    delete permutationTab;

}

bool permutationTabOrder(int a, int b)
{
    return permutationTab[a] < permutationTab[b];
}


bool checkPermutation()
{

    for(int i=0; i<v_f; i++)
    {
        if(FirstGraph[i].size() != SecondGraph[permutationTab[i]].size()) /// checking degree of vertex
            return false;

        std::sort(FirstGraph[i].begin() , FirstGraph[i].end(), permutationTabOrder); /// Sorting each record of Graph by permutationTabOrder

        for(int j=0; j<FirstGraph[i].size(); j++)
            if( permutationTab[ FirstGraph[i][j] ] != SecondGraph[permutationTab[i]][j] )
                return false;

    }
    return true;


}




int main(int argc, char* argv[])
{
    if(argc == 3 && openFile(argv))
    {                                   /// basicPropereties checked
        createPermutationTab();
        sortSecondGraph();
        if(!checkDegsV())
        {
            Isomorphic(false);
            return 0;
        }

        do
        {
            if(checkPermutation())
            {
                Isomorphic(true);
                return 0;
            }

        }while(std::next_permutation(permutationTab,permutationTab+v_f));


    }
    else

        Isomorphic(false);
    return 0;


}




