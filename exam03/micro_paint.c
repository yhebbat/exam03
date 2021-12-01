#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

int w;
int h;
char bg;
char **all;

typedef struct micro_paint
{
	char c;
	float x;
	float y;
	float w;
	float h;
	char s;
}m_c;

int	ft_error(FILE *fd, int err)
{
	if (err == 2 && (err = 1))
		write(1, "Error: Operation file corrupted\n", 32);
	else if (err == 1)
		write(1, "Error: argument\n", 16);
	else
	{
		for (int i = 0; i < h; i++)
		{
			write(1, all[i], w);
			write(1, "\n",1);
		}
	}
	if (fd)
		fclose(fd);
	return (err);
}

int is_rec(int col, int line, m_c *m)
{
	if (col < m->x || col > (m->x + m->w) || line < m->y || line > (m->y + m->h))
		return 0;
	if (col - m->x < 1 || (m->x + m->w) - col < 1 || line - m->y < 1 || (m->y + m->h) - line < 1)
		return 2;
	return (1);
}

int main(int ac, char **av)
{
	FILE	*fd;
	int		res;
	m_c		m;

	fd = NULL;
	if (ac != 2)
		return (ft_error(fd, 1));
	if ((fd = fopen(av[1], "r")))
	{
		if ((res = fscanf(fd, "%d %d %c", &w, &h, &bg)) == 3)
		{
			if (w > 0 && w <= 300 && h > 0 && h <= 300)
			{
				all = malloc(sizeof(char *) * h);
				for (int r = 0; r < h; r++)
				{
					all[r] = malloc(sizeof(char) * w);
					memset(all[r] , bg, w);
				}
				while (1)
				{
					res = fscanf(fd, "\n%c %f %f %f %f %c", &m.c, &m.x, &m.y, &m.w, &m.h, &m.s);
					if (res == -1)
						return (ft_error(fd, 0));
					else if (res != 6 || m.w <= 0 || m.h <= 0 || (m.c != 'r' && m.c != 'R'))
						break ;
					for (int line = 0; line < h; line++)
					{
						for (int col = 0; col < w; col++)
						{
							int ll = is_rec(col, line, &m);
							if (ll == 2 && m.c == 'r')
								all[line][col] = m.s;
							else if (ll && m.c == 'R')
								all[line][col] = m.s;
						}
					}
				}
			}
		}
	}
	return (ft_error(fd, 2));
}
