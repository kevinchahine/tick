#pragma once

#include <string>
#include <map>

#include "StopWatch.h"
#include <boost/property_tree/ptree_fwd.hpp>

namespace tick
{
	class StopWatchManager : public std::map<std::string, StopWatch>
	{
	public:
		template<typename KEY_T, typename SW_T>
		void insert(KEY_T&& key, SW_T&& stopwatch)
		{
			this->std::map<std::string, StopWatch>::insert(
				std::make_pair(
					std::forward<KEY_T>(key),
					std::forward<SW_T>(stopwatch)));
		}

		//// Inserts a stopwatch and gives it a default name
		//template<typename SW_T>
		//void insert(SW_T&& stopwatch = StopWatch{})
		//{
		//	// 1.) --- Search for an unused name ---
		//	std::string name = "stopwatch0";	// TODO: IMplement this
		//
		//	// 2.) 
		//	this->insert(
		//		std::move(name),
		//		std::forward<SW_T>(stopwatch));
		//}
		//
		//// Inserts a default constructed stopwatch with a specified name
		//template<typename KEY_T>
		//void insert(KEY_T&& name)
		//{
		//	insert(
		//		std::forward<KEY_T>(name),
		//		StopWatch{});
		//}

		// Insert a default constructed StopWatch with a default name
		//void insert()
		//{
		//	insert(StopWatch{});
		//}

		boost::property_tree::ptree serialize() const;
		void parse(const boost::property_tree::ptree& tree);

	private:

	};
} // namespace tick