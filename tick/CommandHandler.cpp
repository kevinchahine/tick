#include "CommandHandler.h"

#include <algorithm>
#include <string>
#include <iomanip>

#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>					// break this down
#include <boost/algorithm/string/split.hpp>				// for boost::split
#include <boost/algorithm/string/classification.hpp>	// for boost::is_any_of

namespace po = boost::program_options;
using namespace std;

namespace tick
{
	CommandHandler::CommandHandler(DeviceManager& devices) :
		devicesPtr(&devices)
	{
	}

	void CommandHandler::handle(int argc, const char** argv)
	{
		vector<string> tokens;
		tokens.reserve(argc);

		for (int i = 0; i < argc; i++) {
			tokens.emplace_back(argv[i]);
		}

		handle(tokens);
	}

	void CommandHandler::handle(const std::string& cmdLine)
	{
		// Might not be enough. Parsing based only on spaces will mean spaces enclosed in quotes will also be
		// separators
		vector<string> tokens;
		boost::split(tokens, cmdLine, boost::is_any_of(" "));

		handle(tokens);
	}

	void CommandHandler::handle(const std::vector<std::string>& args)
	{
		if (args.size()) {
			handle1(args.begin(), args.end());
		}
		else {
			cout << "Error: No args" << endl;
		}
	}

	void CommandHandler::handle1(const std::vector<std::string>::const_iterator begin, const std::vector<std::string>::const_iterator end)
	{
		const string& first = *begin;

		if (boost::iequals(first, "tick")) {
			handle2(begin + 1, end);
		}
		else {
			handle2(begin, end);
		}
	}

	void CommandHandler::handle2(const std::vector<std::string>::const_iterator begin, const std::vector<std::string>::const_iterator end)
	{
		if (begin == end) {
			throw exception("Expected a 2nd argument");
		}

		string second = *begin;
		boost::algorithm::to_lower(second);

		if (second == "make") {
			handleMake(begin + 1, end);
		}
		else if (second == "start") {
			handleStart(begin + 1, end);
		}
		else if (second == "stop") {
			handleStop(begin + 1, end);
		}
		else if (second == "set") {
			handleSet(begin + 1, end);
		}
		else if (second == "remove" || second == "rm") {
			handleRemove(begin + 1, end);
		}
		else if (second == "restore") {
			handleRestore(begin + 1, end);
		}
		else if (second == "switch") {
			// TODO: for a later version
		}
		else if (second == "show") {
			handleShow(begin + 1, end);
		}
		else if (second == "help") {
			handleHelp(begin + 1, end);
		}
		else {
			cout << "Unknown 2nd argument: \'" << second << "\'\n";
		}
	}

	void CommandHandler::handleMake(
		const std::vector<std::string>::const_iterator begin,
		const std::vector<std::string>::const_iterator end)
	{
		if (begin == end) {
			// No arguments
			// Nothing to do here
			throw exception("Error: No device specified.Ex : timer, stopwatch, ...\n");
		}
		else {
			// --- Determine the Device Type ---
			const string & device = *begin;
			boost::algorithm::to_lower(device);

			DeviceManagerBase & man = devicesPtr->getManager(device);
			if (begin + 1 == end) {
				// No device names given. Have manager pick a name automatically
				man.insert();	
			}
			else {
				// One or more device names given
				for (auto it = begin + 1; it != end; ++it) {
					man.insert(*it);
				}
			}
		}
	}

	void CommandHandler::handleStart(
		const std::vector<std::string>::const_iterator begin,
		const std::vector<std::string>::const_iterator end)
	{
		if (begin == end) {
			// No arguments
			// Nothing to do here
			cout << "Error: No device specified. Ex: timer, stopwatch, ...\n";
			return;
		}
		else {
			// --- Determine the Device Type ---
			string device = *begin;
			boost::algorithm::to_lower(device);

			if (device == "timer") {
				if (begin + 1 == end || *(begin + 1) == "all") {
					// No names given
					devicesPtr->timers().startAll();
				}
				else {
					for (auto it = begin + 1; it != end; ++it) {
						devicesPtr->timers().start(*it);
					}
				}
			}
			else if (device == "stopwatch") {
				if (begin + 1 == end) {
					// No names given. Use default name
					devicesPtr->stopwatches().startAll();
				}
				else {
					for (auto it = begin + 1; it != end; ++it) {
						devicesPtr->stopwatches().start(*it);
					}
				}
			}
			else if (device == "alarm") {
			}
			else if (device == "worldclock") {
			}
			else {
				cout << "Error: Unexpected device type: " << device << endl;
				return;
			}
		}
	}

	void CommandHandler::handleStop(
		const std::vector<std::string>::const_iterator begin,
		const std::vector<std::string>::const_iterator end)
	{
		if (begin == end) {
			// No arguments
			// Nothing to do here
			cout << "Error: No device specified. Ex: timer, stopwatch, ...\n";
			return;
		}
		else {
			// --- Determine the Device Type ---
			string device = *begin;
			boost::algorithm::to_lower(device);

			if (device == "timer") {
				if (begin + 1 == end || *(begin + 1) == "all") {
					// No names given
					devicesPtr->timers().stopAll();
				}
				else {
					for (auto it = begin + 1; it != end; ++it) {
						devicesPtr->timers().stop(*it);
					}
				}
			}
			else if (device == "stopwatch") {
				if (begin + 1 == end) {
					// No names given. Use default name
					devicesPtr->stopwatches().stopAll();
				}
				else {
					for (auto it = begin + 1; it != end; ++it) {
						devicesPtr->stopwatches().stop(*it);
					}
				}
			}
			else if (device == "alarm") {
			}
			else if (device == "worldclock") {
			}
			else {
				cout << "Error: Unexpected device type: " << device << endl;
				return;
			}
		}
	}

