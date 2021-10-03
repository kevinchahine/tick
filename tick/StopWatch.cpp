#include "StopWatch.h"

#define BOOST_DATE_TIME_HAS_NANOSECONDS	// Allows use of boost::posix_time::nanoseconds()
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/property_tree/ptree.hpp>

#include <string>
#include <optional>

using namespace std;
using namespace std::chrono;

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

	std::chrono::nanoseconds StopWatch::elapsed() const
	{
		switch (state)
		{
		case STATE::PAUSED:			return m_elapsed;
		case STATE::RESUMED:		return m_elapsed + (chrono::high_resolution_clock::now() - lastResumed);
		}
	}

	boost::property_tree::ptree StopWatch::serialize() const
	{
		boost::property_tree::ptree tree;
	
		tree.put("lastResumed", lastResumed.time_since_epoch().count());
		tree.put("m_elapsed", m_elapsed.count());
		
		string stateStr = "PAUSED";
		switch (state)
		{
		case STATE::PAUSED:		stateStr = "PAUSED";	break;
		case STATE::RESUMED:	stateStr = "RESUMED";	break;
		default:	cout << "Unknown STATE, " << (int)state << endl;	break;
		}
		tree.put("state", std::move(stateStr));
	
		return tree;
	}
	
	void StopWatch::parse(const boost::property_tree::ptree& tree)
	{
		{ // --- lastResumed ---
			auto op = tree.get_optional<long long>("lastResumed");
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
			auto op = tree.get_optional<long long>("m_elapsed");
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
			auto op = tree.get_optional<string>("state");
	
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
		minutes min = duration_cast<minutes>(elapsed);
		seconds sec = duration_cast<seconds>(elapsed) - min;

		os << min.count() << ':';
		
		if (sec.count() < 10)
			os << '0';
		
		os << sec.count();

		return os;
	}
} // namespace tick

