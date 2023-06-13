/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:11:28 by tplanes           #+#    #+#             */
/*   Updated: 2023/06/13 20:26:48 by tplanes          ###   ########.fr       */
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
		PmergeMe(char** input);
		~PmergeMe(void);

		void	sortVec(void);
//		void	printVec(void) const;
		static void	printVec(std::vector<int> const&);

	private:
		PmergeMe(void);
		PmergeMe(PmergeMe const&);
		PmergeMe&	operator=(PmergeMe const&);

		void	_parseInput(char** input);

		static void	_recurSortVec(std::vector<int>& vec);


		std::vector<int> _vec;

};

#endif
