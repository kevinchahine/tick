#include "DeviceManagerBase.h"

using namespace std;
namespace pt = boost::property_tree;

namespace tick
{
	boost::property_tree::ptree DeviceManagerBase::serialize() const
	{
		boost::property_tree::ptree tree;
	
		// Iterate each device in this container
		for (const auto& it : *this) {
			// Grab the key (name) and value (device)
			const string& name = it.first;
			const DeviceBase& device = static_cast<const DeviceBase&>(*it.second);
	
			// Serialize the device
			pt::ptree subtree = device.serialize();
			
			// Push subtree into bigger tree
			tree.add_child(name, subtree);
		}
	
		return tree;
	}

	string DeviceManagerBase::findUnusedName() const
	{
		const int DEFAULT_NAME_LIMIT = 100;

		string timerName;

		int i;
		for (i = 0; i < DEFAULT_NAME_LIMIT; i++) {
			timerName = "timer" + to_string(i);

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