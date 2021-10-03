#include "TestTimerManager.h"

#include <sstream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace std;

namespace tick
{
	namespace test
	{
		void timerManagerInsert()
		{
			
		}

		void timerManagerPropertyTree()
		{
			tick::TimerManager tman;
			tick::Timer t;
			t.expires_from_now(chrono::seconds(34));

			tman.insert();
			tman.insert("timerA");
			tman.insert(t);
			tman.insert("timerB", Timer{});

			for (const auto& it : tman) {
				cout << it.first << ": " << it.second << endl;
			}

			boost::property_tree::ptree tree;

			tree = tman.serialize();

			boost::property_tree::write_json(cout, tree);
		}
	}
}