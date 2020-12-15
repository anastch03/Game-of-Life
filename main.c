#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void update_world(void);
void print_world(int i);
int check(int width, int height);

//create a 50 by 20 array which would be the "world"
char cell[50][20]; 
char new_cell[50][20];

int main(void) {
  
  //initialize array to "-"s (dead)
  for (int i = 0; i < 50; i++)
  {
    for (int j = 0; j < 20; j++)
    {
      cell[i][j] = '-';
    }
  }
  
  //initialize configuration ie. put some life into the world 
  cell[0][1] = 'O';
  cell[9][0] = 'O';
  cell[0][0] = 'O';
  cell[9][9] = 'O';
  cell[1][2] = 'O';
  cell[10][8] = 'O';
  cell[40][12] = 'O';
  cell[49][19] = 'O';

  //outer loop for iteration of each cycle
  for (int i = 0; i < 30; i++) //goes for 30 generations
  {
    if (i == 0)
      print_world(0); //initial configuration
    else
      print_world(1); //updated configuration
    update_world();
    //write new cell into old cell before the new cell updates
    for (int i = 0; i < 50; i++)
    {
      for (int j = 0; j < 20; j++)
      {
        cell[i][j] = new_cell[i][j];
      }
    }
    usleep(500000);
    printf("\033[2J\033[H"); //clear terminal 
  }
  return 0;
}

//print out the world onto terminal
void print_world(int i)
{
  for (int column = 0; column < 20; column++)
  {
    for (int row = 0; row < 50; row++)
    {
      if (row % 50 == 0)
        printf("\n");
      if (i == 1)
        printf("%c", new_cell[row][column]);
      if (i == 0)
        printf("%c", cell[row][column]);
    }
  }
  printf("\n");
}

//update world
void update_world(void)
{
  //traverse world
  for (int i = 0; i < 50; i++)
  {
    for (int j = 0; j < 20; j++)
    {
      if (check(i, j) == 1)
        new_cell[i][j] = '-'; //cell dies
      else if (check(i,j) == 0)
        new_cell[i][j] = 'O'; //cell is 
      else 
        new_cell[i][j] = cell[1][j];
    }
  } 
}

//check if cell should die, be born, or stay as is
int check(int width, int height)
{
  int alive = 0;

  //traverse surrounding cells
  for (int h = height - 1; h <= height + 1; h++)
  {
    for (int w = width - 1; w <= width + 1; w++)
    {
      //if cell is a surrounding cell and is alive 
      if ((h != height && h > 0 && h < 50) && (w != width && w > 0 && w < 20) && cell[h][w]== 79)
        alive++;//increment alive count
    }
  } 

  //check conditions to determine cell
  if (alive > 3)
    return 1; //cell dies
  else if (alive < 2)
    return 1; //cell dies
  else //if alive count is equal to 3
    return 0; //cell is born
  return 2;
}

