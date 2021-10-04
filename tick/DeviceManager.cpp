#include "DeviceManager.h"

#include <fstream>

#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace std;

namespace pt = boost::property_tree;

namespace tick
{
	boost::property_tree::ptree DeviceManager::serialize() const
	{
		// 1.) --- Serialize all devices into separate property trees ---
		boost::property_tree::ptree timersTree = m_timers.serialize();
		boost::property_tree::ptree swTree = m_stopwatches.serialize();

		// 2.) --- Combine into one big tree ---
		boost::property_tree::ptree tree;
		tree.put_child("Timers", move(timersTree));
		tree.put_child("StopWatches", move(swTree));

		return tree;
	}
	
	void DeviceManager::parse(const boost::property_tree::ptree& tree)
	{
		// 1.) --- Iterate 1st level for each device ---
		for (const auto & it : tree) {
			const string& device = it.first;
			const pt::ptree& subtree = it.second;

			if (device == "Timers") {
				this->m_timers.parse(subtree);
			}
			else if (device == "StopWatches") {
				this->m_stopwatches.parse(subtree);
			}
			else {
				cout << "Error: " << __FUNCTION__ << " unknown device" << endl;
			}
		}
	}
}

std::ostream& operator<<(std::ostream& os, const tick::DeviceManager& devMan)
{
	os << devMan.timers() << endl
		<< devMan.stopwatches() << endl;

	return os;
}
