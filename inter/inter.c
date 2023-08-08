#include <unistd.h>

int main(int ac, char **av)
{
	int		i;
	int		j;
	int		tab[255];

	if (ac == 3)
	{
		i = 0;
		while (i < 255)
			tab[i++] = 0;
		i = 2;
		while (i > 0)
		{
			j = 0;
			while (av[i][j])
			{
				if (i == 2 && !tab[(unsigned char)av[i][j]])
					tab[(unsigned char)av[i][j]] = 1;
				else if (i == 1 && tab[(unsigned char)av[i][j]] == 1)
				{
					write(1, &av[i][j], 1);
					tab[(unsigned char)av[i][j]] = 2;
				}
				j++;
			}
			i--;
		}
	}
	write (1, "\n", 1);
}