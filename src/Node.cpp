#include "Node.h"

#include <cmath>

float Node::GetDistance(const Node& other) const {
    return sqrt(pow(this->x_ - other.x_, 2) + pow(this->y_ - other.y_, 2));
}