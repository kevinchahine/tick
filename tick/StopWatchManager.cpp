#include "StopWatchManager.h"

#include <boost/property_tree/ptree.hpp>

namespace tick
{

	boost::property_tree::ptree StopWatchManager::serialize() const
	{
		boost::property_tree::ptree tree;

		return tree;
	}

	void StopWatchManager::parse(const boost::property_tree::ptree& tree)
	{

	}

}