/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parallels <parallels@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:44:10 by madjogou          #+#    #+#             */
/*   Updated: 2023/12/10 23:22:16 by parallels        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int    good_name_file_cub(int ac, char **av)//✅
{    
    // Récupère le nom du fichier à partir du premier argument
    char *name_file;
    name_file = av[1];

    if (ac != 2) 
    {
        if (ac < 2)
            printf("Error : insufficient number of arguments\n");
        else
            printf("Error : too much of arguments\n");
        return 1; // Quitte le programme avec un code d'erreur
    }

    // Vérifie si le nom du fichier se termine par l'extension ".cub"
    if (strstr(name_file, ".cub") == NULL || strcmp(name_file + strlen(name_file) - 4, ".cub") != 0) 
    {
        printf("Error : The file must have the .cub extension\n");
        return 1; 
    }

    // Si nous sommes arrivés ici, le nom du fichier a l'extension ".cub"
        return 0; // Quitte le programme avec succès

}

int main(int ac, char **av)
{
    t_data data;
    
    /*bon nombre d'argument et bon nom de fichier .cub ✅*/
    if (good_name_file_cub(ac, av) == 1)
            return (1);

    /*parsing*/
    if (parsing(av[1], &data) == 1)
        return (1);
    for (int i = data.parsing.start_map; data.parsing.map[i]; i++)
        printf("map[%d] = %s\n", i, data.parsing.map[i]);
    /*execution*/
    ft_raycasting(&data);
    //fonction exec si parsing ok
    return (0);
}