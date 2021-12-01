#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

int w;
int h;
char bg;
char **all;

typedef struct inside
{
	char c;
	float x;
	float y;
	float radius;
	char cercle;
}	t_inside;

int ft_error(FILE *fd, int ret)
{
    if (ret == 2)
    {
        ret = 1;
        write(1,"Error: argument\n",17);
    }
    else if (ret == 1)
        write(1,"Error: Operation file corrupted\n",33);
    else
    {
		for (int i = 0; i < h; i++)
		{
			write(1,all[i],w);
			write(1,"\n",1);
		}
    }
	if (fd)
		fclose (fd);
	return(ret);
}

int main(int ac, char **av)
{
	FILE *fd;
	int res;
	float sqr;
	t_inside ins;

	fd = NULL;
	if (ac != 2)
		ft_error(fd, 2);
	if ((fd = fopen(av[1], "r")))
	{
		if ((res = fscanf(fd, "%d %d %c", &w, &h ,&bg)) == 3)
		{
			if (w > 0 && w <= 300 && h > 0 && h <= 300)
			{
				all = malloc(h * sizeof(char *));
				for (int k = 0; k < h; k++)
				{
					all[k] = malloc(w * sizeof(char));
					memset(all[k], bg, w);
				}
				while (1)
				{
					res = fscanf(fd, "\n%c %f %f %f %c", &ins.c, &ins.x, &ins.y, &ins.radius, &ins.cercle);
					if (res == -1)
						return(ft_error(fd, 0));
					if (res != 5 || ins.radius <= 0 || (ins.c != 'c' && ins.c != 'C'))
						break ;
					for (int line = 0; line < w; line++)
					{
						for (int col = 0; col < h; col++)
						{
							sqr = sqrtf((col - ins.x)*(col - ins.x) + (line - ins.y)*(line - ins.y));
							if (sqr <= ins.radius)
							{
								if (ins.c == 'c' && sqr + 1 > ins.radius)
									all[line][col] = ins.c;
								else if (ins.c == 'C')
									all[line][col] = ins.c;
							}
						}
					}
				}
			}
		}
	}
	return (ft_error(fd, 1));
}
