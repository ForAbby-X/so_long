#include "engine.h"

/* NEED TO ADD ELAPSED TIME CALCULATION */
static int	ft_eng_loop(t_engine *eng)
{
	int	flag;

	flag = eng->on_repeat(eng, eng->data, 0.0f);
	mlx_put_image_to_window(eng->mlx, eng->win, eng->img.image, 0, 0);
	if (flag == 0)
		ft_eng_close(eng);
	return (flag);
}

static	void	ft_setup_hooks(t_engine *eng)
{
	mlx_hook(eng->win, 2, (1L << 0), (&ft_eng_pressed_keys), eng);
	mlx_hook(eng->win, 3, (1L << 1), (&ft_eng_released_keys), eng);
	mlx_hook(eng->win, 4, (1L << 2), (&ft_eng_pressed_mouse), eng);
	mlx_hook(eng->win, 5, (1L << 3), (&ft_eng_released_mouse), eng);
	mlx_hook(eng->win, 6, (1L << 6), (&ft_eng_moved_mouse), eng);
	mlx_hook(eng->win, 17, (0L), (&ft_eng_close), eng);
	mlx_loop_hook(eng->mlx, (&ft_eng_loop), eng);
}

t_engine	*ft_eng_create(size_t size_x, size_t size_y, char *title)
{
	t_engine	*eng;

	eng = malloc(sizeof(t_engine));
	if (eng == NULL)
		return (NULL);
	eng->mlx = mlx_init();
	if (eng->mlx == NULL)
		return (free(eng), NULL);
	eng->win = mlx_new_window(eng->mlx, size_x, size_y, title);
	if (eng->win == NULL)
		return (free(eng->mlx), free(eng), NULL);
	eng->img.image = mlx_new_image(eng->mlx, size_x, size_y);
	eng->img.data = mlx_get_data_addr(eng->img.image, &eng->img.bpp,
			&eng->img.size_line, &eng->img.format);
	ft_setup_hooks(eng);
	ft_memset(eng->keys, 0, MAX_KEYS + 1);
	ft_memset(eng->mouse, 0, MAX_MOUSE + 1);
	eng->win_x = size_x;
	eng->win_y = size_y;
	eng->mouse_x = 0;
	eng->mouse_y = 0;
	eng->on_repeat = NULL;
	return (eng);
}

void	ft_eng_destroy(t_engine *eng)
{
	mlx_destroy_image(eng->mlx, eng->img.image);
	mlx_destroy_window(eng->mlx, eng->win);
	mlx_destroy_display(eng->mlx);
	free(eng);
}

int	ft_eng_play(t_engine *eng, t_data *data,
		int (*on_repeat)(t_engine *eng, t_data *data,float elapsed_time))
{
	if (on_repeat)
	{
		eng->data = data;
		eng->on_repeat = on_repeat;
		mlx_loop(eng->mlx);
	}
	return (1);
}

