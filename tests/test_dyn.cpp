// test entry point

#include "test.h"
#include <iostream>
#include <cstdlib>
#include <conio.h>

void main()
{
    dyn::test::run("dynamic typification testing");

    std::cout << "Press any key... ";
    getch();
}

// Unicode signature: Владимир Керимов