	void CommandHandler::handleSet(
		const std::vector<std::string>::const_iterator begin,
		const std::vector<std::string>::const_iterator end)
	{
	}

	void CommandHandler::handleRemove(
		const std::vector<std::string>::const_iterator begin,
		const std::vector<std::string>::const_iterator end)
	{
	}

	void CommandHandler::handleRestore(
		const std::vector<std::string>::const_iterator begin,
		const std::vector<std::string>::const_iterator end)
	{
	}

	void CommandHandler::handleShow(
		const std::vector<std::string>::const_iterator begin,
		const std::vector<std::string>::const_iterator end)
	{
		if (begin == end) {
			// No arguments
			// Show everything
			cout << *devicesPtr << endl;
		}
		else {
			// --- Determine the Device Type ---
			string device = *begin;
			boost::algorithm::to_lower(device);

			if (device == "timer") {
				if (begin + 1 == end) {
					// Show all timers
					cout << devicesPtr->timers() << endl;
				}
				else {
					for (auto it = begin + 1; it != end; ++it) {
						devicesPtr->timers().insert(*it, Timer{});
					}
				}
			}
			else if (device == "stopwatch") {
				if (begin + 1 == end) {
					// Show all StopWatches
					devicesPtr->stopwatches().insert();
				}
				else {
					for (auto it = begin + 1; it != end; ++it) {
						devicesPtr->stopwatches().insert(*it, StopWatch{});
					}
				}
			}
			else if (device == "alarm") {
			}
			else if (device == "worldclock") {
			}
			else {
				cout << "Error: Unexpected device type: " << device << endl;
				return;
			}
		}
	}

	void CommandHandler::handleHelp(
		const std::vector<std::string>::const_iterator begin,
		const std::vector<std::string>::const_iterator end)
	{
		int w = 12;

		auto flags = cout.flags();
		cout << left;

		// --- First Command ---
		cout << "Tick" << endl;

		if (begin == end) {
			// --- Second Commands ---
			cout
				<< setw(w) << "\tMake" << "Creates a device" << endl
				<< setw(w) << "\tStart" << "Resumes or activates a device" << endl
				<< setw(w) << "\tStop" << "Pauses or deactivates a device" << endl
				<< setw(w) << "\tSet" << "Assigns value to a device" << endl
				<< setw(w) << "\tRemove" << "Moves a device to local recycling bin" << endl
				<< setw(w) << "\tRestore" << "Restores a device from local recycling bin" << endl
				<< setw(w) << "\tShow" << "Prints information about devices" << endl
				<< setw(w) << "\tExit" << "Exits the tick session. Devices will remain operational" << endl
				<< endl;

			// --- Devices ---
			cout << "Devices:" << endl
				<< setw(w) << "\tTimer" << "Counts down from a set duration. Can perform a set action at time out." << endl
				<< setw(w) << "\tStopwatch" << "Counts up from 0" << endl
				<< setw(w) << "\tAlarm" << "Triggers an event at its set time" << endl
				<< setw(w) << "\tWorldClock" << "Displays time at a specified time zone" << endl
				<< endl;

			// --- Examples ---
			cout << "Examples:" << endl
				<< "\trun \'tick help examples\' to see examples" << endl;
		}
		else if (*begin == "examples") {
			w = 28;

			// --- Creating Devices ---
			cout << "Examples:" << endl
				<< setw(w) << "\ttick make timer" << "Creates a timer with an automatic name" << endl
				<< setw(w) << "\ttick make timer myTimer1" << "Creates a timer called \'myTimer1\'" << endl
				<< setw(w) << "\ttick make timer t1 t2 t3" << "Creates 3 timers" << endl
				<< endl
				<< setw(w) << "\ttick start timer t1" << "Resumes timer \'t1\'" << endl
				<< setw(w) << "\ttick start timer t2 t3" << "Resumes timers \'t1\' and \'t2\'" << endl
				<< setw(w) << "\ttick start timer" << "Resumes all timers" << endl
				<< endl
				<< setw(w) << "\ttick stop timer t1" << "Pauses timer \'t1\'" << endl
				<< setw(w) << "\ttick stop timer t2 t3" << "Pauses timers \'t1\' and \'t2\'" << endl
				<< setw(w) << "\ttick stop timer" << "Pauses all timers" << endl
				<< endl
				<< setw(w) << "\ttick show" << "Shows all devices" << endl
				<< setw(w) << "\ttick show timer" << "Show all timers" << endl
				<< setw(w) << "\ttick show timer t1 t2" << "Show timers \'t1\' and \'t2\'" << endl
				<< setw(w) << "\ttick show stopwatch" << "Shows all stopwatches" << endl
				<< setw(w) << "\ttick show alarm" << "Shows all alarms" << endl
				<< setw(w) << "\ttick show worldclock" << "Shows all world clocks" << endl
				<< endl;
		}

		cout << endl;
		cout.flags(flags);
	}

} // namespace tick