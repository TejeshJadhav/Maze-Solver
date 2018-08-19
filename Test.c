#include <stdio.h>
#include "maze_solver.h"

int main()
{
	char dir = 'a';
	int i = 0;

	_initialize();
	while(dir != 'x')
	{
		printf(":");
		scanf(" %c",&dir);
		if(dir != 'x')
		{
			insert(dir);
		}
		else
		{
			dir = 'x';	
		}
	}
	i = 0;
	dir= run(i);
	while(dir!='x')
	{
		printf("%c\t",dir);
		i++;
		dir= run(i);
	}
	
	return 0;
	printf("\ndone\n");
}
