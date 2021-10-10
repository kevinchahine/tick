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

	private:
		
	};
} // namespace tick

std::ostream& operator<<(std::ostream& os, const tick::StopWatchManager& manager);