#include <iostream>
#include <chrono>

class Timer
{
public:
	using clock_t = std::chrono::steady_clock;
	using time_point_t = clock_t::time_point;
	Timer() : m_begin(clock_t::now()), m_flag(false), m_duration(0){}
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
	int a = 0;
	{
		Timer t;

		t.start();
		for (int i = 0; i < 10000; i++) {
			a += i;
		}
		t.pause();


		for (int i = 0; i < 10000; i++) {
			a += i;
		}
		a = 0;


		t.start();
		for (int i = 0; i < 10000; i++) {
			a += i;
		}
		t.finish();


	}


	return EXIT_SUCCESS;
}