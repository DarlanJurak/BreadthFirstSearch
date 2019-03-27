#include <unordered_map>    // came_from ("closed list" with track)
#include <vector>           // path
#include <queue>            // frontier
#include <iostream>         // "debug"
#include <algorithm>        // std::reverse
#include <unordered_set>    // 

struct Graph{

    std::unordered_map<char, std::vector<char>> edges;

    std::vector<char> neighbors(char node){
        return edges[node];
    }

};

// using namespace std;

struct Pos{

		int x;
		int y;
				
		// size_t operator()(const Pos& p) const noexcept {
		//     size_t hash = (p.x + 10 * p.y);
		//     return hash;
		// };

	};

namespace std{

	template<> struct hash<Pos>{
		std::size_t operator()(const Pos& p) const noexcept
		{
		    return std::hash<int>()(p.x ^ (p.y << 4));
		}
	};
	
	bool operator==(const Pos& pos1, const Pos& pos2){
		return pos1.x == pos2.x && pos1.y == pos2.y;
	}
}

static std::array<Pos, 4> DIRS = {Pos{1, 0}, Pos{0, -1}, Pos{-1, 0}, Pos{0, 1}};

struct SquareGrid {
    
    int width, height;
    std::unordered_set<Pos> walls;

    SquareGrid(int width_, int height_) : width(width_), height(height_) {}

    bool in_bounds(Pos id) const {
        return 0 <= id.x && id.x < width
            && 0 <= id.y && id.y < height;
    }

    bool passable(Pos id) const {
        return walls.find(id) == walls.end();
    }

    std::vector<Pos> neighbors(Pos id) const {
        std::vector<Pos> results;

        for (Pos dir : DIRS) {
            Pos next{id.x + dir.x, id.y + dir.y};
            // if (in_bounds(next) && passable(next)) {
            //     results.push_back(next);
            // }
        }

        if ((id.x + id.y) % 2 == 0) {
            // aesthetic improvement on square grids
            std::reverse(results.begin(), results.end());
        }

        return results;
    }
};


std::vector<char> BreadthFirstSearch(Graph, char start, char goal);

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

    std::vector<char> path = BreadthFirstSearch(graph,'S', 'G');

    // printing path
    std::cout << "Path: ";
    for(auto node : path){
        std::cout << node;
    }
    std::cout << std::endl;
    
    return 0;
}

std::vector<char> BreadthFirstSearch(Graph graph, char start, char goal){

    char current;                                                                   // current node being examined
    std::vector<char> path;                                                         // nodes path from start to goal

    std::queue<char> frontier;                                                      // nodes that compound the external frontier of the search expansion
    frontier.push(start);                                                           // first frontier start with the start node

    std::unordered_map<char, char> came_from;                                       // hash composed by node and from where it came from
    came_from.insert(std::pair<char, char>(start, NULL));                           // initial condition

    while(! frontier.empty()){                                                      // while there are reachable nodes that were not explored yet then expand frontier
        current = frontier.front();                                                 // analyse frontier's nodes
        frontier.pop();                                                             

        if (current == goal){
            break;
        }

        std::cout << "Visiting " << current << '\n';
        for (auto next : graph.neighbors(current)){                                 // update frontier adding the neighbors nodes of the nodes on the current frontier and mark each node's parent
            if (came_from.find(next) == came_from.end()) {                          // if is not in the closed list
                frontier.push(next);                                                // update frontier
                came_from.insert(std::pair<char, char>(next, current));             // saves parent
            }
        }
    }

    for(auto element : came_from){                                                  // cout nodes and theirs parent
        std::cout << element.first << " came from " << element.second << std::endl; 
    }

    // discovering path
    current = goal;
    while(current != start){
        path.push_back(current);
        current = came_from[current];
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    
    return path;

}