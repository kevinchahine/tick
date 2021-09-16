#include "CommandHandler.h"

#include <algorithm>

#include <boost/program_options.hpp>
#include <boost/algorithm/string/split.hpp>				// for boost::split
#include <boost/algorithm/string/classification.hpp>	// for boost::is_any_of

namespace po = boost::program_options;
using namespace std;

namespace tick
{
	CommandHandler::CommandHandler() :
		desc("commands"),
		showDesc("show"),
		newDesc("new"),
		deleteDesc("delete"),
		startDesc("start"),
		pauseDesc("pause"),
		stopDesc("stop"),
		switchDesc("switch"),
		setDesc("set")
	{
		desc.add_options()
			("help", "Show help message")
			("show", po::value<string>(), "Show existing devices")
			("add", po::value<string>(), "Create new device")
			("delete", po::value<string>(), "Delete existing device")
			("start", po::value<string>(), "Start a device")
			("pause", po::value<string>(), "Pause a device")
			("stop", po::value<string>(), "Same as pause")
			("switch", po::value<string>(), "Pauses one device and resumes another")
			("set", po::value<string>(), "Sets time of a device")
			;

		showDesc.add_options()
		;

		newDesc.add_options()
		;
		
		showDesc.add_options()
		;
		
		newDesc.add_options()
		;
		
		deleteDesc.add_options()
		;
		
		startDesc.add_options()
		;
		
		pauseDesc.add_options()
		;
		
		stopDesc.add_options()
		;
		
		switchDesc.add_options()
		;
		
		setDesc.add_options()
		;
	}
	
	void CommandHandler::handle(int argc, const char** argv)
	{
		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, desc), vm);
		po::notify(vm);

		//cout << "---" << endl;
		//for (const auto& elem : vm) {
		//	cout << vm.size() << ' ' << elem.first << '-' << endl;
		//}

		// --- Help ---
		if (vm.count("help") || vm.size() <= 0) {
			cout << desc << endl;
			return;
		}

		// --- Show ---

	}

	void CommandHandler::handle(const std::vector<std::string>& args)
	{
		vector<const char*> tokenPtrs;
		tokenPtrs.reserve(args.size());

		transform(args.begin(), args.end(), back_inserter(tokenPtrs), [](const string& tok) { return tok.data(); });

		this->handle(tokenPtrs.size(), tokenPtrs.data());
	}

	void CommandHandler::handle(const std::string& cmdLine)
	{
		// Might not be enough. Parsing based only on spaces will mean spaces enclosed in quotes will also be
		// separators
		vector<string> tokens;
		boost::split(tokens, cmdLine, boost::is_any_of(" "));

		handle(tokens);
	}
} // namespace tick