#include <unistd.h>

int main(int ac, char **av)
{
	int i;
	int	j;
	int tab[255];

	if (ac == 3)
	{
		i = 0;
		while (i < 255)
			tab[i++] = 0;
		i = 1;
		while (i < 3)
		{
			j = 0;
			while (av[i][j])
			{
				if (!tab[(unsigned char)av[i][j]])
				{
					write(1, &av[i][j], 1);
					tab[(unsigned char)av[i][j]] = 1;
				}
				j++;
			}
			i++;
		}
	}
	write (1, "\n", 1);
	return (0);
}
