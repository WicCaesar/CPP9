/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnascime <cnascime@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 09:43:52 by cnascime          #+#    #+#             */
/*   Updated: 2024/08/03 04:53:33 by cnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <climits>
#include <stack>

// Stack is the preferrable container since it can store and pick up the results
// in a LIFO sequence. So, when arithmetic operators appear in a sequence, it 
// conveniently grabs the latest results in the memory and does the arithmetic, 
// with no need of parentheses and other symbols to determine precedence.
class RPN {
	private:
		std::stack<int>	stack_;

	public:
		RPN(void);
		RPN(const RPN &copy);
		RPN &operator=(const RPN &copy);
		~RPN(void);

		void	calculator(const std::string &input);
};
