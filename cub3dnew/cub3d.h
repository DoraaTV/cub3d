/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrio <thrio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:36:04 by thrio             #+#    #+#             */
/*   Updated: 2023/12/13 17:03:46 by thrio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# include "mlx_linux/mlx.h"
# include "mlx_linux/mlx_int.h"
# include <X11/Xlib.h>
# include <ctype.h>
# include <fcntl.h>
# include <math.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WINDOW_HEIGHT 1280
# define M_PI 3.14159265358979323846
# define WINDOW_WIDTH 1280

# define MAX_LINE_LENGTH 1024
# define MAX_MAP_SIZE_X 24
# define MAX_MAP_SIZE_Y 24

typedef struct s_rgb
{
	int			r;
	int			g;
	int			b;
}				t_rgb;

typedef struct s_parsing
{
	t_rgb		rgb;
	int			b;
	int			num_lines;
	int			ligne_vide;
	int			*n_ptr;
	int			config_count;
	int			map_count;
	char		buffer[MAX_LINE_LENGTH];
	int			counter;
	int			counter2;
	char		current_char;
	int			line_index;
	int			config_size;
	int			floor_value_1;
	int			floor_value_2;
	int			floor_value_3;
	int			floor_color;
	int			sky_value_1;
	int			sky_value_2;
	int			sky_value_3;
	int			ceiling_color;
	int			r_value_x;
	int			r_value_y;
	char		*no_txt;
	char		*so_txt;
	char		*we_txt;
	char		*ea_txt;
	char		*s_texture_value;
	char		**map;
	int			sign_count;
	int			map_height;
	int			start_map;
	char		**copied_map;
	char		**config_elements;
	char		*line;
}				t_parsing;

typedef struct s_image
{
	void		*img;
	char		*addr;
	int			bpp;
	int			endian;
	int			line_l;
	int			width;
	int			height;
}				t_image;

typedef struct s_ray
{
	float		dir_x;
	float		dir_y;
	int			step_x;
	int			step_y;
	float		vert_x;
	float		vert_y;
	float		horz_x;
	float		horz_y;
	float		vert_dist;
	float		horz_dist;
	float		vert_w;
	float		horz_w;
}				t_ray;

typedef struct s_data
{
	t_parsing	parsing;
	t_image		img;
	t_image		*texture;

	void		*win;
	void		*mlx;

	int			i;
	float		player_x;
	float		player_y;
	float		player_direction;
	float		txt_width;

	int			a[2];
	int			facing_left;
	int			vhit;
	float		theta;

}				t_data;

int				check_no_wall();
int				map_closed();
int				check_all_wall_closed(t_parsing *parsing, int i);
int				map_less_3_lines();
int				check_texture_value(char **text_file, char *name_texture,
					t_parsing *parsing);
void			too_much_player(t_parsing *parsing, int *player_count,
					int start);
int				correct_number2(t_parsing *parsing, char current_char,
					char *player_chars);
int				check_nbr_player();
int				check_last_wall(t_parsing *parsing);
int				correct_number(t_parsing *parsing);
void			correct_number3(t_parsing *parsing, char current_char, int i,
					char *player_chars);
void			init_textures(t_parsing *parsing);
int				free_init_window(t_data *s);
int				check_map_section(t_parsing *parsing, int num_lines, int i, int j);
int				open_file(const char *filename, int *fd);
int				resize_and_copy(char ***array, int current_size, int new_size);
int				ft_get_size(char *file_cub3d_name, t_parsing *s);
int				parsing(char *file_cub3d_name, t_data *data);
int 			check_all_text(t_parsing *parsing);
void			free_gnl(int fd, char *line);
void 			ft_free_process(t_parsing *parsing, int fd);
char			*ft_strdup(const char *s);
void			*ft_calloc(size_t nmemb, size_t size);
void			*ft_memset(void *s, int c, size_t n);
int				parsing_rgbs();
int				parsing_resolution();
int				parsing_textures();
int				check_map_prefixes();
int				parsing_cub3d(char **text_file, t_parsing *parsing);
int				put_text_struct(char *file_cub3d_name, t_parsing *parsing);
int				free_parsing2(t_parsing *parsing);
int				put_map_in_struct(t_parsing *parsing);
int				check_nbr_directions(t_parsing *parsing);
int				free_parsing(t_parsing *parsing);
int				free_parsing2(t_parsing *parsing);
char			*ft_check_file(char *dst, t_data *s, int i);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				rgb_to_hex_floor(t_parsing *parsing);
int				rgb_to_hex_sky(t_parsing *parsing);
int				parsing_rgbs_sky(char **text_file, t_parsing *parsing);
int				parse_rgb(char *str, int *r, int *g, t_parsing *parsing);
int				parsing_rgbs_floor(char **text_file, t_parsing *parsing);
int				is_digit(char c);
int				print_error_rgb(t_parsing *parsing);
int				print_error_rgb_value(t_parsing *parsing, int i);

/*EXECUTION*/
void			ft_raycasting(t_data *s);
void			ft_find_player(t_data *s);
int				ft_key_press(int key, t_data *cub3d);
int				ft_key_release(int key, t_data *cub3d);

int				ft_move_forward(t_data *s, int speed);
int				ft_move_left(t_data *s, int speed);
int				ft_rotateminus(t_data *s);
int				ft_rotate(t_data *s);
void			ft_free(t_data *s);
int				ft_init_textures(t_data *s);
float			ft_ray(t_data *s, float angle);
int				ft_close(t_data *s);
void			ft_free_txt(t_data *s, int i);
float			ft_sign(float n);
int				ft_keys(int key, t_data *s);
void			draw_game(t_data *s);
void			draw_line(t_data *s, int w, float dist);
void			draw_floor_ceiling(t_data *s);
void			free_texture(t_parsing *parsing);

/*GNL*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 7
# endif

char			*ft_copy_before(char *buffer);
char			*ft_copy_after(char *buffer);
char			*ft_read_my_varstatic(int fd, char *varstatic);
char			*get_next_line(int fd);
char			*ft_strdup(const char *s1);
char			*ft_strjoin(char *s1, char *s2);
int				ft_search_newline(char *varstatic);
size_t			ft_strlen(const char *s);
int				ft_lenbuffern(char *buffer);

#endif