#ifndef ENGINE_H
# define ENGINE_H

# define MAX_KEYS 65535
# define MAX_MOUSE 5

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "../libft/libft.h"

typedef struct s_engine	t_engine;
typedef union u_color	t_color;
typedef struct s_sprite	t_sprite;
/* USER ASSIGNED STRUCT */
typedef struct s_data	t_data;

/* ENGINE SETUP */
t_engine	*ft_eng_create(size_t size_x, size_t size_y, char *title);
void		ft_eng_destroy(t_engine *eng);
int			ft_eng_play(t_engine *eng, t_data *data,
				int (*on_repeat)(t_engine *a, t_data *data,float elapsed_time));

/* ENGINE DRAWING */
/* [1] DRAW */
int	ft_draw(t_engine *eng, int x, int y, t_color color);
int	ft_clear(t_engine *eng, t_color color);
int	ft_circle(t_engine *eng, int x, int y, int r, t_color color);

/* ENGINE EVENT */
/* [1] KEYS AND MOUSE */
int	ft_eng_pressed_keys(int keycode, t_engine *eng);
int	ft_eng_pressed_mouse(int keycode, int x, int y, t_engine *eng);
int	ft_eng_released_keys(int keycode, t_engine *eng);
int	ft_eng_released_mouse(int keycode, int x, int y, t_engine *eng);
int	ft_eng_moved_mouse(int x, int y, t_engine *eng);
/* [2] CLOSING WINDOW*/
int	ft_eng_close(t_engine *eng);

/* SPRITE COLOR */
t_color		ft_color(unsigned int d);
t_sprite	*ft_sprite(size_t dx, size_t dy);
t_sprite	*ft_sprite_p(t_engine *eng, char *path);
int			ft_destroy_sprite(t_sprite *spr);
int			ft_put_sprite(t_engine *eng, t_sprite *spr, int x, int y);

struct	s_engine
{
	/* ENGINE */
	void	*mlx;
	void	*win;
	size_t	win_x;
	size_t	win_y;
	t_img	img;
	/* KEYS AND MOUSE */
	char	keys[MAX_KEYS + 1];
	char	mouse[MAX_MOUSE + 1];
	size_t	mouse_x;
	size_t	mouse_y;
	/* FUNCTIONAL */
	int 	(*on_repeat)(t_engine *eng, t_data *data,float elapsed_time);
	t_data	*data;
};

union	u_color
{
	unsigned int d;
	struct
	{
		unsigned char a;
		unsigned char r;
		unsigned char g;
		unsigned char b;
	};
};

struct	s_sprite
{
	t_color	*data;
	size_t	size_x;
	size_t	size_y;
};

#endif
