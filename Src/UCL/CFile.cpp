#include "CFile.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

namespace UCL
{

CFile::CFile()
: m_fileHandle(-1)
, m_fileAccessFlags(modeNONE)
{
}

CFile::~CFile()
{
	Close();
}

bool CFile::Open(const std::string& filename, const int fileOpenMode )
{
	bool status(false);
	int openFlags(0);

	if ( 0 != (modeREAD & fileOpenMode) && 0 != ( modeWRITE & fileOpenMode ) )
	{
		openFlags = O_RDWR;
	}
	else if ( 0 != ( modeREAD & fileOpenMode ) )
	{
		openFlags = O_RDONLY;
	}
	else if ( 0 != ( modeWRITE & fileOpenMode ) )
	{
		openFlags = O_WRONLY;
	}

	if ( 0 != ( modeWRITE & fileOpenMode ) )
	{
		openFlags |= O_CREAT;

		if ( 0 != ( modeNO_OVERWRITE & fileOpenMode ) )
		{
			openFlags |= O_EXCL;
		} 
		else if ( 0 != ( modeAPPEND & fileOpenMode ) )
		{
			openFlags |= O_APPEND;
		}

	}

	m_fileHandle = open( filename.c_str(), openFlags , ( S_IRWXU | S_IRWXG | S_IRWXO) );

	if ( -1 != m_fileHandle )
	{
		status = true;
		m_fileAccessFlags = fileOpenMode;
	}

	
	return status;
}

void CFile::Close()
{
	if ( -1 == m_fileHandle )
	{
		close ( m_fileHandle );
		m_fileAccessFlags = modeNONE;
	}
}

int CFile::Write( const char* buffer, const int bufferSize )
{
	int written(0);
	if ( ( -1 != m_fileHandle ) && ( 0 != ( m_fileAccessFlags & modeWRITE ) ) )
	{
		written = write ( m_fileHandle , buffer, bufferSize );
	}
	return written;
}

int CFile::Read( char* buffer, const int bufferSize)
{
	int bytesRead(0);
	if ( ( -1 != m_fileHandle ) && ( 0 != ( m_fileAccessFlags & modeREAD ) ) )
	{
		bytesRead = read ( m_fileHandle, buffer, bufferSize );
	}
	return bytesRead;
}

void CFile::Seek ( int position )
{
	if ( -1 != m_fileHandle )
	{
		lseek( m_fileHandle, SEEK_SET , position);
	}
}


}
