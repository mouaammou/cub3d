/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:38:07 by mouaammo          #+#    #+#             */
/*   Updated: 2023/09/25 20:06:14 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <mlx.h>
# include <limits.h>
# include <float.h>
# include <sys/types.h>
# include <fcntl.h>
# include <string.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif


#define FOV_ANGLE (60 * (M_PI / 180))
#define EPSILON 1e-9
#define SCALE_MAP 0.2

typedef enum screen_data
{
	UP_KEY				= 13,
	DOWN_KEY			= 1,
	RIGHT_KEY			= 124,
	LEFT_KEY			= 123,
	A_KEY				= 0,
	D_KEY				= 2,
	ON_KEYDOWN			= 2,
	WINDOW_HEIGHT		= 1100,
	WINDOW_WIDTH		= 2000,
	ON_KEYUP			= 3,
	ON_DESTROY			= 17,
	TILE_SIZE			= 2000,
	MAP_SIZE			= 10
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
	uint32_t *cast_texture;
	char	*tex;
	int		width;
	int		height;
}t_texture;


typedef struct x
{
	double x;
	double y;
}t_cords;

typedef struct s_list
{
	char			**map;
	char			*NO;
	char			*WE;
	char			*EA;
	char			*SO;
	int				F;
	int				C;
	int				num_col;
	int				num_row;
	int				win_width;
	int				win_height;
	int				player_x;
	int				player_y;
}t_list;

typedef struct minimap
{
	double	ray_x;
	double	ray_y;
	int		px;
	int		py;
}t_minimap;

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
char	has_wall(double x, double y, t_cub3d *data);
void	render_map(t_cub3d *data);
void	fill_my_map(t_cub3d *data);
void	initialize_map(t_cub3d *data, t_list *list);
void	put_color_map(t_cub3d *data, int x, int y, int color);
void	draw_case(t_cub3d *data, int tile_x, int tile_y, int tile_color);
void	draw_line(t_cords p0, t_cords p1, t_cub3d *data, int color);

// player functions in c
void	initialize_player(t_cub3d *data);
void	render_player(t_cub3d *data);
void	draw_line(t_cords p0, t_cords p1, t_cub3d *data, int color);
int		move_player(int keycode, t_cub3d *data);
void	update_position_player(t_cub3d *data);
int		key_released(int key_code, t_cub3d *data);

//ray.c functions
void	render_textures(t_cub3d *data);
void	render_rays(t_cub3d *data);
void	ray_casting(t_cub3d *data, int i);
void	color_sky(t_cub3d *data);
void	color_floor(t_cub3d *data);

//put color insted of put pixel
void	put_color(t_cub3d *data, int x, int y, int color);
double normalize_ray_angle(double angle);
double	distance(double x1, double y1, double x2, double y2);

//test ray
void casting(double rayAngle, t_cub3d *data, int i);

//normalize angle
double	normalize_ray_angle(double angle);
int		is_ray_down(double angle);
int		is_ray_up(double angle);
int		is_ray_right(double angle);
int		is_ray_left(double angle);
double	distance(double x1, double y1, double x2, double y2);
int		is_in_map(t_cub3d *data, double x, double y);

//render cube 3d projection
void	render_cube_3d(t_cub3d *data);
void	get_textures(t_cub3d *data);

//libft
long	ft_atoi(const char *str);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
int		ft_strcmp(const char *first, const char *second);
size_t	ft_strlen(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		is_white_space(char c);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strchr(char *str, char c);
char	*ft_strdup(char *s1);
char	*get_next_line(int fd);
void	error(char *str);
void	free_2d_tab(char **tab);

// parsing

void	free_list(t_list *list);
t_list	*parsing(int argc, char **argv);

#endif
