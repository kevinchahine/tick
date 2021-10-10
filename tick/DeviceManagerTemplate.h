#pragma once

#include "DeviceManagerBase.h"

namespace tick
{
	template<class DEVICE_T>
	class DeviceManagerTemplate : public DeviceManagerBase
	{
	public:

		// Insert a default constructed Timer with a default name
		virtual void insert() override
		{
			insert(findUnusedName());
		}

		// Inserts a default constructed timer with a specified name
		virtual void insert(const std::string& deviceName) override
		{
			insert(deviceName, DEVICE_T{});
		}

		// Inserts a default constructed timer with a specified name
		virtual void insert(std::string&& deviceName) override
		{
			insert(std::move(deviceName), DEVICE_T{});
		}

		// Inserts a timer and gives it a default name
		void insert(const DEVICE_T& device)
		{
			// 1.) --- Search for an unused name ---
			std::string name = findUnusedName();

			// 2.) 
			this->insert(
				std::move(name),
				device);
		}

		void insert(const std::string& key, const DEVICE_T& device = DEVICE_T{})
		{
			this->DeviceManagerBase::insert(
				key,
				std::make_unique<DEVICE_T>(device)
			);
		}

		virtual void parse(const boost::property_tree::ptree& tree) override
		{
			// 1.) --- Delete existing devices in their container ---
			this->clear();

			// 2.) --- Iterate tree ---
			for (const auto& it : tree) {
				const std::string& name = it.first;
				const boost::property_tree::ptree& subtree = it.second;

				DEVICE_T device;
				device.parse(subtree);

				// 3.) --- Insert the new Timer ---
				this->insert(name, device);
			}
		}
	};
}