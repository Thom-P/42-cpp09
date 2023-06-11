/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 15:00:11 by tplanes           #+#    #+#             */
/*   Updated: 2023/06/11 15:30:22 by tplanes          ###   ########.fr       */
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


		


	private:
		BitcoinExchange(BitcoinExchange const&);
		BitcoinExchange&	operator=(BitcoinExchange const&);
		
		void	_importDatabase(std::string const&);

		std::map<std::string, float>	_table;

};

#endif
