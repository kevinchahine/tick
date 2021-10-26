#pragma once

#include "DeviceBase.h"

#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <map>

#include <boost/property_tree/ptree.hpp>

namespace tick
{
	class DeviceManagerBase : public std::map<std::string, std::unique_ptr<DeviceBase>>
	{
	public:
		virtual void insert() = 0;
		virtual void insert(const std::string& deviceName) = 0;
		virtual void insert(std::string&& deviceName) = 0;
		virtual void insert(const std::string& deviceName, std::unique_ptr<DeviceBase>&& devicePtr)
		{
			this->std::map<std::string, std::unique_ptr<DeviceBase>>::insert(
				std::make_pair(deviceName, std::move(devicePtr))
			);
		}
		//virtual void insert(std::string&& deviceName, std::unique_ptr<DeviceBase>&& devicePtr)
		//{
		//	std::cout << __FUNCTION__ << std::endl;
		//	this->std::map<std::string, std::unique_ptr<DeviceBase>>::insert(
		//		std::make_pair(std::move(deviceName), std::move(devicePtr))
		//	);
		//}
		
		void start(const std::string & name);
		void startAll();

		void stop(const std::string& name);
		void stopAll();

		void subtract(const std::string& name, const std::chrono::nanoseconds & dur);
		void subtractAll(const std::chrono::nanoseconds& dur);
		
		void set(const std::string& name, int whatGoesHere);
		void setAll(int whatGoesHere);

		// This method should return a unique_ptr<DeviceBase> of the removed object
		std::unique_ptr<DeviceBase> remove(const std::string& name);
		// Think about this one.
		void removeAll();

		boost::property_tree::ptree serialize() const;
		virtual void parse(const boost::property_tree::ptree& tree) = 0;

	protected:

		// base is the first part of the device name.
		// ex: "timer", "stopwatch", "alarm", ...
		std::string findUnusedName(const std::string & base) const;
	};
}