#include "base.h"
#include "XRapidxmlWriter.h"
//-------------------------------------------------------------------------
#include <fstream>
#include "Rapidxml\rapidxml.hpp"
#include "Rapidxml\rapidxml_print.hpp"
bool CXRapidxmlWriter::AppendChild( CXRapidxmlNode* node )
{
	CXASSERT_RETURN_FALSE(node);
	if (!mRootNode)
	{
		mRootNode=node;
	}
	else
	{
		mRootNode->append_node(node);
	}
	return true;
}

bool CXRapidxmlWriter::Write( CChar* name )
{
	std::ofstream of(name);
	CXASSERT_RETURN_FALSE(!of.bad());
	CXASSERT_RETURN_FALSE(mRootNode);
	of<<(*mRootNode);
	of.close();
	return true;
}

CXRapidxmlWriter::~CXRapidxmlWriter( void )
{

}

CXRapidxmlWriter::CXRapidxmlWriter()
	:mRootNode(0)
{

}