#include "get_next_line.h"

int	main(void)
{
	int		i;
	char	*h;

	i = open("file", O_RDONLY | O_CREAT);
	// h = get_next_line(i);
	// printf("%s", h);
	// free(h);
	while (1)
	{
		h = get_next_line(666666666);
		if (!h)
			break ;
		printf("%s", h);
		free(h);
	}
	return (0);
}
// mange overflow in malloc