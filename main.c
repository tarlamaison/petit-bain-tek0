#include <unistd.h>

void my_putchar(char c)
{
    write(1, &c, 1);
}

int main(void)
{
    // Mettez votre code ici
    // ex:
    // my_putchar('a');
}
