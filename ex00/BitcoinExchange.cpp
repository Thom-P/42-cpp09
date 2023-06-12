/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 15:24:18 by tplanes           #+#    #+#             */
/*   Updated: 2023/06/12 11:45:31 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void)
{
	//std::cout << "BitcoinExchange default ctor called" << std::endl;
	this->_importDatabase("data.csv");
	return ; 
}

BitcoinExchange::~BitcoinExchange(void)
{
	//std::cout << "BitcoinExchange default dtor called" << std::endl;
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
	try
	{
		this->_checkDateValid(date);
	}
	catch (std::exception const& e)
	{
		std::string err("Error: wrong entry in database\n");
		err.append(e.what());
		throw	std::invalid_argument(err); 
	}
	valueStr = line.substr(indComma + 1);
	value = strtof(valueStr.c_str(), &endptr);
	if (*endptr)
		throw	std::invalid_argument("Error: wrong entry in database");
	if (value < 0 || value == HUGE_VALF)
		throw	std::invalid_argument("Error: wrong entry in database");
	this->_table.insert(std::pair<std::string, float>(date, value));
	return ;
}

float	BitcoinExchange::getPrice(std::string const& date) const
{
	this->_checkDateValid(date);
	
	std::map<std::string,float>::const_iterator itup;
	itup = this->_table.upper_bound(date);
	if (itup == this->_table.begin())
		throw	std::invalid_argument("Error: input date is earlier than database");
	itup--;
	return (itup->second);
}

void	BitcoinExchange::_checkDateValid(std::string const& date) const
{
	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		throw std::invalid_argument(std::string("Error: bad input => ").append(date));
	
	struct tm tm;
	memset(&tm, 0, sizeof(tm));
	char *endptr = NULL;
	
	endptr = strptime(date.c_str(), "%Y-%m-%d", &tm);
	if (endptr == NULL || *endptr != 0)
		throw std::invalid_argument(std::string("Error: bad input => ").append(date));
	if (tm.tm_year < (2009 - 1900))
		throw std::invalid_argument(std::string("Error: btc value starts in 2009 => ").append(date));
	time_t now = time(0);
	time_t etime = mktime(&tm);
	if (etime > now)
		throw std::invalid_argument(std::string("Error: this program doesn't make future prediction => ").append(date));
	return ;
}
