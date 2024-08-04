/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnascime <cnascime@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:29:38 by cnascime          #+#    #+#             */
/*   Updated: 2024/08/03 04:53:27 by cnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.cpp"
#include <iomanip> // std::setprecision
#include <ctime> // clock_t, clock

int	main(int argc, char **argv) {
	if (argc < 2) {
		std::cerr << "Error" << std::endl;
		return (1);
	};

	//* DEQUE
	std::deque<int>	dequeseque;
	for (int i = 1; i < argc; ++i) {
		int element = std::atoi(argv[i]);
		if (element <= 0) {
			std::cerr << "Error" << std::endl;
			return (1);
		};
		dequeseque.push_back(element);
	};

	std::cout << "\033[2;31mBefore: ";
	printContainer(dequeseque);
	std::cout << "\033[0m";
	// Copies the original sequence before it's sorted.
	std::vector<int> vecseq(dequeseque.begin(), dequeseque.end());

	clock_t	start = clock();
	mergeInsert(dequeseque);
	clock_t	finish = clock();
	// Calculates the time it took to sort the sequence in microseconds.
	// Clocks per second is a constant that equals 1000000.
	double	dequetimer = static_cast<double>(finish - start) / CLOCKS_PER_SEC;

	// Comment the lines below to avoid printing the result twice.
	//std::cout << "After:  ";
	//printContainer(dequeseque);

	//* VECTOR
	start = clock();
	mergeInsert(vecseq);
	finish = clock();
	double	vectortimer = static_cast<double>(finish - start) / CLOCKS_PER_SEC;	
	
	std::cout << "After:  ";
	printContainer(vecseq);

	std::cout << "Time to process a range of " << dequeseque.size()
			  << " elements with std::deque:  " << std::fixed
			  << std::setprecision(6) << dequetimer << " μs\n";
	std::cout << "Time to process a range of " << vecseq.size()
			  << " elements with std::vector: " << std::fixed
			  << std::setprecision(6) << vectortimer << " μs" << std::endl;
	// std::fixed forces the output to be in fixed-point notation (decimals),
	// instead of scientific notation (exponents).
	// Deque usually takes longer than vector, because it's a double-ended queue
	// (allows insertion and deletion at both ends), while vector is a dynamic 
	// array that allows for fast random access and insertion only at the end.
	// The time complexity of merge-insertion is O(n log n) for both containers,
	// but the space complexity is O(n) for deque and O(n log n) for vector.
	// That means deque is more efficient in terms of memory allocation, 
	// but vector is more efficient in time complexity.

	return (0);
};
