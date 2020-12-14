#include <stdio.h>
#include <string.h>
#include <unistd.h>

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
  //put some life into the world (O)
  cell[2][1] = 'O';
  cell[9][0] = 'O';
  cell[0][0] = 'O';
  cell[9][9] = 'O';
  cell[13][3] = 'O';
  cell[10][8] = 'O';
  cell[40][12] = 'O';
  cell[49][19] = 'O';

  //print original world
  print_world(0);
  sleep(1);
  printf("\033[2J\033[H"); //clear terminal

  //outer loop for iteration of each cycle
  for (int i = 0; i < 30; i++) //goes for 30 generations
  {
    print_world(1);
    update_world();
    //rewrite old cell to be new cell before the new cell updates
    for (int i = 0; i < 50; i++)
    {
      for (int j = 0; j < 20; j++)
      {
        cell[i][j] = new_cell[i][j];
      }
    }
    sleep(1);
    printf("\033[2J\033[H"); //clear terminal 
  }
  return 0;
}

//prints out the world onto terminal
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
      if(check(i,j) == 1)
        new_cell[i][j] = '-'; //cell dies
      else if (check(i,j) == 0)
        new_cell[i][j] = 'O'; //cell is born
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
      //if cell is alive 
      if (h != height && w != width && cell[h][w] == 79)
        alive++;//update alive count
      //if alive count is greater than 3
      if (alive > 3)
        return 1; //cell dies
      //else if alive count is fewer than 2
      else if (alive < 2)
        return 1; //cell dies
      else if (alive == 3)
        return 0; //cell is born
      else 
        return 2; //cell remains as is
    }
  } 
}

