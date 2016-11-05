using ConsoleExtender;
using System;
using System.Threading;

namespace Snake
{
    internal class Program
    {
        private const int FIELD_SIZE = 25;
        private static readonly Rect FULL_SCREEN_RECT = new Rect(0, 0, FIELD_SIZE, FIELD_SIZE);

        // Data
        private static Game _game;
        //private static Timer _timer;

        static void Main(string[] args)
        {
            Console.SetWindowSize(FIELD_SIZE, FIELD_SIZE);
            Console.SetBufferSize(FIELD_SIZE, FIELD_SIZE);
            Console.CursorVisible = false;
            //Console.CursorSize = 1;

            //#if DEBUG
            //            var fonts = ConsoleHelper.ConsoleFonts;
            //            for (int f = 0; f < fonts.Length; f++)
            //            {
            //                Console.WriteLine("{0}: X={1}, Y={2}", fonts[f].Index, fonts[f].SizeX, fonts[f].SizeY);
            //            }
            //            ConsoleHelper.SetConsoleFont(3);
            //            //ConsoleHelper.SetConsoleIcon(SystemIcons.Information);

            //            Console.WriteLine(Console.InputEncoding);
            //#endif

            StartGame();

            while (true)
            {
                switch (Console.ReadKey(true).Key)
                {
                    case ConsoleKey.UpArrow:
                        _game.MoveSnake(Direction.Up);
                        break;
                    case ConsoleKey.RightArrow:
                        _game.MoveSnake(Direction.Right);
                        break;
                    case ConsoleKey.DownArrow:
                        _game.MoveSnake(Direction.Down);
                        break;
                    case ConsoleKey.LeftArrow:
                        _game.MoveSnake(Direction.Left);
                        break;
                    case ConsoleKey.OemPlus:
                        _game.Speed++;
                        break;
                    case ConsoleKey.OemMinus:
                        _game.Speed--;
                        break;
                    default:
                        break;
                }
            }
        }

        private static void StartGame()
        {
            _game = new Game(FIELD_SIZE, FIELD_SIZE);
            //_timer = new Timer(_timer_Elapsed, null, 0, 1000 / _game.Speed);
            Thread gameThread = new Thread(new ThreadStart(_timer_Elapsed));
            gameThread.Start();
        }

        static void _timer_Elapsed()
        {
            while (true)
            {
                _game.DoStep();
                //DrawField(_game.GetBounds());
                DrawField(FULL_SCREEN_RECT);

                Thread.Sleep(1000 / _game.Speed);
            }
        }

        private static void DrawField(Rect rect)
        {
            int top = (int)rect.Top, right = (int)rect.Right, down = (int)rect.Bottom, left = (int)rect.Left;

            if (top < 0)
                top = 0;

            if (right >= FIELD_SIZE)
                right = FIELD_SIZE;

            if (down >= FIELD_SIZE)
                down = FIELD_SIZE;

            if (left < 0)
                left = 0;

            for (int y = top; y < down; y++)
            {
                for (int x = left; x < right; x++)
                {
                    Console.SetCursorPosition(x, y);

                    char currentChar = ' ';

                    switch (_game.GetCell(x, y))
                    {
                        case Field.CellType.Empty:
                            currentChar = ' ';
                            break;
                        case Field.CellType.Snake:
                            //currentChar = 'O';
                            currentChar = (char)0x2588;
                            break;
                        case Field.CellType.Food:
                            currentChar = '@';
                            break;
                    }

                    if (x != right - 1 || y != down - 1)
                    {
                        Console.Write(currentChar);
                    }
                }
            }
        }
    }
}
