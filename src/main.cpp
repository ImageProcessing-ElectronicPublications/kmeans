#include "kimages.h"

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        printf("Usage: %s image ncolors\n", argv[0]);
    }
    else
    {
        kimages foo(argv[1], atoi(argv[2]));
        foo.displayPalette();
    }
    return 0;
}
