#include "../headers/parsing.h"

// unsigned int get_rgba(int r, int g, int b)
// {
//     return (r << 24 | g << 16 | b << 8 | 1);
// }

int	create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b)
{
	return (*(int *)(unsigned char [4]){b, g, r, t});
}