#ifndef GRAFY_GRAPH_H
#define GRAFY_GRAPH_H

#include <fstream>
#include <vector>
#include <algorithm>

class Graph
{
public:

    Graph(char *NameOfFile);
    ~Graph();
    std::vector<int> * vertexes;
    int e;
    int v;

private:
    std::fstream file;
    char *NameOfFile;
};


#endif //GRAFY_GRAPH_H
