#include <iostream>
#include <array>
#include <random>
#include "boost/container_hash/hash.hpp"
#include <set>
#include <chrono>
#include <string>

std::set < std::string > make_random_words(std::size_t N, std::size_t length) // length = 10 - good enough
{
	std::uniform_int_distribution <> letter(97, 122);
	std::default_random_engine e(static_cast <std::size_t> (
		std::chrono::system_clock::now().time_since_epoch().count()));
	std::set < std::string > words;
	for (std::string s(length, '_'); std::size(words) < N; words.insert(s))
		for (auto& c : s)
			c = letter(e);
	return words;
}

std::size_t hash_value(int Day, std::string Strange_hello)
{
	std::size_t seed = 0;
	boost::hash_combine(seed, Day);
	boost::hash_combine(seed, Strange_hello);
	return seed;
}

int main() {

	const int n = 2000000;
	int i_Collisions = 0;

	std::set < std::string > words = make_random_words(n, 10);
	auto begin = words.begin();

	std::set < std::size_t > set;
	std::pair < std::set<std::size_t>::iterator, bool> pair;

	for (int k = 1; k < n+1; ++k) {
		pair = set.insert(hash_value(k, *(begin++)));
		if (pair.second == false)
			i_Collisions += 1;
		if (k % 1000 == 0) {
			std::cout << k << " " << i_Collisions << '\n';
		}
	}	

	return 0;
}
