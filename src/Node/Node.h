#ifndef NODE_H
#define NODE_H

#include <cstddef>
#include <functional>


namespace NODE {

    struct Pos
    {
        unsigned int x;
        unsigned int y;

        bool operator==(const Pos &other) const{ 

            return x == other.x && y == other.x; 
        }

    };

    // // specialized hash function for unordered_map keys
    // struct hash_fn
    // {
    //     std::size_t operator() (const NODE::Pos &pos) const
    //     {
    //         std::size_t h1 = std::hash<unsigned int>()(pos.x);
    //         std::size_t h2 = std::hash<unsigned int>()(pos.y);

    //         return h1 ^ h2;
    //     }
    // };

}

class Node
{
    private:
        NODE::Pos position;
    public:
        Node();
        Node(unsigned int, unsigned int);
        ~Node();
        NODE::Pos GetPos();
};

#endif