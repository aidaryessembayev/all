//In collaboration of Aidar Yessembayev and Tauyekel Kunzhol

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define size 10

typedef struct {
  int heading; // 0 (west), 1 (north), 2 (east), 3 (south)
  _Bool alive; // 1 (true) at game start, set to (false) when robot crashes
}
robot;

void state_out(robot* site[10][10])
{
  int x,y;

  for (y=0; y<size; y++) {
    for (x=0; x<size; x++) {
      if (site[x][y]!=NULL) {
        if ((*site[x][y]).alive) printf(" R ");
	else printf(" @ ");
      }
      else printf(" . ");
    }
    printf("%3i\n",y);
  }
  for (x=0; x<size; x++)
    printf(" %i ",x%10);
}


_Bool is_valid(int x, int y) {
// checks if coordinate pair is on the grid
  if ((x>=0)&&(x<size)&&(y>=0)&&(y<size)) return 1;
  else return 0;
}


int main()
{
	srand( time(NULL) );
  setvbuf(stdout, NULL, _IONBF, 0);

  robot* site[size][size];
  robot* osr;
  int nrobs;
  int i,j,k;
  int x,y,xn,yn;
  int totalRobots = 0;
  int parkedRobots = 0;
  char aletter;

  // initialize array of sites with NULLs
  for (j=0; j<size; j++)
    for (k=0; k<size; k++)
      site[j][k]=NULL;


  nrobs = 10;


// In the following line, replace NULL
// by the correct malloc instruction
// to obtain memory for nrobs robots

  osr = malloc(nrobs * sizeof(robot));

  // initialize robots
  for (i=0; i<nrobs; i++)
  {
    (*(osr+i)).heading=rand()%4;
    (*(osr+i)).alive=1;
    do
    {
      j=rand()%size;
      k=rand()%size;
    }
    while (site[j][k]!=NULL);
    site[j][k]=osr+i;
  }

  // main loop of the game
  do
  {
    state_out(site);

    // obtain user input (move)
    do
    {
      printf("\n input action and coordinates, please: ");
      scanf(" %c %i %i",&aletter,&x,&y);
    }
    while (!is_valid(x,y));

    // WRITE CODE HERE
    // to execute the move entered by the user
    if (site[x][y] != NULL && site[x][y]->alive)
    {
    	if (aletter == 'F')
    	{
    		if (site[x][y]->heading == 0)
    		{
    			if (site[x - 1][y] == NULL && x - 1 >= 0)
    			{
					site[x - 1][y] = site[x][y];
					site[x][y] = NULL;
    			}
    			else if (x - 1 < 0)
    			{
    				//site[x][y]->alive = 0;
    			}
    			else
    			{
    				site[x - 1][y]->alive = 0;
    				site[x][y]->alive = 0;
    			}
    		}
    		else if (site[x][y]->heading == 1)
    		{
    			if (site[x][y - 1] == NULL && y - 1 >= 0)
    			{
					site[x][y - 1] = site[x][y];
					site[x][y] = NULL;
    			}
    			else if (y - 1 < 0)
    			{
    				//site[x][y]->alive = 0;
    			}
    			else
    			{
    				site[x][y - 1]->alive = 0;
    				site[x][y]->alive = 0;
    			}
    		}
    		else if (site[x][y]->heading == 2)
    		{
    			if (site[x + 1][y] == NULL && x + 1 < size)
    			{
					site[x + 1][y] = site[x][y];
					site[x][y] = NULL;
    			}
    			else if (x + 1 >= size)
    			{
    				//site[x][y]->alive = 0;
    			}
    			else
    			{
    				site[x + 1][y]->alive = 0;
    				site[x][y]->alive = 0;
    			}
    		}
    		else if (site[x][y]->heading == 3)
    		{
    			if (site[x][y + 1] == NULL && y + 1 < size)
    			{
					site[x][y + 1] = site[x][y];
					site[x][y] = NULL;
    			}
    			else if (y + 1 >= size)
    			{
    				//site[x][y]->alive = 0;
    			}
    			else
    			{
    				site[x][y + 1]->alive = 0;
    				site[x][y]->alive = 0;
    			}
    		}
    	}
    	else if (aletter == 'R')
		{
			site[x][y]->heading = (site[x][y]->heading + 1) % 4;
		}
		else if (aletter == 'L')
		{
			site[x][y]->heading = (site[x][y]->heading - 1);

			if (site[x][y]->heading == -1)
			{
				site[x][y]->heading = 3;
			}
		}
    }
    else
    {
    	printf("There is no any robot here, or it is dead!\n");
    }

    totalRobots = 0;
    parkedRobots = 0;

    //Check how many robots
    for (y = 0; y < nrobs; y++)
    {
    	for (x = 0; x < nrobs; x++)
    	{
    		if (site[x][y] != NULL && site[x][y]->alive)
    		{
    			totalRobots++;
    		}
    	}
    }

    //Check if win
    for (y = 0; y < nrobs; y++)
    {
    	for (x = 0; x < nrobs; x++)
    	{
			if (site[x][y] != NULL && site[x][y]->alive)
			{
				if (x == 0)
				{
					parkedRobots++;
				}
			}
    	}
    }

    //Lose condition
    if (totalRobots == 0)
    {
    	printf("You lose!");
    	state_out(site);
    	break;
    }

    //Win condition
    if (totalRobots == parkedRobots)
    {
    	int crashed = nrobs - totalRobots;
    	printf("You won! Your crashed %i robots", crashed);
    	state_out(site);
    	break;
    }



  }
  while (aletter!='Q');

  free(osr);
  free(site);

  return 0;
}
