#include <stdio.h>
#include <unistd.h>
#include <string.h>

void update_world(void);
void print_world(void);
int check(int height, int width);

//create a 50 by 100 array which would be the "world"
char cell[50][100]; 
char new_cell[50][100];

int main(void) {
  printf("\033[2J\033[H"); //clear terminal 
  //initialize array to "-"s (dead)
  for (int i = 0; i < 50; i++)
  {
    for (int j = 0; j < 100; j++)
    {
      cell[i][j] = '-';
    }
  }
  
  //initialize configuration ie. put some life into the world 
  cell[24][49] = 'O';
  cell[24][50] = 'O';
  cell[24][51] = 'O';
  cell[23][50] = 'O';
  cell[21][49] = 'O';
  cell[21][50] = 'O';
  cell[21][51] = 'O';
  cell[20][50] = 'O';
  cell[19][18] = 'O';
  cell[19][19] = 'O';
  cell[19][20] = 'O';
  cell[18][19] = 'O';
  cell[18][18] = 'O';
  cell[18][17] = 'O';
  cell[17][17] = 'O';
  cell[17][19] = 'O';
    

  //outer loop for iteration of each cycle
  for (int i = 0; i < 40; i++) //goes for 40 generations
  {
    print_world(); //initial configuration
    update_world();
    //write new cell into old cell before the new cell updates
    memcpy(cell, new_cell, sizeof(new_cell)+1);
    usleep(500000);
    printf("\033[2J\033[H"); //clear terminal 
  }
}

//print out the world onto terminal
void print_world(void)
{
  for (int row = 0; row < 50; row++)
  {
    for (int column = 0; column < 100; column++)
    {
      if (column % 100 == 0)
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
  for (int i = 0; i < 50; i++)
  {
    for (int j = 0; j < 100; j++)
    {
      switch (check(i, j))
      {
        case 1:
          new_cell[i][j] = '-'; //cell dies
          break;
        case 0:
          new_cell[i][j] = 'O'; //cell is born
          break;
        default:
          new_cell[i][j] = cell[i][j]; //cell stays the same
          break;
      }
    }
  } 
}

//check if cell should die, be born, or stay as is
int check(int height, int width)
{
  int alive = 0;

  //traverse cell's neightboring cells (including itself)
  for (int h = height - 1; h <= height + 1; h++)
  {
    for (int w = width - 1; w <= width + 1; w++)
    {
      //if (h,w) is a surrounding cell, within in bounds of the grid, and is alive 
      if (!(h == height && w == width) && h >= 0 && h <= 50
       && w >= 0 && w <= 100 && cell[h][w] == 79)
        alive++;//increment alive count
    }
  } 

  //check conditions to determine cell
  if (alive > 3 || alive < 2)
    return 1; //cell dies
  else if (alive == 3)
    return 0; //cell is born or lives on to next generation
  return 2; //alive count = 2, nothing changes
}

