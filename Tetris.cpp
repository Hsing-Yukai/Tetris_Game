#include "stdafx.h"
#include "operation.h"
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>


operation operation_obj;
bool game_over = false;
int speed = 600;
int shift_a = 0, shift_b = 0;
vector<vector<char>> map;
vector<pair<int, int>> block_pos;

void game_setup();
void print_frame();
void get_input();
void judge_elimination();

int main()
{
	game_setup();
	while (!game_over)
	{
		print_frame();
		get_input();
		judge_elimination();
		Sleep(speed / 3);
	}
	cout << "Game Over !";
	return 0;
}

void game_setup()
{
	vector<char> row;
	row.resize(12);
	for (int i = 0; i < 22; i++)
	{
		map.push_back(row);
	}
	for (int a = 0; a < 22; a++)
	{
		for (int b = 0; b < 12; b++)
		{
			if (b == 0 || b == 11 || a == 0 || a == 21)
				map[a][b] = '#';
		}
	}
	srand(time(NULL));
	operation_obj.generate_random();
	operation_obj.change_block_pos(block_pos, map, shift_a, shift_b);
	operation_obj.display_on_map(map, block_pos);
}

void print_frame()
{
	system("cls");
	for (int a = 0; a < 22; a++)
	{
		for (int b = 0; b < 12; b++)
		{
			printf("%c", map[a][b]);
		}
		printf("\n");
	}
}

void get_input() 
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 's':
			shift_a++;
			break;
		case 'a':
			shift_b--;
			break;
		case 'd':
			shift_b++;
			break;
		case 'w':
			operation_obj.call_rotate();
			break;
		default:
			break;
		}
	}
	else
	{
		shift_a++;
		Sleep(speed / 3 * 2);
	}
	operation_obj.change_block_pos(block_pos, map, shift_a, shift_b);
	operation_obj.display_on_map(map, block_pos);
	
}

void judge_elimination()
{
	game_over = operation_obj.attach_left_right(block_pos);
	if (operation_obj.attach_bottom(block_pos, map))
	{
		shift_a = 0;
		shift_b = 0;
		operation_obj.push_to_map(map, block_pos);
		operation_obj.generate_random();
		operation_obj.change_block_pos(block_pos, map, shift_a, shift_b);
		operation_obj.display_on_map(map, block_pos);
	}
	operation_obj.elimination(map);
}
