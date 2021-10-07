#include "StopWatchManager.h"

#include <boost/property_tree/ptree.hpp>

#include <iomanip>

namespace pt = boost::property_tree;

using namespace std;

namespace tick
{
	void StopWatchManager::start(const std::string& name)
	{
		baseMethod(&StopWatch::start, name);
	}
	
	void StopWatchManager::startAll()
	{
		baseMethodAll(&StopWatch::start);
	}
	
	void StopWatchManager::stop(const std::string& name)
	{
		baseMethod(&StopWatch::stop, name);
	}
	
	void StopWatchManager::stopAll()
	{
		baseMethodAll(&StopWatch::stop);
	}

	pt::ptree StopWatchManager::serialize() const
	{
		pt::ptree tree;

		for (const auto& it : *this) {
			/////////////////const string& name = it.first;
			/////////////////const StopWatch& watch = it.second;
			/////////////////
			/////////////////pt::ptree subtree = watch.serialize();
			/////////////////
			/////////////////tree.add_child(name, subtree);
		}

		return tree;
	}

	void StopWatchManager::parse(const boost::property_tree::ptree& tree)
	{
		// 1.) --- Delete existing stopwatches ---
		this->clear();

		// 2.) --- Iterate tree ---
		for (const auto& it : tree) {
			///////////////const string& name = it.first;
			///////////////const pt::ptree& subtree = it.second;
			///////////////
			///////////////StopWatch sw;
			///////////////sw.parse(subtree);
			///////////////
			///////////////// 3.) --- Insert the new StopWatch ---
			///////////////this->insert(name, sw);
		}
	}

	void StopWatchManager::baseMethod(void (StopWatch::* methodPtr)(), const std::string& name)
	{
		// Look for a timer that matches 'name'
		auto it = this->find(name);

		// Did we find a matching timer?
		if (it != this->end()) {
			// Yes. Lets start it.
			//////////////(it->second.*methodPtr)();	// Call method pointer
		}
	}

	// See comments for baseMethod()
	void StopWatchManager::baseMethodAll(void (StopWatch::* methodPtr)())
	{
		for (auto& pair : (*this)) {
			///////////////////(pair.second.*methodPtr)();	// Call method pointer
		}
	}
}

std::ostream& operator<<(std::ostream& os, const tick::StopWatchManager& manager)
{
	auto flags = os.flags();

	os << "Stop Watches:\n";

	os << left;

	for (const auto& pair : manager) {
		///////////const string& name = pair.first;
		///////////const tick::StopWatch& sw = pair.second;
		///////////
		///////////os << setw(4) << '\0' << setw(10) << name << setw(10) << sw << endl;
	}

	os.flags(flags);

	return os;
}