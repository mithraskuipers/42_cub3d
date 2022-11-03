#include "../headers/parsing.h"

int get_rgba(int r, int g, int b)
{
    return (r << 24 | g << 16 | b << 8 | 1);
}