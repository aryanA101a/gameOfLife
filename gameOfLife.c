#include "raylib.h"
#include<stdio.h>
#include<stdlib.h>
#include <time.h>

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

int main(){
	int board[rows][cols];
	int next_board[rows][cols];
	memset( board, 0,rows*cols*sizeof(int) );
	memset( next_board, 0,rows*cols*sizeof(int) );
	srand(time(NULL));

	
	for(int i=0;i<rows;i++){
				for(int j=0;j<cols;j++){
					if(random()%10<8){
						board[i][j]=true;
					}
				}
	}
	// board[1][2]=true;
	// board[2][3]=true;
	// board[3][1]=true;
	// board[3][2]=true;
	// board[3][3]=true;

	// board[rows/2][5]=true;
	// board[rows/2][6]=true;
	// board[rows/2][7]=true;
	// board[rows/2][8]=true;

	InitWindow(screenWidth,screenHeight,"Game Of Life");
	SetTargetFPS(fps);  

	while(!WindowShouldClose()){
	
		BeginDrawing();
            		ClearBackground(BLACK);
			//render
			for(int i=0;i<rows;i++){
				for(int j=0;j<cols;j++){
					if(board[i][j])
						DrawRectangleV((Vector2){startPos.x+j*cellSize.x,
									startPos.y+i*cellSize.y},
									cellSize,
									RAYWHITE);
				}
			}

			// //compute next state
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

			// //update current state
			for(int i=0;i<rows;i++){
				for(int j=0;j<cols;j++){
					board[i][j]=next_board[i][j];
				}
			}


            		
		EndDrawing();
	}

	CloseWindow();
}
