
#include <libc.h>
void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str;

	str = s;
	while (n--)
		*str++ = '\0';
}
void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*p;
	size_t			s;

	if ((int)count < 0 && (int)size < 0)
		return (NULL);
	s = count * size;
	p = malloc(s);
	if (!p)
		return (NULL);
	ft_bzero((void *)p, s);
	return ((void *)p);

}

int main()
{
    if (!ft_calloc(30198988799, 30198988799))
        printf("NULL");
}