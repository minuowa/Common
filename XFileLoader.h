#pragma once

#include <io.h>
class CXFileLoader
{
public:
	CXFileLoader( void );
	~CXFileLoader( void );

	bool	OpenFile( const char* name );
	u32	GetBufferSize();
	void	Close();
	void	ReadToBuffer( Char* buffer );
protected:
	FILE* mFile;
	u32 mFileSize;
};
inline CXFileLoader::CXFileLoader ( void )
	: mFile ( 0 )
{
	Close();
}

inline CXFileLoader::~CXFileLoader ( void )
{
}

inline bool CXFileLoader::OpenFile ( const char* name )
{
	CXASSERT_RETURN_FALSE ( name );

	CXASSERT_RETURN_FALSE ( !fopen_s ( &mFile, name, "a+" ) );
	fseek ( mFile, 0, SEEK_END );
	mFileSize = ftell ( mFile );
	fseek ( mFile, 0, SEEK_SET );
	return true;
}



inline u32 CXFileLoader::GetBufferSize()
{
	return mFileSize;
}

inline void CXFileLoader::Close()
{
	if ( mFile )
	{
		fclose ( mFile );
		mFile = nullptr;
	}
}

inline void CXFileLoader::ReadToBuffer ( Char* buffer )
{
	if ( mFile && buffer )
	{
		fread ( buffer, 1, mFileSize, mFile );
	}
}