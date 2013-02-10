#ifndef UCL_FILESYSTEM_H
#define UCL_FILESYSTEM_H

#include <list>
#include <string>

namespace UCL
{

class FileSystem
{
public:
	typedef std::list<std::string> tFileNameList;
	typedef tFileNameList::iterator tFileNameIterator;
	typedef tFileNameList::const_iterator tFileNameConstIterator;


	static tFileNameList FindFiles( const std::string& path, const std::string& fileMask);

	static bool CreateDirectory( const std::string& dirpath );

	static bool DeleteFile( const std::string& filemask );

	static bool CopyFile(const std::string& sourceFileMask, const std::string& destinationFileMas);

	static bool MoveFile(const std::string& sourceFileMask, const std::string& destination);
	
};
}


#endif
