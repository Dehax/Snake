#pragma once

#include <cstdlib>

enum Direction
{
    Up = 0,
    Right = 1,
    Down = 2,
    Left = 3
};


struct Point
{
public:
    Point(int x, int y);
    ~Point();

    bool operator==(Point p);

    int X;
    int Y;
};


struct Rect
{
public:
    Rect(int x, int y, int width, int height);

    int GetLeft();
    int GetTop();
    int GetRight();
    int GetBottom();

private:
    int m_x;
    int m_y;
    int m_width;
    int m_height;
};


class Random
{
public:
    Random();
    ~Random();

    int Next(int maxValue);
    int Next(int minValue, int maxValue);
private:

};
