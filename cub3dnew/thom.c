#include "cub3d.h"

void draw_game(t_data *s);
float ft_sign(float n);
float ft_ray(t_data *s, float angle);

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

int ft_close(t_data *s)
{
    if (s->zbuffer)
        free(s->zbuffer);
    if (s->mlx)
        free(s->mlx);
    if (s->win)
        free(s->win);
    exit(0);
}

void ft_move (t_data *s, int direction)
{
    float dist;
    float dist_x;
    float dist_y;
    float angle;

    angle = s->player_direction + direction * M_PI / 2;
    dist_x = 0.1f * cos(angle);
    dist_y = 0.1f * sin(angle);
    dist = ft_ray(s, ft_sign(dist_y) * M_PI / 2);
    if (dist * dist < dist_y * dist_y)
        dist_y = 0.0f;
    dist = ft_ray(s, (1 - (ft_sign(dist_x) + 1) / 2) * M_PI);
    if (dist * dist < dist_x * dist_x)
        dist_x = 0.0f;
    dist = ft_ray(s, angle);
    if (dist * dist < dist_x * dist_x + dist_y * dist_y)
    {
        if (ft_sign(dist_y) * ft_sign(dist_x) != 0)
            dist_y = 0.0f;
    }
    s->player_x += dist_x;
    s->player_y += dist_y;
    printf("lala= %f\n", s->player_x);
}

int ft_keys(int key, t_data *s)
{
    if (s->win == NULL)
        return (0);
    if (key == XK_Escape || key == XK_q || key == XK_Q)
    {
        ft_close(s);
        exit (0);
    }
    if (key == 65362 || key == 119)
        ft_move(s, 0);
    else if (key == 65364 || key == 115)
        ft_move(s, 2);
    else if (key == 65361)
        s->player_direction -= 0.02f * M_PI;
    else if (key == 65363)
        s->player_direction += 0.02f * M_PI;
    else if (key == 100)
        ft_move(s, 1);
    else if (key == 97)
        ft_move(s, 3);
    else
        return (0);
    mlx_destroy_image(s->mlx, s->img.img);
    draw_game(s);
    return (1);
}

float ft_sign(float n)
{
    if (n > 0)
        return (1.0f);
    else if (n < 0)
        return (-1.0f);
    else
        return (0.0f);
}

static void init_ray(t_data *s, t_ray *ray, float angle)
{
    ray->dir_x = cos(angle);
    ray->dir_y = sin(angle);
    ray->step_x = ft_sign(ray->dir_x);
    ray->step_y = ft_sign(ray->dir_y);
    ray->vert_x = (int)s->player_x;
    if (ray->step_x > 0)
        ray->vert_x += 1.0f;
    ray->horz_y = (int)s->player_y;
    if (ray->step_y > 0)
        ray->horz_y += 1.0f;
        	 	//  printf("ray->horz_y  = %f\n", ray->horz_y);

}

static void ft_ray2(t_data *s, t_ray *ray)
{
    if (ray->step_x != 0)
    {
        ray->vert_y = s->player_y + ray->dir_y / ray->dir_x * (ray->vert_x - s->player_x);
        // printf("%f %f %f %f verty%f\n", s->player_x, ray->vert_x, s->player_y, ray->vert_y, ray->vert_y);
        ray->vert_dist = sqrt(pow(s->player_x - ray->vert_x, 2.0) + pow(s->player_y - ray->vert_y, 2.0));
        ray->vert_w = ray->vert_y - (int)ray->vert_y;
        if (ray->step_x > 0)
            ray->vert_w = 1 - ray->vert_w;
    }
    else
        ray->vert_dist = INFINITY;
    if (ray->step_y != 0)
    {
        ray->horz_x = s->player_x + ray->dir_x / ray->dir_y * (ray->horz_y - s->player_y);
        // printf("%f %f %f %f vertx%f\n", s->player_x, ray->horz_x, s->player_y, ray->horz_y, ray->vert_x);
        ray->horz_dist = sqrt(pow(s->player_x - ray->horz_x, 2.0) + pow(s->player_y - ray->horz_y, 2.0));
        ray->horz_w = ray->horz_x - (int)ray->horz_x;
        if (ray->step_y > 0)
            ray->horz_w = 1 - ray->horz_w;
    }
    else
        ray->horz_dist = INFINITY;
}

