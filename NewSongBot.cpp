/*
			*					*					*
				*				*				*
					*			*			*
						*				*
			*	*	*		    SongBuddy		*	*	*
						*				*
					*			*			*
				*				*				*
			*					*					*

	This buddy helps you make and maintain your music by:

	- using organized and consistent naming
	- autogenerating files/folders necessary for your songs
		- no time wasted; get right to making music
	-using templates to streamlines your workflow habits
		-decide what steps turn your ideas into final products
									
						author: michael jarvis
						last updated: 12-10-19
*/


//dependencies
#include <boost/filesystem.hpp>
#include <iostream>
#include <string>
std::string tempName;

//creates a file
bool createFile(std::string pathName, bool isInDirectory, std::string fileExt)
{
	//add file extension
	pathName += fileExt;


	//if file exists already
	if (boost::filesystem::exists(pathName))
	{
		//if file is in a folder, format output
		if (isInDirectory)
		{
			pathName = "/" + pathName;
		}

		//log failure
		std::cout << "ALREADY EXIST: " + pathName << std::endl;
	}
	else
	{
		if (boost::filesystem::ofstream(pathName))
		{
			boost::filesystem::rename(pathName, pathName);

			//if file is in a folder, format output
			if (isInDirectory)
			{
				pathName = "/" + pathName;
			}

			//log success
			std::cout << pathName << std::endl;
			return true;

		}
		else {
			//log failure
			std::cout << "FAILED TO ADD: /" + pathName << std::endl;
			return false;
		}

	}

	return false;
}

//creates a folder
bool createFolder(std::string pathName)
{
	//build path
	boost::filesystem::path dir((pathName).c_str());

	//if file exists already
	if (boost::filesystem::exists(pathName))
	{
		//log failure
		std::cout << "ALREADY EXIST: /" + pathName << std::endl;
	}
	else
	{
		//create directory
		if (boost::filesystem::create_directory(dir))
		{
			//log success
			std::cout << "/" + pathName << std::endl;
			return true;
		}
		else {
			//log failure
			std::cout << "FAILED TO ADD: /" + pathName << std::endl;
			return false;
		}
	}
	

	return false;
}

int main(int argc, char* argv[])
{
	for (int i = 0; i < argc-1; ++i)
	{
		if (argc == 1)
		{
			std::cout << "Not enough arguments" << std::endl;
			return 0;
		}
		//load input name from cmd line
		std::string songName = argv[1 + i];

		//beginning of execution log
		std::cout << "SONG "<< i + 1 << std::endl;

		//create root directory
		createFolder(songName);

		//create root files
		createFile(songName + "/" + songName + "_credits", true, ".txt");
		createFile(songName + "/" + songName + "_lyrics", true, ".txt");

		//create 1st level of directories
		createFolder(songName + "/instrumental");
		createFolder(songName + "/vocal");

		//create vocal files/folders
		createFile(songName + "/vocal/" + songName + "_vocal_recordings", true, ".flp");
		createFile(songName + "/vocal/" + songName + "_vocal_mix", true, ".flp");

		//create instrumental files/folders
		createFile(songName + "/instrumental/" + songName + "_instrumental_recording", true, ".flp");
		createFile(songName + "/instrumental/" + songName + "_instrumental_mix", true, ".flp");
	}
	
	
	return 0;
}
