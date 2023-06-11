/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 15:24:18 by tplanes           #+#    #+#             */
/*   Updated: 2023/06/11 18:31:08 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void)
{
	std::cout << "BitcoinExchange default ctor called" << std::endl;
	//this->_importDatabase("data.csv");
	this->_importDatabase("databad.csv");
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
	std::string line;
	
	std::ifstream	ifs(fname);
    if (!ifs.is_open()) 
        throw std::invalid_argument("Error: could not open the database file");

	if (!std::getline(ifs, line))
		throw	std::invalid_argument("Error while reading database header.");
	if (line.compare("date,exchange_rate") != 0)
		throw	std::invalid_argument("Error: wrong database header");
	
	while (std::getline(ifs, line))
		this->_processDataLine(line);
	if (ifs.bad())
		throw	std::invalid_argument("Error while reading database");
	if (this->_table.size() == 0)
		throw	std::invalid_argument("Error: database is empty");
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
	valueStr = line.substr(indComma + 1, line.size());
	value = strtof(valueStr.c_str(), &endptr);
	if (*endptr)
		throw	std::invalid_argument("Error: wrong entry in database");
	//check errno here for overflow?
	this->_table.insert(std::pair<std::string, float>(date, value));
	return ;
}

float	BitcoinExchange::getPrice(std::string const& date) const
{
	if (!this->_isDateValid())
		throw std::invalid_argument(std::string("Error: bad input => ").append(line));
	
	//check date bounds
	//the get upper and -1 and return price...


}

void	BitcoinExchange::isDateValid(std::string const& date) const
{
	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		return (0);
	
	int		year, month, day;
	char	*endptr = NULL;

	year = (int)strtol((date.substr(0, 4)).c_str(), &endptr, 10);
	if (*endptr)
		return (0);
	month = (int)strtol((date.substr(5, 2)).c_str(), &endptr, 10);
	if (*endptr)
		return (0);
	day = (int)strtol((date.substr(8, 2)).c_str(), &endptr, 10);
	if (*endptr)
		return (0);
	// where to check if too early or too late a date?
	return (1);
}
