/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:11:28 by tplanes           #+#    #+#             */
/*   Updated: 2023/06/15 10:19:15 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_H
# define PMERGEME_H

# include <iostream>
# include <string>
# include <vector>
# include <cstdlib>
# include <algorithm>

# define VERBOSE 0

class PmergeMe
{
	public:
		PmergeMe(void);
		~PmergeMe(void);

		void	parseInputVec(char** input);
		void	sortVec(void);
		std::vector<int> const&	getVec(void) const; 
		


		static void	printVec(std::vector<int> const&);

	private:
		PmergeMe(PmergeMe const&);
		PmergeMe&	operator=(PmergeMe const&);


		static void	_recurSortVec(std::vector<int>& vec, std::vector<int>& indexes);
		static void	_rearrangeVec(std::vector<int>& vec, std::vector<int>& indexes);
		static void	_binaryInsertVec(std::vector<int>& vecMain, std::vector<int>& vecPend,
			std::vector<int>& indMain, std::vector<int>& indPend);

		std::vector<int> _vec;

};

#endif
