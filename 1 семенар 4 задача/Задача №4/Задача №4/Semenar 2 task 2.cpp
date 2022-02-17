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
	Timer() : m_begin(clock_t::now()), m_flag(false), m_duration(0) {}
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
			m_duration += std::chrono::duration_cast<std::chrono::microseconds>(clock_t::now() - m_begin);
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
			m_flag = true;
			m_begin = clock_t::now();
		}
	}
	void finish()
	{
		m_duration += std::chrono::duration_cast<std::chrono::microseconds>(clock_t::now() - m_begin);
		std::cout << m_duration.count() << " microseconds" << std::endl;
		m_duration -= m_duration;
		m_flag = false;
	}

	auto& getter() const noexcept
	{
		return m_duration;
	}

private:
	time_point_t m_begin;
	std::chrono::microseconds m_duration;
	bool m_flag;
};


int main(int argc, char** argv) {


	std::array <int, 10000 > a_1;
	std::vector <int> a_2;
	std::deque<int> a_3;
	std::list<int> a_4;
	std::forward_list<int> a_5;

	int b;
	std::array <int, 100000 > a;
	for (int i = 0; i < 10000; ++i) {
		std::cin >> b;
		a[i] = b;
	}


	for (int i = 0; i < 10000; ++i) {
		a_1[i] = a[i];
		a_2.push_back(a[i]);
		a_3.push_back(a[i]);
		a_4.push_back(a[i]);
		a_5.push_front(a[9999-i]);
	}

	{
		Timer t;
		t.start();
		std::sort(a_1.begin(), a_1.end());
		t.finish();

		t.start();
		std::sort(a_2.begin(), a_2.end());
		t.finish();

		t.start();
		std::sort(a_3.begin(), a_3.end());
		t.finish();

		t.start();
		a_4.sort();
		t.finish();

		t.start();
		a_5.sort();
		t.finish();
		
	}


	//18 15 10 microseconds
	//31 23 9 microseconds
	//144 95 122 microseconds
	//989 565 325 microseconds
	//515 513 422 microseconds
	

	
	///Our winners
	//1)array
	//2)vector
	//3)deque
	//4)forward_list
	//5)list

	//Maybe I didn't judge honestly

	return EXIT_SUCCESS;
}