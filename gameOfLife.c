#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int fps = 30;
const int screenWidth = 800;
const int screenHeight = 450;
const int cellSize = 8;
const int cols = screenWidth / cellSize;
const int rows = screenHeight / cellSize;
const Vector2 startPos = {screenWidth * .5 - (cols * cellSize) * 0.5,
						  screenHeight * .5 - (rows * cellSize) * 0.5};

int mod(int x, int y)
{
	return (x % y + y) % y;
}
int neighbours(int i, int j, int **board)
{
	int n = 0;
	for (int l = i - 1; l <= i + 1; l++)
	{
		for (int m = j - 1; m <= j + 1; m++)
		{
			if (!((i == l) && (j == m)) && board[mod(l, rows)][mod(m, cols)])
			{
				n++;
			}
		}
	}
	return n;
}

void render(int **board)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (board[i][j])
				DrawRectangleV((Vector2){startPos.x + j * cellSize,
										 startPos.y + i * cellSize},
							   (Vector2){cellSize, cellSize},
							   RAYWHITE);
		}
	}
}
void compute_next_state(int **board, int **next_board)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			int n = neighbours(i, j, board);
			if (board[i][j])
			{
				next_board[i][j] = (n == 2 || n == 3);
			}
			else
			{
				next_board[i][j] = (n == 3);
			}
		}
	}
}

void push_next_state(int **board, int **next_board)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			board[i][j] = next_board[i][j];
		}
	}
}

void randomInitState(__uint8_t percentage, int **board)
{
	if (percentage > 100)
		percentage = 100;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (random() % 100 < percentage)
			{
				board[i][j] = true;
			}
		}
	}
}
int main()
{
	int **board = malloc(rows * sizeof(int *));
	int **next_board = malloc(rows * sizeof(int *));
	for (int i = 0; i < rows; i++)
	{
		board[i] = (int *)calloc(cols, sizeof(int));
		next_board[i] = (int *)calloc(cols, sizeof(int));
	}
	// int board[rows][cols];
	// int next_board[rows][cols];
	// memset(board, 0, rows * cols * sizeof(int));
	// memset(next_board, 0, rows * cols * sizeof(int));

	randomInitState(10, board);

	InitWindow(screenWidth, screenHeight, "Game Of Life");
	SetTargetFPS(fps);

	while (!WindowShouldClose())
	{

		BeginDrawing();
		ClearBackground(BLACK);
		render(board);
		compute_next_state(board, next_board);
		push_next_state(board, next_board);
		EndDrawing();
	}

	for (int i = 0; i < rows; i++)
	{
		free(board[i]);
		free(next_board[i]);
	}
	CloseWindow();
}
