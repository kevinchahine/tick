#include "TestPropertyTree.h"

#include <sstream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace std;

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

			boost::property_tree::ptree tree;
			boost::property_tree::ptree tree1 = t1.serialize();
			boost::property_tree::ptree tree2 = t2.serialize();
			boost::property_tree::ptree tree3 = t3.serialize();

			tree.put_child("Timer1", std::move(tree1));
			tree.put_child("Timer2", std::move(tree2));
			tree.put_child("Timer3", std::move(tree3));

			stringstream ss;
			boost::property_tree::write_json(ss, tree);

			cout << ss.str();

			boost::property_tree::ptree tree4;
			boost::property_tree::read_json(ss, tree4);

			t1.parse(tree4.get_child("Timer1"));
			t2.parse(tree4.get_child("Timer2"));
			t3.parse(tree4.get_child("Timer3"));

		}
	}
}