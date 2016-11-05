#include "Game.h"


Game::Game(int fieldWidth, int fieldHeight) : m_fieldWidth(fieldWidth), m_fieldHeight(fieldHeight)
{
    m_field = new Field(m_fieldWidth, m_fieldHeight);

    ResetGame();

    SetSpeed(INIT_SPEED);
}


Game::~Game()
{
    if (m_field) {
        delete m_field;
        m_field = NULL;
    }
}


void Game::ResetGame()
{
    m_gameState = InProcess;

    Random random;
    Point head = Point(random.Next(m_fieldWidth / 3, m_fieldWidth - m_fieldWidth / 3), random.Next(m_fieldHeight / 3, m_fieldHeight - m_fieldWidth / 3));

    int x, y;
    Direction direction = (Direction)random.Next(3);

    switch (direction) {
        case Up:
            // Up
            x = head.X;
            y = head.Y - (INIT_SNAKE_SIZE - 1);
            break;
        case Right:
            // Right
            x = head.X + (INIT_SNAKE_SIZE - 1);
            y = head.Y;
            break;
        case Down:
            // Down
            x = head.X;
            y = head.Y + (INIT_SNAKE_SIZE - 1);
            break;
        case Left:
            // Left
            x = head.X - (INIT_SNAKE_SIZE - 1);
            y = head.Y;
            break;
    }

    m_snake = new Snake(head, Point(x, y));
    m_snake->Move(direction);

    m_food = new Food(random.Next(m_fieldWidth), random.Next(m_fieldHeight));
}


Field::CellType Game::GetCell(int x, int y)
{
    return m_field->GetCell(x, y);
}


void Game::DoStep()
{
    // Clears old field data
    ClearOldData();

    // Move snake
    m_snake->DoStep();

    CheckForCollisions();

    // Can finish game
    CheckForGameState();

    // Fills field data
    FillData();
}


void Game::CheckForGameState()
{
    if (m_gameState == Finished) {
        // GameOver
        exit(0);
    }
}


void Game::CheckForCollisions()
{
    if (m_snake->GetHead().X < 0) {
        // Boom! Snake collided with wall. Game over!
        //_gameState = GameState.Finished;

        // Or just let snake to go throw the wall? :)
        int x = m_fieldWidth - 1;
        int y = m_snake->GetHead().Y;
        m_snake->SetHead(Point(x, y));
    } else if (m_snake->GetHead().X >= m_fieldWidth) {
        int x = 0;
        int y = m_snake->GetHead().Y;
        m_snake->SetHead(Point(x, y));
    } else if (m_snake->GetHead().Y < 0) {
        int x = m_snake->GetHead().X;
        int y = m_fieldHeight - 1;
        m_snake->SetHead(Point(x, y));
    } else if (m_snake->GetHead().Y >= m_fieldHeight) {
        int x = m_snake->GetHead().X;
        int y = 0;
        m_snake->SetHead(Point(x, y));
    }

    // If the snake has eaten food
    if (m_snake->GetHead() == m_food->Position) {
        // Increase snake length
        m_snake->Eat(m_food->Position);

        // WARNING: Is optimal to create new Random on each game step?
        Random random = Random();
        // WARNING: Need to check randomized position to prevent collides
        m_food->Position = Point(random.Next(m_fieldWidth), random.Next(m_fieldHeight));
    }
}


void Game::ClearOldData()
{
    // Clear old snake tail data
    Point tailPoint = m_snake->GetTail();
    m_field->GetCell()[tailPoint.X][tailPoint.Y] = Field::CellType::Empty;
}


void Game::FillData()
{
    // Fill snake position
    vector<Point> *points = m_snake->GetPoints();
    for (unsigned int i = 0; i < points->size(); i++) {
        Point point = (*points)[i];
        m_field->GetCell()[point.X][point.Y] = Field::CellType::Snake;
    }

    // Fill food position
    m_field->GetCell()[m_food->Position.X][m_food->Position.Y] = Field::CellType::Food;
}


void Game::MoveSnake(Direction direction)
{
    switch (direction) {
        case Up:
            if (m_snake->GetCurrentDirection() != Down) {
                m_snake->Move(direction);
            }
            break;
        case Right:
            if (m_snake->GetCurrentDirection() != Left) {
                m_snake->Move(direction);
            }
            break;
        case Down:
            if (m_snake->GetCurrentDirection() != Up) {
                m_snake->Move(direction);
            }
            break;
        case Left:
            if (m_snake->GetCurrentDirection() != Right) {
                m_snake->Move(direction);
            }
            break;
        default:
            break;
    }
}


Rect Game::GetBounds()
{
    int top, right, down, left;

    Rect snake = m_snake->GetBounds();

    top = (int)snake.GetTop();
    right = (int)snake.GetRight();
    down = (int)snake.GetBottom();
    left = (int)snake.GetLeft();

    return Rect(left, top, right - left + 1, down - top + 1);
}


int Game::GetSpeed()
{
    return m_speed;
}


void Game::SetSpeed(int speed)
{
    if (speed <= 0) {
        m_speed = 1;
    } else if (speed > 10) {
        m_speed = 10;
    } else {
        m_speed = speed;
    }
}
