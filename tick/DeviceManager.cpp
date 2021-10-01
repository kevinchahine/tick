#include "DeviceManager.h"

#include <fstream>

#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace std;

namespace tick
{
	void DeviceManager::write(const boost::filesystem::path& filename)
	{
		// 1.) --- Check to see if the file exists ---
		if (boost::filesystem::exists(filename)) {
			// 1-1.) --- If it exists, create a backup of it ---

		}
		else {
			// 1-2.) --- If it does not exists create it ---

		}

		ofstream fileout(filename.string());

		// 2.) --- Serialize all devices into one big property tree ---
		boost::property_tree::ptree tree;
		boost::property_tree::ptree timersTree = m_timers.serialize();
		boost::property_tree::ptree swTree = m_stopwatches.serialize();

		tree.put_child("Timers", move(timersTree));
		tree.put_child("StopWatches", move(swTree));

		// 3.) --- Convert the property tree into a JSON file ---
		// 4.) --- Write to file ---
		boost::property_tree::write_json(fileout, tree);

		fileout.close();
	}
}