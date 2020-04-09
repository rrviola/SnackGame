// ConsoleApplication-Snake.cpp : Define o ponto de entrada para a aplicação de console.
// Created by Rodrigo Ribeiro Viola

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;
bool gameOver, resetGame, gameEnd;
const int width = 50;
const int height = 15;
int x, y, fruitX, fruitY, score, speed, gameGhost, gameReset, iScore;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;
char namePlayer[20];

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

void Setup()
{
	ShowConsoleCursor(false);
	system("mode 54,21");
	system("Refresh 0.4");
	gameOver = false;
	gameEnd = false;
	resetGame = false;
	speed = 100;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
	iScore = 1;
	nTail = 0;
}

void SetupReset()
{
	resetGame = false;
	gameEnd = false;
	speed = 100;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
	iScore = 1;
	nTail = 0;
}

void Intro()
{
	FILE *fileRead;
	fileRead = fopen("record.txt", "r");
	if (fileRead != NULL)
	{
		char *buffer;
		size_t result;

		// obtain file size:
		fseek(fileRead, 0, SEEK_END);
		int Size = ftell(fileRead);
		rewind(fileRead);

		// allocate memory to contain the whole file:
		buffer = (char*)malloc(sizeof(char)*Size);
		if (buffer == NULL)
			fputs("Memory error", stderr);
		
		// copy the file into the buffer:
		result = fread(buffer, 1, Size, fileRead);
		if (result != Size)
			fputs("Reading error", stderr);
	
		system("cls");
		for (int i = 0; i < width + 2; i++)
			cout << "#";
		cout << endl;
		cout << "\n \t \t CREATED BY \n \t    RODRIGO RIBEIRO VIOLA \n \n \t \t SNAKE GAME ++ \n";
		cout << endl;
		cout << "\nRecord: "; 
		for (int i = 0; i < 12; i++)
			cout << buffer[i];
		
		cout << "\n\n\t GAME PLAY MODE GHOST: (Y/N) \t";
		cout << endl;
		for (int i = 0; i < width + 2; i++)
			cout << "#";
		cout << endl;
		char GhostMode;
		cin >> GhostMode;
		gameGhost = GhostMode;

		system("cls");
		for (int i = 0; i < width + 2; i++)
			cout << "#";
		cout << endl;
		cout << "\n \t \t CREATED BY \n \t    RODRIGO RIBEIRO VIOLA \n \n \t \t SNAKE GAME ++ \n" << endl;
		cout << "\nRecord: ";
		for (int i = 0; i < 12; i++)
			cout << buffer[i];
		cout << "\n\n\t YOUR NAME: \t";
		cin >> namePlayer;
		system("cls");
		for (int i = 0; i < width + 2; i++)
			cout << "#";
		cout << endl;
		//cout << "\n \t \t CREATED BY \n \t    RODRIGO RIBEIRO VIOLA \n \n" << endl;
		cout << "\n\n\t\t INSTRUTIONS: \n\n\n\n\t\t   UP = 'W' \n \n \t LEFT = 'A' \t    RIGHT = 'D' \n\n\t\t   DOW = 'S' \n\n\n\n\t EXIT = 'X' \n\t RESET = 'R' \n\n" << endl;
		//namePlayer = strupr(nameP) || toupper(nameP) - conversão maíusculas
		
		Beep(510, 100); Sleep(350);
		Beep(380, 100); Sleep(300);
		Beep(320, 100); Sleep(400);
		Beep(440, 100); Sleep(200);
		Beep(480, 80); Sleep(230);
		Beep(450, 100); Sleep(50);
		Beep(430, 100); Sleep(200);
		Beep(380, 100); Sleep(100);
		Beep(660, 80); Sleep(100);
		Beep(760, 50); Sleep(50);
		Beep(860, 100); Sleep(200);
		Beep(700, 80); Sleep(50);
		Beep(760, 50); Sleep(250);
		Beep(660, 80); Sleep(250);
		Beep(520, 80); Sleep(100);
		Beep(580, 80); Sleep(100);
		Beep(480, 80); Sleep(400);

		system("pause");

		// terminate	
		fclose(fileRead);
		free(buffer);	
		
	}

	else
	{
		system("cls");
		for (int i = 0; i < width + 2; i++)
			cout << "#";
		cout << endl;
		cout << "\n \t \t CREATED BY \n \t    RODRIGO RIBEIRO VIOLA \n \n \t \t SNAKE GAME ++ \n";
		cout << endl;
		cout << "\t GAME PLAY MODE GHOST: (Y/N) \t";
		cout << endl;
		for (int i = 0; i < width + 2; i++)
			cout << "#";
		cout << endl;
		char GhostMode;
		cin >> GhostMode;
		gameGhost = GhostMode;

		system("cls");
		for (int i = 0; i < width + 2; i++)
			cout << "#";
		cout << endl;
		cout << "\n \t \t CREATED BY \n \t    RODRIGO RIBEIRO VIOLA \n \n \t \t SNAKE GAME ++ \n" << endl;
		cout << "\t YOUR NAME: \t";
		cin >> namePlayer;
		
		Beep(510, 100); Sleep(450);
		Beep(380, 100); Sleep(400);
		Beep(320, 100); Sleep(500);
		Beep(440, 100); Sleep(300);
		Beep(480, 80); Sleep(330);
		Beep(450, 100); Sleep(150);
		Beep(430, 100); Sleep(300);
		Beep(380, 100); Sleep(200);
		Beep(660, 80); Sleep(200);
		Beep(760, 50); Sleep(150);
		Beep(860, 100); Sleep(300);
		Beep(700, 80); Sleep(150);
		Beep(760, 50); Sleep(350);
		Beep(660, 80); Sleep(300);
		Beep(520, 80); Sleep(150);
		Beep(580, 80); Sleep(150);
		Beep(480, 80); Sleep(500);
	}
}
	

