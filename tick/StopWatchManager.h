#pragma once

#include "StopWatch.h"
#include "DeviceManagerTemplate.h"

#include <string>
#include <map>

#include <boost/property_tree/ptree_fwd.hpp>

namespace tick
{
	class StopWatchManager : public DeviceManagerTemplate<StopWatch>
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
		void baseMethod(void (StopWatch::* methodPtr)(), const std::string& name);

		// See comments for baseMethod()
		void baseMethodAll(void (StopWatch::* methodPtr)());


	};
} // namespace tick

std::ostream& operator<<(std::ostream& os, const tick::StopWatchManager& manager);