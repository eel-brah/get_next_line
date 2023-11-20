
#include "get_next_line.h"

int main()
{
    int i = open("file",  O_RDONLY | O_CREAT);
    char *h;
    // h = get_next_line(i);
    // printf("%s", h);
    // free(h);
    // h = get_next_line(i);
    // printf("%s", h);
    // free(h);
    // h = get_next_line(i);
    // printf("%s", h);
    // free(h);
    // h = get_next_line(i);
    // printf("%s", h);
    // free(h);
    // h = get_next_line(i);
    // printf("%s", h);
    // free(h);
    // h = get_next_line(i);
    // printf("%s", h);
    // free(h);
    while (1)
    {
        h = get_next_line(i);
        if (!h)
            break;
        printf("%s", h);
        free(h);
    }
}