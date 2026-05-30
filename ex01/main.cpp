/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilnassi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 19:54:24 by ilnassi           #+#    #+#             */
/*   Updated: 2026/05/30 12:05:57 by ilnassi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "PhoneBook.hpp"

int main()
{
    PhoneBook   phonebook;
    std::string command;

    while (true)
    {
        std::cout << "Comando (ADD/SEARCH/EXIT): ";
        if (!std::getline(std::cin, command))
            break;
        if (command == "ADD")
            phonebook.addContact();
        else if (command == "SEARCH")
            phonebook.searchContact();
        else if (command == "EXIT")
            break;
    }
    return 0;
}
