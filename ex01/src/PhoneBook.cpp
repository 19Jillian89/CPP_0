/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilnassi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 19:53:24 by ilnassi           #+#    #+#             */
/*   Updated: 2026/05/27 19:53:26 by ilnassi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "PhoneBook.hpp"

PhoneBook::PhoneBook() : _count(0) {}

static std::string truncate(std::string str)
{
    if (str.length()> 10)
        return str.substr(0, 9) + ".";
    return str;
}

void PhoneBook::addContact()
{
    Contact newContact;
    std::string input;
    int index;

    index = _count % 8;

    std::cout << "First name: ";
    std::getline(std::cin, input);
    if (input.empty()) { std::cout << "Is empty!\n"; return; }
    newContact.setFirstName(input);

    std::cout << "Last name: ";
    std::getline(std::cin, input);
    if (input.empty()) { std::cout << "Is empty!\n"; return; }
    newContact.setLastName(input);

    std::cout << "Nickname: ";
    std::getline(std::cin, input);
    if (input.empty()) { std::cout << "Is empty!\n"; return; }
    newContact.setNickname(input);

    std::cout << "Phone number: ";
    std::getline(std::cin, input);
    if (input.empty()) { std::cout << "Is empty!\n"; return; }
    newContact.setPhoneNumber(input);

    std::cout << "Darkest secret: ";
    std::getline(std::cin, input);
    if (input.empty()) { std::cout << "Is empty!\n"; return; }
    newContact.setDarkestSecret(input);

    _contacts[index] = newContact;
    _count++;
}

void PhoneBook::searchContact() const
{
    int total;
    std::string input;
    int index;

    total = (_count < 8) ? _count : 8;
    if (total == 0)
    {
        std::cout << "Phone book is empty!\n";
        return;
    }

    std::cout << std::setw(10) << "Index"   << "|"
              << std::setw(10) << "First"   << "|"
              << std::setw(10) << "Last"    << "|"
              << std::setw(10) << "Nickname"    << std::endl;

    for (int i = 0; i < total; i++)
    {
        std::cout << std::setw(10) << std::right << i                                     << "|"
                  << std::setw(10) << std::right << truncate(_contacts[i].getFirstName()) << "|"
                  << std::setw(10) << std::right << truncate(_contacts[i].getLastName())  << "|"
                  << std::setw(10) << std::right << truncate(_contacts[i].getNickname())  << std::endl;
    }

    std::cout << "Enter index: ";
    std::getline(std::cin, input);
    if (input.empty() || !std::isdigit(input[0]))
    {
        std::cout << "Invalid index!" << std::endl;
        return;
    }
    index = std::atoi(input.c_str());
    if (index < 0 || index >= total)
    {
        std::cout << "Index out of range!" << std::endl;
        return;
    }

    std::cout << "First name:     " << _contacts[index].getFirstName()    << std::endl;
    std::cout << "Last name:      " << _contacts[index].getLastName()     << std::endl;
    std::cout << "Nickname:       " << _contacts[index].getNickname()     << std::endl;
    std::cout << "Phone number:   " << _contacts[index].getPhoneNumber()  << std::endl;
    std::cout << "Darkest secret: " << _contacts[index].getDarkestSecret()<< std::endl;
}
