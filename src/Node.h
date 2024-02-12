#pragma once

class Node {
public:
    Node(const unsigned& N, const float& x, const float& y)
        : N_(N), x_(x), y_(y) {}
    Node() {}
    ~Node() {}

    float GetDistance(const Node& other) const;

    inline const unsigned& GetN_() const { return N_; }
    inline const float& GetX_() const { return x_; }
    inline const float& GetY_() const { return y_; }

    inline bool operator==(const Node& other) const { return this->x_ == other.x_ && this->y_ == other.y_; }

private:
    unsigned N_;
    float x_;
    float y_;
};