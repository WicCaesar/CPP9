/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnascime <cnascime@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 09:43:50 by cnascime          #+#    #+#             */
/*   Updated: 2024/08/02 14:11:51 by cnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(void) {
};

RPN::RPN(const RPN &copy) : stack_(copy.stack_) {
};

RPN &RPN::operator=(const RPN &copy) {
	if (this != &copy)
		this->stack_ = copy.stack_;
	return (*this);
};

RPN::~RPN(void) {
};

void	RPN::calculator(const std::string &input) {
	std::string	current;
	std::istringstream	iss(input);

	long	operand;
	long	operato;

	while (iss >> current) {
		if (current.length() == 1 && std::isdigit(current[0]))
			this->stack_.push(std::atoi(current.c_str()));
		else if ((current == "+" || current == "-" || current == "*" || current == "/")
				&& this->stack_.size() > 1) {
			operato = this->stack_.top(); // Adds operator to the stack
			this->stack_.pop(); // Picks it.
			operand = this->stack_.top(); // Does the same to the operand
			this->stack_.pop();
			// Checks if result is within the int range and pushes to stack
			if (current == "+" && (operand + operato <= INT_MAX))
				this->stack_.push(operand + operato);
			else if (current == "-" && (operand - operato >= INT_MIN))
				this->stack_.push(operand - operato);
			else if (current == "*" && (operand * operato <= INT_MAX) && (operand * operato >= INT_MIN))
				this->stack_.push(operand * operato);
			else if (current == "/") {
				if (operato == 0) {
					std::cout << "Error" << std::endl; // Division by 0
					return ;
				} else
					this->stack_.push(operand / operato);
			} else {
				std::cout << "Error" << std::endl; // Result out of int range
				return ;
			};
		} else {
			std::cout << "Error" << std::endl; // Invalid input
			return ;
		};
	};
	if (this->stack_.size() == 1) // If there is only one element in the stack
		std::cout << this->stack_.top() << std::endl; // Prints the result
	else
		std::cout << "Error" << std::endl; // Otherwise, prints error
};
