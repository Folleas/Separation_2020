/*
** EPITECH PROJECT, 2020
** B-MAT-500-PAR-5-1-302separation-rayann.folleas
** File description:
** Engine
*/

#include "Engine.hpp"

Engine::Engine(std::string filePath)
{
    this->_fileStream.open(filePath.c_str(), std::ios::in);
    this->_fileOpen = _fileStream.is_open();
    this->_fileEmpty = _fileStream.peek() == std::ifstream::traits_type::eof();
    std::string tmp;
    this->_fileLength = 0;
    std::fstream fileStream;
    fileStream.open(filePath.c_str(), std::ios::in);
    if (this->_fileOpen && !this->_fileEmpty) {
        while(getline(fileStream, tmp)) {
            for (char c : tmp) {
                this->_fileLength++;
            }
        }
    }
}

Engine::~Engine()
{
}

bool Engine::isFileOpen()
{
    return _fileOpen;
}

bool Engine::isFileEmpty()
{
    return _fileEmpty;
}


std::pair<std::string, std::string> Engine::getRelatedPeople(std::string line)
{
    std::pair<std::string, std::string> names;

    std::string delimiter(" is friends with ");
    auto delimiterPos = line.find(delimiter);
    names.first = line.substr(0, delimiterPos);
    names.second = line.substr(delimiterPos + delimiter.length());
    return names;
}

std::shared_ptr<Person> Engine::findPerson(std::string name)
{
    std::shared_ptr<Person> person = std::make_shared<Person>();

    for (std::shared_ptr<Person> tmp : this->_people) {
        if (name == tmp->getName()) {
            person = tmp;
            return person;
        }
    }
    person->setName(name);
    this->_people.push_back(person);
    return person;
}

bool Engine::areFriends(std::shared_ptr<Person> person1, std::shared_ptr<Person> person2)
{
    for (std::shared_ptr<Person> person : person1->getFriends()) {
        if (person == person2)
            return true;
    }
    return false;
}

void Engine::manageRelation(std::pair<std::string, std::string> names)
{
    std::shared_ptr<Person> person1 = findPerson(names.first);
    std::shared_ptr<Person> person2 = findPerson(names.second);

    for (std::shared_ptr<Person> tmp : this->_people) {
        if (names.first == tmp->getName() && !areFriends(person1, person2)) {
            person1->addFriend(person2);
            person2->addFriend(person1);
        }
    }
}

bool Engine::compareString(std::shared_ptr<Person> person1, std::shared_ptr<Person> person2)
{
    return person1->getName() < person2->getName();
}

void Engine::findSeparationDegree()
{
    for (std::size_t y = 0; y != this->_agencyMatrix.size(); y++)
        for (std::size_t x = 0; x != this->_agencyMatrix.at(y).size(); x++)
            if (x != y && this->_agencyMatrix.at(y).at(x) == 0)
                this->_agencyMatrix.at(y).at(x) = 123456;
    for (std::size_t k = 0; k < this->_agencyMatrix.at(0).size(); k++)
        for (std::size_t i = 0; i < this->_agencyMatrix.at(0).size(); i++)
            for (std::size_t j = 0; j < this->_agencyMatrix.at(0).size(); j++)
                this->_agencyMatrix.at(j).at(i) = std::min(this->_agencyMatrix.at(j).at(i), this->_agencyMatrix.at(k).at(i) + this->_agencyMatrix.at(j).at(k));
}

void Engine::run()
{
    std::string tmp;
    while(getline(this->_fileStream, tmp)) {
        manageRelation(getRelatedPeople(tmp));
    }
    std::sort(this->_people.begin(), this->_people.end(), Engine::compareString);
    this->_fileStream.close();
}

void Engine::displayPeople()
{
    for (std::shared_ptr<Person> person : this->_people)
        std::cout << person->getName() << std::endl;
    std::cout << std::endl;
}

void Engine::setDisplay(bool status)
{
    this->_display = status;
}

void Engine::displayAgencyList(std::size_t n)
{
    this->n = n;
    for (std::shared_ptr<Person> vertical : this->_people) {
        std::vector<int> tmp;
        for (std::size_t i = 0; i != this->_people.size(); i++) {
            if (areFriends(vertical, this->_people.at(i))) {
                if (_display)
                    std::cout << 1;
                tmp.push_back(1);
            }
            else {
                if (_display)
                    std::cout << 0;
                tmp.push_back(0);
            }
            if (i != this->_people.size() - 1)
                if (_display)
                    std::cout << " ";
        }
        this->_agencyMatrix.push_back(tmp);
        if (_display)
            std::cout << std::endl;
    }
    if (_display)
        std::cout << std::endl;
}

int Engine::getSeparationDegree(std::string person1, std::string person2)
{
    int x = 0;
    int y = 0;
    bool checkX = false;
    bool checkY = false;

    for (; x < this->_people.size(); x++)
        if (this->_people.at(x)->getName() == person1) {
            checkX = true;
            break;
        }
    for (; y < this->_people.size(); y++) {
        if (this->_people.at(y)->getName() == person2) {
            checkY = true;
            break;
        }
    }
    if (!checkX || !checkY)
        return -1;
    return this->_agencyMatrix.at(x).at(y);
}

void Engine::displaySeparationDegrees(std::size_t n)
{
    std::vector<std::shared_ptr<Person>> visited;

    findSeparationDegree();
    for (std::size_t j = 0; j != this->_people.size(); j++) {
        for (std::size_t i = 0; i != this->_people.size(); i++) {
            if (this->_agencyMatrix.at(j).at(i) > this->n)
                std::cout << 0;
            else
                std::cout << this->_agencyMatrix.at(j).at(i);
            if (i != this->_people.size() - 1)
                std::cout << " ";
        }
        std::cout << std::endl;
    }
}