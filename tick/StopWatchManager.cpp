#include "StopWatchManager.h"

#include <boost/property_tree/ptree.hpp>

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

	boost::property_tree::ptree StopWatchManager::serialize() const
	{
		boost::property_tree::ptree tree;

		cout << __FUNCTION__ << " Not implemented\n";
		
		return tree;
	}

	void StopWatchManager::parse(const boost::property_tree::ptree& tree)
	{
		cout << __FUNCTION__ << " Not implemented\n";
	}
}