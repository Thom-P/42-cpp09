/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:16:06 by tplanes           #+#    #+#             */
/*   Updated: 2023/06/14 17:39:18 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void)
{
	return ;
}

PmergeMe::~PmergeMe(void)
{
	return ;
}

/*Getters*******************************/

std::vector<int> const&	PmergeMe::getVec(void) const
{
	return (this->_vec);
}

/***********************************/

// ################ CODE FOR VECTOR CONTAINER ####################

void	PmergeMe::parseInputVec(char** input)
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

void	PmergeMe::printVec(std::vector<int> const& vec)
{
	std::vector<int>::const_iterator	it;
	for (it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	return ;
}

void	PmergeMe::sortVec(void)
{
	std::vector<int> vec = this->_vec; // create copy
	std::vector<int> indexes; // not used in outermost call of recurrence so kept empty
	// Actually fill indexes here just to verify function ok
	for (int i = 0; i < (int)vec.size(); i++)
		indexes.push_back(i);

	PmergeMe::_recurSortVec(vec, indexes); // recursively sort copy
	this->_vec = vec; // replace original
	return ;
}

void	PmergeMe::_recurSortVec(std::vector<int>& vec, std::vector<int>& indexes)
{
	//DEBUG
	std::cout << "Vec and indexes before pair sort:" << std::endl;
	PmergeMe::printVec(vec);
	PmergeMe::printVec(indexes);

	/* 	Virtually split into two equal-length segments (odd element unused if any)
		Virtually pair i-th element of each segment and make comparison
		Swap to have elements in first segment <= corresponding elements in second segment */
	
	std::vector<int>::iterator	it1 = vec.begin(); // points to beginning of first segment
	std::vector<int>::iterator	it2 = it1; // will point to beginning of second segment
	
	std::vector<int>::iterator	itInd1 = indexes.begin(); // same for index sequence
	std::vector<int>::iterator	itInd2 = itInd1;
	
	while (std::distance(it1, it2) < static_cast<long>(vec.size() / 2))
	{
		it2++;
		if (!indexes.empty())
			itInd2++;
	}
	for (int j = 0; j < static_cast<int>(vec.size() / 2); j++)
	{
		if (*it1 > *it2)
		{
			std::iter_swap(it1, it2);
			if (!indexes.empty())
				std::iter_swap(itInd1, itInd2);
		}
		it1++;
		it2++;
		if (!indexes.empty())
		{
			itInd1++;
			itInd2++;
		}
	}
	
	//DEBUG
	std::cout << "Vec and Indexes after pair sort:" << std::endl;
	PmergeMe::printVec(vec);
	PmergeMe::printVec(indexes);

	return ;	
}



