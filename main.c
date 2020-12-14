#include <stdio.h>

void update_world(void);
int check(int width, int height);

//create a 50 by 50 array which would be the "world"
char cell[50][50]; 

int main(void) {
  
  //initialize array to "-"s (dead)
  for (int i = 0; i < 50; i++)
  {
    for (int j = 0; j < 50; j++)
    {
      cell[i][j] = '-';
    }
  }
  //put some life into the world (O)
  cell[2][1] = 'O';
  cell[9][0] = 'O';
  cell[0][0] = 'O';
  cell[9][1] = 'O';
  cell[3][3] = 'O';
  cell[10][8] = 'O';
  cell[50][46] = 'O';
  cell[10][19] = 'O';

  //print current world
  for (int row = 0; row < 50; row++)
  {
    for (int column = 0; column < 50; column++)
    {
      if (column % 50 == 0)
        printf("\n");
      printf("%c", cell[row][column]);
    }
  }

  //outer loop for iteration of each cycle
    //update_world();
    //clear terminal
    //wait 0.5 second
    //print out array
}

void update_world(void)
{
  //traverse array
  for (int i = 0; i < 10; i++)
  {
    for (int j = 0; j < 10; j++)
    {
      if(check(i,j) == 1)
        cell[i][j] = '-'; //cell dies
      else if (check(i,j) == 0)
        cell[i][j] = 'O'; //cell is born
    }
    
  }
      
}

int check(int width, int height)
{
  int alive;
  //traverse surrounding cells
    //if cell is alive 
      alive++;//update alive count

    //if alive count is greater than 3
      if (alive > 3)
        return 1; //cell dies
    //else if alive count is fewer than 2

    //reset alive count to 0
    alive = 0;
    
}

