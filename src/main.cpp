/*
** EPITECH PROJECT, 2020
** B-MAT-500-PAR-5-1-302separation-rayann.folleas
** File description:
** Main
*/

#include "Engine.hpp"
#include "Graph.hpp"

bool errorHandling(int ac, char **av, bool isFileOpen, bool fileEmpty, std::size_t length)
{
    if (!isFileOpen || fileEmpty || length < 5)
        return false;
    if (ac == 3) {
        for (std::size_t i = 0; av[2][i] != '\0'; i++) if (!isdigit(av[2][i])) return false;
    }
    if (ac == 4) {
        for (std::size_t i = 0; av[2][i] != '\0'; i++) if (!isalpha(av[2][i]) && !isspace(av[2][i])) return false;
        for (std::size_t i = 0; av[3][i] != '\0'; i++) if (!isalpha(av[3][i]) && !isspace(av[3][i])) return false;
    }
    return true;
}

int main(int ac, char **av)
{
    if (ac == 1)
        return 84;
    Engine engine(av[1]);

    if (!errorHandling(ac, av, engine.isFileOpen(), engine.isFileEmpty(), engine.getFileLength()))
        return 84;
    engine.run();
    switch (ac) {
    case 3:
        engine.setDisplay(true);
        engine.displayPeople();
        engine.displayAgencyList(std::atoi(av[2]));
        engine.displaySeparationDegrees(std::atoi(av[2]));
        break;
    case 4:
        engine.setDisplay(false);
        engine.displayAgencyList(std::atoi(av[2]));
        engine.findSeparationDegree();
        std::cout << "Degree of separation between " << av[2] << " and " << av[3] << ": " << engine.getSeparationDegree(av[2], av[3]) << std::endl;
        break;
    default:
        return (84);
    }
    return (0);
}