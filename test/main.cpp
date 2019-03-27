#include <unordered_map>    // came_from ("closed list" with track)
#include <vector>           // Final discovered path (s toed in a vector)
#include <queue>            // Auxiliary data structure for definition of frontier in the expansion analysis in Breadth First Search algorithm
#include <iostream>         // "debug"
#include <algorithm>        // std::reverse (used as aesthetic to show the found path)
#include <unordered_set>    // Store Pos structs
#include <iomanip>          // std::setw (draw_grid)

/*
    Graph
        - Compounded by edges (explicitly) and nodes (implicitly).
        - Capable to inform the neighbors of a node.
*/
struct Graph{

    std::unordered_map<char, std::vector<char>> edges;

    std::vector<char> neighbors(char node){
        return edges[node];
    }

};


struct Pos{

	int x;
	int y;
};

// Comparison method for Pos struct
bool operator==(const Pos& pos1, const Pos& pos2){
		return pos1.x == pos2.x && pos1.y == pos2.y;
}

// Hash definition for specialized <unordered_set> of Pos struct
namespace std{

	template<> struct hash<Pos>{
        typedef Pos argument_type;
        typedef std::size_t result_type;
		std::size_t operator()(const Pos& p) const noexcept
		{
		    return std::hash<int>()(p.x ^ (p.y << 4));
		}
	};
}

// Possible moviment's directions
static std::array<Pos, 4> DIRS = {Pos{1, 0}, Pos{0, -1}, Pos{-1, 0}, Pos{0, 1}};

/*
    Squared grid:
        - Size: width x height
        - Compounded by walls (borders and obstacles inside the grid)
        - 
*/
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

    std::vector<Pos> Neighbors(Pos id) const {
        std::vector<Pos> results;

        for (Pos dir : DIRS) {
            Pos next{id.x + dir.x, id.y + dir.y};
            if (in_bounds(next) && passable(next)) {
                results.push_back(next);
            }
        }

        if ((id.x + id.y) % 2 == 0) {
            // aesthetic improvement on square grids
            std::reverse(results.begin(), results.end());
        }

        return results;
    }
};

// This outputs a grid. Pass in a distances map if you want to print
// the distances, or pass in a point_to map if you want to print
// arrows that point to the parent location, or pass in a path vector
// if you want to draw the path.
template<class Graph>
void draw_grid(const Graph& graph, int field_width,
               std::unordered_map<Pos, double>* distances=nullptr,
               std::unordered_map<Pos, Pos>* point_to=nullptr,
               std::vector<Pos>* path=nullptr) {
  for (int y = 0; y != graph.height; ++y) {
    for (int x = 0; x != graph.width; ++x) {
      Pos id {x, y};
      std::cout << std::left << std::setw(field_width);
      if (graph.walls.find(id) != graph.walls.end()) {
        std::cout << std::string(field_width, '#');
      } else if (point_to != nullptr && point_to->count(id)) {
        Pos next = (*point_to)[id];
        if (next.x == x + 1) { std::cout << "> "; }
        else if (next.x == x - 1) { std::cout << "< "; }
        else if (next.y == y + 1) { std::cout << "v "; }
        else if (next.y == y - 1) { std::cout << "^ "; }
        else { std::cout << "* "; }
      } else if (distances != nullptr && distances->count(id)) {
        std::cout << (*distances)[id];
      } else if (path != nullptr && find(path->begin(), path->end(), id) != path->end()) {
        std::cout << '@';
      } else {
        std::cout << '.';
      }
    }
    std::cout << '\n';
  }
}

void add_rect(SquareGrid& grid, int x1, int y1, int x2, int y2) {
  for (int x = x1; x < x2; ++x) {
    for (int y = y1; y < y2; ++y) {
      grid.walls.insert(Pos{x, y});
    }
  }
}

SquareGrid make_diagram1() {
  SquareGrid grid(30, 15);
  add_rect(grid, 3, 3, 5, 12);
  add_rect(grid, 13, 4, 15, 15);
  add_rect(grid, 21, 0, 23, 7);
  add_rect(grid, 23, 5, 26, 7);
  return grid;
}

// struct GridWithWeights: SquareGrid {
//   std::unordered_set<Pos> forests;
//   GridWithWeights(int w, int h): SquareGrid(w, h) {}
//   double cost(Pos from_node, Pos to_node) const {
//     return forests.find(to_node) != forests.end()? 5 : 1;
//   }
// };

// GridWithWeights make_diagram4() {
//   GridWithWeights grid(10, 10);
//   add_rect(grid, 1, 7, 4, 9);
//   typedef Pos L;
//   grid.forests = std::unordered_set<Pos> {
//     L{3, 4}, L{3, 5}, L{4, 1}, L{4, 2},
//     L{4, 3}, L{4, 4}, L{4, 5}, L{4, 6},
//     L{4, 7}, L{4, 8}, L{5, 1}, L{5, 2},
//     L{5, 3}, L{5, 4}, L{5, 5}, L{5, 6},
//     L{5, 7}, L{5, 8}, L{6, 2}, L{6, 3},
//     L{6, 4}, L{6, 5}, L{6, 6}, L{6, 7},
//     L{7, 3}, L{7, 4}, L{7, 5}
//   };
//   return grid;
// }

// template<typename T, typename priority_t>
// struct PriorityQueue {
//   typedef std::pair<priority_t, T> PQElement;
//   std::priority_queue<PQElement, std::vector<PQElement>,
//                  std::greater<PQElement>> elements;

//   inline bool empty() const {
//      return elements.empty();
//   }

//   inline void put(T item, priority_t priority) {
//     elements.emplace(priority, item);
//   }

//   T get() {
//     T best_item = elements.top().second;
//     elements.pop();
//     return best_item;
//   }
// };


std::vector<char> BreadthFirstSearch(Graph, char start, char goal);

int main(){

    // Graph graph {{
    //     {'A', {'B'}},
    //     {'B', {'A', 'C', 'D'}},
    //     {'C', {'A'}},
    //     {'D', {'A', 'E'}},
    //     {'E', {'B'}},
    // }};

    // Graph graph {{
    //     {'S', {'A', 'B'}},
    //     {'A', {'S', 'B', 'D'}},
    //     {'B', {'S', 'A', 'C'}},
    //     {'C', {'B', 'E'}},
    //     {'D', {'A', 'G'}},
    //     {'E', {'C'}},
    //     {'G', {'D'}}        
    // }};

    // std::vector<char> path = BreadthFirstSearch(graph,'S', 'G');

    // // printing path
    // std::cout << "Path: ";
    // for(auto node : path){
    //     std::cout << node;
    // }
    // std::cout << std::endl;

    SquareGrid grid = make_diagram1();
    Pos goal;
    auto parents = BreadthFirstSearch(grid, goal);
    draw_grid(grid, 2);
    
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