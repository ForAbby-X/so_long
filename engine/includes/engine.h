#ifndef ENGINE_H
# define ENGINE_H

# define MAX_KEYS 65535
# define MAX_MOUSE 5

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <stdint.h>
# include <time.h>
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "../libft/libft.h"
# include "../libvec/inc/vec2.h"

typedef struct s_engine	t_engine;
typedef union u_color	t_color;
typedef struct s_sprite	t_sprite;
/* USER ASSIGNED STRUCT */
typedef struct s_data	t_data;

/* ENGINE SETUP */
t_engine	*ft_eng_create(size_t size_x, size_t size_y, char *title);
void		ft_eng_destroy(t_engine *eng);
int			ft_eng_play(t_engine *eng, t_data *data,
				int (*on_repeat)(t_engine *a, t_data *data, double elapsed_time));

/* ENGINE DRAWING */
/* [1] SHAPES */
int			ft_draw(t_engine *eng, t_v2i pos, t_color color);
int			ft_clear(t_engine *eng, t_color color);
int			ft_circle(t_engine *eng, t_v2i pos, int r, t_color color);
int			ft_rect(t_engine *eng, t_v2i pos, t_v2i dim, t_color color);

/* [2] SPRITE */
t_color		ft_get_color(t_sprite *spr, t_v2i pos);
int			ft_put_sprite(t_engine *eng, t_sprite *spr, t_v2i pos);
int			ft_put_sprite_s(t_engine *eng, t_sprite *spr, t_v2i pos, int d);
int			ft_put_sprite_r(t_engine *eng, t_sprite *spr,
				t_v2i pos, t_v2i cen, float rot);

/* ENGINE EVENT */
/* [1] KEYS AND MOUSE */
int			ft_eng_pressed_keys(int keycode, t_engine *eng);
int			ft_eng_pressed_mouse(int keycode, int x, int y, t_engine *eng);
int			ft_eng_released_keys(int keycode, t_engine *eng);
int			ft_eng_released_mouse(int keycode, int x, int y, t_engine *eng);
int			ft_eng_moved_mouse(int x, int y, t_engine *eng);
/* [2] CLOSING WINDOW*/
int			ft_eng_close(t_engine *eng);

/* COLOR */
t_color		ft_color_d(uint32_t d);
t_color		ft_color(uint8_t a, uint8_t r, uint8_t g, uint8_t b);
t_color		ft_color_f(float a, float r, float g, float b);
t_color		ft_color_inter(t_color col_a, t_color col_b, float n);
uint8_t		ft_color_med(t_color col);

/* SPRITE */
t_sprite	*ft_sprite(t_engine *eng, size_t dx, size_t dy);
t_sprite	*ft_sprite_p(t_engine *eng, char *path);
int			ft_destroy_sprite(t_engine *eng, t_sprite *spr);
t_sprite	*ft_cpy_sprite(t_engine *eng, t_sprite *spr);

/* UTILS */
int			ft_min(int a, int b);
int			ft_max(int a, int b);

struct	s_engine
{
	/* ENGINE */
	void			*mlx;
	void			*win;
	size_t			win_x;
	size_t			win_y;
	struct timespec	time_s;
	struct timespec	time_e;
	t_img			img;
	/* KEYS AND MOUSE */
	char	keys[MAX_KEYS + 1];
	char	mouse[MAX_MOUSE + 1];
	size_t	mouse_x;
	size_t	mouse_y;
	/* FUNCTIONAL */
	int 	(*on_repeat)(t_engine *eng, t_data *data, double elapsed_time);
	t_data	*data;
};

union	u_color
{
	uint32_t d;
	struct
	{
		uint8_t a;
		uint8_t r;
		uint8_t g;
		uint8_t b;
	};
};

struct	s_sprite
{
	t_img	img;
	t_color	*data;
	t_v2i 	size;
};

#endif
