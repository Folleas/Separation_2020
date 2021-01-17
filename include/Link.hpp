/*
** EPITECH PROJECT, 2020
** B-MAT-500-PAR-5-1-302separation-rayann.folleas
** File description:
** Link
*/

#ifndef LINK_HPP_
#define LINK_HPP_

#include <string>

class Link {
    public:
        Link(std::string linkString);
        ~Link();

    private:
        std::string _str;
};

#endif /* !LINK_HPP_ */