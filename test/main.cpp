#include <unordered_map>
#include <vector>
#include <queue>
#include <iostream>

struct Graph{

    std::unordered_map<char, std::vector<char>> edges;

    std::vector<char> neighbors(char node){
        return edges[node];
    }

};

std::vector<char> BreadthFirstSearch(Graph, char);

int main(){

    // Graph graph {{
    //     {'A', {'B'}},
    //     {'B', {'A', 'C', 'D'}},
    //     {'C', {'A'}},
    //     {'D', {'A', 'E'}},
    //     {'E', {'B'}},
    // }};

    Graph graph {{
        {'S', {'A', 'B'}},
        {'A', {'S', 'B', 'D'}},
        {'B', {'S', 'A', 'C'}},
        {'C', {'B', 'E'}},
        {'D', {'A', 'G'}},
        {'E', {'C'}},
        {'G', {'D'}}        
    }};

    std::vector<char> path = BreadthFirstSearch(graph,'S');
    
    return 0;
}

std::vector<char> BreadthFirstSearch(Graph graph, char start){

    char current;                                                                   // current node being examined
    std::vector<char> path;                                                         // nodes path from start to goal

    std::queue<char> frontier;                                                      // nodes that compound the external frontier of the search expansion
    frontier.push(start);                                                           // first frontier start with the start node

    std::unordered_map<char, char> came_from;                                       // hash composed by node and from where it came from
    came_from.insert(std::pair<char, char>(start, NULL));                           // initial condition

    while(! frontier.empty()){                                                      // while there are reachable nodes that were not explored yet expand frontier
        current = frontier.front();                                                 // analyse frontier's nodes
        frontier.pop();                                                             
        std::cout << "Visiting " << current << '\n';
        for (auto next : graph.neighbors(current)){                                 // update frontier adding the neighbors nodes of the nodes on the current frontier and mark each node's parent
            if (came_from.find(next) == came_from.end()) {
                frontier.push(next);                                                // update frontier
                came_from.insert(std::pair<char, char>(next, current));             // saves parent
            }
        }
    }

    for(auto element : came_from){                                                  // cout nodes and their parent
        std::cout << element.first << " came from " << element.second << std::endl; 
    }

    return path;

}