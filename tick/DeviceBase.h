#pragma once

#include <boost/property_tree/ptree_fwd.hpp>

#include <chrono>

namespace tick
{
	class DeviceBase
	{
	public:
		static std::string name() { return "DeviceBase"; }

		virtual void start() = 0;
		virtual void stop() = 0;
		virtual void subtract(const std::chrono::nanoseconds& dur) = 0;
		//virtual void setTime(const std::chrono::nanoseconds& dur) = 0;	// Timer, world clock and alarm: time_point, Stopwatch: duration
		//virtual void show() = 0;

		virtual boost::property_tree::ptree serialize() const = 0;
		virtual void parse(const boost::property_tree::ptree&) = 0;

	private:

	};
} // namespace tick