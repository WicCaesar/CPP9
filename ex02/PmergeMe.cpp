/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnascime <cnascime@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 06:24:24 by cnascime          #+#    #+#             */
/*   Updated: 2024/08/02 09:08:15 by cnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

template <typename Container>
void	printContainer(const Container &sequence) {
	typename	Container::const_iterator iter = sequence.begin();
	if (iter != sequence.end()) {
		std::cout << *iter;
		++iter;
	};
	while (iter != sequence.end()) {
		std::cout << " " << *iter;
		++iter;
	};
	std::cout << std::endl;
};

template <typename Container>
void	splitAndSortPairs(Container &sequence, Container &mainchain, Container &pend) {
	int	n = sequence.size();
	for (int i = 0; i < n / 2; ++i) {
		// Checks if pair is sorted, the highest value goest to the main chain.
		if (sequence[2 * i] < sequence[2 * i + 1]) {
			mainchain.push_back(sequence[2 * i + 1]);
			pend.push_back(sequence[2 * i]); // The lowest goes to the pend.
		} else {
			mainchain.push_back(sequence[2 * i]);
			pend.push_back(sequence[2 * i + 1]);
		};		
	};
	if (n % 2 != 0) // If the number is odd, the last element is left unpaired.
		pend.push_back(sequence[n - 1]);
};

template <typename Container>
void	insertPend(Container &mainchain, Container &pend) {
	Container	result;
	//result.reserve(mainchain.size() + pend.size());
	// To reserve space in memory when using deque:
	//result.resize(mainchain.size() + pend.size());

	typename	Container::iterator miter = mainchain.begin();
	typename	Container::iterator piter = pend.begin();
	// Inserts the lowest number in the sequence.
	while (piter != pend.end()) {
		while (miter != mainchain.end() && *miter < *piter)
			result.push_back(*miter++);
		result.push_back(*piter++);
	};
	// Inserts the remaining elements in the sequence.
	while (miter != mainchain.end())
		result.push_back(*miter++);

	mainchain = result;
};

template <typename Container>
// Ford-Johnson's merge-insertion sort algorithm
void	mergeInsert(Container &sequence) {
	// Stops recursion upon reaching the base case.
	if (sequence.size() <= 1)
		return ;

	Container	mainchain;
	Container	pend;

	// Splits the collection in two pairs, and orders them pairwise.
	splitAndSortPairs(sequence, mainchain, pend);
	// Recursively sort the pairs of elements by their highest value.
	mergeInsert(mainchain); // The highest values form the main chain.
	mergeInsert(pend); // The rest are known as pend elements.
	insertPend(mainchain, pend); // Insert the pend elements in the main chain.

	sequence = mainchain;
};
