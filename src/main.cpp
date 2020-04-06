/*
** EPITECH PROJECT, 2020
** cpp_pool
** File description:
** .cpp
*/

#include "../include/Core.hpp"

int dash_h()
{
    std::cout << "USAGE"<< std::endl;
    std::cout << "    ./arcade lib\n"<< std::endl;
    std::cout << "DESCRIPTION"<< std::endl;
    std::cout << "    lib    choose which lib you want to use to start the game"<< std::endl;
    return 0;
}

int main(int ac, char **av)
{
    if (ac < 2) {
        //usage();
        return (84);
    }
    if (!strcmp(av[1], "-h")) {
        return(dash_h());
    }
    Core core;
    core.load(av[1]);
    core.run(av[1]);
    return (0);
}