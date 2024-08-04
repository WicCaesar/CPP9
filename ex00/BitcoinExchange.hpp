/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnascime <cnascime@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 01:59:28 by cnascime          #+#    #+#             */
/*   Updated: 2024/08/03 04:32:19 by cnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <cstddef>
#include <string>
#include <cstdlib>

enum e_months {
	JANUARY = 1,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER
};

class BitcoinExchange {
	private:
		std::string						filename_;
		std::map<std::string, double>	price_;
		bool							isValidFormat(const std::string &date);
		bool							isValidDate(const std::string &date);
		bool							isLeapYear(int year);

	public:
		BitcoinExchange(void);
		BitcoinExchange(const std::string &filename);
		BitcoinExchange(const BitcoinExchange &copy);
		BitcoinExchange &operator=(const BitcoinExchange &copy);
		~BitcoinExchange(void);

		void	exchange(void);

		class	InvalidFileException;
};
