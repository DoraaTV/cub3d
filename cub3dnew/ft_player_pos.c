#include "cub3d.h"

void ft_find_player(t_data *s)
{
    int i;
    int j;

    i = s->parsing.start_map;
    while (s->parsing.map[i])
    {
        j = 0;
        while (s->parsing.map[i][j])
        {
            if (s->parsing.map[i][j] == 'N' || s->parsing.map[i][j] == 'S' || s->parsing.map[i][j] == 'E' || s->parsing.map[i][j] == 'W')
            {
                s->pletter = s->parsing.map[i][j];
                s->player_x = i + 0.5;
                s->player_y = j + 0.5;
                s->cols = (j > s->cols) ? j : s->cols;
            }
            j++;
        }
        i++;
    }
    s->rows = i;
    printf("%d %d\n", s->rows, s->cols);
}