#include <unordered_map>
#include <vector>

struct Graph{

    std::unordered_map<char, std::vector<char>> edges;

    std::vector<char> neighbors(char node){
        return edges[node];
    }

};

int main(){

    Graph graph {{
        {'A', {'B'}},
        {'B', {'A', 'C', 'D'}},
        {'C', {'A'}},
        {'D', {'A', 'E'}},
        {'E', {'B'}},
    }};

    return 0;
}