/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:11:28 by tplanes           #+#    #+#             */
/*   Updated: 2023/06/14 17:24:02 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_H
# define PMERGEME_H

# include <iostream>
# include <string>
# include <vector>
# include <cstdlib>
# include <algorithm>

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


		std::vector<int> _vec;

};

#endif
