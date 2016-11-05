using System;

namespace Snake
{
    internal enum GameState
    {
        InProcess,
        Finished
    }

    internal class Game
    {
        const int INIT_SNAKE_SIZE = 2;
        const int INIT_SPEED = 2;

        // Size
        private int _fieldWidth;
        private int _fieldHeight;

        // Data
        private Field _field;
        private Snake _snake;
        private Food _food;

        private GameState _gameState;

        private int _speed;

        internal int Speed
        {
            get
            {
                return _speed;
            }
            set
            {
                if (value <= 0)
                {
                    _speed = 1;
                }
                else
                {
                    _speed = value;
                }
            }
        }

        internal Game(int fieldWidth, int fieldHeight)
        {
            _fieldWidth = fieldWidth;
            _fieldHeight = fieldHeight;

            _field = new Field(_fieldWidth, _fieldHeight);

            ResetGame();

            Speed = INIT_SPEED;
        }

        private void ResetGame()
        {
            _gameState = GameState.InProcess;

            Random random = new Random();
            Point head = new Point(random.Next(_fieldWidth / 3, _fieldWidth - _fieldWidth / 3), random.Next(_fieldHeight / 3, _fieldHeight - _fieldWidth / 3));

            int x, y;
            Direction direction = (Direction)random.Next(3);

            switch (direction)
            {
                case Direction.Up:
                    // Up
                    x = head.X;
                    y = head.Y - (INIT_SNAKE_SIZE - 1);
                    break;
                case Direction.Right:
                    // Right
                    x = head.X + (INIT_SNAKE_SIZE - 1);
                    y = head.Y;
                    break;
                case Direction.Down:
                    // Down
                    x = head.X;
                    y = head.Y + (INIT_SNAKE_SIZE - 1);
                    break;
                case Direction.Left:
                    // Left
                    x = head.X - (INIT_SNAKE_SIZE - 1);
                    y = head.Y;
                    break;
                default:
                    throw new NotImplementedException("Недостижимая область");
            }

            _snake = new Snake(head, new Point(x, y));
            // WARNING: Need to check randomized position to prevent collides
            _food = new Food(random.Next(_fieldWidth), random.Next(_fieldHeight));
        }

        internal Field.CellType GetCell(int x, int y)
        {
            return _field.GetCell(x, y);
        }

        internal void DoStep()
        {
            // Clears old field data
            ClearOldData();

            // Move snake
            _snake.DoStep();

            CheckForCollisions();

            // Can finish game
            CheckForGameState();

            // Fills field data
            FillData();
        }

        private void CheckForGameState()
        {
            if (_gameState == GameState.Finished)
            {
                throw new NotImplementedException("Game Over!");
            }
        }

        /// <summary>
        /// Checks current positions of game objects for collisions with one another.
        /// (Maybe it's not universal (the best) solution)
        /// </summary>
        private void CheckForCollisions()
        {
            if (_snake.Head.X < 0)
            {
                // Boom! Snake collided with wall. Game over!
                //_gameState = GameState.Finished;

                // Or just let snake to go throw the wall? :)
                int x = _fieldWidth - 1;
                int y = _snake.Head.Y;
                _snake.Head = new Point(x, y);
            }
            else if (_snake.Head.X >= _fieldWidth)
            {
                int x = 0;
                int y = _snake.Head.Y;
                _snake.Head = new Point(x, y);
            }
            else if (_snake.Head.Y < 0)
            {
                int x = _snake.Head.X;
                int y = _fieldHeight - 1;
                _snake.Head = new Point(x, y);
            }
            else if (_snake.Head.Y >= _fieldHeight)
            {
                int x = _snake.Head.X;
                int y = 0;
                _snake.Head = new Point(x, y);
            }

            // If the snake has eaten food
            if (_snake.Head == _food.Position)
            {
                // Increase snake length
                _snake.Eat(_food.Position);

                // WARNING: Is optimal to create new Random on each game step?
                Random random = new Random();
                // WARNING: Need to check randomized position to prevent collides
                _food.Position = new Point(random.Next(_fieldWidth), random.Next(_fieldHeight));
            }
        }

        private void ClearOldData()
        {
#if DEBUG
            // Clear all
            _field.ResetField();
#else
            // Clear old snake tail data
            Point tailPoint = _snake.Tail;
            _field.Cell[tailPoint.X, tailPoint.Y] = Field.CellType.Empty;
#endif
        }

        private void FillData()
        {
            // Fill snake position
            foreach (Point point in _snake)
            {
                _field.Cell[point.X, point.Y] = Field.CellType.Snake;
            }

            // Fill food position
            _field.Cell[_food.Position.X, _food.Position.Y] = Field.CellType.Food;
        }

        internal void MoveSnake(Direction direction)
        {
            switch (direction)
            {
                case Direction.Up:
                    if (_snake.CurrentDirection != Direction.Down)
                    {
                        _snake.Move(direction);
                    }
                    break;
                case Direction.Right:
                    if (_snake.CurrentDirection != Direction.Left)
                    {
                        _snake.Move(direction);
                    }
                    break;
                case Direction.Down:
                    if (_snake.CurrentDirection != Direction.Up)
                    {
                        _snake.Move(direction);
                    }
                    break;
                case Direction.Left:
                    if (_snake.CurrentDirection != Direction.Right)
                    {
                        _snake.Move(direction);
                    }
                    break;
                default:
                    break;
            }
        }

        internal Rect GetBounds()
        {
            int top, right, down, left;

            Rect snake = _snake.GetBounds();

            top = (int)snake.Top;
            right = (int)snake.Right;
            down = (int)snake.Bottom;
            left = (int)snake.Left;

            return new Rect(left, top, right - left + 1, down - top + 1);
        }
    }
}
