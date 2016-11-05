#pragma once

#include "Snake.h"
#include "Food.h"
#include "Field.h"

enum GameState
{
    InProcess,
    Finished
};

class Game
{
public:
    Game(int fieldWidth, int fieldHeight);
    ~Game();

    Field::CellType GetCell(int x, int y);
    void DoStep();
    void MoveSnake(Direction direction);
    
    Rect GetBounds();

    int GetSpeed();
    void SetSpeed(int speed);

private:
    void ResetGame();
    void CheckForGameState();
    void CheckForCollisions();
    void ClearOldData();
    void FillData();

    const int INIT_SNAKE_SIZE = 2;
    const int INIT_SPEED = 2;

    int m_fieldWidth;
    int m_fieldHeight;

    Field *m_field;
    Snake *m_snake;
    Food *m_food;

    GameState m_gameState;

    int m_speed;
};
