/*
** EPITECH PROJECT, 2020
** B-MAT-500-PAR-5-1-302separation-rayann.folleas
** File description:
** Person
*/

#ifndef PERSON_HPP_
#define PERSON_HPP_

#include <string>
#include <memory>
#include <vector>

class Person {
    public:
        Person() = default;
        Person(const std::string &name);
        ~Person() = default;

        void setName(const std::string &newName) {
            this->_name = newName;
        }
        void addFriend(std::shared_ptr<Person> newFriend) {
            this->_friends.push_back(newFriend);
        }
        std::string getName(void) const {
            return _name;
        };
        std::vector<std::shared_ptr<Person>> getFriends(void) const {
            return _friends;
        }
    private:
        std::string _name;
        std::vector<std::shared_ptr<Person>> _friends;
};

inline bool operator== (const Person& lhs, const Person& rhs) {
    if (lhs.getName() == rhs.getName())
        return true;
    return false;
}

#endif /* !PERSON_HPP_ */