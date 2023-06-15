/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:16:06 by tplanes           #+#    #+#             */
/*   Updated: 2023/06/15 09:46:55 by tplanes          ###   ########.fr       */
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
	std::vector<int> indexes; // not useful in 1st call but needed in recurrence 

	PmergeMe::_recurSortVec(vec, indexes); // recursively sort copy
	this->_vec = vec; // replace original
	return ;
}

void	PmergeMe::_recurSortVec(std::vector<int>& vec, std::vector<int>& indexes)
{
	bool isFirstCall = indexes.empty();

	// Base case (length 1, do nothing)
	if (vec.size() == 1)
		return ;

	/* 	Virtually split into two equal-length segments (odd element unused if any)
		Virtually pair i-th element of each segment and make comparison
		Swap to have elements in first segment >= corresponding elements in second segment */
	
	std::vector<int>::iterator	it1 = vec.begin(); // points to beginning of first segment
	std::vector<int>::iterator	it2 = it1 + vec.size() / 2; // point to begin. of second segment
	std::vector<int>::iterator	itInd1; // same for index sequence
	std::vector<int>::iterator	itInd2;
	if (!isFirstCall)
	{
		itInd1 = indexes.begin(); // same for index sequence
		itInd2 = itInd1 + vec.size() / 2;
	}
	
	for (unsigned long j = 0; j < vec.size() / 2; j++)
	{
		if (*it2 > *it1)
		{
			std::iter_swap(it1, it2);
			if (!isFirstCall)
				std::iter_swap(itInd1, itInd2);
		}
		it1++;
		it2++;
		if (!isFirstCall)
		{
			itInd1++;
			itInd2++;
		}
	}
	
	/*
	//DEBUG
	if (VERBOSE && isFirstCall)
	{
		//std::cout << "Vec and Indexes after pair swap:" << std::endl;
		std::cout << "Vec after pair swap:" << std::endl;
		PmergeMe::printVec(vec);
		//PmergeMe::printVec(indexes);
	}
	*/

	// Split main and pend parts for both vec and Indexes
	std::vector<int> vecMain(vec.begin(), vec.begin() + vec.size() / 2);
	std::vector<int> vecPend(vec.begin() + vec.size() / 2, vec.end());
	std::vector<int> indMain;
	std::vector<int> indPend;
	if (!isFirstCall)
	{
		indMain.insert(indMain.end(), indexes.begin(), indexes.begin() + vec.size() / 2);
		indPend.insert(indPend.end(), indexes.begin() + vec.size() / 2, indexes.end());
	}
	
	//DEBUG
	if (VERBOSE && isFirstCall)
	{
		//std::cout << "Splitted Vec and Indexes:" << std::endl;
		std::cout << "Splitted Vec into main chain and pend chain + pair swap:" << std::endl;
		PmergeMe::printVec(vecMain);
		PmergeMe::printVec(vecPend);
		//PmergeMe::printVec(indMain);
		//PmergeMe::printVec(indPend);
	}

	std::vector<int> subIndexes;
	for (unsigned long i = 0; i < vecMain.size(); i++)
		subIndexes.push_back(i);
	PmergeMe::_recurSortVec(vecMain, subIndexes);
	PmergeMe::_rearrangeVec(vecPend, subIndexes);
	if (!isFirstCall)
	{
		PmergeMe::_rearrangeVec(indMain, subIndexes);
		PmergeMe::_rearrangeVec(indPend, subIndexes);
	}

	// DEBUG
	if (VERBOSE && isFirstCall)
	{
		//std::cout << "Splitted Vec and Indexes after rearrage:" << std::endl;
		std::cout << "\nMain and pend and after recursive sort:" << std::endl;
		PmergeMe::printVec(vecMain);
		PmergeMe::printVec(vecPend);
		//PmergeMe::printVec(indMain);
		//PmergeMe::printVec(indPend);
	}
	PmergeMe::_binaryInsertVec(vecMain, vecPend, indMain, indPend);
	vec = vecMain;
	indexes = indMain;

	//DEBUG
	/*std::cout << "Vec and Indexes before return from general case:" << std::endl;
	PmergeMe::printVec(vec);
	PmergeMe::printVec(indexes);
	*/
	return ;	
}

void	PmergeMe::_rearrangeVec(std::vector<int>& vec, std::vector<int>& indexes)
{
	std::vector<int> vecCopy = vec;
	for (unsigned long i = 0; i < indexes.size(); i++)
		vec[i] = vecCopy[indexes[i]];
	return ;
}

