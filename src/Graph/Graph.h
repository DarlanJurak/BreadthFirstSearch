#ifndef GRAPH_H
#define GRAPH_H

#include "../Node/Node.h"

#include <vector>
#include <unordered_map> 

class Graph
{
    private:
        std::vector<Node> nodes;
        std::unordered_map<NODE::Pos*, std::vector<Node*>> edges;
    public:
        Graph(/* args */);
        ~Graph();
        std::vector<Node*>* Neighbors(Node* node);
        std::vector<Node*> BreadthFirstSearch();
};

#endif