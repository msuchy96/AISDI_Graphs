#include <iostream>
#include <algorithm>
#include "Graph.h"

Graph::Graph(char *NameOfFile)
{
    v = e = 0;

    file.open(NameOfFile, std::ios::in);
    file >> v;
    vertexes = new std::vector<int>[v];
    int a,b;
    while (file >> a >> b)
    {
        vertexes[a].push_back(b);
        if( a != b )
            vertexes[b].push_back(a);
        ++e;
    }
    file.close();
}


Graph::~Graph()
{

    delete [] vertexes;
}
