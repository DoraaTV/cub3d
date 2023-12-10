#include "cub3d.h"

void ft_compare(char c, t_data *s)
{
    if (c == 'N')
        s->player_direction = 1.5f * M_PI;
    else if (c == 'S')
        s->player_direction = 0.5f * M_PI;
    else if (c == 'W')
        s->player_direction = M_PI;
    else if (c == 'E')
        s->player_direction = 0.0f;
}

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
                ft_compare(s->parsing.map[i][j], s);
                s->player_x = (float)i + 0.2f;
                s->player_y = (float)j + 0.2f;
                s->cols = (j > s->cols) ? j : s->cols;
            }
            j++;
        }
        i++;
    }
    s->rows = i;
}