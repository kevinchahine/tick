#pragma once

#include <iostream>
#include <string>
#include <map>

#include "Timer.h"
#include "DeviceManagerTemplate.h"

namespace tick
{
	class TimerManager : public DeviceManagerTemplate<Timer>
	{
	public:

		void start(const std::string& name);
		void startAll();

		void stop(const std::string& name);
		void stopAll();

	private:
		// Base method which other methods can call.
		// Most methods have very similar internal implementations.
		// To prevent having to implement each method as a copy of the others
		//  except for one line which might be a little different, all methods
		//  can be implemented as 'baseMethod()' and the little difference can be
		//	passed as a function pointer.
		// Hint: This is an example of functional programming.
		// methodPtr could be any method in class Timer which returns void and takes no parameters
		void baseMethod(void (Timer::*methodPtr)(), const std::string& name);

		// See comments for baseMethod()
		void baseMethodAll(void (Timer::*methodPtr)());

	};
} // namespace tick

std::ostream& operator<<(std::ostream& os, const tick::TimerManager& manager);