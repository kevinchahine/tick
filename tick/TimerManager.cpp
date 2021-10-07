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

	boost::property_tree::ptree TimerManager::serialize() const
	{
		boost::property_tree::ptree tree;

		for (const auto& it : *this) {
			const string& name = it.first;
			/////////////const Timer& timer = it.second;

			////////////pt::ptree subtree = timer.serialize();

			//////////tree.add_child(name, subtree);
		}

		return tree;
	}

	void TimerManager::parse(const pt::ptree& tree)
	{
		// 1.) --- Delete existing timers ---
		this->clear();

		// 2.) --- Iterate tree ---
		for (const auto& it : tree) {
			const string& name = it.first;
			const pt::ptree& subtree = it.second;

			///////////////Timer t;
			///////////////t.parse(subtree);
			///////////////
			///////////////// 3.) --- Insert the new Timer ---
			///////////////this->insert(name, t);
		}
	}

	void TimerManager::baseMethod(void(Timer::*methodPtr)(), const std::string& name)
	{
		// Look for a timer that matches 'name'
		auto it = this->find(name);

		// Did we find a matching timer?
		if (it != this->end()) {
			// Yes. Lets start it.
			/////////////(it->second.*methodPtr)();	// Call method pointer
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
		os << setw(4) << '\0' << setw(10) << pair.first << setw(10) << pair.second << endl;
	}

	os.flags(flags);

	return os;
}