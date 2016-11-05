#include "Util.h"
#include "Game.h"
#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <thread>

using namespace std;

const int FIELD_SIZE = 25;
Rect FULL_SCREEN_RECT = Rect(0, 0, FIELD_SIZE, FIELD_SIZE);

Game *m_game;

// Windows API
HWND consoleHWND = GetConsoleWindow();
HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);


void gotoxy(int x, int y)
{
    COORD pos = { (short)x, (short)y };
    SetConsoleCursorPosition(consoleHandle, pos);
}


void SetWindowSize(int width, int height)
{
    CONSOLE_SCREEN_BUFFER_INFO SBInfo;
    COORD NewSBSize;
    int Status;

    GetConsoleScreenBufferInfo(consoleHandle, &SBInfo);
    NewSBSize.X = SBInfo.dwSize.X - 2;
    NewSBSize.Y = SBInfo.dwSize.Y;

    Status = SetConsoleScreenBufferSize(consoleHandle, NewSBSize);
    if (Status == 0) {
        Status = GetLastError();
        cout << "SetConsoleScreenBufferSize() failed! Reason : " << Status << endl;
        exit(Status);
    }
    //=======================================
    //COORD coord;
    //coord.X = width;
    //coord.Y = height;

    //SMALL_RECT Rect;
    //Rect.Top = 0;
    //Rect.Left = 0;
    //Rect.Bottom = height - 1;
    //Rect.Right = width - 1;

    //SetConsoleScreenBufferSize(consoleHandle, coord);            // Set Buffer Size 
    //SetConsoleWindowInfo(consoleHandle, TRUE, &Rect);            // Set Window Size 
}


void DrawField(Rect rect)
{
    int top = rect.GetTop(), right = rect.GetRight(), down = rect.GetBottom(), left = rect.GetLeft();

    if (top < 0)
        top = 0;

    if (right >= FIELD_SIZE)
        right = FIELD_SIZE;

    if (down >= FIELD_SIZE)
        down = FIELD_SIZE;

    if (left < 0)
        left = 0;

    for (int y = top; y < down; y++) {
        for (int x = left; x < right; x++) {
            //Console.SetCursorPosition(x, y);
            //gotoxy(x, y);

            TCHAR currentChar = ' ';

            switch (m_game->GetCell(x, y)) {
                case Field::CellType::Empty:
                    currentChar = ' ';
                    break;
                case Field::CellType::Snake:
                    currentChar = 'O';
                    //currentChar = (char)0x2588;
                    break;
                case Field::CellType::Food:
                    currentChar = '@';
                    break;
            }

            if (x != right - 1 || y != down - 1) {
                //Console.Write(currentChar);
                //cout << currentChar;
                DWORD charsWritten;
                WriteConsoleOutputCharacterW(consoleHandle, &currentChar, 1, { (short)x, (short)y }, &charsWritten);
            }
        }
    }
}


void _timer_Elapsed()
{
    while (true) {
        m_game->DoStep();
        //DrawField(_game.GetBounds());
        DrawField(FULL_SCREEN_RECT);

        //Thread.Sleep(1000 / m_game->GetSpeed());
        this_thread::sleep_for(chrono::milliseconds(1000 / m_game->GetSpeed()));
    }
}


void StartGame()
{
    m_game = new Game(FIELD_SIZE, FIELD_SIZE);
    //_timer = new Timer(_timer_Elapsed, null, 0, 1000 / _game.Speed);
    //Thread gameThread = new Thread(new ThreadStart(_timer_Elapsed));
    thread *gameThread = new thread(_timer_Elapsed);
    //gameThread.Start();
}


int main()
{
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = FALSE;
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
    ////Console.SetWindowSize(FIELD_SIZE, FIELD_SIZE);
    ////Console.SetBufferSize(FIELD_SIZE, FIELD_SIZE);
    //RECT consoleRect;
    //GetWindowRect(consoleHWND, &consoleRect);
    ////MoveWindow(consoleHWND, consoleRect.left, consoleRect.top, consoleRect.left + FIELD_SIZE, consoleRect.top + FIELD_SIZE, TRUE);
    //SMALL_RECT consoleWindowRect = { 0, 0, FIELD_SIZE, FIELD_SIZE };
    //SetConsoleWindowInfo(consoleHandle, TRUE, &consoleWindowRect);
    ////SetConsoleScreenBufferSize(consoleHandle, { FIELD_SIZE, FIELD_SIZE });

    //SetWindowSize(FIELD_SIZE, FIELD_SIZE);

    StartGame();

    while (true) {
        int key = _getch();
        switch (key) {
            case 72:
                m_game->MoveSnake(Up);
                break;
            case 77:
                m_game->MoveSnake(Right);
                break;
            case 80:
                m_game->MoveSnake(Down);
                break;
            case 75:
                m_game->MoveSnake(Left);
                break;
            case '+':
                m_game->SetSpeed(m_game->GetSpeed() + 1);
                break;
            case '-':
                m_game->SetSpeed(m_game->GetSpeed() - 1);
                break;
            default:
                break;
        }
    }

    return 0;
}
