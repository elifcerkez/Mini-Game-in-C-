#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>

char displayMatrix[20][30];
char placementMatrix[20][30];
char player_position[2];
int R=20, C=30; //size of the matrix 

void prepareDisplayMatrix(int R, int C, char displayMatrix[20][30])
{
	int i,j;
	for(i=0; i<R; i++)
	{
		for(j=0; j<C; j++)
			{
				if (i==0 && j==0)
				displayMatrix[i][j] = 'P';
				else
				displayMatrix[i][j]= -78 ;
			//	printf("%c", displayMatrix[i][j]);
			}
		//	printf("\n");
	
	}
}

void preparePlacementMatrix(char placementMatrix[20][30], int tree_count, int enemy_count)
{
	int i,j,t=0,e=0;

	srand ( time(0) );

	while (t<tree_count)
	{
		
		int tree_index = rand() %600 ;
		
		if (tree_index!=1 && tree_index!=20 && tree_index!=21)
		
		{
			int row_index = tree_index / C;
			int column_index = tree_index % C ;
			
			if(placementMatrix[row_index][column_index]!= 'T')
			{
				placementMatrix[row_index][column_index]= 'T';
				t++;
			}
		
		//	printf("tree index is %d row index is %d and column index is %d. \n" ,tree_index, row_index, column_index);
		}
		
	}
	
		while (e<enemy_count)
	{
		
		int enemy_index = rand() %600 ;
		
		if (enemy_index!=1 && enemy_index!=20 && enemy_index!=21)
		
		{
			int row_index = enemy_index / C;
			int column_index = enemy_index % C ;
			
			if(placementMatrix[row_index][column_index]!= 'T' && 'E')
			{
				placementMatrix[row_index][column_index]= 'E';
				e++;
			}
		
		//	printf("enemy index is %d row index is %d and column index is %d. \n" ,enemy_index, row_index, column_index);
		}
		
	}
	
	for(i=0; i<R; i++)
	{
		for(j=0; j<C; j++)
			{
				if(placementMatrix[i][j]!= 'T' && placementMatrix[i][j]!= 'E')
					placementMatrix[i][j]= ' ';	
			//	printf("%c", placementMatrix[i][j]);	
			}
		//	printf("\n");
	}
}


void prepareTheGame (int R, int C, char displayMatrix[20][30], char placementMatrix[20][30], int tree_count, int enemy_count)
{
	prepareDisplayMatrix(R, C, displayMatrix);
	preparePlacementMatrix(placementMatrix, tree_count, enemy_count);
}


void fightWithTheEnemy(int R, int C, char placementMatrix[20][30], char input, int *enemy_count)
{
	int i= player_position[0], j= player_position[1];
	if (input == 'h' || input == 'H' )
	{
		if(placementMatrix[i+1][j] == 'E')
			{placementMatrix[i+1][j] = ' '; (*enemy_count)--;}
			
		else if (placementMatrix[i][j+1] == 'E') 
			{placementMatrix[i][j+1] = ' '; (*enemy_count)--;}
			
		else if(placementMatrix[i-1][j] == 'E')
			{placementMatrix[i-1][j] = ' '; (*enemy_count)--;}
			
		else if(placementMatrix[i][j-1] == 'E')
			{placementMatrix[i][j-1] = ' '; (*enemy_count)--;}
			
		else if(placementMatrix[i+1][j+1] == 'E')
			{placementMatrix[i+1][j+1] = ' '; (*enemy_count)--;}
			
		else if (placementMatrix[i+1][j-1] == 'E') 
			{placementMatrix[i+1][j-1] = ' '; (*enemy_count)--;}
			
		else if (placementMatrix[i-1][j+1] == 'E') 
			{placementMatrix[i-1][j+1] = ' '; (*enemy_count)--;}
			
		else if(placementMatrix[i-1][j-1] == 'E')
			{placementMatrix[i-1][j-1] = ' '; (*enemy_count)--;}
		
	}
	
}

