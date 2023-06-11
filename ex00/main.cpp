/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 15:17:34 by tplanes           #+#    #+#             */
/*   Updated: 2023/06/11 16:12:07 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include "BitcoinExchange.hpp"

int	main(int ac, char**av)
{
	if (ac != 2 || *(av[1]) == '\0')
	{
		std::cout << "Error: need one filename as input" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	BitcoinExchange	btx;
	return (0);
}
