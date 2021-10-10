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

	};
} // namespace tick

std::ostream& operator<<(std::ostream& os, const tick::TimerManager& manager);