/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:16:06 by tplanes           #+#    #+#             */
/*   Updated: 2023/06/12 18:56:28 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(char** input)
{
	this->_parseInput(input);
	return ;
}

PmergeMe::~PmergeMe(void)
{
	return ;
}

/************************************/

void	PmergeMe::_parseInput(char** input)
{
	char*	endptr = NULL;
	long	tmp;
	int		num;
	while (*input && **input)
	{
		tmp = strtol(*input, &endptr, 10);
		if (*endptr)
			throw std::invalid_argument("Error: not a number.");
		if (tmp <= 0)
			throw std::invalid_argument("Error: accepts only strictly positive numbers.");
		if (tmp > INT_MAX)
			throw std::invalid_argument("Error: int overflow.");
		num = static_cast<int>(tmp);
		this->_vec.push_back(num);
		input++;
	}
	if (this->_vec.size() == 0)
		throw std::invalid_argument("Error: empty sequence."); // this should never happen
	return ;
}

void	PmergeMe::printVec(void) const
{
	std::vector<int>::const_iterator	it;
	for (it = this->_vec.begin(); it != this->_vec.end(); it++)
		std::cout << *it << " ";
	return ;
}

/*void	PmergeMe::_sortInput(void)
{
	return ;
}*/

