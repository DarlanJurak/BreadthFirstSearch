#include "Graph.h"

#include <queue>

/*
    If node exists and has neighbors, 
    returns a pointer to the vector of 
    pointers to neighbors on "edges" hash.
*/
std::vector<Node*>* Graph::Neighbors(Node* node){
    return &(this->edges.find(node->GetPos())->second);
}

std::vector<Node*> Graph::BreadthFirstSearch(){

    std::queue<Node*> frontier;
    frontier.push(&this->nodes[0]);                    // Start position
    std::unordered_map<NODE::Pos, Node*> came_from;    // Hash <NodePos, >
    Node *current;

    while (!frontier.empty){

        current = frontier.front;
        for (auto & element : *this->Neighbors(current)) {
            if (came_from.find(element->GetPos()) != came_from.end()){
                frontier.push(element);
                came_from.insert(std::make_pair(element->GetPos(), current));
            };
        }
    }
}

Graph::Graph()
{
    unsigned int m = 3;
    unsigned int n = 3;

    // Creates mxn nodes
    for (int i = 0; i < m; i++){
        for(int j = 0; j < n; j++)
        {
            this->nodes.push_back(Node(i, j));
        }
        
    }

    /*
        Creates aux vectors.
        Each vector is related to one existing node.
        Each vector represents the neighbors of one node.
    */
    std::vector<Node*> vec_1 {&nodes[2], &nodes[4], &nodes[5]};
    std::vector<Node*> vec_2 {&nodes[1], &nodes[3], &nodes[4], &nodes[5], &nodes[6]};
    std::vector<Node*> vec_3 {&nodes[2], &nodes[5], &nodes[6]};
    std::vector<Node*> vec_4 {&nodes[1], &nodes[2], &nodes[5], &nodes[7], &nodes[8]};
    std::vector<Node*> vec_5 {&nodes[1], &nodes[2], &nodes[3], &nodes[4], &nodes[5], &nodes[6], &nodes[7], &nodes[8], &nodes[9]};
    std::vector<Node*> vec_6 {&nodes[2], &nodes[3], &nodes[5], &nodes[8], &nodes[9]};
    std::vector<Node*> vec_7 {&nodes[4], &nodes[5], &nodes[8]};
    std::vector<Node*> vec_8 {&nodes[4], &nodes[5], &nodes[6], &nodes[7], &nodes[9]};
    std::vector<Node*> vec_9 {&nodes[5], &nodes[6], &nodes[8]};

    // Creates a hash with the existing edges
    std::unordered_map<NODE::Pos, std::vector<Node*>> edgs({
        { nodes[0].GetPos(), vec_1},
        { nodes[1].GetPos(), vec_2},
        { nodes[2].GetPos(), vec_3},
        { nodes[3].GetPos(), vec_4},
        { nodes[4].GetPos(), vec_5},
        { nodes[5].GetPos(), vec_6},
        { nodes[6].GetPos(), vec_7},
        { nodes[7].GetPos(), vec_8},
        { nodes[8].GetPos(), vec_9},
    });

    // Set Graph class edges
    this->edges = edgs;
}

Graph::~Graph()
{
}