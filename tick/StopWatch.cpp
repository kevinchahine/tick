#include "StopWatch.h"

using namespace std;
using namespace std::chrono;

namespace tick
{
	void StopWatch::reset(std::chrono::nanoseconds elapsedTime)
	{
		m_elapsed = elapsedTime;

		state = STATE::PAUSED;
	}

	void StopWatch::stop()
	{
		if (state == STATE::RESUMED) {
			m_elapsed += (high_resolution_clock::now() - lastResumed);

			state = STATE::PAUSED;
		}
	}

	void StopWatch::start()
	{
		if (state == STATE::PAUSED) {
			lastResumed = high_resolution_clock::now();

			state = STATE::RESUMED;
		}
	}

	std::chrono::nanoseconds StopWatch::elapsed() const
	{
		switch (state)
		{
		case STATE::PAUSED:			return m_elapsed;
		case STATE::RESUMED:		return m_elapsed + (chrono::high_resolution_clock::now() - lastResumed);
		}
	}

	std::ostream & operator<<(std::ostream & os, const StopWatch & sw)
	{
		nanoseconds elapsed = sw.elapsed();
		minutes min = duration_cast<minutes>(elapsed);
		seconds sec = duration_cast<seconds>(elapsed) - min;

		os << min.count() << ':';
		
		if (sec.count() < 10)
			os << '0';
		
		os << sec.count();

		return os;
	}
} // namespace tick

