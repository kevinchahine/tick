#include "TimerManager.h"

#include <iomanip>

#include <boost/property_tree/ptree.hpp>

using namespace std;
namespace pt = boost::property_tree;

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
			///////////////(it->second.*methodPtr)();	// Call method pointer
		}
	}

	void TimerManager::baseMethodAll(void(Timer::* methodPtr)())
	{
		for (auto& pair : (*this)) {
			//////////////////(pair.second.*methodPtr)();	// Call method pointer
		}
	}
}

std::ostream& operator<<(std::ostream& os, const tick::TimerManager& manager)
{
	auto flags = os.flags();

	os << "Timers:\n";

	os << left;

	for (const auto& pair : manager) {
		const string& name = pair.first;
		const tick::Timer& timer = static_cast<const tick::Timer&>(*pair.second);

		os << setw(4) << '\0' << setw(10) << name << setw(10) << timer << endl;
	}

	os.flags(flags);

	return os;
}