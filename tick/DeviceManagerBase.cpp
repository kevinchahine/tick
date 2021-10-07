#include "DeviceManagerBase.h"

using namespace std;

namespace tick
{
	std::string DeviceManagerBase::findUnusedName() const
	{
		const int DEFAULT_NAME_LIMIT = 100;

		std::string timerName;

		int i;
		for (i = 0; i < DEFAULT_NAME_LIMIT; i++) {
			timerName = "timer" + std::to_string(i);

			auto it = this->find(timerName);
			
			if (it == this->end()) {
				// This name is free and hasn't been used.
				break;
			}
		}

		if (i >= DEFAULT_NAME_LIMIT) {
			throw exception("Error: Exceeded count of default timer names");
		}

		return timerName;
	}
}