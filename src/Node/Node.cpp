#include "Node.h"

NODE::Pos Node::GetPos(){
    return this->position;
}


Node::Node(){
    position.x = 0;
    position.y = 0;
}

Node::Node(unsigned int pos_x, unsigned int pos_y)
{
    position.x = pos_x;
    position.y = pos_y;
}

Node::~Node()
{
}