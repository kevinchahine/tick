#pragma once

#include <boost/program_options/options_description.hpp>	

#include <iostream>
#include <string>

#include "DeviceManager.h"

namespace tick
{
	// Parses and handles command line arguments.
	// 
	// Command format:
	//	tick <subCommand> <options | switches | etc>
	// 
	// ex:
	//	tick show timer1		# shows state of timer1
	//
	// ex: --- timer commands ---
	//	tick timer add timer2		# creates a new timer calling it timer2
	//	tick start timer2			# resumes timer2's countdown
	//	tick resume timer2			# same as "tick start timer2"
	//	tick stop timer2			# pauses timer2's countdown
	//	tick pause timer2			# same as "tick stop timer2"
	//	tick set
	//	tick timer remove timer1	# places timer1 into a recycling bin. Can be deleted manualy by modifying json file.
	class CommandHandler
	{
	public:
		CommandHandler(DeviceManager & devices);
		CommandHandler(const CommandHandler&) = default;
		CommandHandler(CommandHandler&&) noexcept = default;
		~CommandHandler() noexcept = default;
		CommandHandler& operator=(const CommandHandler&) = default;
		CommandHandler& operator=(CommandHandler&&) noexcept = default;

		void handle(int argc, const char** argv);
		void handle(const std::string& cmdLine);
		void handle(const std::vector<std::string>& args);

	private:
		// Converts each string from its nickname to its regular name
		void solveAliases(const std::vector<std::string>& args);

		// Handles 1st command argument (tick)
		void handle1(
			const std::vector<std::string>::const_iterator begin,
			const std::vector<std::string>::const_iterator end);

		// Handles 2nd command argument (make, set, show, ...)
		void handle2(
			const std::vector<std::string>::const_iterator begin,
			const std::vector<std::string>::const_iterator end);

		void handleMake(
			const std::vector<std::string>::const_iterator begin,
			const std::vector<std::string>::const_iterator end);

		void handleStart(
			const std::vector<std::string>::const_iterator begin,
			const std::vector<std::string>::const_iterator end);
		
		void handleStop(
			const std::vector<std::string>::const_iterator begin,
			const std::vector<std::string>::const_iterator end);
		
		void handleSubtract(
			const std::vector<std::string>::const_iterator begin,
			const std::vector<std::string>::const_iterator end);

		void handleSet(
			const std::vector<std::string>::const_iterator begin,
			const std::vector<std::string>::const_iterator end);
		
		void handleRemove(
			const std::vector<std::string>::const_iterator begin,
			const std::vector<std::string>::const_iterator end);
		
		void handleRestore(
			const std::vector<std::string>::const_iterator begin,
			const std::vector<std::string>::const_iterator end);
		
		void handleShow(
			const std::vector<std::string>::const_iterator begin,
			const std::vector<std::string>::const_iterator end);

		void handleHelp(
			const std::vector<std::string>::const_iterator begin,
			const std::vector<std::string>::const_iterator end);

	private:

		// Points to the DeviceManager object that stores all the clock 
		// devices. 
		// Does not need to be deallocated.
		// Can sometimes be null.
		// TODO: Should we make this a reference?
		DeviceManager* devicesPtr = nullptr;
	};
} // namespace tick