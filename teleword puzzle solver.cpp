#include "pch.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <windows.h>
#include<chrono>
#include<conio.h>
using namespace std::chrono;
using namespace std;

char name[500];
char name2d[15][16];
int w[] = { -1,-1,-1,0,0,1,1,1 };
int z[] = { -1,0,1,-1,1,-1,0,1 };
int array_char_find(char grid[15][16], int row, int column, string word) {

	if (grid[row][column] != word[0]) {
		return 10;
	}
	int length = word.length();
	for (int direction = 0; direction < 8; direction++)
	{
		int k = 0;
		int rowdirection = row + w[direction];
		int columndirection = column + z[direction];
		for (k = 1; k < length; k++)
		{
			if (rowdirection >= 15 || rowdirection < 0 || columndirection >= 15 || columndirection < 0)
				break;
			if (grid[rowdirection][columndirection] != word[k])
				break;
			rowdirection = rowdirection + w[direction];
			columndirection = columndirection + z[direction];
		}
		if (k == length)
			return direction;
	}
	return 10;
}


void search_word(char grid[15][16], string word, int Amb[][15])
{
	int Direction = 0;
	int row1, column1;
	for (int row = 0; row < 15; row++)
	{
		for (int column = 0; column < 15; column++)
		{
			Direction = array_char_find(grid, row, column, word);
			if (Direction != 10) {
				row1 = row;
				column1 = column;
				if (Direction == 0) {
					for (int i = 0; i < word.length(); i++)
					{
						Amb[row1][column1]++;
						row1--;
						column1--;
					}
				}
				if (Direction == 1) {
					for (int i = 0; i < word.length(); i++)
					{
						Amb[row1][column1]++;
						row1--;
					}
				}
				if (Direction == 2) {
					for (int i = 0; i < word.length(); i++)
					{
						Amb[row1][column1]++;
						row1--;
						column1++;
					}
				}
				if (Direction == 3) {
					for (int i = 0; i < word.length(); i++)
					{
						Amb[row1][column1]++;
						column1--;
					}
				}
				if (Direction == 4) {
					for (int i = 0; i < word.length(); i++)
					{
						Amb[row1][column1]++;
						column1++;
					}
				}
				if (Direction == 5) {
					for (int i = 0; i < word.length(); i++)
					{
						Amb[row1][column1]++;
						row1++;
						column1--;
					}
				}
				if (Direction == 6) {
					for (int i = 0; i < word.length(); i++)
					{
						Amb[row1][column1]++;
						row1++;
					}
				}
				if (Direction == 7) {
					for (int i = 0; i < word.length(); i++)
					{
						Amb[row1][column1]++;
						row1++;
						column1++;
					}
				}

			}
		}
	}
}
void gotoxy(int xpos, int ypos, int col, char ch)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos; scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
	HANDLE  screen = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(screen, col);
	DWORD useless;
	WriteConsole(screen, &ch, 1, (LPDWORD)&useless, NULL);
	SetConsoleTextAttribute(screen, 15);
	SMALL_RECT windowSize = { 0, 0, 100, 100 };
	SetConsoleWindowInfo(screen, TRUE, &windowSize);
}

