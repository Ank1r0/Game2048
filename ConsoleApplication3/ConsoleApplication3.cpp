#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <string>

using namespace std;
typedef unsigned char index;

#define SIZE 4

struct game
{
	char board[4][4];
	int score;

	struct record
	{
		string name;
		int score;

		record(string name, int score)
		{
			this->name = name;
			this->score = score;
		}
	};

	game()
	{
		srand(time(0));
		for (int i = 0; i < SIZE; ++i)
		{
			for (int j = 0; j < SIZE; ++j)
			{
				board[i][j] = ' ';
			}
		}
		score = 0;
	}

	void print_tablet()
	{
		for (int i = 0; i < SIZE; ++i)
		{
			printf("+---+---+---+---+\n|");
			for (int j = 0; j < SIZE; ++j)
			{
				printf(" %c |", board[i][j]);
			}
			printf("\n");
		}
		printf("+---+---+---+---+\n");
	}

	bool add_random_tile()
	{
		bool isFree = false;

		for (int i = 0; i < 16; ++i)
		{
			if (board[i / 4][i % 4] == ' ')
			{
				isFree = true;
				break;
			}
		}
		if (!isFree) return 0;

		int r_t;
		do
		{
			r_t = rand() % 16;
		} while (board[r_t % 4][r_t / 4] != ' ');

		board[r_t % 4][r_t / 4] = 'A';
		return 1;
	}

	bool update(char dirc)
	{
		bool wasMoving = false;
		if (dirc == 'a')
		{
			for (int i = 0; i < SIZE; ++i)
			{
				for (int j = 1; j < SIZE; ++j)
				{
					if (board[i][j] != ' ')
					{
						char k = j;
						while (k > 0 && board[i][k - 1] == ' ') --k;
						if (k != 0 && board[i][k - 1] == board[i][j])
						{
							++board[i][k - 1];
							score += pow(2, board[i][k - 1] - ('A' - 1));
							board[i][j] = ' ';
							wasMoving = true;
						}
						if (k != j)//См
						{
							board[i][k] = board[i][j];
							board[i][j] = ' ';
							wasMoving = true;
						}
					}
				}
			}
			return wasMoving;
		}

		if (dirc == 'd')
		{
			for (int i = SIZE - 1; i >= 0; --i)
			{
				for (int j = SIZE - 2; j >= 0; --j)
				{
					if (board[i][j] != ' ')
					{
						char k = j;
						while (k < SIZE - 1 && board[i][k + 1] == ' ') ++k;
						if (k != SIZE - 1 && board[i][k + 1] == board[i][j])
						{
							++board[i][k + 1];
							score += pow(2, board[i][k + 1] - ('A' - 1));
							board[i][j] = ' ';
							wasMoving = true;
						}
						if (k != j)
						{
							board[i][k] = board[i][j];
							board[i][j] = ' ';
							wasMoving = true;
						}
					}
				}
			}
			return wasMoving;
		}

		if (dirc == 'w')
		{
			for (index c = 0; c < SIZE; ++c)
			{
				for (index r = 1; r < SIZE; ++r)
				{
					if (board[r][c] == ' ') continue;
					index k = r;
					while (k > 0 && board[k - 1][c] == ' ') --k;
					if (k != 0 && board[k - 1][c] == board[r][c])
					{
						++board[k - 1][c];
						score += (int)pow(2, board[k - 1][c] - 'A' + 1);
						board[r][c] = ' ';
						wasMoving = true;
					}
					else if (k != r)
					{
						board[k][c] = board[r][c];
						board[r][c] = ' ';
						wasMoving = true;
					}
				}
			}
			return wasMoving;
		}

		if (dirc == 's')
		{

			for (index c = 0; c < SIZE; ++c)// Пройтись нужно по всех колонках
			{
				for (char r = SIZE - 2; r != -1; --r)// Последнюю линию не нужно проверять так как нельзя ни сдвинуть ни слиять
				{
					if (board[r][c] == ' ') continue;
					index k = r;
					while (k < SIZE - 1 && board[k + 1][c] == ' ') ++k;//Сдвинуть К до первого символа
					if (k != SIZE - 1 && board[k + 1][c] == board[r][c])//Если символ одинаковый то сделать слияние
					{
						++board[k + 1][c];
						score += (int)pow(2, board[k + 1][c] - 'A' + 1);
						board[r][c] = ' ';
						wasMoving = true;
					}
					else if (k != r)//Если символ другой то заменить на свободное место в игровой таблице есил мы его нашли
					{
						board[k][c] = board[r][c];
						board[r][c] = ' ';
						wasMoving = true;
					}
				}
			}
			return wasMoving;
		}
		return wasMoving;
	}

