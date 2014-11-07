#include "base.h"
#include "XFileLoader.h"
#include <io.h>

CXFileLoader::CXFileLoader ( void )
	: mFile ( 0 )
{
	Close();
}

CXFileLoader::~CXFileLoader ( void )
{
}

bool CXFileLoader::OpenFile ( CChar* name )
{
	CXASSERT_RETURN_FALSE ( name );

	CXASSERT_RETURN_FALSE ( !fopen_s ( &mFile, name, "a+" ) );
	fseek ( mFile, 0, SEEK_END );
	mFileSize = ftell ( mFile );
	fseek ( mFile, 0, SEEK_SET );
	return true;
}



XI32 CXFileLoader::GetBufferSize()
{
	return mFileSize;
}

void CXFileLoader::Close()
{
	if ( mFile )
	{
		fclose ( mFile );
		mFile = nullptr;
	}
}

void CXFileLoader::ReadToBuffer ( Char* buffer )
{
	if ( mFile && buffer )
	{
		fread ( buffer, 1, mFileSize, mFile );
	}
}
