#include "Snake.h"


Snake::Snake(Point head, Point tail) : m_path(), isJustAte(false)
{
    m_path.push_back(head);
    m_path.push_back(tail);
}


Snake::Snake(int headX, int headY, int tailX, int tailY) : m_path(), isJustAte(false)
{
    Point head = Point(headX, headY);
    Point tail = Point(tailX, tailY);

    m_path.push_back(head);
    m_path.push_back(tail);
}


Snake::~Snake()
{
}


void Snake::Move(Direction direction)
{
    m_direction = direction;
}


void Snake::DoStep()
{
    if (isJustAte) {
        isJustAte = false;
        return;
    }

    Point headPoint = m_path[0];

    int x = headPoint.X;
    int y = headPoint.Y;

    switch (m_direction) {
        case Up:
            y -= 1;
            break;
        case Right:
            x += 1;
            break;
        case Down:
            y += 1;
            break;
        case Left:
            x -= 1;
            break;
    }

    Point newHeadPoint = Point(x, y);

    m_path.pop_back();
    m_path.insert(m_path.begin(), newHeadPoint);
}


void Snake::Eat(Point foodPoint)
{
    m_path.insert(m_path.end(), m_path[m_path.size() - 1]);
}


Rect Snake::GetBounds()
{
    Point point = m_path[0];
    int top = point.Y, right = point.X, down = point.Y, left = point.X;

    for (unsigned int i = 1; i < m_path.size(); i++) {
        point = m_path[i];

        if (point.Y < top)
            top = point.Y;

        if (point.X > right)
            right = point.X;

        if (point.Y > down)
            down = point.Y;

        if (point.X < left)
            left = point.X;
    }

    return Rect(left, top, right - left + 1, down - top + 1);
}


Point Snake::GetTail()
{
    return m_path[m_path.size() - 1];
}


Point Snake::GetHead()
{
    return m_path[0];
}

void Snake::SetHead(Point point)
{
    m_path[0] = point;
}

Direction Snake::GetCurrentDirection()
{
    return m_direction;
}


vector<Point> *Snake::GetPoints()
{
    return &m_path;
}
