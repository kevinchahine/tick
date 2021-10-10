#pragma once

#include <boost/property_tree/ptree_fwd.hpp>

namespace tick
{
	class DeviceBase
	{
	public:
		static std::string name() { return "DeviceBase"; }

		virtual void start() = 0;
		virtual void stop() = 0;
		//virtual void setTime() = 0;
		//virtual void show() = 0;

		virtual boost::property_tree::ptree serialize() const = 0;
		virtual void parse(const boost::property_tree::ptree&) = 0;

	private:

	};
} // namespace tick