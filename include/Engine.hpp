/*
** EPITECH PROJECT, 2020
** B-MAT-500-PAR-5-1-302separation-rayann.folleas
** File description:
** Regex
*/

#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include "Link.hpp"
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <bits/stdc++.h>
#include <algorithm>
#include "Person.hpp"

class Engine {
    public:
        Engine(std::string filePath);
        ~Engine();

        void run();

        void displayPeople();
        void displayAgencyList(std::size_t n);
        void displaySeparationDegrees(std::size_t n);

        static bool compareString(std::shared_ptr<Person> person1, std::shared_ptr<Person> person2);
        std::shared_ptr<Person> findPerson(std::string name);
        bool areFriends(std::shared_ptr<Person> person1, std::shared_ptr<Person> person2);
        void manageRelation(std::pair<std::string, std::string> names);

        void findSeparationDegree();
        int getSeparationDegree(std::string person1, std::string person2);

        void setDisplay(bool status);

        std::pair<std::string, std::string> getRelatedPeople(std::string line);
        std::size_t getFileLength() const {
            return _fileLength;
        }
        bool isFileOpen();
        bool isFileEmpty();
    private:
        std::size_t n;
        bool _display;
        bool _fileOpen;
        bool _fileEmpty;
        std::size_t _fileLength;
        std::fstream _fileStream;
        std::vector<std::shared_ptr<Person> > _people;
        std::vector<std::vector<int>> _agencyMatrix;
};

#endif /* !ENGINE_HPP */