void	draw_floor_ceiling(t_data *s)
{
	unsigned int	*dst;
	unsigned int	i;

	dst = (unsigned int *)s->img.addr;
	i = WINDOW_WIDTH * WINDOW_HEIGHT / 2 + 1;
	while (--i > 0)
		*dst++ = s->parsing.ceiling_color;
	i = WINDOW_WIDTH * WINDOW_HEIGHT / 2 + 1;
	while (--i > 0)
		*dst++ = s->parsing.floor_color;
}

static float save_color(t_data *s, float dist, int color_idx, float wall_hit)
{
    s->i = color_idx;
    s->txt_width = wall_hit;
    return (dist);
}

float ft_ray(t_data *s, float angle)
{
    t_ray ray;

    init_ray(s, &ray, angle);
    while (1)
    {
        ft_ray2(s, &ray);
        if (ray.vert_dist < ray.horz_dist)
        {
            if (s->parsing.map[(int)ray.vert_y + s->parsing.start_map][(int)ray.vert_x + (ray.step_x - 1) / 2] == '1')
            {
                //  printf("ray.vert_dist = %f\n ray.step_x + 1 %d\n ray.vert_w %f\n", ray.vert_dist, ray.step_x + 1, ray.vert_w);
                return (save_color(s, ray.vert_dist, ray.step_x + 1, ray.vert_w));
            }
            else
                ray.vert_x += ray.step_x;
        }
        else
        {
            if (s->parsing.map[((int)ray.horz_y + (ray.step_y - 1) / 2) + s->parsing.start_map][(int)ray.horz_x] == '1')
            {
                // printf("ray.horz_dist = %f\n ray.step_y + 1 %d\n ray.horz_w %f\n", ray.horz_dist, ray.step_y + 1, ray.horz_w);
                return (save_color(s, ray.horz_dist, ray.step_y + 2, ray.horz_w));
            }
            else
                ray.horz_y += ray.step_y;
        }
    }
}

void draw_line(t_data *s, int w, float dist)
{
    unsigned int *dst;
    unsigned int *src;
    unsigned int h;
    float src_factor;
    float dst_shift;

    h = (float)WINDOW_HEIGHT / dist;
    src_factor = 0.0f;
    dst_shift = (float)s->texture[s->i].height / h;
    if (h > WINDOW_HEIGHT)
    {
        src_factor = 0.5f * (h - WINDOW_HEIGHT) * dst_shift;
        h = WINDOW_HEIGHT;
    }
    src = (unsigned int *)s->texture[s->i].addr;
    src += (int)((float)s->txt_width * s->texture[s->i].width);
    dst = (unsigned int *)s->img.addr + w + (WINDOW_HEIGHT - h) / 2 * WINDOW_WIDTH;
    while (h-- > 0)
    {
        *dst = *(src + ((int)src_factor) * s->texture[s->i].width);
        dst += WINDOW_WIDTH;
        src_factor += dst_shift;
    }
}

void ft_raycast(t_data *s)
{
    int x;
    float dv;
    float angle;
    static float fov;

    fov = 60 * M_PI / 180;
    angle = s->player_direction - fov / 2;
    dv = fov / (WINDOW_WIDTH - 1);
    x = 0;
    //(void)angle;
    while (x < WINDOW_WIDTH)
    {
        draw_line(s, x, ft_ray(s, angle) * cos(s->player_direction - angle));
        angle += dv;
        // printf("angle= %f\n", angle);
        x++;
    }
}

void draw_game(t_data *s)
{
    s->img.img = mlx_new_image(s->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    s->img.addr = mlx_get_data_addr(s->img.img, &s->img.bpp, &s->img.line_l, &s->img.endian);
    draw_floor_ceiling(s);
    ft_raycast(s);
    mlx_put_image_to_window(s->mlx, s->win, s->img.img, 0, 0);
}

int init_var(t_data *s)
{
    int i;

    i = -1;
    s->i = 0;
    s->txt_width = 0.0f;
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
    draw_game(s);
    mlx_hook(s->win, 17, 0, &ft_close, s);
    mlx_hook(s->win, 2, 1L<<0, &ft_keys, s);
    printf("YES %f %f %f\n", s->player_direction, s->player_x, s->player_y);
    mlx_loop(s->mlx);
}