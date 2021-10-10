#pragma once

#include "DeviceBase.h"

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
			std::cout << __FUNCTION__ << " is called " << deviceName << " size = " << this->size() << std::endl;
			this->std::map<std::string, std::unique_ptr<DeviceBase>>::insert(
				std::make_pair(deviceName, std::move(devicePtr))
			);
			std::cout << this->size() << std::endl;
		}
		//virtual void insert(std::string&& deviceName, std::unique_ptr<DeviceBase>&& devicePtr)
		//{
		//	std::cout << __FUNCTION__ << std::endl;
		//	this->std::map<std::string, std::unique_ptr<DeviceBase>>::insert(
		//		std::make_pair(std::move(deviceName), std::move(devicePtr))
		//	);
		//}
		
		boost::property_tree::ptree serialize() const;
		virtual void parse(const boost::property_tree::ptree& tree) = 0;

	protected:

		std::string findUnusedName() const;
	};
}