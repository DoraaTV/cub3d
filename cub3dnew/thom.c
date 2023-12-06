#include "cub3d.h"

float pi = 3.14159265358979323846;

int map[]=
{
 1,1,1,1,1,1,1,1,
 1,0,1,0,0,0,0,1,
 1,0,1,0,0,0,0,1,
 1,0,1,0,0,0,0,1,
 1,0,0,0,0,0,0,1,
 1,0,0,0,0,1,0,1,
 1,0,0,0,0,0,0,1,
 1,1,1,1,1,1,1,1,    
};

int    drawPlayer(t_data *s);

double	degToRad(double a)
{
	return (a * M_PI / 180.0);
}
double	fixang(double a)
{
	if (a > 360.0)
		a -= 360.0;
	if (a < 0)
		a += 360.0;
	return (a);
}

double	dist(float ax, float ay, float bx, float by)
{
	return (sqrt(((bx - ax) * (bx - ax)) + ((by - ay) * (by - ay))));
}

int closer(t_data *s)
{
    mlx_destroy_window(s->mlx, s->win);
    exit(0);
}

int    key_event(int button, t_data *s)
{
    (void)s;
    if (button == 65307)
        closer(s);
    // if (button == 65361) { s->player_direction+=5; s->player_direction=FixAng(s->player_direction); s->player_dx=cos(degToRad(s->player_direction)); s->player_dy=-sin(degToRad(s->player_direction));}
    // if (button == 65363) { s->player_direction-=5; s->player_direction=FixAng(s->player_direction); s->player_dx=cos(degToRad(s->player_direction)); s->player_dy=-sin(degToRad(s->player_direction));} 
    if (button == 65361) { s->player_direction -= 0.1 ; s->player_dx = cos(s->player_direction) * 5; s->player_dy = sin(s->player_direction) * 5;}
    if (button == 65363) { s->player_direction += 0.1 ; s->player_dx = cos(s->player_direction) * 5; s->player_dy = sin(s->player_direction) * 5;}
    if (button == 65362) { s->player_x += s->player_dx * 5; s->player_y += s->player_dy * 5;}
    if (button == 65364) { s->player_y -= s->player_dy * 5; s->player_x -= s->player_dx * 5;}
    // drawPlayer(s);
    return (0);
}

// int drawMap2d(t_data *s)
// {
//     int x = 0;
//     int y = 0;
//     int mapX = 8;
//     int mapY = 8;
//     int color;
//     int xo;
//     int yo;
//     // mlx_clear_window(s->mlx, s->win);

//     while(y < mapY)
//     {
//         while(x < mapX)
//         {
//             if(map[y*mapX+x]==1){ color = 0x288BA8;} else{ color = 0xFFFFFF;}
//             xo = x * 64; yo = y * 64;
//             while (xo < (x * 64) + 64)
//             {
//                 while (yo < (y * 64) + 64)
//                 {
//                     mlx_pixel_put(s->mlx, s->win, xo, yo, color);
//                     yo++;
//                 }
//                 yo = y * 64;
//                 xo++;
//             }
//             x++;
//         }
//         x = 0;
//         y++;
//     }

//     return (0);
// }

// int    drawPlayer(t_data *s)
// {
//     int i;
//     int j;
//     int x;
//     int y;

//     // mlx_clear_window(s->mlx, s->win);
//     drawMap2d(s);
//     i = 0;
//     j = 0;
//     x = s->player_x / 2;
//     y = s->player_y / 2;
//     while (i < 10)
//     {
//         while (j < 10)
//         {
//             mlx_pixel_put(s->mlx, s->win, x + i, y + j, 0x00FF0000);
//             j++;
//         }
//         j = 0;
//         i++;
//     }

//     i = 0;
//     while (i < 30)
//     {
//         mlx_pixel_put(s->mlx, s->win, x + (s->player_dx * i), y + (s->player_dy * i), 0x00FF0000);
//         i++;
//     }
    
    
//     return (0);
// }

