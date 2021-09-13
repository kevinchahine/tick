#pragma once

#include <boost/program_options/options_description.hpp>	

#include <iostream>
#include <string>

namespace tick
{
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

	private:
		boost::program_options::options_description desc;
	};
} // namespace tick