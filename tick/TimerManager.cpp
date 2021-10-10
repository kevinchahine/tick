#include "TimerManager.h"

#include <iomanip>

#include <boost/property_tree/ptree.hpp>

using namespace std;
namespace pt = boost::property_tree;

namespace tick
{
	
}

std::ostream& operator<<(std::ostream& os, const tick::TimerManager& manager)
{
	auto flags = os.flags();

	os << "Timers:\n";

	os << left;

	for (const auto& pair : manager) {
		const string& name = pair.first;
		const tick::Timer& timer = static_cast<const tick::Timer&>(*pair.second);

		os << setw(4) << '\0' << setw(10) << name << setw(10) << timer << endl;
	}

	os.flags(flags);

	return os;
}