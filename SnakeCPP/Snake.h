#pragma once

#include "Util.h"
#include <vector>

using namespace std;

class Snake
{
public:
    Snake(Point head, Point tail);
    Snake(int headX, int headY, int tailX, int tailY);
    ~Snake();

    void Move(Direction direction);
    void DoStep();
    void Eat(Point foodPoint);

    Rect GetBounds();

    Point GetTail();
    Point GetHead();
    void SetHead(Point point);

    vector<Point> *GetPoints();

    Direction GetCurrentDirection();

private:
    Direction m_direction;

    vector<Point> m_path;

    bool isJustAte; // TODO = false;
};

