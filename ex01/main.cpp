/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnascime <cnascime@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:29:38 by cnascime          #+#    #+#             */
/*   Updated: 2024/08/02 14:39:47 by cnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int	main(int argc, char **argv) {
	if (argc < 2) {
		std::cerr << "Error" << std::endl;
		return (1);
	};

	RPN postfix;

	std::string input = argv[1];
	postfix.calculator(input.c_str());

	return (0);
};
