#include "cub3d.h"

// void ft_init_variables(t_data *s)
// {
//     int i;

//     i = 0;
//     s->sprite = (t_sprite *)malloc(sizeof(*s->sprite) * 10);
//     s->zbuffer = (float *)malloc(sizeof(float *) * WINDOW_WIDTH);
//     s->mlx = mlx_init();
//     s->alphacam = 0.f;
//     s->nbr_sprites = 0;
//     s->a[0] = 0;
//     s->a[1] = 0;
//     s->win = mlx_new_window(s->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
//     while (i < 5)
//         s->texture[i++].ptr = NULL;
//     i = 0;
//     while (i < 6)
//         s->move[i++] = 0;
// }

// void ft_error(char *str, t_data *s)
// {
//     printf("%s", str);
//     if (s->zbuffer)
//         free(s->zbuffer);
//     if (s->mlx)
//         free(s->mlx);
//     if (s->win)
//         free(s->win);
//     exit(0);
// }

// static int ft_init_img(t_data *s)
// {
//     if ((s->img.ptr = mlx_new_image(s->mlx, WINDOW_WIDTH, WINDOW_HEIGHT)) == NULL)
//         return (0);
//     s->img.data = (int *)mlx_get_data_addr(s->img.ptr, &s->img.bpp, &s->img.size_l, &s->img.endian);
//     s->img.size_l = s->img.size_l >> 2;
//     ft_find_player(s);
//     if (s->pletter == 'N')
//         s->player_direction = 90.f;
//     else if (s->pletter == 'S')
//         s->player_direction = 270.f;
//     else if (s->pletter == 'E')
//         s->player_direction = 0.f;
//     else if (s->pletter == 'W')
//         s->player_direction = 180.f;
//     return (1);
// }

int ft_init_textures(t_data *s)
{

    s->texture[0].img = mlx_xpm_file_to_image(s->mlx, s->parsing.no_texture_value, &s->texture[0].width, &s->texture[0].height);
    s->texture[1].img = mlx_xpm_file_to_image(s->mlx, s->parsing.so_texture_value, &s->texture[1].width, &s->texture[1].height);
    s->texture[2].img = mlx_xpm_file_to_image(s->mlx, s->parsing.we_texture_value, &s->texture[2].width, &s->texture[2].height);
    s->texture[3].img = mlx_xpm_file_to_image(s->mlx, s->parsing.ea_texture_value, &s->texture[3].width, &s->texture[3].height);
    // printf("2 text valu = %d\n", size[0][0]);
    // printf("3 text valu = %d\n", size[0][1]);
    if (!s->texture[0].img || !s->texture[1].img || !s->texture[2].img || !s->texture[3].img)
    {
        printf("Error while loading image.\n");
        return (0);
    }
    s->texture[0].addr = mlx_get_data_addr(s->texture[0].img, &s->texture[0].bpp, &s->texture[0].line_l, &s->texture[0].endian);
    s->texture[1].addr = mlx_get_data_addr(s->texture[1].img, &s->texture[1].bpp, &s->texture[1].line_l, &s->texture[1].endian);
    s->texture[2].addr = mlx_get_data_addr(s->texture[2].img, &s->texture[2].bpp, &s->texture[2].line_l, &s->texture[2].endian);
    s->texture[3].addr = mlx_get_data_addr(s->texture[3].img, &s->texture[3].bpp, &s->texture[3].line_l, &s->texture[3].endian);
    return (1);
}

// static void ft_rays(t_data *s)
// {
//     if (s->theta < 0.f)
//         s->theta += 6.283185f;
//     else if (s->theta > 6.283185f)
//         s->theta -= 6.283185f;
//     // printf("s->theta = %f\n", s->theta);
//     s->cos_beta = cosf(s->alphacam - s->theta);
//     s->tan_theta = tanf(s->theta);
//     s->facing_up = (s->theta < 3.141593f) ? 1 : 0;
//     s->facing_left = (s->theta > 1.570796f && s->theta < 4.712389f) ? 1 : 0;
//     s->vhit = 0;
// }

// static int ft_obstacles(t_data *s, int x, int y)
// {
//     float sprite_cam[2];
//     // int i;
//     // (void)s, (void)x, (void)y;
//     x = x + s->parsing.start_map;
//     if (x <= s->parsing.start_map || x >= s->rows || y < 0 || y > s->cols)
// 		return (1);
//     if (s->parsing.map[x][y] <= '1')
//         return (s->parsing.map[x][y] == '1');
//     s->sprite[s->nbr_sprites].x = x;
//     s->sprite[s->nbr_sprites].y = y;
//     sprite_cam[0] = (x << 6) + 32 - s->player_x;
//     sprite_cam[1] = (y << 6) + 32 - s->player_y;
//     (void)sprite_cam;
//     // printf("%d %d %d\n", x, y, s->nbr_sprites);
//     s->sprite[s->nbr_sprites].dst = sprite_cam[0] * sprite_cam[0] + sprite_cam[1] * sprite_cam[1];
//     s->nbr_sprites++;
//     printf("%d %d %c\n", x, y, s->parsing.map[x][y]);
//     // s->parsing.map[x][y] -= 8;
//     return (0);
// }

// static float ft_hray(t_data *s)
// {
//     float a[2];
//     float step[2];

