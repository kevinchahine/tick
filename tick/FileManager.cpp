#include "FileManager.h"

#include <boost/filesystem/operations.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <fstream>

namespace fs = boost::filesystem;
namespace pt = boost::property_tree;
using namespace std;

namespace tick
{
	void FileManager::read(DeviceManager& devMan)
	{
		pt::ptree tree;
		
		// TODO: What if the file doesn't exist?

		ifstream in(this->tickFilePath.string());
		pt::read_json(in, tree);
		in.close();

		pt::write_json(cout, tree);
		
		devMan.parse(tree);
	}
	
	void FileManager::write(const DeviceManager& devMan)
	{
		pt::ptree tree = devMan.serialize();

		ofstream out(this->tickFilePath.string());
		pt::write_json(out, tree);
		out.close();
	}
	
	void FileManager::setTickDir(const fs::path& tickDir)
	{
	}
	
	fs::path FileManager::getTickDir() const
	{
		return fs::path();
	}
	
	void FileManager::setTickFile(const fs::path& tickFilePath)
	{
		//if (tickFilePath.is_absolute()) {
		//	this->tickFilePath.remove_filename();
		//	this->tickFilePath /= tickFilePath;
		//}
		//else if (tickFilePath.is_relative()) {
		//}
		//else if (tickFilePath.is_absolute()) {
		//}
		//else {
		//	cout << "Error: " << __FUNCTION__ << endl;
		//}
	}
	
	fs::path FileManager::getTickFile() const
	{
		return fs::path();
	}
	
	void FileManager::setToDefaultTickFile()
	{
		this->tickFilePath = getHomeDir() / ".tick" / "default.tick";

		// Does this file exist (as a regular file)?
		if (fs::exists(this->tickFilePath)) {
			// Yes it exists. Make sure its a regular file.
			if (fs::is_regular_file(this->tickFilePath)) {
				// Its a regular file. All good. 
			}
			else {
				// Nope its something else.
				// TODO: Add support for symbolic links.
				cout << "Error: The file " << this->tickFilePath
					<< " should be a regular file." << endl;
			}
		}
		else {
			// Does directory exist?
			if (fs::exists(this->tickFilePath.parent_path()) == false) {
				fs::create_directory(this->tickFilePath.parent_path());
			}

			// No. The file does not exist.
			// Create it as an empty json file.
			ofstream out(this->tickFilePath.string());
			out << "{" << endl
				<< endl
				<< "}" << endl;
			out.close();
		}
	}

	fs::path FileManager::getHomeDir()
	{
		fs::path homeDir;

		// 1.) --- See if HOME environment variable exists --- 
		char* str = getenv("HOME");

		// Does it exist?
		if (str == nullptr) {
			// No it does not. We can prompt user to create it.
			cout << "Error: environment variable HOME does not exist. "
				<< "Please create and set to your home directory. "
				<< endl;

			//TODO: We should have a fallback here
			// Maybe we can ask the user to type in their home dir and 
			// then set the environment variable that way

			// For now set it to "C:\Users\kchah\"
			homeDir = R"dil(C:\Users\kchah\)dil";
		}
		else {
			// Yes HOME does exist.
			homeDir = str;
		}

		return homeDir;
	}
}