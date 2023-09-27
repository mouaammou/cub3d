/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:48:00 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/27 16:04:56 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <mlx.h>
# include <limits.h>
# include <fcntl.h>

# define FOV_ANGLE 1.0471975512
# define EPSILON 1e-9
# define SCALE_MAP 0.2

typedef enum screen_data
{
	UP_KEY				= 13,
	DOWN_KEY			= 1,
	RIGHT_KEY			= 124,
	LEFT_KEY			= 123,
	A_KEY				= 0,
	D_KEY				= 2,
	ON_KEYDOWN			= 2,
	WINDOW_HEIGHT		= 1200,
	WINDOW_WIDTH		= 2400,
	ON_KEYUP			= 3,
	ON_DESTROY			= 17,
	TILE_SIZE			= 2000,
	MAP_SIZE			= 8
}t_window_data;

typedef struct player
{
	int				turn_direction;
	int				walk_direction;
	int				a_flag;
	int				move_speed;
	double			rotation_angle;
	double			x;
	double			y;
	double			rotation_speed;
}t_player;

typedef struct s_ray_casting
{
	double	_x;
	double	_y;
	int		found_horz_hit;
	int		found_vert_hit;
	double	first_p_x;
	double	first_p_y;
	double	xstep;
	double	ystep;
}t_raycasting;

typedef struct distance
{
	double	x;
	double	y;
	double	distance;
}t_distance;

typedef struct ray
{
	double	ray_angle;
	double	wall_hit_x;
	double	wall_hit_y;
	double	distance;
	int		was_hit_vertical;
	double	hit_wall_color;
}t_ray;

typedef struct texture
{
	uint32_t	*cast_texture;
	char		*tex;
	int			width;
	int			height;
}t_texture;

typedef struct x
{
	double	x;
	double	y;
}t_cords;

typedef struct hit
{
	t_cords	horz;
	t_cords	vert;
}t_hit;

typedef struct s_list
{
	char			**map;
	char			*no;
	char			*we;
	char			*ea;
	char			*so;
	int				f;
	int				c;
	int				num_col;
	int				num_row;
	int				win_width;
	int				win_height;
	int				player_x;
	int				player_y;
}t_list;

typedef struct minimap
{
	int		px;
	int		py;
	int		size;
}t_minimap;

typedef struct var
{
	int			max_top;
	t_cords		x_y_tex;
	double		wall3d_height;
	int			d_from_top;
	t_texture	texture;
	t_cords		tex_cods;
}t_var;

typedef struct cub3d
{
	void			*mlx;
	void			*win;
	void			*img;
	void			*map_img;
	unsigned int	*frame;
	unsigned int	*frame_map;
	char			**grid;
	double			scale_factor;
	t_player		myplayer;
	t_ray			*myray;
	t_cords			pos;
	int				num_ray;
	int				wall_strip_width;
	t_texture		*texture;
	t_list			*list;
	t_minimap		map;
}t_cub3d;

//map.c functions
t_cords		horizontal_increment(t_cub3d *data, int *found_hit,
				t_cords step, int i);
t_cords		vertical_increment(t_cub3d *data, int *found_hit,
				t_cords result, int i);
char		has_wall(double x, double y, t_cub3d *data);
void		free_data(t_cub3d **data);
void		render_map(t_cub3d *data);
void		fill_my_map(t_cub3d *data);
void		initialize_map(t_cub3d *data, t_list *list);
void		put_color_map(t_cub3d *data, int x, int y, int color);
void		draw_case(t_cub3d *data, int tile_x, int tile_y, int tile_color);
void		draw_line(t_cords p0, t_cords p1, t_cub3d *data, int color);
double		return_rotation_angle(t_cub3d *data);
int			destroy_window(void *param);
void		up_down_direction(t_cub3d *data, int i, t_texture *tex);
void		left_right_direction(t_cub3d *data, int i, t_texture *tex);
t_texture	what_direction(t_cub3d *data, int i);
t_cords		x_step(t_cub3d *data, int i);
t_cords		y_step(t_cub3d *data, int i);
t_var		x_y_textures(t_cub3d *data, int i);

// player functions in c
void		initialize_player(t_cub3d *data);
void		draw_line(t_cords p0, t_cords p1, t_cub3d *data, int color);
int			key_pressed(int key_code, t_cub3d *data);
void		update_position_player(t_cub3d *data);
int			key_released(int key_code, t_cub3d *data);

//ray.c functions
void		render_textures(t_cub3d *data);
void		render_rays(t_cub3d *data);
void		color_sky(t_cub3d *data);
void		color_floor(t_cub3d *data);

//put color insted of put pixel
void		put_color(t_cub3d *data, int x, int y, int color);
double		normalize_ray_angle(double angle);
double		distance(double x1, double y1, double x2, double y2);

//test ray
void		casting(double rayAngle, t_cub3d *data, int i);

//normalize angle
double		normalize_ray_angle(double angle);
int			is_ray_down(double angle);
int			is_ray_up(double angle);
int			count_lines(int fd);
int			is_ray_right(double angle);
int			is_ray_left(double angle);
double		distance(double x1, double y1, double x2, double y2);
int			is_in_map(t_cub3d *data, double x, double y);
void		get_textures(t_cub3d *data);
long		ft_atoi(const char *str);
void		ft_putstr_fd(char *s, int fd);
char		**ft_split(char const *s, char c);
int			ft_strcmp(const char *first, const char *second);
size_t		ft_strlen(const char *str);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			is_white_space(char c);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strdup(char *s1);
char		*get_next_line(int fd);
void		error(char *str);
void		free_2d_tab(char **tab);
t_list		*parsing(int argc, char **argv);
void		free_list(t_list **list);
void		check_number_of_args(int argc);
void		check_extension(char **argv);
char		**read_map(char **argv, int count);
int			count_lines(int fd);
char		**get_map(char **argv);
t_list		*create_and_initialize_list(void);
int			line_of_white_spaces(char *s);
char		*get_value_of_elmnts(char *line, int j);
void		check_is_digit(char *s);
void		check_f_and_c(char *value);
void		add_value(t_list *list, char *value, int flag);
int			create_trgb(int t, int r, int g, int b);
int			get_rgb_value(char *value);
void		check_elem_and_value(char *line, char *sub, int j, t_list *list);
int			count_max_size(char **map);
char		*al_spaces(int len);
char		**join_line_with_spaces(char **map, int count);
void		check_first_and_last_line(char *s);
void		check_elements(char **m);
int			check_four_sides(char **map, int i, int j);
void		check_middle_lines(char **m);
void		pars_map(t_list *list, char **map);
void		fill_struct(char **argv, t_list *list);
int			*return_dim(char **map);
void		continue_filling_struct(t_list *list);
void		free_data(t_cub3d **data);
#endif