// Binary insert with jacobsthal sequence
void	PmergeMe::_binaryInsertVec(std::vector<int>& vecMain, std::vector<int>& vecPend,
	std::vector<int>& indMain, std::vector<int>& indPend)
{
	bool isFirstCall = indMain.empty();

	/*
	//DEBUG
	if (verbose && isFirstCall)
	{
	std::cout << "\nBefore binary insert:" << std::endl;
	std::cout << "vecMain:" << std::endl;
	PmergeMe::printVec(vecMain);
	std::cout << "vecPend:" << std::endl;
	PmergeMe::printVec(vecPend);
	std::cout << "indMain:" << std::endl;
	PmergeMe::printVec(indMain);
	std::cout << "indPend:" << std::endl;
	PmergeMe::printVec(indPend);
	}
	*/

	std::vector<unsigned long> jacob;
	std::vector<long> maxChainSize; // to insert into
	unsigned long	jacobPrev = 1;
	jacob.push_back(1);
	maxChainSize.push_back(1);
	
	// Generate needed Jacobsthal sequence and maxChainSize
	while (jacob.back() < vecPend.size())
	{
		jacob.push_back(jacob.back() + 2 * jacobPrev);
		jacobPrev = *(jacob.end() - 2);
		maxChainSize.push_back((maxChainSize.back() + 1) * 2 - 1); //2^n - 1
	}
	
	// DEBUG
	/*if (VERBOSE && isFirstCall)
	{
		std::cout << "Main chain size is " << vecMain.size() << " and jacob sequence:" << std::endl;
		PmergeMe::printVec(std::vector<int>(jacob.begin(), jacob.end()));
		std::cout << "Maximum chain sizes for successive insertions are: " << std::endl;
		PmergeMe::printVec(std::vector<int>(maxChainSize.begin(), maxChainSize.end()));
	}*/

	long	insertSize; // size of chain to insert into

	std::vector<int>::iterator	it;
	for (unsigned long j = 0; j < jacob.size(); j++)
	{
		jacobPrev = (jacob[j] == 1) ? 0 : jacob[j - 1];
		for (unsigned long i = jacob[j]; i > jacobPrev; i--)
		{
			if (i > vecPend.size())
				continue ;
			
			insertSize = std::min(vecMain.end() - vecMain.begin(), maxChainSize[j]);
			if (VERBOSE && isFirstCall)	
				std::cout << "\nInserting pend element " <<  vecPend[i - 1] 
					<< " into sub main chain of length " << insertSize << ":" << std::endl;
			
			// Very first insert need no comparison
			if (i == 1)
			{
				it = vecMain.begin();	
			}
			else // Lower_bound performs binary search
			{
				it = std::lower_bound(vecMain.begin(), 
					vecMain.begin() + insertSize, vecPend[i - 1]); // need 2nd it to pass bound
			}

			if (!isFirstCall)
				indMain.insert(indMain.begin() + std::distance(vecMain.begin(), it), indPend[i - 1]);
			vecMain.insert(it, vecPend[i - 1]);
			
			if (VERBOSE && isFirstCall)
			{
				PmergeMe::printVec(vecMain);
				PmergeMe::printVec(vecPend);
			}
		}
	}
	return ;
}

/*
//Binary insert without jacobsthal sequence
void	PmergeMe::_binaryInsertVec(std::vector<int>& vecMain, std::vector<int>& vecPend,
	std::vector<int>& indMain, std::vector<int>& indPend)
{
	std::vector<int>::iterator	it;
	for (unsigned long i = 0; i < vecPend.size(); i++)
	{
		// lower_bound performs binary search
		it = std::lower_bound(vecMain.begin(), vecMain.end(), vecPend[i]);
		indMain.insert(indMain.begin() + std::distance(vecMain.begin(), it), indPend[i]);
		vecMain.insert(it, vecPend[i]); 
	}
	return ;
}
*/

/*
//Simple insert
void	PmergeMe::_binaryInsertVec(std::vector<int>& vecMain, std::vector<int>& vecPend,
	std::vector<int>& indMain, std::vector<int>& indPend)
{
	// for the moment just do a basic insertion
	bool flagInsert;

	for (unsigned long i = 0; i < vecPend.size(); i++)
	{
		flagInsert = false;
		for (unsigned long j = 0; j < vecMain.size(); j++)
		{
			if (vecPend[i] <= vecMain[j])
			{	
				vecMain.insert(vecMain.begin() + j, vecPend[i]); 
				indMain.insert(indMain.begin() + j, indPend[i]);
				flagInsert = true;
				break;
			}
		}
		if (!flagInsert)
		{
			vecMain.push_back(vecPend[i]); // insert at end
			indMain.push_back(indPend[i]);
		}
	}
	return ;
}
*/

