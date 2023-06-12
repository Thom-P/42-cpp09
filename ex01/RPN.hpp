/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:31:46 by tplanes           #+#    #+#             */
/*   Updated: 2023/06/12 15:08:16 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_H
# define RPN_H

# include <iostream>
# include <string>
# include <stack>

class RPN
{
	public:
		RPN(std::string const&);
		~RPN(void);

	private:
		RPN(void);
		RPN(RPN const&);
		RPN&	operator=(RPN const&);
		
		void	_compute(std::string const&);
		void	_doOp(char c);

		std::stack<int>	_stack;
};

#endif
