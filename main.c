#include "get_next_line.h"

int	main(void)
{
	int		i;
	char	*h;

	i = open("hhh", O_RDONLY | O_CREAT);
	// h = get_next_line(i);
	// printf("%s", h);
	// free(h);
	while (1)
	{
		h = get_next_line(i);
		if (!h)
			break ;
		printf("%s", h);
		free(h);
	}
	return (0);
}
// -15
// 100000000000000000000000000000000000000000000000000