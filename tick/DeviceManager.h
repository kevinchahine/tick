#pragma once

#include "TimerManager.h"
#include "StopWatchManager.h"

namespace tick
{
	class DeviceManager
	{
	public:

		TimerManager& timers() { return m_timers; }
		const TimerManager& timers() const { return m_timers; }

		StopWatchManager& stopwatches() { return m_stopwatches; }
		const StopWatchManager& stopwatches() const { return m_stopwatches; }

	private:
		TimerManager m_timers;
		StopWatchManager m_stopwatches;

	};
} // namespace tick