	bool is_move_possible()
	{
		for (int i = 0; i < SIZE; ++i)
		{
			for (int j = 0; j < SIZE - 1; ++j)
			{
				if (board[i][j] == board[i][j + 1] || board[j][i] == board[j + 1][i])
					return true;
			}
		}
		return false;
	}

	bool is_game_won()
	{

		for (int i = 0; i < SIZE; ++i)
		{
			for (int j = 0; j < SIZE; ++j)
			{
				if (board[i][j] == 'K')
					return 1;
			}
		}
		return 0;
	}

	void new_game()
	{
		for (int i = 0; i < SIZE; ++i)
		{
			for (int j = 0; j < SIZE; ++j)
			{
				board[i][j] = ' ';
			}
		}
		score = 0;
		this->add_random_tile();
		this->add_random_tile();
	}

	void top(const char* filename)
	{
		vector<record> table; //1......10
		string name;
		int score;
		ifstream ifs(filename);
		if (ifs.is_open())
		{
			while (1)
			{
				ifs >> name;
				ifs >> score;
				if (ifs.eof()) break;
				table.emplace_back(name, score);
			}
		}
		ifs.close();
		if (table.size() != 10 || table.back().score < this->score)
		{
			cout << "Enter your name: ";
			cin >> name;
			table.emplace_back(name, this->score);
			int i = table.size() - 1;
			while (i != 0 && table[i].score > table[i - 1].score)
			{
				record temp = table[i];
				table[i] = table[i - 1];
				table[i - 1] = temp;
				--i;
			}
		}
		ofstream ofs(filename);
		for (size_t i = 0; i < table.size(); ++i)
		{
			if (i == 10) break;
			ofs << table[i].name << ' ' << table[i].score << '\n';
		}
		ofs.close();
	}

	bool gameover()
	{
		char input = 0;
		printf("Your score is: %d\n", score);
		top("data.tbl");
		printf("Do you want to continue?\nFor continue press R. If you want exit press Esc\n");

		while (1)
		{
			input = _getch();
			if (input == 'r' || input == 'R')
			{
				return 1;
			}
			if (input == 27)
			{
				return 0;
			}
			printf("Please enter ONLY english 'R' or Esc\n");
		}
	}
};


void main()
{
	// string s;
	//
	//
	//
	// cout << s << '\n';
	//
	//
	// getchar();
	// exit(0);
	game a;
	char input = 0;

	a.new_game();
	a.print_tablet();
	printf("If you dont know how to play press english 'I'\n");
	while (1)
	{
		input = _getch();
		if (input == 'P')
		{
			a.board[2][2] = 'K';
		}
		if (input == 'I' || input == 'i')
		{
			printf("For replace numbers UP use 'W'\nFor replace numbers DOWN use 'S'\nFor replace numbers LEFT use 'A'\nFor replace numbers RIGHT use 'D'\nFor EXIT press Esc\n");
			system("pause");
		}
		if (input == 27)
		{
			break;
		}
		if (a.update(input))
		{
			if (a.is_game_won())
			{
				printf("You won\n");
				if (!a.gameover())
				{
					return;
				}
				system("cls");
				a.new_game();
				a.print_tablet();
			}
			if (!a.add_random_tile())
			{
				printf("Movi is - %d", a.is_move_possible());
				bool b = a.is_move_possible();
				if (!b)
				{
					printf("Game over\n");

					if (a.gameover())
					{
						system("cls");
						a.new_game();
						a.print_tablet();
					}
					else
					{
						return;
					}
				}
			}
		}
		system("cls");
		a.print_tablet();
		printf("score: %d\n", a.score);
	}
}