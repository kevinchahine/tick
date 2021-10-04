#pragma once

#include "DeviceManager.h"

#include <boost/filesystem/path.hpp>

namespace tick
{
	// Reads and Writes device data to and from .tick files. 
	// .tick files can be stored in a set directory that tick will always read from
	// This directory defaults to the users home directory: ~/.tick/
	// The .tick/ directory can hold multiple .tick files. The default will be called default.tick
	// If multiple tick sessions are needed, then the path to the tick file can be specified 
	// in the command line arguments. Otherwise, ~/.tick/default.tick will be used.
	// The tick file can also be named anything like session1.tick, session2.tick
	// But if a file is not specified then tick will default to the file ~/.tick/default.tick
	// A tick session can only operate on a single tick file at a time. 
	class FileManager
	{
	public:
		FileManager() { setToDefaultTickFile(); }
		FileManager(const FileManager&) = default;
		FileManager(FileManager&&) noexcept = default;
		virtual ~FileManager() noexcept = default;
		FileManager& operator=(const FileManager&) = default;
		FileManager& operator=(FileManager&&) noexcept = default;

		void read(DeviceManager& devMan);
		void write(const DeviceManager& devMan);

		void setTickDir(const boost::filesystem::path& tickDir);
		boost::filesystem::path getTickDir() const;

		// If tickFilePath is:
		//	- only a filename. Then it will be appended to the existing directory.
		//	- an absolute path. Then it will be set as is.
		//	- a relative path. Then it will be appended to current working dir.
		void setTickFile(const boost::filesystem::path& tickFilePath);
		boost::filesystem::path getTickFile() const;

		void setToDefaultTickFile();

	private:
		boost::filesystem::path getHomeDir();

	private:
		// Stores the path to the tick file that is being used in this tick session.
		// If no path is specified and this object is being used, it will default
		// to the path ~/.tick in the users home dir
		boost::filesystem::path tickFilePath;
	};
}