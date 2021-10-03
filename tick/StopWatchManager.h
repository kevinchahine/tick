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

		// Inserts a stopwatch and gives it a default name
		void insert(StopWatch&& stopwatch)
		{
			// 1.) --- Search for an unused name ---
			std::string name = "stopwatch0";	// TODO: IMplement this
		
			// 2.) 
			this->insert(
				std::move(name),
				std::forward<StopWatch>(stopwatch));
		}
		
		// Inserts a default constructed stopwatch with a specified name
		void insert(std::string&& name)
		{
			insert(
				std::forward<std::string>(name),
				StopWatch{});
		}

		// Insert a default constructed StopWatch with a default name
		void insert()
		{
			const int DEFAULT_NAME_LIMIT = 100;

			std::string base = "stopwatch";

			int i;
			for (i = 0; i < DEFAULT_NAME_LIMIT; i++) {
				std::string stopwatchName = base + std::to_string(i);

				auto it = this->find(stopwatchName);

				if (it == this->end()) {
					// This name is free. Create and name a stopwatch after it.
					insert(std::move(stopwatchName));
				}
				else {
					// This name is already taken
					continue;	// Try another name
				}
			}

			if (i >= DEFAULT_NAME_LIMIT) {
				std::cout << "Error: Exceeded count of default stopwatch names." << std::endl;
			}
		}

		void start(const std::string& name);
		void startAll();

		void stop(const std::string& name);
		void stopAll();

		boost::property_tree::ptree serialize() const;
		void parse(const boost::property_tree::ptree& tree);

	private:

	};
} // namespace tick