// test entry point

#include <iostream>
#include <conio.h>
#include <string>

namespace dyn
{
    bool test_object(std::string& message);
    bool test_scalar(std::string& message);
}

void main()
{
    try
    {
        std::string message;
        std::cout << "test object: ";
        if (dyn::test_object(message))
            std::cout << "OK";
        else
            std::cout << "FAIL " << message;
        std::cout << std::endl;
    }
    catch (std::exception& error)
    {
        std::cout << "ERROR: " << error.what() << std::endl;
    }

    try
    {
        std::string message;
        std::cout << "test scalar: ";
        if (dyn::test_scalar(message))
            std::cout << "OK";
        else
            std::cout << "FAIL " << message;
        std::cout << std::endl;
    }
    catch (std::exception& error)
    {
        std::cout << "ERROR: " << error.what() << std::endl;
    }

    std::cout << "Press any key... ";
    getch();
}

// Unicode signature: Владимир Керимов
