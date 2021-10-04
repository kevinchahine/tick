#pragma once

#include <iostream>
#include <string>
#include <map>

#include "Timer.h"

namespace tick
{
	class TimerManager : public std::map<std::string, Timer>
	{
	public:
		template<typename KEY_T, typename TIMER_T>
		void insert(KEY_T&& key, TIMER_T&& timer = Timer{})
		{
			this->std::map<std::string, Timer>::insert(
				std::make_pair(
					std::forward<KEY_T>(key), 
					std::forward<TIMER_T>(timer)));
		}
		
		// Inserts a timer and gives it a default name
		void insert(const Timer& timer)
		{
			// 1.) --- Search for an unused name ---
			std::string name = findUnusedName();

			// 2.) 
			this->insert(
				std::move(name), 
				timer);
		}

		// Inserts a default constructed timer with a specified name
		void insert(std::string&& name)
		{
			insert(std::move(name), Timer{});
		}
		
		// Inserts a default constructed timer with a specified name
		void insert(const std::string& name)
		{
			insert(name, Timer{});
		}

		// Insert a default constructed Timer with a default name
		void insert()
		{
			std::string timerName = findUnusedName();

			insert(std::move(timerName));
		}

		void start(const std::string& name);
		void startAll();

		void stop(const std::string& name);
		void stopAll();

		boost::property_tree::ptree serialize() const;
		void parse(const boost::property_tree::ptree& tree);

	private:
		// Base method which other methods can call.
		// Most methods have very similar internal implementations.
		// To prevent having to implement each method as a copy of the others
		//  except for one line which might be a little different, all methods
		//  can be implemented as 'baseMethod()' and the little difference can be
		//	passed as a function pointer.
		// Hint: This is an example of functional programming.
		// methodPtr could be any method in class Timer which returns void and takes no parameters
		void baseMethod(void (Timer::*methodPtr)(), const std::string& name);

		// See comments for baseMethod()
		void baseMethodAll(void (Timer::*methodPtr)());

		std::string findUnusedName() const;
	};
} // namespace tick

std::ostream& operator<<(std::ostream& os, const tick::TimerManager& manager);