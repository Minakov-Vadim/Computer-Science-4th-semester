#include <iostream>
#include <chrono>
#include <iterator> 
#include <algorithm>
#include <array>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>


class Timer
{
public:
	using clock_t = std::chrono::steady_clock;
	using time_point_t = clock_t::time_point;
	Timer() : m_begin(clock_t::now()), m_flag(false), m_doub(0.0) {}
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
		if (m_flag)
		{

		}
		else
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


int main(int argc, char** argv) {
	
	const int n = 200000;
	const int m = 100;
	double b_1 = 0.0, b_2 = 0.0, b_3 = 0.0, b_4 = 0.0, b_5 = 0.0;
	std::array <int, n > a_1;

	for (int j = 0; j < m; ++j) {
		
		for (int i = 0; i < n; ++i) {
			a_1[i] = rand();
		}
		std::array<int, n>::const_iterator begin = a_1.begin();
		std::array<int, n>::const_iterator end = a_1.end();

		std::vector <int> a_2(begin, end);
		std::deque<int> a_3(begin, end);
		std::list<int> a_4(begin, end);
		std::forward_list<int> a_5(begin, end);



		{
			Timer t;
			t.start();
			std::sort(a_1.begin(), a_1.end());
			t.pause();
			b_1 += t.getter_doub();


			t.start();
			std::sort(a_2.begin(), a_2.end());
			t.pause();
			b_2 += t.getter_doub();

			t.start();
			std::sort(a_3.begin(), a_3.end());
			t.pause();
			b_3 += t.getter_doub();

			t.start();
			a_4.sort();
			t.pause();
			b_4 += t.getter_doub();

			t.start();
			a_5.sort();
			t.pause();
			b_5 += t.getter_doub();

		}
	}


	std::cout << "Average working time array = " << b_1 / m << '\n';
	std::cout << "Average working time vector = " << b_2 / m << '\n';
	std::cout << "Average working time deque = " << b_3 / m << '\n';
	std::cout << "Average working time list = " << b_4 / m << '\n';
	std::cout << "Average working time forward_list = " << b_5 / m << '\n';
	//Winner array

	return EXIT_SUCCESS;
}