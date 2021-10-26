#include "StopWatch.h"

#define BOOST_DATE_TIME_HAS_NANOSECONDS	// Allows use of boost::posix_time::nanoseconds()
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/property_tree/ptree.hpp>

#include <string>
#include <optional>

using namespace std;
using namespace std::chrono;

namespace pt = boost::property_tree;

namespace tick
{
	void StopWatch::reset(std::chrono::nanoseconds elapsedTime)
	{
		m_elapsed = elapsedTime;

		state = STATE::PAUSED;
	}

	void StopWatch::stop()
	{
		if (state == STATE::RESUMED) {
			m_elapsed += (high_resolution_clock::now() - lastResumed);

			state = STATE::PAUSED;
		}
	}

	void StopWatch::start()
	{
		if (state == STATE::PAUSED) {
			lastResumed = high_resolution_clock::now();

			state = STATE::RESUMED;
		}
	}

	void StopWatch::subtract(const chrono::nanoseconds& dur)
	{
		m_elapsed -= dur;
	}

	std::chrono::nanoseconds StopWatch::elapsed() const
	{
		switch (state)
		{
		case STATE::PAUSED:			return m_elapsed;
		case STATE::RESUMED:		return m_elapsed + (chrono::high_resolution_clock::now() - lastResumed);
		}
	}

	pt::ptree StopWatch::serialize() const
	{
		pt::ptree fieldTree;

		fieldTree.put("lastResumed", lastResumed.time_since_epoch().count());
		fieldTree.put("m_elapsed", m_elapsed.count());
		
		string stateStr = "PAUSED";
		switch (state)
		{
		case STATE::PAUSED:		stateStr = "PAUSED";	break;
		case STATE::RESUMED:	stateStr = "RESUMED";	break;
		default:	cout << "Unknown STATE, " << (int)state << endl;	break;
		}
		fieldTree.put("state", std::move(stateStr));
	
		// ------------------------------------------------------

		pt::ptree classTree;
		classTree.add_child("StopWatch", fieldTree);

		return classTree;
	}
	
	void StopWatch::parse(const pt::ptree& tree)
	{
		// 1.) --- Make sure this tree contains a "StopWatch" ---
		auto op = tree.get_child_optional("StopWatch");
		if (!op) {
			throw exception("This ptree did not contain a StopWatch object. The JSON file might be corrupt.");
		}

		// 2.) --- Parse Fields ---
		const pt::ptree& fieldTree = op.value();

		{ // --- lastResumed ---
			auto op = fieldTree.get_optional<long long>("lastResumed");
			long long timeSinceEpoch;
	
			if (op) {
				timeSinceEpoch = op.value();
			}
			else {
				cout << "Error: Corrupt property tree. Missing value for lastResumed. "
					<< "Using default of now() instead" << endl;
	
				timeSinceEpoch = chrono::high_resolution_clock::now().time_since_epoch().count();
			}
	
			lastResumed -= lastResumed.time_since_epoch();
			lastResumed += chrono::high_resolution_clock::duration{ timeSinceEpoch };
		}
	
		{ // --- m_elapsed ---
			auto op = fieldTree.get_optional<long long>("m_elapsed");
			long long dur;
	
			if (op) {
				dur = op.value();
			}
			else {
				cout << "Error: Corrupt property tree. Missing value for m_elapsed. "
					<< "Using default of 0 instead" << endl;
	
				dur = 0;
			}
	
			m_elapsed = chrono::nanoseconds(dur);
		}
	
		{ // --- state ---
			auto op = fieldTree.get_optional<string>("state");
	
			if (!op) {
				cout << "Error: Corrupt property tree. Missing value for state. "
					<< "Using default of PAUSED instead" << endl;
			}
	
			const string& stateVal = op.value_or("PAUSED");
	
			if (stateVal == "PAUSED") {
				state = STATE::PAUSED;
			}
			else if (stateVal == "RESUMED") {
				state = STATE::RESUMED;
			}
			else {
				cout << "Error: Unknown state found in property tree: " << stateVal << endl;
				state = STATE::PAUSED;
			}
		}
	}

	std::ostream & operator<<(std::ostream & os, const StopWatch & sw)
	{
		nanoseconds elapsed = sw.elapsed();
		hours hrs = duration_cast<hours>(elapsed);
		minutes min = duration_cast<minutes>(elapsed) - hrs;
		seconds sec = duration_cast<seconds>(elapsed) - hrs - min;

		stringstream ss;

		ss << hrs.count() << ':';

		ss << min.count() << ':';
		
		if (sec.count() < 10)
			ss << '0';
		
		ss << sec.count();

		ss << setw(10) << (sw.is_resumed() ? "running" : "stopped");

		os << ss.str();

		return os;
	}
} // namespace tick

