#include "StopWatchManager.h"

#include <boost/property_tree/ptree.hpp>

#include <iomanip>

namespace pt = boost::property_tree;

using namespace std;

namespace tick
{

}

std::ostream& operator<<(std::ostream& os, const tick::StopWatchManager& manager)
{
	auto flags = os.flags();

	os << "Stop Watches:\n";

	os << left;

	for (const auto& pair : manager) {
		const string& name = pair.first;
		const tick::StopWatch& sw = static_cast<const tick::StopWatch&>(*pair.second);
		
		os << setw(4) << '\0' << setw(10) << name << setw(10) << sw << endl;
	}

	os.flags(flags);

	return os;
}