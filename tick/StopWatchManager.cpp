#include "StopWatchManager.h"

#include <boost/property_tree/ptree.hpp>

namespace pt = boost::property_tree;

using namespace std;

namespace tick
{
	void StopWatchManager::start(const std::string& name)
	{
	}
	
	void StopWatchManager::startAll()
	{
	}
	
	void StopWatchManager::stop(const std::string& name)
	{
	}
	
	void StopWatchManager::stopAll()
	{
	}

	pt::ptree StopWatchManager::serialize() const
	{
		pt::ptree tree;

		for (const auto& it : *this) {
			const string& name = it.first;
			const StopWatch& watch = it.second;

			pt::ptree subtree = watch.serialize();

			tree.add_child(name, subtree);
		}

		return tree;
	}

	void StopWatchManager::parse(const boost::property_tree::ptree& tree)
	{
		// 1.) --- Delete existing stopwatches ---
		this->clear();

		// 2.) --- Iterate tree ---
		for (const auto& it : tree) {
			const string& name = it.first;
			const pt::ptree& subtree = it.second;

			StopWatch sw;
			sw.parse(subtree);

			// 3.) --- Insert the new StopWatch ---
			this->insert(name, sw);
		}
	}
}