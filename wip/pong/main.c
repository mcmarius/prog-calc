#include <stdio.h>
#include <SFML/Graphics.h>

int main()
{
    sfTime t = {1e6};
    sfSleep(t);
    printf("Hello world!\n");
    return 0;
}
