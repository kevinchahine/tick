#pragma once

#include "TimerManager.h"
#include "StopWatchManager.h"

#include <boost/filesystem/path.hpp>

namespace tick
{
	class DeviceManager
	{
	public:

		TimerManager& timers() { return m_timers; }
		const TimerManager& timers() const { return m_timers; }

		StopWatchManager& stopwatches() { return m_stopwatches; }
		const StopWatchManager& stopwatches() const { return m_stopwatches; }

		boost::property_tree::ptree serialize() const;
		void parse(const boost::property_tree::ptree& tree);

	private:
		TimerManager m_timers;
		StopWatchManager m_stopwatches;

	};
} // namespace tick

std::ostream& operator<<(std::ostream& os, const tick::DeviceManager& devMan);
