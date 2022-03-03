#include <iostream>
#include <random>
#include "boost/container_hash/hash.hpp"
#include <set>
#include <chrono>
#include <string>
#include "Semenar 3 task 3_hpp.h"


int main() {

	const int l_s = 10;
	const int m = 9;
	const int n = 2000000;
	std::set < std::string > words = make_random_words(n, l_s);


	for (int i = 0; i < 9; ++i) {
		int i_Collisions = 0;
		auto begin = words.begin();
		std::set < std::size_t > set;
		std::pair < std::set<std::size_t>::iterator, bool> pair;

		for (int k = 1; k < n+1; ++k) {
			
			if (i == 0) {
				if (k == 1) {
					std::cout << "A hash function called <<RSHash>> " << '\n';
				}
				pair = set.insert(RSHash(*(begin++), l_s));
				if (pair.second == false)
					i_Collisions += 1;
				if (k % 1000 == 0) {
					std::cout << k << " " << i_Collisions << '\n';
				}
			}
			if (i == 1) {
				if (k == 1) {
					std::cout << "A hash function called <<JSHash>> " << '\n';
				}
				pair = set.insert(JSHash(*(begin++), l_s));
				if (pair.second == false)
					i_Collisions += 1;
				if (k % 1000 == 0) {
					std::cout << k << " " << i_Collisions << '\n';
				}
			}
			if (i == 2) {
				if (k == 1) {
					std::cout << "A hash function called <<PJWHash>> " << '\n';
				}
				pair = set.insert(PJWHash(*(begin++), l_s));
				if (pair.second == false)
					i_Collisions += 1;
				if (k % 1000 == 0) {
					std::cout << k << " " << i_Collisions << '\n';
				}
			}
			if (i == 3) {
				if (k == 1) {
					std::cout << "A hash function called <<ELFHash>> " << '\n';
				}
				pair = set.insert(ELFHash(*(begin++), l_s));
				if (pair.second == false)
					i_Collisions += 1;
				if (k % 1000 == 0) {
					std::cout << k << " " << i_Collisions << '\n';
				}
			}
			if (i == 4) {
				if (k == 1) {
					std::cout << "A hash function called <<BKDRHash>> " << '\n';
				}
				pair = set.insert(BKDRHash(*(begin++), l_s));
				if (pair.second == false)
					i_Collisions += 1;
				if (k % 1000 == 0) {
					std::cout << k << " " << i_Collisions << '\n';
				}
			}
			if (i == 5) {
				if (k == 1) {
					std::cout << "A hash function called <<SDBMHash>> " << '\n';
				}
				pair = set.insert(SDBMHash(*(begin++), l_s));
				if (pair.second == false)
					i_Collisions += 1;
				if (k % 1000 == 0) {
					std::cout << k << " " << i_Collisions << '\n';
				}
			}
			if (i == 6) {
				if (k == 1) {
					std::cout << "A hash function called <<DJBHash>> " << '\n';
				}
				pair = set.insert(DJBHash(*(begin++), l_s));
				if (pair.second == false)
					i_Collisions += 1;
				if (k % 1000 == 0) {
					std::cout << k << " " << i_Collisions << '\n';
				}
			}
			if (i == 7) {
				if (k == 1) {
					std::cout << "A hash function called <<DEKHash>> " << '\n';
				}
				pair = set.insert(DEKHash(*(begin++), l_s));
				if (pair.second == false)
					i_Collisions += 1;
				if (k % 1000 == 0) {
					std::cout << k << " " << i_Collisions << '\n';
				}
			}
			if (i == 8) {
				if (k == 1) {
					std::cout << "A hash function called <<APHash>> " << '\n';
				}
				pair = set.insert(APHash(*(begin++), l_s));
				if (pair.second == false)
					i_Collisions += 1;
				if (k % 1000 == 0) {
					std::cout << k << " " << i_Collisions << '\n';
				}
			}
		}
	}
	return 0;
}
