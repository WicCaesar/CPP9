/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnascime <cnascime@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 03:07:06 by cnascime          #+#    #+#             */
/*   Updated: 2024/08/03 04:32:32 by cnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void) {
};

// If there's a problem with the file format, exits instantly.
// For all other cases where the problem is just with content, goes to the next.
BitcoinExchange::BitcoinExchange(const std::string &filename) : filename_(filename) {
	std::ifstream	datafile("data.csv");
	std::string		header;

	if (!datafile || !datafile.is_open() || !getline(datafile, header)) {
		std::cerr << "Error: could not open file." << std::endl;
		exit(1);
	};

	std::string		line;
	while (getline(datafile, line)) {
		size_t		delimiter = line.find(',');
		if (delimiter == std::string::npos) {
			std::cerr << "Error: bad input." << line << std::endl;
			exit(1);
		};
		std::string	date = line.substr(0, delimiter);
		double price = std::strtod(line.substr(delimiter + 1).c_str(), NULL);
		price_[date] = price;
	};
	datafile.close();
};

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy) {
	this->filename_ = copy.filename_;
	this->price_ = copy.price_;
};

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &copy) {
	if (this != &copy) {
		this->filename_ = copy.filename_;
		this->price_ = copy.price_;
	};
	return (*this);
};

BitcoinExchange::~BitcoinExchange(void) {
};

void	BitcoinExchange::exchange(void) {
	std::ifstream	database(filename_.c_str());
	std::string		line;
	if (!database || !database.is_open() || !getline(database, line)) {
		std::cerr << "Error: impossible to read from file." << std::endl;
		exit(1);
	};
	if (line != "date | value") {
		std::cerr << "Error: wrong header (\"date | value\")." << std::endl;
		exit(1);
	};
	std::string	firstdate = price_.begin()->first;
	std::string	lastdate = price_.rbegin()->first;
	while (getline(database, line)) {
		if (line.empty())
			continue;
		size_t	delimiter = line.find('|');
		if (delimiter == std::string::npos) { // If delimiter is not found (-1).
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		};
		std::string	date = line.substr(0, 10);
		if (!isValidFormat(date) || !isValidDate(date)) {
			std::cerr << "Error: invalid date." << std::endl;
			continue;
		};
		if (date < firstdate || date > lastdate) {
			std::cerr << "Error: date out of range." << std::endl;
			continue;
		};
		std::string	amount = line.substr(delimiter + 1);
		try {
			char	*endptr;
			double	value = std::strtod(amount.c_str(), &endptr);
			if (*endptr != '\0' || amount == "" || amount == " ") {
				std::cerr << "Error: invalid amount." << std::endl;
				continue;
			};
			if (value <= 0) {
				std::cerr << "Error: not a positive number." << std::endl;
				continue;
			}
			else if (value > 1000) {
				std::cerr << "Error: too large a number." << std::endl;
				continue;
			};
			// If the specified date is not present in the database, the rate
			// will be the previous one.
			std::map<std::string, double>::iterator iter = price_.lower_bound(date);
			if (iter != price_.end() && iter->first == date) {
				// If it's an exact date match.
				double	exchangerate = iter->second;
				double	result = (value * exchangerate);
				std::cout << date << " => " << value << " = " << result << std::endl;
			} else {
				if (iter == price_.begin())
					std::cout << "Bitcoin launches. ";
				else if (iter == price_.end())
					--iter;
				else
					--iter; // Adjust to the closest previous date.
				double	exchangerate = iter->second;
				double	result = (value * exchangerate);
				std::cout << date << " => " << value << " = " << result << std::endl;
			};
		}
		catch (...) {
			std::cerr << "Error: bad input " << line << std::endl;	
		};
	};
	database.close();
};

// Checks if the date is in the format "YYYY-MM-DD".
bool	BitcoinExchange::isValidFormat(const std::string &date) {
	if (date.length() != 10 || (date[4] != '-' && date[7] != '-'))
		return (false);
	for (int i = 0; i < 10; i++) {
		if (i == 4 || i == 7)
			continue;
		if (!isdigit(date[i]))
			return (false);
	};
	return (true);
};

// If year is not divisible by 4, it's not a leap year.
// If year is divisible by 100, but not by 400, it's not a leap year.
bool	BitcoinExchange::isLeapYear(int year) {
	if (year % 4 != 0)
		return (false);
	if (year % 100 == 0 && year % 400 != 0) 
		return (false);
	return (true);
};

bool	BitcoinExchange::isValidDate(const std::string &date) {
	int	year, month, day;
	if (sscanf(date.c_str(), "%4d-%2d-%2d", &year, &month, &day) != 3)
		return (false);
	if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
		return (false);
	// Treatment for months with less than 31 days.
	switch (month) {
		case FEBRUARY:
			return (day <= (isLeapYear(year) ? 29 : 28));
		case APRIL: case JUNE: case SEPTEMBER: case NOVEMBER:
			return (day <= 30);
		default:
			return (day <= 31);
	};
};
