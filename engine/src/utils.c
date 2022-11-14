#include "engine.h"

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

void	ft_swap(void **a, void **b)
{
	void	*c;

	c = *a;
	*a = *b;
	*b = c;
}
