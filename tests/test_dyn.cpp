// test entry point

#include "test.h"
#include <iostream>
#include <cstdlib>
#include <conio.h>

void main()
{
    dyn::test::run("Dynamic typification testing");

    std::cout << "\nPress any key... ";
    getch();
}

// Unicode signature: Владимир Керимов
