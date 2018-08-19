#ifndef MAZE_SOLVER_ #define MAZE_SOLVER_

#define size 100
char array[size];
int pointer = 0;

void _initialize()
{
	int i = 0;
	for(i = 0; i <= size ; i++)
	{
		array[i] = 'x';
	}
}

char check(char direction)
{
	char give;
	if(array[pointer -2] == 'L')
	{
		if(direction == 'R')
		{
			give = 'B';
		}
		else if(direction == 'L')
		{
			give = 'S';
		}
		else if(direction == 'S')
		{
			give = 'R';
		}
	}
	else if(array[pointer -2] == 'S')
	{
		if(direction == 'L')
		{
			give = 'R';
		}
		else if(direction == 'S')
		{
			give = 'B';
		}
	}
	else if(array[pointer -2] == 'R')
	{
		if(direction == 'L')
		{
			give = 'B';
		}
	}
return give;
}

void insert(char direction)
{
	char temp;
	if(pointer > 1)
	{  if(array[pointer-1] == 'B')
		{
			temp = check(direction);
			array[pointer-1]='x',
			pointer = pointer -2;
			array[pointer++] = temp;
		}
		else
		{
		array[pointer++] = direction;
		}
	}
	else
	{
		array[pointer++] = direction;
	}
}

char run(int junction_number)
{
	return (array[junction_number]);
}

#endif
