#include <cstdio>
#include <stdlib.h>
#include <unistd.h>

#include "shell.h"

#pragma GCC diagnostic (push)
#pragma GCC diagnostic(disable: "-Wwrite-strings")

int main()
{
    eventLoop();

    return 0;
}

#pragma GCC diagnostic pop
