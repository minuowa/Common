#include "base.h"
#include "XRapidxmlLoader.h"

CXRapidxmlLoader::CXRapidxmlLoader( CChar* name )
{
    CXASSERT_RETURN( LoadFile( name ) );
}

CXRapidxmlLoader::~CXRapidxmlLoader( void )
{
    mFileLoader.Close();

    CXSafeDelete( mBuffer );
}

bool CXRapidxmlLoader::LoadFile( CChar* name )
{
	CXASSERT_RETURN_FALSE( mFileLoader.OpenFile( name ) );

	mBuffer = new Char[mFileLoader.GetBufferSize() + 1];
	memset( mBuffer, 0, mFileLoader.GetBufferSize() + 1 );
	mFileLoader.ReadToBuffer( mBuffer );
	mRapidxmlDoc.parse<rapidxml::parse_default>( mBuffer );

    return true;
}

CXRapidxmlNode* CXRapidxmlLoader::GetRootNode()
{
    return mRapidxmlDoc.first_node();
}
