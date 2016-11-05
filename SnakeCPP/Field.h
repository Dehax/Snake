#pragma once

class Field
{
public:
    enum CellType
    {
        Empty = 0,
        Snake = 1,
        Food = 2
    };

    Field(int fieldWidth, int fieldHeight);
    ~Field();

    void ResetField();

    CellType GetCell(int x, int y);

    CellType **GetCell();

private:
    // Size
    int m_fieldWidth;
    int m_fieldHeight;

    // Data
    CellType **m_field;
};

