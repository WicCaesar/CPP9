/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnascime <cnascime@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 22:52:21 by cnascime          #+#    #+#             */
/*   Updated: 2024/08/02 09:38:10 by cnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>

// Merge uses the same sorting method to all collections, 
// while merge-insert uses insertion sort when it reaches small collections.

template <typename Container>
void	printContainer(const Container &sequence);

template <typename Container>
void	splitAndSortPairs(Container &sequence, Container &mainchain, Container &pend);

template <typename Container>
void	insertPend(Container &mainchain, Container &pend);

template <typename Container>
void	mergeInsert(Container &sequence);

#endif