void updateAroundPlayer (int R, int C, char displayMatrix[20][30], char placementMatrix[20][30])
{	

int px = player_position[0], py = player_position[1];
	for (int i=-1; i<2; ++i)
		{
			if ( (px == 0 && i == -1) || (px == R-1 && i == 1) )
					continue;
					
			for (int j=-1; j<2; ++j)
				{	
					if ( (py == 0 && j == -1) || (py == C-1 && j == 1) )
						continue;
					if (placementMatrix[px+i][py+j] == 'T' || placementMatrix[px+i][py+j] == 'E')
					{
						displayMatrix[px+i][py+j] = placementMatrix[px+i][py+j];
					}
					
					else
					{
						displayMatrix[px+i][py+j] = -80;
					}
				}
		}
	displayMatrix[px][py] = 'P';	
}

void updateDisplayMatrix (int R, int C, char displayMatrix[20][30], char placementMatrix[20][30], char input)
{
	int i= player_position[0], j= player_position[1];
		
		switch (input) //Moves belong to player and his/her place.
		{
			case 'w': case 'W': 
			if ( (placementMatrix[i-1][j]!= 'T' && placementMatrix[i-1][j]!= 'E') && i>0)
			{
				player_position[0]-=1;
				displayMatrix[i][j] = -80;
			}
			break;
			
			case 'a': case 'A':
			if ( (placementMatrix[i][j-1]!= 'T' && placementMatrix[i][j-1]!= 'E') && j>0)
			{	player_position[1]-=1;
				displayMatrix[i][j] = -80;	
			}
			break;
			
			case 's': case 'S':
			if ( (placementMatrix[i+1][j]!= 'T' && placementMatrix[i+1][j]!= 'E') && i<R-1)
			{	player_position[0]+=1;
				displayMatrix[i][j] = -80;	
			}
			break;
			
			case 'd': case 'D':
			if ( (placementMatrix[i][j+1]!= 'T' && placementMatrix[i][j+1]!= 'E') && j<C-1)
			{	player_position[1]+=1;
				displayMatrix[i][j] = -80;
			}
			break;
		}
	
	
}


void display(int R, int  C, char displayMatrix[20][30])
{
	int i,j;
	for(i=0; i<R; i++)
	{
		for(j=0; j<C; j++)
			{
				printf("%c", displayMatrix[i][j]);
			}
			printf("\n");
	}
}


void displayGodMode(int R, int C, char displayMatrix[20][30], char placementMatrix[20][30])
{
	for(int i=0; i<R; i++)
	{
		for(int j=0; j<C; j++)
			{
				if(displayMatrix[i][j]== -78)
				displayMatrix[i][j]=placementMatrix[i][j];

				if(displayMatrix[i][j]== ' ')
				{
					displayMatrix[i][j] = -80;
				}
			}
			printf("\n");
			system("cls");
	}
}


void update(int R, int C, char displayMatrix[20][30], char placementMatrix[20][30], int *enemy_count)
{
	char input;
	int c_key_counter=0;
	while (((input = getch()) != 'q' ) && *enemy_count != 0 && input != 'Q')
	{
		fightWithTheEnemy(R, C, placementMatrix, input, enemy_count);
		updateDisplayMatrix (R, C, displayMatrix, placementMatrix, input);
		updateAroundPlayer (R, C, displayMatrix, placementMatrix);
		
				system("cls");
		
		display(R,C,displayMatrix);
		
		if (input == 'c' || input == 'C')
		{	
			c_key_counter++;
			if (c_key_counter %2 ==1)
			{
				displayGodMode(R, C, displayMatrix, placementMatrix);
				display(R,C,displayMatrix);
			}
		//	else if(c_key_counter %2 ==0)
		//	display(R,C,displayMatrix);
		}
	}
}


int main ()
{
	srand ( time(0) );
	int tree_count = rand() % 7 +4 ;
	int enemy_count = rand() % 8 +3 ;
	
	//printf("There are %d trees and %d enemies. \n", tree_count, enemy_count);
	
	prepareTheGame (R,C,displayMatrix,placementMatrix,tree_count,enemy_count);
	display(R,C,displayMatrix);
	update(R,C,displayMatrix,placementMatrix,&enemy_count);
	

}
