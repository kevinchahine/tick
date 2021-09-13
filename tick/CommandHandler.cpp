#include "CommandHandler.h"

#include <boost/program_options.hpp>

namespace po = boost::program_options;
using namespace std;

namespace tick
{
	CommandHandler::CommandHandler() :
		desc("commands")
	{
		desc.add_options()
			("help", "Show help message"),
			("show", po::value<string>(), "Show existing clocks"),
			("new", po::value<string>(), "Create new clock"),
			("delete", po::value<string>(), "Delete existing clock"),
			("start", po::value<string>(), "Start a clock"),
			("pause", po::value<string>(), "Pause a clock"),
			("stop", po::value<string>(), "Same as pause"),
			("switch", po::value<string>(), "Pauses one clock and resumes another"),
			("set", po::value<string>(), "Sets time of a clock")
			;

	}
	
	void CommandHandler::handle(int argc, const char** argv)
	{
		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, desc), vm);
		po::notify(vm);

		// --- Help ---
		if (vm.count("help") || vm.size() < 0) {
			cout << desc << endl;
			return;
		}

		// --- Show ---

	}
} // namespace tick