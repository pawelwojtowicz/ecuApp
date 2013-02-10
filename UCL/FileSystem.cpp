#include "FileSystem.h"
#include <fnmatch.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>

namespace UCL
{

FileSystem::tFileNameList FileSystem::FindFiles( const std::string& path, const std::string& fileMask)
{
	tFileNameList foundFiles;
	DIR *dp = 0;
       	struct dirent *ep = 0;

	dp = opendir (path.c_str());
	if ( 0 != dp )
	{
		ep = readdir (dp);
		while ( 0 !=ep )
		{
			if (0 == fnmatch (fileMask.c_str(), ep->d_name, FNM_FILE_NAME))
			{
				foundFiles.push_back(ep->d_name);
			}
			ep = readdir (dp);
			
		}

		closedir(dp);
	}

	return foundFiles;
}


bool FileSystem::CreateDirectory( const std::string& dirpath )
{
	bool retVal(false);
	if ( !dirpath.empty() )
	{
		return (0 == mkdir(dirpath.c_str(), ( S_IRWXO | S_IRWXU | S_IRWXG ) ) ); 
	}
	return retVal;
}


bool FileSystem::DeleteFile( const std::string& filemask )
{
	bool retVal(false);
	if ( !filemask.empty() )
	{
		retVal = ( 0 == remove( filemask.c_str() ) );
	}
	return retVal;
}

bool FileSystem::CopyFile(const std::string& sourceFileMask, const std::string& destinationFileMas)
{
	bool retVal(false);
	return retVal;
}

bool FileSystem::MoveFile(const std::string& sourceFileMask, const std::string& destination)
{
	bool retVal(false);
	return retVal;
}


}
