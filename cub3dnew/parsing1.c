/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrio <thrio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:57:13 by thrio             #+#    #+#             */
/*   Updated: 2023/12/12 20:04:35 by thrio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int     ft_get_size(char *file_cub3d_name, t_parsing *s)
{
    int fd;
    char *line;
    int  check;
    int  count;
    int i;

    check = 0;
    count = 0;
    fd = open(file_cub3d_name, O_RDONLY);
    if (fd < 2)
        return (1);
    line = get_next_line(fd);
    while (line && check == 0)
    {
        if (line[0] == '1' || line[0] == ' ')
        {
            if (line[0] == ' ')
            {
                i = 0;
                while (line[i])
                {
                    if (line[i] == '1')
                    {
                        s->counter = count;
                        check = 1;
                    }
                    i++;
                }
            }
            s->counter = count;
            check = 1;
        }
        s->config_size++;
        count++;
        free(line);
        line = get_next_line(fd);
    }
    free(line);
    line = get_next_line(fd);
    while (line)
    {
        free(line);
        line = get_next_line(fd);
    }
    return (0);
}

void	init_struct(t_parsing	*parsing)
{
    //parsing->text_file = NULL;
    
    // Initialisation des valeurs RGB dans la structure
    parsing->floor_value_1 = -1;  // Valeur par défaut -> mettre 0 ?
    parsing->floor_value_2 = -1;  // Valeur par défaut
    parsing->floor_value_3 = -1;  // Valeur par défaut
    parsing->sky_value_1 = -1;  // Valeur par défaut
    parsing->sky_value_2 = -1;  // Valeur par défaut
    parsing->sky_value_3 = -1;  // Valeur par défaut

    //init textures
    
    parsing->no_texture_value = NULL;
    parsing->we_texture_value = NULL;
    parsing->so_texture_value = NULL;
    parsing->ea_texture_value = NULL;
    parsing->s_texture_value = NULL;

    //init map
    parsing->map = NULL;
    parsing->config_count = 0;
    parsing->sign_count = 0;
    parsing->config_size = 0;
    parsing->map_count = 0;
    parsing->start_map = 0;
    parsing->ligne_vide = 0;
    parsing->config_elements = NULL;
	parsing->copied_map = NULL;
	parsing->map_height = 0;
    
    //ETC
}

//l'exec commence ici, parsing est l'equivalent de game
void ft_init(t_parsing *parsing)
{
    (void)parsing;
}

int parsing(char *file_cub3d_name, t_data *data)
{
    t_parsing *parsing;

    // g_allocs = malloc(sizeof(t_allocs *));
	// *g_allocs = NaULL;
    data->parsing.counter = 0;
    init_struct(&data->parsing);
    if (ft_get_size(file_cub3d_name, &data->parsing) == 1)
        return (1);
    if (data->parsing.counter < 6)
        return (1);
    //parsing pointe vers la même structure que data.parsing
    parsing = &data->parsing;
    if (put_text_struct(file_cub3d_name, &data->parsing) == 1)
        {
            printf("Error : text cannot be put into structure\n");
            free_parsing(&data->parsing);
            return 1;
        }
        // Vérifiez si parsing->text_file a été correctement initialisé
 
        //printf("ici 2 = %s\n", parsing->map[15]);
        //printf("ici 3 = %s\n", parsing->config_elements[5]);

        // if (*parsing->num_lines_ptr == 0)
        //     {
        //         printf("Error : the file is empty\n");
        //         return 1;
        //     }

        // if (!parsing->map || !parsing->config_elements) 
        // {
        //     printf("Error: struct is not properly initialized\n");
        //     return 1;
        // }
        // printf("ici = %s\n", parsing->text_file[9]);
      
        if (parsing_cub3d(parsing->config_elements, &data->parsing) == 1)
        {
            //faire mes frees si parsing errone
           
            return 1;
        }
         // Ferme le descripteur de fichier si terminé (a revoir si ok)
// parsing->mlx = mlx_init();
// parsing->mlx_win = mlx_new_window(parsing->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
// ft_init(parsing); //equivalent de ft_init(game);

// //les fonctions ci-dessous ne sont pas encore implementees : 
// // mlx_hook(parsing->mlx_win, 2, 1L << 0, key_hook1, parsing);
// // mlx_hook(parsing->mlx_win, 3, 1L << 1, key_hook2, parsing);
// // mlx_hook(parsing->mlx_win, 17, 0L, red_cross, parsing);
// // mlx_loop_hook(parsing->mlx, ft_hook, parsing);
// mlx_loop(parsing->mlx);
return (0);
}