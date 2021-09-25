#include "TimerManager.h"

#include <iomanip>

using namespace std;

namespace tick
{
	void TimerManager::start(const std::string& name)
	{
		baseMethod(&Timer::start, name);
	}
	
	void TimerManager::startAll()
	{
		baseMethodAll(&Timer::start);
	}

	void TimerManager::stop(const std::string& name)
	{
		baseMethod(&Timer::stop, name);
	}

	void TimerManager::stopAll()
	{
		baseMethodAll(&Timer::stop);
	}

	void TimerManager::baseMethod(void(Timer::*methodPtr)(), const std::string& name)
	{
		// Look for a timer that matches 'name'
		auto it = this->find(name);

		// Did we find a matching timer?
		if (it != this->end()) {
			// Yes. Lets start it.
			(it->second.*methodPtr)();	// Call method pointer
		}
	}

	void TimerManager::baseMethodAll(void(Timer::* methodPtr)())
	{
		for (auto& pair : (*this)) {
			(pair.second.*methodPtr)();	// Call method pointer
		}
	}

}

std::ostream& operator<<(std::ostream& os, const tick::TimerManager& manager)
{
	auto flags = os.flags();

	os << "Timers:\n";

	os << left;

	for (const auto& pair : manager) {
		os << setw(10) << pair.first << setw(10) << pair.second << endl;
	}

	os.flags(flags);

	return os;
}