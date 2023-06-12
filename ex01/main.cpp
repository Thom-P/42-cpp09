/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:37:25 by tplanes           #+#    #+#             */
/*   Updated: 2023/06/12 15:11:20 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int ac, char** av)
{
	if (ac != 2 || *av[1] == '\0')
	{
		std::cout << "Error" << std::endl;
		exit(EXIT_FAILURE);
	}
	try
	{
		RPN rpn(av[1]);
	}
	catch (std::exception const& e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}
