/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:35:21 by tplanes           #+#    #+#             */
/*   Updated: 2023/06/12 15:32:43 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(std::string const& line)
{
	//std::cout << "RPN param ctor called" << std::endl;
	this->_compute(line);
	return ;
}

RPN::~RPN(void)
{
	//std::cout << "RPN dtor called" << std::endl;
	return ;
}

/***************************/

void	RPN::_compute(std::string const& line)
{
	char const* buf = line.c_str();

	while (*buf)
	{
		if (*buf >= '0' && *buf <= '9')
			this->_stack.push(static_cast<int>(*buf - '0'));
		else if (*buf == '+' || *buf == '-' || *buf == '*' || *buf == '/')
			this->_doOp(*buf);
		else
			throw std::invalid_argument("Error");
		buf++;
		if (*buf == 0)
			break;
		if (*buf != ' ')
			throw std::invalid_argument("Error");
		buf++;
	}
	if (this->_stack.size() > 1)
		throw std::invalid_argument("Error");
	std::cout << this->_stack.top() << std::endl;
	return ;
}

void	RPN::_doOp(char c)
{
	int num1, num2, res;
	
	if (this->_stack.size() < 2)
		throw std::invalid_argument("Error");
	num2 = this->_stack.top();
	this->_stack.pop();
	num1 = this->_stack.top();
	this->_stack.pop();
	if (c == '+')
		res = num1 + num2;
	else if (c == '-')
		res = num1 - num2;
	else if (c == '*')
		res = num1 * num2;
	else if (c == '/')
	{
		if (num2 == 0)
			throw std::invalid_argument("Error: division by zero");
		res = num1 / num2;
	}
	this->_stack.push(res);
	return ;	
}
