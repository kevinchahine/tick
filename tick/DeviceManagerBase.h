#pragma once

#include "DeviceBase.h"

#include <iostream>
#include <memory>
#include <string>
#include <map>

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
			std::cout << __FUNCTION__ << std::endl;
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
		///template<typename KEY_T>
		///void insertt(KEY_T && key, )

	protected:

		std::string findUnusedName() const;
	};
}