#ifndef UCL_CFILE_H
#define UCL_CFILE_H
#include <string>

namespace UCL
{

class CFile
{
public:
	typedef enum 
	{
		modeNONE	= 0x00,
		modeREAD 	= 0x01,
		modeWRITE	= 0x02,
		modeRW		= modeREAD | modeWRITE,
		modeAPPEND	= 0x04,
		modeOVERWRITE	= 0x08,
		modeNO_OVERWRITE= 0x10
	} tFileModeFlags;

public:
	CFile();
	virtual ~CFile();
	bool Open(const std::string& filename, const int fileOpenMode );
	void Close();

	int Write( const char* buffer, const int bufferSize );
	int Read( char* buffer, const int bufferSize);

	void Seek ( int position );

private:
	int m_fileHandle;

	int m_fileAccessFlags;

};


}


#endif
