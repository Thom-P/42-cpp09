/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:20:31 by tplanes           #+#    #+#             */
/*   Updated: 2023/06/12 18:54:10 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int ac, char** av)
{
	if (ac == 1 || *av[1] == 0)
	{
		std::cout << "Error: empty input sequence." << std::endl;
		exit(EXIT_FAILURE);
	}
	try
	{
		PmergeMe pme(++av);
		std::cout << "Before: ";
		pme.printVec();
		std::cout << std::endl;
	//pme.sortInput();
	}
	catch (std::exception const& e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}