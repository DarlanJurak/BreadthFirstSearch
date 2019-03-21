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
        {'A', {'S', 'B', 'D'}},
        {'B', {'S', 'A', 'C'}},
        {'C', {'B', 'E'}},
        {'D', {'A', 'G'}},
        {'E', {'C'}},
        {'G', {'D'}},
        {'S', {'A', 'B'}}
    }};

    std::vector<char> path = BreadthFirstSearch(graph,'S');
    
    return 0;
}

std::vector<char> BreadthFirstSearch(Graph graph, char start){

    char current;
    std::vector<char> path;

    std::queue<char> frontier;
    frontier.push(start);
    
    std::unordered_map<char, char> came_from;
    came_from.insert(std::pair<char, char>(start, NULL));

    while(! frontier.empty()){
        current = frontier.front();
        frontier.pop();
        for (auto next : graph.neighbors(current)){
            if (came_from.find(next) == came_from.end()) {
                frontier.push(next);
                came_from.insert(std::pair<char, char>(next, current));
            }
        }
    }

    for( auto element : came_from){
        std::cout << element.first << " came from " << element.second << std::endl;
    }    

    return path;

}