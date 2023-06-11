/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 15:24:18 by tplanes           #+#    #+#             */
/*   Updated: 2023/06/11 16:10:38 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void)
{
	std::cout << "BitcoinExchange default ctor called" << std::endl;
	this->_importDatabase("data.csv");
	return ; 
}

BitcoinExchange::~BitcoinExchange(void)
{
	std::cout << "BitcoinExchange default dtor called" << std::endl;
	return ; 
}

/************************************/

void	BitcoinExchange::_importDatabase(std::string const& fname)
{
	std::ifstream ifs;
	ifs.exceptions(std::ifstream::failbit | std::ifstream::badbit); // will throw exception in case of failure
	
	std::string line;

	ifs.open(fname, std::ifstream::in);
	if (ifs.eof())
		throw	std::length_error("Error: database is empty");
	std::getline(ifs, line);
	if (line.compare("date,exchange_rate") != 0)
		throw	std::invalid_argument("Error: wrong database header");
	if (ifs.eof())
		throw	std::length_error("Error: database body is empty");
	
	while (!ifs.eof())
	{
		std::getline(ifs, line);
		this->_processDataLine(line);
	}

	ifs.close();	
	return ;
}

void	BitcoinExchange::_processDataLine(std::string const& line)
{
	std::string	date;
	std::string	valueStr;
	float		value;
	size_t		indComma;
	char*		endptr = NULL;

	indComma = line.find_first_of(",");
	if (indComma == std::string::npos || indComma == line.size() - 1)
		throw	std::invalid_argument("Error: wrong entry in database");
	date = line.substr(0, indComma);
	valueStr = line.substr(indComma, line.size());
	value = strtof(valueStr.c_string(), &endptr);
	if (*endptr)
		throw	std::invalid_argument("Error: wrong entry in database");
	//check errno here for overflow?
	this->_table.insert(std::pair<std::string, float>(date, value));
	return ;
}
