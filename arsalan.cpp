#include "pch.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <windows.h>
#include <chrono>
#include<conio.h>
using namespace std::chrono;
using namespace std;
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

int x[] = { -1,-1,-1,0,0,1,1,1 };
int y[] = { -1,0,1,-1,1,-1,0,1 };

int scan(char grid[15][16], int row, int column, string word) {
	if (grid[row][column] != word[0]) {
		return 10;
	}
	int length = word.length();
	for (int direction = 0; direction < 8; direction++)
	{
		int k = 0;
		int rowdirection = row + x[direction];
		int columndirection = column + y[direction];
		for (k = 1; k < length; k++)
		{
			if (rowdirection >= 15 || rowdirection < 0 || columndirection >= 15 || columndirection < 0)
				break;
			if (grid[rowdirection][columndirection] != word[k])
				break;
			rowdirection = rowdirection + x[direction];
			columndirection = columndirection + y[direction];
		}

		if (k == length)
			return direction;
	}
	return 10;
}


void wordSearch(char grid[15][16], string word, int appe[][15])
{
	int Direction = 0;
	int row1, column1;
	for (int row = 0; row < 15; row++)
	{
		for (int column = 0; column < 15; column++)
		{
			Direction = scan(grid, row, column, word);
			if (Direction != 10) {

				row1 = row;
				column1 = column;
				if (Direction == 0) {
					int d_back = 0;
					for (size_t i = 0; i < word.length(); i++)
					{
						appe[row1][column1]++;
						row1--;
						column1--;
						d_back++;
					}
				}

				if (Direction == 1) {
					int v_back = 0;

					for (size_t i = 0; i < word.length(); i++)
					{
						appe[row1][column1]++;
						row1--;
						//column1;
						v_back++;
					}
				}
				if (Direction == 2) {
					int d_for = 0;
					for (size_t i = 0; i < word.length(); i++)
					{
						appe[row1][column1]++;
						row1--;
						column1++;
						d_for++;
					}
				}
				if (Direction == 3) {
					int h_back = 0;
					for (size_t i = 0; i < word.length(); i++)
					{
						appe[row1][column1]++;
						//row1;
						column1--;
						h_back++;
					}
				}
				if (Direction == 4) {
					int h_for = 0;
					for (size_t i = 0; i < word.length(); i++)
					{
						appe[row1][column1]++;
						//row1;
						column1++;
						h_for++;
					}
				}
				if (Direction == 5) {
					int	d_back = 0;
					for (size_t i = 0; i < word.length(); i++)
					{
						appe[row1][column1]++;
						row1++;
						column1--;
						d_back++;
					}
				}
				if (Direction == 6) {
					int v_for = 0;
					for (size_t i = 0; i < word.length(); i++)
					{
						appe[row1][column1]++;
						row1++;
						//column1;
						v_for++;
					}
				}
				if (Direction == 7) {
					int d_for = 0;
					for (size_t i = 0; i < word.length(); i++)
					{
						appe[row1][column1]++;
						row1++;
						column1++;
						d_for++;
					}
				}

			}
		}
	}
}