int compare(int a, t_data *s)
{
    if (a == 'N' || a == 'W' || a == 'S' || a == 'E')
    {
        if (a == 'N')
            s->player_direction = 270;
        else if (a == 'W')
            s->player_direction = 180;
        else if (a == 'S')
            s->player_direction = 90;
        else if (a == 'E')
            s->player_direction = 0;
        return (1);
    }
    return (0);
}

void    get_player_pos(t_data *s)
{
    int i = s->parsing.start_map;
    int j;

    while (s->parsing.map[i])
    {
        j = 0;
        while (s->parsing.map[i][j])
        {
            if (compare(s->parsing.map[i][j], s) == 1)
            {
                printf("coucou %d %d\n", i, j);
                s->player_x = (i - s->parsing.start_map) * 64;
                s->player_y = j * 64;
                printf("%d %d\n", s->player_x, s->player_y);
                return ;
            }
            j++;
        }
        i++;
    }
}

void ft_pixel_put(t_data *s, int x, int y, int color)
{
    char *dst;

    dst = s->addr + (y * s->llen[0] + x * (s->bpp[0] / 8));
    *(unsigned int*)dst = color;
}

void draw_line_4(t_data *s, float y1, double lineh, float x)
{
    char *dst;
    int i;

    i = 0;
    if (lineh > WINDOW_HIGHT)
        i = (lineh - WINDOW_HIGHT) / 2;
    while (i < lineh)
    {
        if (y1 >= WINDOW_HIGHT)
            break ;
        if ((s->ray_angle >= 0 && s->ray_angle <= 90) || (s->ray_angle > 270 && s->ray_angle <= 360))
            dst = s->parsing.we_texture_value + (int)(i * (s->w_h / lineh)) % s->w_h * s->llen[3] + (int)(x * s->w_w / 50) % s->w_w * (s->bpp[3] / 8);
        if (s->ray_angle > 90 && s->ray_angle <= 270)
            dst = s->parsing.ea_texture_value + (int)(i * (s->e_h / lineh)) % s->e_h * s->llen[4] + (int)(x * s->e_w / 50) % s->e_w * (s->bpp[4] / 8);
        ft_pixel_put(s, s->i, y1, *(unsigned int*)dst);
        y1++;
        i++;
    }
}

void draw_line_3(t_data *s, float y1, double lineh, float x)
{
    char *dst;
    int i;

    i = 0;
    if (lineh > WINDOW_HIGHT)
        i = (lineh - WINDOW_HIGHT) / 2;
    while (i < lineh)
    {
        if (y1 >= WINDOW_HIGHT)
            break ;
        if (s->ray_angle > 180 && s->ray_angle <= 360)
            dst = s->parsing.no_texture_value + (int)(i * (s->n_h / lineh)) % s->n_h * s->llen[1] + (int)(x * s->n_w / 50) % s->n_w * (s->bpp[1] / 8);
        if (s->ray_angle > 0 && s->ray_angle <= 180)
            dst = s->parsing.so_texture_value + (int)(i * (s->s_h / lineh)) % s->s_h * s->llen[2] + (int)(x * s->s_w / 50) % s->s_w * (s->bpp[2] / 8);
        ft_pixel_put(s, s->i, y1, *(unsigned int*)dst);
        y1++;
        i++;
    }
}

void draw_sky(t_data *s, float lineo)
{
    int i;

    i = 0;
    while (i < lineo)
    {
        ft_pixel_put(s, s->i, i, s->parsing.sky_value_1);
        i++;
    }
}

void draw_floor(t_data *s, double lineh, float lineo)
{
    int j;

    j = (int)(lineh + lineo);
    while (j < WINDOW_HIGHT)
    {
        ft_pixel_put(s, s->i, j, s->parsing.floor_value_1);
        j++;
    }
}