int main()
{
	int avg_word = 0;
	auto start = high_resolution_clock::now();
	int longest_word = 0, long_word = 0, smallest_word = 10, small_word = 0;
	char word[100][16];
	int Amb[15][15] = { 0 };
	int row = 0, col = 0;
	ifstream fin("C:\\Users\\aasha\\Desktop\\teleword_10.txt");
	if (fin.fail()) { cout << "could not open" << endl; }
	else
	{
		char buff[500];
		for (int i = 0; i < 15; i++)
		{
			fin.getline(buff, 500);
			int j = 0, k = 0;
			while (buff[k] != '\0') {
				if (buff[k] != ' ') {
					name2d[i][j] = buff[k];
					j++;
				}
				k++;
			}
			name2d[i][j] = '\0';
		}
		fin.getline(buff, 500);
		fin.getline(buff, 500);
		int k = 0;
		while (buff[k] != '\0') {
			if (buff[k] != ',' && buff[k] != ' ' && buff[k] != '.') {
				word[row][col] = toupper(buff[k]);
				col++;
			}
			if (buff[k] == ',' || buff[k] == '.') {
				word[row][col] = '\0';
				if (longest_word < col) { longest_word = col; long_word = row; }
				if (smallest_word > col) { smallest_word = col; small_word = row; }
				avg_word = avg_word + col;
				row++;
				col = 0;
			}
			k++;
		}
	}
	avg_word = avg_word / (row - 1);
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			cout << name2d[i][j] << " ";
		}
		cout << endl;
	}
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < 15 && word[i][j] != '\0'; j++) {
			cout << word[i][j];
		}
		cout << ", ";
		if (i % 8 == 0 && i != 0) { cout << endl; }
	}
	cout << endl << endl;
	cout << "press s to solve puzzle at once" << endl << "press t to solve puzzle step by step " << endl << "press x to print staticts" << endl;
	char spe;
	spe = _getch();
	system("cls");
	if (spe == 't') {
		for (int special = -1; special < row; special++) {
			_getch();
			search_word(name2d, word[special], Amb);
			for (int i = 0; i < 15; i++)
			{
				for (int j = 0, a = 0; j < 30 && a < 15; j++)
				{
					if (j % 2 == 0) {
						if (Amb[i][a] == 0) {
							gotoxy(j, i, 15, name2d[i][a]);
						}

						if (Amb[i][a] == 1) {
							gotoxy(j, i, 14, name2d[i][a]);
						}

						if (Amb[i][a] == 2) {
							gotoxy(j, i, 1, name2d[i][a]);
						}

						if (Amb[i][a] > 2) {
							gotoxy(j, i, 4, name2d[i][a]);
						}
						a++;
					}
					else { gotoxy(j, i, 0, 32); }
				}
			}
			cout << endl;
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < 15 && word[i][j] != '\0'; j++) {
					cout << word[i][j];
				}
				cout << ", ";
				if (i % 8 == 0 && i != 0) { cout << endl; }
			}
		}
		cout << endl << endl;
		cout << "the teleword is =  ";
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 15; j++) {
				if (Amb[i][j] == 0) {
					cout << name2d[i][j];
				}
			}
		}
	}
	int josh = 0;
	int p = 0, q = 0;
	if (spe == 's') {
		for (int l = 0; l < row; l++)
		{
			search_word(name2d, word[l], Amb);
		}

		for (int i = 0; i < 15; i++)
		{
			for (int j = 0, a = 0; j < 30 && a < 15; j++)
			{
				if (j % 2 == 0) {
					if (Amb[i][a] == 0) {
						gotoxy(j, i, 15, name2d[i][a]);
					}

					if (Amb[i][a] == 1) {
						gotoxy(j, i, 14, name2d[i][a]);
					}

					if (Amb[i][a] == 2) {
						gotoxy(j, i, 1, name2d[i][a]);
					}

					if (Amb[i][a] > 2) {
						gotoxy(j, i, 4, name2d[i][a]);
					}
					a++;
				}
				else { gotoxy(j, i, 0, 32); }
			}
		}
		cout << endl;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < 15 && word[i][j] != '\0'; j++) {
				cout << word[i][j];
			}
			cout << ", ";
			if (i % 8 == 0 && i != 0) { cout << endl; }
		}
		cout << endl << endl;
		cout << "the teleword is =  ";
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 15; j++) {
				if (Amb[i][j] == 0) {
					cout << name2d[i][j];
				}
			}
		}
	}
	cout << endl;
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	int jo = 0, q1 = 0;
	if (spe == 'x') {
		int scatter = 0, sac = 0;
		for (int l = 0; l < row; l++)
		{
			search_word(name2d, word[l], Amb);
		}
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0, a = 0; j < 15; j++)
			{
				if (Amb[i][j] == 0) {
					p = p + 0;
					scatter++;
				}

				if (Amb[i][j] == 1) {
					p = p + 1;
				}
				if (Amb[i][j] == 2) {
					p = p + 2;
				}
				if (Amb[i][j] > 2) {
					p = p + 3;
				}
			}
			if (p > q) {
				q = p;
				josh = i;
				p = 0;
			}
			if (scatter >= 1) {
				sac++;
				scatter = 0;
			}
		}
		for (int j = 0; j < 15; j++)
		{
			for (int i = 0, a = 0; i < 15; i++)
			{
				if (Amb[i][j] == 0) {
					p = p + 0;
				}

				if (Amb[i][j] == 1) {
					p = p + 1;
				}

				if (Amb[i][j] == 2) {
					p = p + 2;
				}
				if (Amb[i][j] > 2) {
					p = p + 3;
				}
			}
			if (p > q1) {
				q1 = p;
				jo = j;
				p = 0;
			}
		}
		cout << "word statistics are :" << endl;
		cout << "Time taken by program: "
			<< duration.count() << " microseconds" << endl;
		cout << "the longest word is  ";
		for (int i = 0; i < 15 && word[long_word][i] != '\0'; i++) {
			cout << word[long_word][i];
		}
		cout << endl;
		cout << "the shortest word is  ";
		for (int i = 0; i < 15 && word[small_word][i] != '\0'; i++) {
			cout << word[small_word][i];
		}
		cout << endl;
		cout << "longest word length is " << longest_word << endl << "shortest word length is " << smallest_word << endl << "average word length is " << avg_word << endl;
		cout << "the teleword scatter is  " << sac << endl;
		cout << "heaviest row is " << josh + 1 << "th row" << endl;
		cout << "heaviest column is " << jo + 1 << "th cloumn" << endl;
	}
	system("pause");
	return 0;
}
