#include "Timer.h"

#define BOOST_DATE_TIME_HAS_NANOSECONDS	// Allows use of boost::posix_time::nanoseconds()
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/property_tree/ptree.hpp>

#include <optional>

using namespace std;

namespace pt = boost::property_tree;

namespace tick
{
	void Timer::start()
	{
		if (state == STATE::PAUSED) {
			lastResumed = chrono::high_resolution_clock::now();

			state = STATE::RESUMED;
		}
	}

	void Timer::stop()
	{
		// Make sure not to pause a paused timer.
		if (state == STATE::RESUMED) {
			// What time is it?
			chrono::high_resolution_clock::time_point currTime = chrono::high_resolution_clock::now();

			// How long has the timer been ticking since it was last resumed?
			chrono::nanoseconds sinceLastResume = (currTime - lastResumed);

			// Decrease that time from expiry
			expiry -= sinceLastResume;

			state = STATE::PAUSED;
		}
	}

	void Timer::subtract(const std::chrono::nanoseconds& dur)
	{
		expiry -= dur;
	}

	bool Timer::is_expired() const
	{
		return expires_from_now().count() > 0;
	}

	void Timer::expires_from_now(const chrono::nanoseconds& duration)
	{
		expiry = duration;
	}

	std::chrono::nanoseconds Timer::expires_from_now() const
	{
		switch (state)
		{
		case STATE::PAUSED:			return expiry;
		case STATE::RESUMED:		return expiry - (chrono::high_resolution_clock::now() - lastResumed);
		}
	}

	void Timer::add_time(const std::chrono::nanoseconds& duration)
	{
		expiry += duration;
	}

	pt::ptree Timer::serialize() const
	{
		pt::ptree fieldTree;
		
		fieldTree.put("lastResumed", lastResumed.time_since_epoch().count());
		fieldTree.put("expiry", expiry.count());

		string stateStr = "PAUSED";
		switch (state) {
		case STATE::PAUSED:		stateStr = "PAUSED";	break;
		case STATE::RESUMED:	stateStr = "RESUMED";	break;
		default:	cout << "Unknown STATE, " << (int)state << endl;	break;
		}
		fieldTree.put("state", std::move(stateStr));

		// ------------------------------------------------------

		pt::ptree classTree;
		classTree.add_child("Timer", fieldTree);

		return classTree;
	}

	void Timer::parse(const pt::ptree& tree)
	{
		// 1.) --- Make sure this tree contains a "Timer" ---
		auto op = tree.get_child_optional("Timer");
		if (!op) {
			throw exception("This ptree did not contain a Timer object. The JSON file might be corrupt.");
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

			lastResumed -= lastResumed.time_since_epoch();					// Zero-out timer_point
			lastResumed += chrono::steady_clock::duration{ timeSinceEpoch };// Increment by saved duration
		}

		{ // --- expiry ---
			auto op = fieldTree.get_optional<long long>("expiry");
			long long dur;

			if (op) {
				dur = op.value();
			}
			else {
				cout << "Error: Corrupt property tree. Missing value for expiry. "
					<< "Using default of 0 instead" << endl;

				dur = 0;
			}

			expiry = chrono::nanoseconds(dur);
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
} // namespace tick

std::ostream& operator<<(std::ostream& os, const tick::Timer& timer)
{
	// Timer duration in microseconds
	chrono::microseconds micro = chrono::duration_cast<chrono::microseconds>(timer.expires_from_now());

	// Convert to posix time duration
	boost::posix_time::time_duration dur = boost::posix_time::microseconds(micro.count());

	bool isNeg = dur.is_negative();
	if (isNeg) {
		dur = -dur;
	}

	stringstream ss;
	ss << (isNeg ? '-' : '\0') << dur.hours() << ':' << dur.minutes() << ':' << dur.seconds();

	os << setw(10) << ss.str()
		<< (timer.is_resumed() ? "" : "not ") << "resumed - "
		<< (timer.is_expired() ? "" : "not ") << "expired";

	return os;
}