void render3d(t_data *s, float x, float y, int i)
{
    double lineh;
    double ch;
    double len;
    float lineo;
    double ca;

    ca = fixang(s->player_direction - s->ray_angle);
    len = dist(s->player_x, s->player_y, x, y);
    len = len * cos(degToRad(ca));
    lineh = (50 * WINDOW_HIGHT) / len;
    ch = lineh;
    if (lineh > WINDOW_HIGHT)
        lineh = WINDOW_HIGHT;
    //lineh est la hauteur de la ligne a tracer
    //lineo est la position de la ligne a tracer
    //ch est la hauteur de la ligne a tracer
    lineo = (WINDOW_HIGHT / 2) - (lineh / 2);
    (void)ch;
    (void)lineo;
    if (i == 1)
        draw_line_3(s, lineo, ch, x);
    else
        draw_line_4(s, lineo, ch, y);
    draw_floor(s, lineh, lineo);
    draw_sky(s, lineo);
}

void castrays2(t_data *s, double x, double y)
{
    double x2;
    double y2;

    x2 = (cos(degToRad(s->ray_angle)) * 5);
    y2 = (sin(degToRad(s->ray_angle)) * 5);
    while (1)
    {
        // ces deux calculs sont pour afficher selon l'angle du joueur (ce qui est present dans son rayon)
        if (s->parsing.map[(int)(y / 50) + s->parsing.start_map][(int) (x + x2 / 64) / 50] == '1')
        {
            x += x2 / 64;
            render3d(s, x, y, 0);
            return ;
        }
        if (s->parsing.map[(int)(y + y2 / 64) + s->parsing.start_map][(int) (x / 50)] == '1')
        {
            y += y2 / 64;
            render3d(s, x, y, 1);
            return ;
        }
        x += x2 / 64;
        y += y2 / 64;
    }
}

void castrays(t_data *s, double x, double y)
{
    double x2;
    double y2;

    x2 = s->player_x;
    y2 = s->player_y;
    while (1)
    {
        // ces deux calculs sont pour afficher selon l'angle du joueur (ce qui est present dans son rayon)
        if (s->parsing.map[((int)(y2) / 50) + s->parsing.start_map][(int) (x2 + x / 4 )/ 50] != '0')
        {
            castrays2(s, x2, y2);
            return ;
        }
        if (s->parsing.map[(int)(y2 + y / 4) + s->parsing.start_map][(int) (x2) / 50] != '0')
        {
            castrays2(s, x2, y2);
            return ;
        }
        x2 += x / 4;
        y2 += y / 4;
    }
}

void    draw_rays(t_data *s)
{
    double x;
    double y;

    s->ray_angle = fixang(s->player_direction - 30);
    s->i = 0;
    while (s->i < 60)
    {
        x = (cos(degToRad(s->ray_angle)) * 5);
        y = (sin(degToRad(s->ray_angle)) * 5);
        castrays(s, x, y);
        s->i++;
        s->ray_angle = 60.0 / WINDOW_WIDTH;
        s->ray_angle = fixang(s->ray_angle);
    }
}

int init_window(t_data s)
{
    s.mlx = mlx_init();
    // printf("r x = %d\n r y =%d\n", s.parsing.r_value_x, s.parsing.r_value_y);
    get_player_pos(&s);
    mlx_get_screen_size(s.mlx, &s.parsing.r_value_x, &s.parsing.r_value_y);
    s.win= mlx_new_window(s.mlx, s.parsing.r_value_x, s.parsing.r_value_y, "cub3d");
    s.player_dx = cos(degToRad(s.player_direction));
    s.player_dy = sin(degToRad(s.player_direction));
    mlx_hook(s.win, 2, 1L << 0, key_event, &s);
    mlx_hook(s.win, 17, 0, closer, &s);
    // drawPlayer(&s);
    draw_rays(&s);
    // mlx_loop_hook(s.mlx, drawMap2d, &s);
    mlx_loop(s.mlx);
    return (0);
}