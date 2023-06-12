/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:11:28 by tplanes           #+#    #+#             */
/*   Updated: 2023/06/12 18:54:34 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_H
# define PMERGEME_H

# include <iostream>
# include <string>
# include <vector>
# include <cstdlib>

class PmergeMe
{
	public:
		PmergeMe(char** input);
		~PmergeMe(void);

		//void	_sortInput(void);
		void	printVec(void) const;

	private:
		PmergeMe(void);
		PmergeMe(PmergeMe const&);
		PmergeMe&	operator=(PmergeMe const&);

		void	_parseInput(char** input);

		std::vector<int> _vec;

};

#endif
