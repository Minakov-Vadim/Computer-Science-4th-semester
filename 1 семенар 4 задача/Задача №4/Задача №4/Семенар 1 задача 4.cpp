#include <iostream>
#include <chrono>

class Timer
{
public:
	using clock_t = std::chrono::steady_clock;
	using time_point_t = clock_t::time_point;
	Timer() : m_begin(clock_t::now()) {}
	~Timer() noexcept 
	{
		std::cout << std::chrono::duration_cast <std::chrono::microseconds> ((clock_t::now()) - m_begin).count() << " microseconds" << std::endl;
	}
private:
	time_point_t m_begin;
};

int main(int argc, char** argv) {
	{
		Timer t;
		int a = 0;
		for (int i = 0; i < 10000; i++) {
			a += i;
		}
	}


	// На счет перестановок, я доделаю задачу. До понедельника.
	return EXIT_SUCCESS;
}