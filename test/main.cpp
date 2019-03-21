#include <unordered_map>
#include <vector>
#include <queue>

struct Graph{

    std::unordered_map<char, std::vector<char>> edges;

    std::vector<char> neighbors(char node){
        return edges[node];
    }

};

std::vector<char> BreadthFirstSearch(Graph, char);

int main(){

    Graph graph {{
        {'A', {'B'}},
        {'B', {'A', 'C', 'D'}},
        {'C', {'A'}},
        {'D', {'A', 'E'}},
        {'E', {'B'}},
    }};

    std::vector<char> path = BreadthFirstSearch(graph,'A');
    
    return 0;
}

std::vector<char> BreadthFirstSearch(Graph graph, char start){

    std::vector<char> path;

    std::queue<char> frontier;
    frontier.push(start);


    return path;

}