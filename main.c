#include <stdio.h>
#include <unistd.h>

void update_world(void);
void print_world(void);
int check(int width, int height);

//create a 50 by 20 array which would be the "world"
char cell[5][5]; 
char new_cell[5][5];

int main(void) {
  
  //initialize array to "-"s (dead)
  for (int i = 0; i < 5; i++)
  {
    for (int j = 0; j < 5; j++)
    {
      cell[i][j] = '-';
    }
  }
  
  //initialize configuration ie. put some life into the world 
  cell[0][1] = 'O';
  cell[4][0] = 'O';
  cell[1][2] = 'O';
  cell[1][4] = 'O';
  cell[4][4] = 'O';
  cell[0][2] = 'O';

  //outer loop for iteration of each cycle
  for (int i = 0; i < 10; i++) //goes for 10 generations
  {
    if (i == 0)
      print_world(); //initial configuration
    update_world();
    //write new cell into old cell before the new cell updates
    for (int i = 0; i < 5; i++)
    {
      for (int j = 0; j < 5; j++)
      {
        cell[i][j] = new_cell[i][j];
      }
    }
    sleep(1);
    printf("\033[2J\033[H"); //clear terminal 
  }
}

//print out the world onto terminal
void print_world(void)
{
  for (int column = 0; column < 5; column++)
  {
    for (int row = 0; row < 5; row++)
    {
      if (row % 5 == 0)
        printf("\n");
      printf("%c", cell[row][column]);
    }
  }
  printf("\n");
}

//update world
void update_world(void)
{
  //traverse world
  for (int i = 0; i < 5; i++)
  {
    for (int j = 0; j < 5; j++)
    {
      if (check(i, j) == 1)
        new_cell[i][j] = '-'; //cell dies
      else if (check(i,j) == 0){
        new_cell[i][j] = 'O'; //cell is born
        printf("%c", new_cell[i][j]);
      }
      else 
        new_cell[i][j] = cell[i][j];
    }
  } 
}

//check if cell should die, be born, or stay as is
int check(int width, int height)
{
  int alive = 0;

  //traverse cell's neightboring cells (including itself)
  for (int h = height - 1; h <= height + 1; h++)
  {
    for (int w = width - 1; w <= width + 1; w++)
    {
      //if (h,w) is a surrounding cell, within in bounds of the grid, and is alive 
      if (!(h == height && w == width) && h >= 0 && h < 5
       && w >= 0 && w < 5 && cell[h][w] == 79)
        alive++;//increment alive count
    }
  } 

  //check conditions to determine cell
  if (alive > 3 || alive < 2)
    return 1; //cell dies
  else if (alive == 3)
    return 0; //cell is born
  return 2; //alive count = 2, nothing changes
}