void Draw()
{
	system("cls");

	cout << "\n   SCORE: " << score << "\tName: " << namePlayer;

	if (gameGhost == 121 || gameGhost == 89)
		cout << "\tGHOST ACTIVED" << "\n" << endl;
	else
		cout << "\tGHOST DESACTIVED" << "\n" << endl;

	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "#";

			if (i == y && j == x)
				cout << "X";
			else if (i == fruitY && j == fruitX)
				cout << "&";
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";

			}

			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;
	
}

void GameOver()
{
	char inGame;
	system("cls");
	Beep(100, 100); Sleep(20);
	Beep(660, 100); Sleep(150);
	Beep(660, 100); Sleep(300);
	Beep(660, 100); Sleep(300);
	Beep(510, 100); Sleep(100);
	Beep(660, 100); Sleep(300);
	Beep(770, 100); Sleep(550);
	Beep(380, 100); Sleep(575);
	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;
	cout << "\n \t \t GAME OVER \n \n";
	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << "\nSCORE: " << score << endl;
	cout << "\n \n \n" << endl;
	cout << " START NEW GAME?: (Y/N) \t";
	cin >> inGame;
	gameReset = 0;
	gameReset = inGame;
	
	if (gameReset == 121 || gameReset == 89)
	{
		gameOver = false;
	}

	else
	{
		gameOver = true;
	}

	system("pause");
}

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
			dir = UP;
			break;
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'r':
			resetGame = true;
			break;
		case 'x':
			gameOver = true;
			break;		
		}
	}

}

void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	default:
		break;
	}

	if (gameGhost == 121 || gameGhost == 89)
	{
		if (x >= width)
			x = 0;
		else if (x < 0)
			x = width - 1;

		if (y >= height)
			y = 0;
		else if (y < 0)
			y = height - 1;
	}
	else
	{
		if (x < 0 || x > width || y < 0 || y > height)
			gameEnd = true;
	}

	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameEnd = true;

	if (x == fruitX && y == fruitY)
	{
		Beep(800, 100); Sleep(5);
		score = score + iScore;
		iScore++;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
		if (speed > 10)
			speed = speed - 1;
	}
}

void Record(char namePlayer[20], int scoreRC)
{
	char rc[20];
	string rcB;
	int readRC;
	FILE *fileRead;
	fileRead = fopen("record.txt", "r");
	if (fileRead == NULL)
	{
		ofstream file("record.txt");
		if (file.is_open())
			{
				file << scoreRC << endl << "\n" << namePlayer << "                  " << endl;
				system("cls");
				for (int i = 0; i < width + 2; i++)
					cout << "#";
				cout << endl;
				cout << "\n \t \t CREATED BY \n \t    RODRIGO RIBEIRO VIOLA \n \n \t \t SNAKE GAME ++ \n";
				cout << endl;
				cout << "\n \t \t NEW RECORD: \t" << namePlayer << "\t" << scoreRC << endl;
				system("pause");
			}
			else
			{
				cout << "FILE CAN NOT OPEN";
			}

	
	}
	else
	{
		fgets(rc, 20, fileRead);
		fclose(fileRead);
		rcB = rc;
		readRC = atoi(rcB.c_str());
		if (scoreRC > readRC)
		{
			ifstream file("record.txt");
			if (file)
			{
				ofstream file("record.txt");
				if (file.is_open())
				{
					file << scoreRC << endl << "\n" << namePlayer << "                  " << endl;
				}
				else
				{
					cout << "FILE CAN NOT OPEN";
				}

			}
			else
			{
				cout << " Excessao";
				system("pause");
			}
			system("cls");
			for (int i = 0; i < width + 2; i++)
				cout << "#";
			cout << endl;
			cout << "\n \t \t CREATED BY \n \t    RODRIGO RIBEIRO VIOLA \n \n \t \t SNAKE GAME ++ \n";
			cout << endl;
			cout << "\n \t \t NEW RECORD: \t" << namePlayer << "\t" << scoreRC << "\n\n" << endl;
			system("pause");
		}
		fclose(fileRead);		
	}	
}

int main()
{
	Setup();
	Intro();

	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(speed);
	
		if (resetGame)
		{
			Record(namePlayer, score);
			SetupReset();
		}

		if (gameEnd)
		{
			Record(namePlayer, score);
			SetupReset();
			GameOver();			
		}
	}	
	return 0;
}

