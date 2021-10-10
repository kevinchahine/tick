#include "TestPropertyTree.h"
#include "DeviceManager.h"
#include "FileManager.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <sstream>

using namespace std;

namespace pt = boost::property_tree;

namespace tick
{
	namespace test
	{
		void timerPropertyTree()
		{
			tick::Timer t1;
			tick::Timer t2;
			tick::Timer t3;

			t2.start();
			t2.expires_from_now(chrono::seconds(100));

			t3.expires_from_now(chrono::seconds(20));
			t3.start();
			t3.stop();

			pt::ptree tree;
			pt::ptree tree1 = t1.serialize();
			pt::ptree tree2 = t2.serialize();
			pt::ptree tree3 = t3.serialize();

			tree.put_child("Timer1", std::move(tree1));
			tree.put_child("Timer2", std::move(tree2));
			tree.put_child("Timer3", std::move(tree3));

			stringstream ss;
			pt::write_json(ss, tree);

			cout << ss.str();

			pt::ptree tree4;
			pt::read_json(ss, tree4);

			t1.parse(tree4.get_child("Timer1"));
			t2.parse(tree4.get_child("Timer2"));
			t3.parse(tree4.get_child("Timer3"));
		}

		void deviceManagerPT()
		{
			DeviceManager devMan;

			StopWatchManager & swMan = devMan.stopwatches();
			TimerManager& tmMan = devMan.timers();

			swMan.insert("swA");
			swMan.insert("swB", StopWatch{});

			tmMan.insert(Timer{});
			tmMan.insert("tmA");
			tmMan.insert("tmB");
			tmMan.insert("tmC");
			
			FileManager fileMan;
			fileMan.write(devMan);
			fileMan.read(devMan);
		}
	}
}