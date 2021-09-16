#pragma once

#include <boost/program_options/options_description.hpp>	

#include <iostream>
#include <string>

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
		CommandHandler();
		CommandHandler(const CommandHandler &) = default;
		CommandHandler(CommandHandler&&) noexcept = default;
		~CommandHandler() noexcept = default;
		CommandHandler& operator=(const CommandHandler&) = default;
		CommandHandler& operator=(CommandHandler&&) noexcept = default;

		void handle(int argc, const char** argv);
		void handle(const std::vector<std::string>& args);
		void handle(const std::string& cmdLine);

	private:
		// Main command description
		boost::program_options::options_description desc;

		// Sub command descriptions
		boost::program_options::options_description showDesc;		
		boost::program_options::options_description newDesc;		
		boost::program_options::options_description deleteDesc;		
		boost::program_options::options_description startDesc;		
		boost::program_options::options_description pauseDesc;		
		boost::program_options::options_description stopDesc;		
		boost::program_options::options_description switchDesc;		
		boost::program_options::options_description setDesc;	
	};
} // namespace tick