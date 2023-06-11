/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 15:00:11 by tplanes           #+#    #+#             */
/*   Updated: 2023/06/11 17:15:26 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_H
# define BITCOINEXCHANGE_H

# include <iostream>
# include <string>
# include <map>
# include <fstream>

class BitcoinExchange
{
	public:
		BitcoinExchange(void);
		~BitcoinExchange(void);
		
		float	getPrice(std::string const&) const;

	private:
		BitcoinExchange(BitcoinExchange const&);
		BitcoinExchange&	operator=(BitcoinExchange const&);
		
		void	_importDatabase(std::string const&);
		void	_processDataLine(std::string const&);

		std::map<std::string, float>	_table;

};

#endif
