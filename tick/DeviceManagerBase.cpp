#include "DeviceManagerBase.h"

using namespace std;
namespace pt = boost::property_tree;

namespace tick
{
	void DeviceManagerBase::start(const std::string& name)
	{
		// Look for a device that matches 'name'
		auto it = this->find(name);

		// Did we find a matching device?
		if (it != this->end()) {
			// Yes. Lets start it.
			it->second->start();	
		}
	}
	
	void DeviceManagerBase::startAll()
	{
		for (const auto& it : *this) {
			it.second->start();
		}
	}

	void DeviceManagerBase::stop(const std::string& name)
	{
		// Look for a device that matches 'name'
		auto it = this->find(name);

		// Did we find a matching device?
		if (it != this->end()) {
			// Yes. Lets stop it.
			it->second->stop();	
		}
	}

	void DeviceManagerBase::stopAll()
	{
		for (const auto& it : *this) {
			it.second->stop();
		}
	}

	void DeviceManagerBase::subtract(const std::string& name, const std::chrono::nanoseconds& dur)
	{
		// Look for a device that matches 'name'
		auto it = this->find(name);

		// Did we find a matching device?
		if (it != this->end()) {
			// Yes. Lets subtract its duration.
			it->second->subtract(dur);
		}
	}

	void DeviceManagerBase::subtractAll(const std::chrono::nanoseconds& dur)
	{
		for (const auto& it : *this) {
			it.second->subtract(dur);
		}
	}

	boost::property_tree::ptree DeviceManagerBase::serialize() const
	{
		pt::ptree tree;
	
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

	string DeviceManagerBase::findUnusedName(const string& base) const
	{
		const int DEFAULT_NAME_LIMIT = 100;

		string deviceName;

		int i;
		for (i = 0; i < DEFAULT_NAME_LIMIT; i++) {
			deviceName = base + to_string(i);

			auto it = this->find(deviceName);
			
			if (it == this->end()) {
				// This name is free and hasn't been used.
				break;
			}
		}

		if (i >= DEFAULT_NAME_LIMIT) {
			throw exception("Error: Exceeded count of default timer names");
		}

		return deviceName;
	}
}