#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

int w;
int h;
char bg;
char **all;

typedef struct test
{
	char c;
	float x;
	float y;
	float rayon;
	char s;
}t_test;


int ft_error(FILE *fd, int err)
{
	if (err == 2)
	{
		err = 1;
		write(1, "Error: Operation file corrupted\n", 32);
	}
	else if (err == 1)
		write(1, "Error: argument\n", 16);
	else
	{
		for (int i = 0; i < h; i++)
		{
			write (1, all[i], w);
			write(1, "\n",1);
		}
	}
	if (fd)
		fclose(fd);
	return (err);
}

int main(int ac, char **av)
{
	FILE *fd;
	int res;
	float sqr;
	t_test hh;

	fd = NULL;
	if (ac != 2)
		return(ft_error(fd, 1));
	if ((fd = fopen(av[1], "r")))
	{
		if ((res = fscanf(fd, "%d %d %c", &w, &h, &bg)) == 3)
		{
			if (w > 0 && w <= 300 && h > 0 && h <= 300)
			{
				all = malloc(sizeof(char *) * h);
				for (int i = 0; i < h; i++)
				{
					all[i] = malloc(sizeof(char) * w);
					memset( all[i], bg, w);
				}
				while (1)
				{
					res = fscanf(fd, "\n%c %f %f %f %c", &hh.c, &hh.x, &hh.y, &hh.rayon, &hh.s);
					if (res == -1)
						return (ft_error(fd, 0));
					else if (res != 5 || hh.rayon <= 0 || (hh.c != 'c' && hh.c != 'C'))
						break ;
					for (int line = 0; line < h; line++)
					{
						for (int col = 0; col < w; col++)
						{
							sqr = sqrtf((col - hh.x) * (col - hh.x) + (line - hh.y) * (line - hh.y));
							if (sqr <= hh.rayon)
							{
								if (hh.c == 'C')
									all[line][col] = hh.s;
								else if (hh.c == 'c' && sqr + 1 > hh.rayon)
									all[line][col] = hh.s;
							}
						}
					}
				}
			}
		}
	}
	return (ft_error(fd, 2));
}
