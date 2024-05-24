#include "raylib.h"
#include<stdio.h>
#include<stdlib.h>
#include <string.h>

const int fps=30;
const int screenWidth=800;
const int screenHeight=450;
const Vector2 cellSize={1,1};
const int cols=screenWidth/cellSize.x;
const int rows=screenHeight/cellSize.y;
const Vector2 startPos={screenWidth*.5 - (cols*cellSize.x)*0.5,
			screenHeight*.5 - (rows*cellSize.y)*0.5};



int mod(int x,int y){
	return (x%y+y)%y;
}
int neighbours(int i, int j,int board[][cols]){
	int n=0;
	for (int l=i-1;l<=i+1;l++){
		for (int m=j-1;m<=j+1;m++){
			if(!((i==l) && (j==m)) && board[mod(l,rows)][mod(m,cols)]){
				n++;
			}
		}
	}
	return n;
}

void render(int board[][cols]){
	for(int i=0;i<rows;i++){
				for(int j=0;j<cols;j++){
					if(board[i][j])
						DrawRectangleV((Vector2){startPos.x+j*cellSize.x,
									startPos.y+i*cellSize.y},
									cellSize,
									RAYWHITE);
				}
			}
}
void compute_next_state(int board[][cols],int next_board[][cols]){
	for(int i=0;i<rows;i++){
				for(int j=0;j<cols;j++){
					int n=neighbours(i,j,board);
					if(board[i][j]){
						next_board[i][j]=(n==2 || n==3);
					} else {
						next_board[i][j]=(n==3);
					}
				}
			}
}

void randomInitState(__uint8_t percentage,int board[][cols]){
	if (percentage>100) percentage=100;
	for(int i=0;i<rows;i++){
			for(int j=0;j<cols;j++){
				if(random()%100<percentage){
					board[i][j]=true;
				}
			}
}
}
int main(){
	int board[rows][cols];
	int next_board[rows][cols];
	memset( board, 0,rows*cols*sizeof(int) );
	memset( next_board, 0,rows*cols*sizeof(int) );

	randomInitState(10,board);

	InitWindow(screenWidth,screenHeight,"Game Of Life");
	SetTargetFPS(fps);  

	while(!WindowShouldClose()){
	
		BeginDrawing();
        	ClearBackground(BLACK);	
			render(board);
			compute_next_state(board,next_board);
			memcpy(board,next_board,rows*cols*sizeof(int));
		EndDrawing();
	}
	CloseWindow();
}
