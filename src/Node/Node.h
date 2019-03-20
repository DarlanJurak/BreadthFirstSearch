#ifndef NODE_H
#define NODE_Hs

namespace NODE {

    struct Pos
    {
        unsigned int x;
        unsigned int y;

        bool operator==(const Pos &other) const
        { return (x == other.x
                    && y == other.x);
        }

    };

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