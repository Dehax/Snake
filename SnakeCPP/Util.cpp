#include "Util.h"


Point::Point(int x, int y)
{
    X = x;
    Y = y;
}


Point::~Point()
{
}


bool Point::operator==(Point p)
{
    if (X == p.X && Y == p.Y)
        return true;

    return false;
}


Rect::Rect(int x, int y, int width, int height)
{
    m_x = x;
    m_y = y;
    m_width = width;
    m_height = height;
}


int Rect::GetLeft()
{
    return m_x;
}


int Rect::GetTop()
{
    return m_y;
}


int Rect::GetRight()
{
    return m_x + m_width;
}


int Rect::GetBottom()
{
    return m_y + m_height;
}


Random::Random()
{
}


Random::~Random()
{
}


int Random::Next(int maxValue)
{
    return rand() % (maxValue + 1);
}


int Random::Next(int minValue, int maxValue)
{
    return Next(maxValue - minValue) + minValue;
}
