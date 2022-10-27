#include "map.h"

t_v2i	ft_crd_sw(t_v2i screen)
{
	return (ft_v2idiv(screen, 32));
}

t_v2i	ft_crd_ws(t_v2i world)
{
	return (ft_v2imul(world, 32));
}
