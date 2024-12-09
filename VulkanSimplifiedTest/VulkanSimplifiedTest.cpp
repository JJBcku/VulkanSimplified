#include "pch.h"
#include <iostream>

#include "RunProgram.h"

int main()
{
    try
    {
        RunProgram();
    }
    catch (std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
    }
}
