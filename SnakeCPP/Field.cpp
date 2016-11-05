#include "Field.h"


Field::Field(int fieldWidth, int fieldHeight) : m_fieldWidth(fieldWidth), m_fieldHeight(fieldHeight)
{
    m_field = new CellType *[m_fieldWidth];

    for (int i = 0; i < m_fieldWidth; i++) {
        m_field[i] = new CellType[m_fieldHeight];
    }

    ResetField();
}


void Field::ResetField()
{
    for (int i = 0; i < m_fieldWidth; i++) {
        for (int j = 0; j < m_fieldHeight; j++) {
            m_field[i][j] = Empty;
        }
    }
}


Field::CellType Field::GetCell(int x, int y)
{
    return m_field[x][y];
}


Field::CellType **Field::GetCell()
{
    return m_field;
}


Field::~Field()
{
}
