#include "base.h"
#include "XRapidxmlLoader.h"

CXRapidxmlLoader::CXRapidxmlLoader ( CChar* name )
    : mFileName ( name )
{
}

CXRapidxmlLoader::~CXRapidxmlLoader ( void )
{
    mFileLoader.Close();

    dSafeDelete ( mBuffer );
}

bool CXRapidxmlLoader::LoadFile ( CChar* name )
{
    CXASSERT_RETURN_FALSE ( mFileLoader.OpenFile ( name ) );

    mBuffer = new Char[mFileLoader.GetBufferSize() + 1];
    memset ( mBuffer, 0, mFileLoader.GetBufferSize() + 1 );
    mFileLoader.ReadToBuffer ( mBuffer );
    mRapidxmlDoc.parse<rapidxml::parse_default> ( mBuffer );
    mFileLoader.Close();
    return true;
}

CXRapidxmlNode* CXRapidxmlLoader::getRootNode()
{
    return mRapidxmlDoc.first_node();
}

bool CXRapidxmlLoader::loadFile()
{
    CXASSERT_RETURN_FALSE ( mFileName );
    return LoadFile ( mFileName );
}

CXXMLHelper::CXXMLHelper ( CXXMLNodeStack& stack, CXRapidxmlNode*& n, const char* nodeName )
    : mNodeStack ( stack )
    , mNode ( n )
{
    if ( mNode )
        mNodeStack.push ( mNode );
    mNode = mNode->first_node ( nodeName );
}

CXXMLHelper::~CXXMLHelper()
{
    mNode = mNodeStack.top();
    mNodeStack.pop();
}