//     if (s->theta == 0.f || s->theta == 3.141593f)
// 		return (3.402823e+38f);
//     printf("1 s->theta = %f\n", s->tan_theta);
//     step[0] = (s->facing_up) ? -64.f : 64.f;
//     a[0] = (s->facing_up) ? (((int)s->player_x >> 6) << 6) : (((int)s->player_x >> 6) << 6) + 64.f;
//     a[1] = s->player_y + (s->player_x - a[0]) / s->tan_theta;
//     step[1] = -step[0] / s->tan_theta;
//     while (!ft_obstacles(s, ((int)(a[0] + (s->facing_up ? -1 : 0))) >> 6, (int)a[1] >> 6))
//     {
//         a[0] += step[0];
//         a[1] += step[1];
//     }
//     s->a[0] = (int)a[1] % 64;
//     return ((a[0] - s->player_x) * (a[0] - s->player_x) + (a[1] - s->player_y) * (a[1] - s->player_y));
// }

// static float ft_vray(t_data *s)
// {
//     float a[2];
//     float step[2];

//     if (s->theta == 1.570796f || s->theta == 4.712389f)
//         return (3.402823e+38f);
//     step[1] = (s->facing_left) ? -64.f : 64.f;
//     a[1] = (s->facing_left) ? (((int)s->player_y >> 6) << 6) : (((int)s->player_y >> 6) << 6) + 64.f;
//     a[0] = s->player_x + (s->player_y - a[1]) * s->tan_theta;
//     step[0] = -step[1] * s->tan_theta;
//     while (!ft_obstacles(s, ((int)a[0] >> 6), (int)(a[1] + (s->facing_left ? -1 : 0)) >> 6))
//     {
//         a[0] += step[0];
//         a[1] += step[1];
//     }
//     s->a[1] = (int)a[0] % 64;
//     return ((a[0] - s->player_x) * (a[0] - s->player_x) + (a[1] - s->player_y) * (a[1] - s->player_y));
// }

// static int ft_wall_hit(t_data *s)
// {
//     if (!s->vhit)
//     {
//         if (s->facing_up)
//             return (0);
//         else
//             return (1);
//     }
//     if (s->facing_left)
//         return (2);
//             return (3);
// }

// void ft_show_wall(t_data *s, int height)
// {
//     int tmp;
//     int texture;
//     t_render render;

//     tmp = (WINDOW_HEIGHT - height) >> 1;
//     render.line_shift = 0;
//     texture = ft_wall_hit(s);
//     while (render.line_shift < tmp)
//         *(s->img.data + render.line_shift++ * s->img.size_l + s->ray_angle) = (s->parsing.sky_value_1 << 16) | (s->parsing.sky_value_2 << 8) | s->parsing.sky_value_3;
//     render.start[0] = tmp < 0 ? -tmp : 0;
//     render.end[0] = tmp < 0 ? render.start[0] + WINDOW_HEIGHT : height;
//     while (render.start[0] < render.end[0])
//     {
// 		*(s->img.data + render.line_shift++ * s->img.size_l +
// 			s->ray_angle) = *(s->texture[texture].data + s->texture[texture].
// 			size_l * ((render.start[0]++ << 6) / height) +
// 			s->a[s->vhit]);    
//     }
//     while (render.line_shift < WINDOW_HEIGHT)
//         *(s->img.data + render.line_shift++ * s->img.size_l + s->ray_angle) = (s->parsing.floor_value_1 << 16) | (s->parsing.floor_value_2 << 8) | s->parsing.floor_value_3;
// }

// void ft_render(t_data *s)
// {
//     float dist[2];

//     s->ray_angle = WINDOW_WIDTH - 1;
//     s->theta = s->alphacam - 0.5235987756f;
//     s->nbr_sprites = 0;
//     // printf("s->theta = %f alphacam %f\n", s->theta, s->alphacam);
//     while (s->ray_angle >= 0)
//     {
//         ft_rays(s);
//         dist[0] = ft_hray(s);
//         dist[1] = ft_vray(s);
//         s->vhit = dist[0] > dist[1];
//         s->zbuffer[s->ray_angle] = dist[s->vhit];
//         ft_show_wall(s, s->cst / sqrtf(dist[s->vhit]) * s->cos_beta);
//         s->theta += s->phi;
//         s->ray_angle--;
//     }
//     mlx_put_image_to_window(s->mlx, s->win, s->img.ptr, 0, 0);
// }

// int ft_close(t_data *s)
// {
//     if (s->zbuffer)
//         free(s->zbuffer);
//     if (s->mlx)
//         free(s->mlx);
//     if (s->win)
//         free(s->win);
//     exit(0);
// }

// int ft_move(t_data *s)
// {
//     int action;

//     action = 0;
//     if (s->move[0])
//         action = ft_move_forward(s, -3);
//     else if (s->move[1])
//         action = ft_move_forward(s, 3);
//     else if (s->move[2])
//         action = ft_move_left(s, -3);
//     else if (s->move[3])
//         action = ft_move_left(s, 3);
//     else if (s->move[4])
//         action = ft_rotateminus(s);
//     else if (s->move[5])
//         action = ft_rotate(s);
//     if (!action)
//         return (0);
//     ft_render(s);
//     return (1);
// }

int init_var(t_data *s)
{
    int i;

    i = -1;
    s->texture = (t_image *)malloc(sizeof(t_image) * 4);
    if (!s->texture)
        return (1);
    while (++i < 4)
        s->texture->img = NULL;
    printf("coucou\n");
    return (0);
}

void init_window(t_data *s)
{
    s->mlx = mlx_init();
    if (!s->mlx)
        exit (1);
    ft_init_textures(s);
    s->win = mlx_new_window(s->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
    if (!s->win)
        exit (1);
}

void ft_raycasting(t_data *s)
{
    if (init_var(s) == 1)
        exit (1);
    init_window(s);
    ft_find_player(s);
    printf("YES %f %f %f\n", s->player_direction, s->player_x, s->player_y);
    mlx_loop(s->mlx);
}