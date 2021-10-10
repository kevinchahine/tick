#pragma once

#include "DeviceBase.h"

#include <iostream>
#include <chrono>

namespace tick
{
	class Timer : public DeviceBase
	{
	public:
		static std::string name() { return "timer"; }

		virtual void start() override;

		virtual void stop() override;

		bool is_paused() const { return state == STATE::PAUSED; }

		bool is_resumed() const { return state == STATE::RESUMED; }

		bool is_expired() const;

		bool is_not_expired() const { return !is_expired(); }

		void expires_from_now(const std::chrono::nanoseconds & duration);

		std::chrono::nanoseconds expires_from_now() const;

		void add_time(const std::chrono::nanoseconds & duration);

		virtual boost::property_tree::ptree serialize() const override;

		virtual void parse(const boost::property_tree::ptree& tree) override;

	protected:

		// Time at which the timer was last resumed
		std::chrono::high_resolution_clock::time_point lastResumed = 
			std::chrono::high_resolution_clock::now();

		// Amount of time left in the timer at the time the timer was last resumed.
		// If the timer is paused then expiry is the time left.
		// Time left before timer expires is (expiry - (now - lastResumed))
		std::chrono::nanoseconds expiry = std::chrono::nanoseconds(0);

		enum class STATE : bool
		{
			PAUSED,
			RESUMED
		} state = STATE::PAUSED;
	};
} // namespace tick

std::ostream& operator<<(std::ostream& os, const tick::Timer& timer);
