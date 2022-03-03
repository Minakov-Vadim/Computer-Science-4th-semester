#include <iostream>
#include <chrono>
#include <iterator> 
#include <algorithm>
#include <array>
#include <vector>
#include <set>


class Timer
{
public:
	using clock_t = std::chrono::steady_clock;
	using time_point_t = clock_t::time_point;
	explicit Timer() : m_begin(clock_t::now()), m_flag(false), m_doub(0.0) {}
	~Timer() noexcept
	{
		try
		{
			pause();
		}
		catch (...)
		{
			std::cerr << "You have a mistake" << std::endl;
		}
	}
	void pause()
	{
		if (m_flag)
		{
			m_doub = std::chrono::duration_cast<std::chrono::microseconds>(clock_t::now() - m_begin).count();
			m_flag = false;
		}
	}
	void start()
	{
		if (m_flag == false)
		{
			m_doub = 0.0;
			m_flag = true;
			m_begin = clock_t::now();
		}
	}

	double getter_doub() const noexcept
	{
		return m_doub;
	}

private:
	time_point_t m_begin;
	bool m_flag;
	double m_doub;
};




int main() {

	const int m = 10;
	const int n = 200000;
	double time_vector = 0.0, time_multiset = 0.0;
	
	std::array <int, n> Random_numbers;
	for (int i = 0; i < n; ++i) {
		Random_numbers[i] = rand();
	}

	auto begin = Random_numbers.begin();
	auto end = Random_numbers.end();

	{
		Timer t;

		for (int i = 0; i < m; i++) {

			std::vector <int> vector(begin, end);
			std::multiset<int> multiset;


				t.start();
				std::sort(vector.begin(), vector.end());
				t.pause();
				time_vector += t.getter_doub();


				t.start();
				for (int i = 0; i < n; ++i) {
					multiset.insert(Random_numbers[i]);
				}
				t.pause();
				time_multiset += t.getter_doub();
			}
	}

	std::cout << "Vector sorting time = " << time_vector / m << '\n';
	std::cout << "Multiset sorting time = " << time_multiset / m << '\n';
	
	//Winner vector
	//Т.к скорость работы вектора и мульти-сэта = O(n*log(n)), то различие будет в какой-то константе.
	// Константа c = 7,5 в среднем

	return EXIT_SUCCESS;
}