int main()
{
	char alph[15][16];
	char wordlist[100][16];
	int appe[15][15] = { 0 };
	int avg_word = 0;
	auto start = high_resolution_clock::now();
	int longest_word = 0, long_word = 0, smallest_word = 10, small_word = 0;
	int row = 0, col = 0;
	ifstream fin("C:\\Users\\Arsalan\\Desktop\\teleword_1.txt");
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
					alph[i][j] = buff[k];
					j++;
				}
				k++;
			}
			alph[i][j] = '\0';
		}
		fin.getline(buff, 500);
		fin.getline(buff, 500);

		int k = 0;
		while (buff[k] != '\0') {
			if (buff[k] != ',' && buff[k] != ' ' && buff[k] != '.') {
				wordlist[row][col] = toupper(buff[k]);
				col++;
			}
			if (buff[k] == ',' || buff[k] == '.') {
				wordlist[row][col] = '\0';
				if (longest_word < col) { longest_word = col; long_word = row; }
				if (smallest_word > col) { smallest_word = col; small_word = row; }
				avg_word = avg_word + col;
				row++;
				col = 0;
			}
			k++;
		}
	}
	avg_word = avg_word / row;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			cout << alph[i][j] << " ";
		}
		cout << endl;
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < 15 && wordlist[i][j] != '\0'; j++) {
			cout << wordlist[i][j];
		}
		cout << ", ";
		if (i % 8 == 0 && i != 0) { cout << endl; }
	}

	cout << endl;
	cout << "press s to solve puzzle at once" << endl << "press t to solve puzzle step by step " << endl << "press x to print staticts" << endl;
	char key;
	key = _getch();
	system("cls");
	int ref = 0;
	int m = 0, n = 0;
	if (key == 's') {
		for (int d = 0; d < row; d++)
		{
			wordSearch(alph, wordlist[d], appe);
		}

		for (int i = 0; i < 15; i++)
		{
			for (int j = 0, c = 0; j < 30 && c < 15; j++)
			{
				if (j % 2 == 0) {
					if (appe[i][c] == 0) {
						gotoxy(j, i, 15, alph[i][c]);
					}

					if (appe[i][c] == 1) {
						gotoxy(j, i, 14, alph[i][c]);
					}

					if (appe[i][c] == 2) {
						gotoxy(j, i, 1, alph[i][c]);
					}

					if (appe[i][c] > 2) {
						gotoxy(j, i, 4, alph[i][c]);
					}
					c++;
				}
				else { gotoxy(j, i, 0, 32); }


			}

		}

		cout << endl << endl;
		cout << "teleword :";
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 15; j++) {
				if (appe[i][j] == 0) {
					cout << alph[i][j];
				}
			}
		}
	}
	if (key == 't') {
		int f = 0;
		while (f < row) {

			char a = _getch();
			while (_kbhit()) { _getch(); }
			wordSearch(alph, wordlist[f], appe);
			f++;
			for (int i = 0; i < 15; i++)
			{
				for (int j = 0, c = 0; j < 30 && c < 15; j++)
				{
					if (j % 2 == 0) {
						if (appe[i][c] == 0) {
							gotoxy(j, i, 15, alph[i][c]);
						}

						if (appe[i][c] == 1) {
							gotoxy(j, i, 14, alph[i][c]);
						}

						if (appe[i][c] == 2) {
							gotoxy(j, i, 1, alph[i][c]);
						}

						if (appe[i][c] > 2) {
							gotoxy(j, i, 4, alph[i][c]);
						}
						c++;
					}
					else { gotoxy(j, i, 0, 32); }


				}

			}
			cout << endl;
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < 15 && wordlist[i][j] != '\0'; j++) {
					cout << wordlist[i][j];
				}
				cout << ", ";
				if (i % 8 == 0 && i != 0) { cout << endl; }
			}


		}
		cout << endl;
		cout << "teleword :";
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 15; j++) {
				if (appe[i][j] == 0) {
					cout << alph[i][j];
				}
			}
		}



	}


	cout << endl;
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	int j1 = 0, n1 = 0;
	if (key == 'x') {
		for (int d = 0; d < row; d++)
		{
			wordSearch(alph, wordlist[d], appe);
		}
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0, c = 0; j < 30 && c < 15; j++)
			{
				if (j % 2 == 0) {
					if (appe[i][c] == 0) {
						gotoxy(j, i, 15, alph[i][c]);
					}

					if (appe[i][c] == 1) {
						gotoxy(j, i, 14, alph[i][c]);
					}

					if (appe[i][c] == 2) {
						gotoxy(j, i, 1, alph[i][c]);
					}

					if (appe[i][c] > 2) {
						gotoxy(j, i, 4, alph[i][c]);
					}
					c++;
				}
				else { gotoxy(j, i, 0, 32); }


			}



			cout << endl;
			cout << "teleword :";
			for (int i = 0; i < 15; i++) {
				for (int j = 0; j < 15; j++) {
					if (appe[i][j] == 0) {
						cout << alph[i][j];
					}
				}
			}
		}
		int scatter = 0;
		int rwcount = 0;
		for (int d = 0; d < row; d++)
		{
			wordSearch(alph, wordlist[d], appe);
		}
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0, a = 0; j < 15; j++)
			{
				if (appe[i][j] == 0) {
					m = m + 0;
					scatter++;
				}

				if (appe[i][j] == 1) {
					m = m + 1;
				}

				if (appe[i][j] == 2) {
					m = m + 2;
				}

				if (appe[i][j] > 2) {
					m = m + 3;
				}
			}
			if (m > n) {
				n = m;
				ref = i;
				m = 0;
			}
			if (scatter >= 1) {
				rwcount++;
				scatter = 0;
			}
		}
		for (int j = 0; j < 15; j++)
		{
			for (int i = 0, a = 0; i < 15; i++)
			{
				if (appe[i][j] == 0) {
					m = m + 0;
				}

				if (appe[i][j] == 1) {
					m = m + 1;
				}

				if (appe[i][j] == 2) {
					m = m + 2;
				}

				if (appe[i][j] > 2) {
					m = m + 3;
				}
			}
			if (m > n1) {
				n1 = m;
				j1 = j;
				m = 0;
			}

		}


		cout << endl;
		cout << "word statistics are :" << endl;
		cout << "Time to solve: "
			<< duration.count() << " microseconds" << endl;
		cout << endl;
		cout << "Longest word length : " << longest_word << endl << "shortest word length : " << smallest_word << endl << "average word length : " << avg_word << endl;
		cout << "The Teleword scatter :  " << rwcount << endl;
		cout << "Heaviest Row : " << ref + 1 << "th row" << endl;
		cout << "Heaviest Column : " << j1 + 1 << "th cloumn" << endl;

	}
	system("pause");
	return 0;
}


