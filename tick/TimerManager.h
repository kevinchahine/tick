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
		void insert(Timer&& timer)
		{
			// 1.) --- Search for an unused name ---
			std::string name = "timer0";	// TODO: IMplement this

			// 2.) 
			this->insert(
				std::move(name), 
				std::forward<Timer>(timer));
		}

		// Inserts a default constructed timer with a specified name
		void insert(std::string&& name)
		{
			insert(
				std::forward<std::string>(name),
				Timer{});
		}

		// Insert a default constructed Timer with a default name
		void insert()
		{
			const int DEFAULT_NAME_LIMIT = 100;
			
			std::string base = "timer";

			int i;
			for (i = 0; i < DEFAULT_NAME_LIMIT; i++) {
				std::string timerName = base + std::to_string(i);

				auto it = this->find(timerName);

				if (it == this->end()) {
					// This name is free. Create and name a timer after it.
					insert(std::move(timerName));
					break;
				}
				else {
					// This name is already taken
					continue;	// Try another name
				}
			}

			if (i >= DEFAULT_NAME_LIMIT) {
				std::cout << "Error: Exceeded count of default timer names." << std::endl;
			}
		}

		void start(const std::string& name);
		void startAll();

		void stop(const std::string& name);
		void stopAll();

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
	};
} // namespace tick

std::ostream& operator<<(std::ostream& os, const tick::TimerManager& manager);