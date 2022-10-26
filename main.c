#include "headers/parsing.h"

int main(int argc, char **argv)
{
    t_mlx	mlx;

	mlx.error = 0;
	mlx.taken = 0;
	if (argc == 2)
	{
		mlx.map_file = argv[1];
		mapparsing(&mlx);
		if (mlx.error == 1)
			return (1);
	}
	else
	{
		printf("Error\n incorrect amount of arguments");
		return (1);
	}
    return (0);
}