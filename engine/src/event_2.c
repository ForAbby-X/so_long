#include "engine.h"

int	ft_eng_close(t_engine *eng)
{
	mlx_loop_end(eng->mlx);
	return (0);
}
