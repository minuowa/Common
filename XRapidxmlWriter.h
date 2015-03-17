#ifndef XRapidxmlWriter_h__
#define XRapidxmlWriter_h__

#include "Rapidxml\rapidxml_help.hpp"

class CXRapidxmlWriter
{
public:
	CXRapidxmlWriter();

	~CXRapidxmlWriter(void);

	bool Write(const char* name);

	bool AppendChild(CXRapidxmlNode* node);

protected:
	CXRapidxmlNode* mRootNode;
public:
	inline CXRapidxmlNode* GetRootNode() const
	{
		return mRootNode;
	}

};

#include <fstream>
#include "Rapidxml\rapidxml.hpp"
#include "Rapidxml\rapidxml_print.hpp"
inline bool CXRapidxmlWriter::AppendChild ( CXRapidxmlNode* node )
{
	CXASSERT_RETURN_FALSE ( node );
	if ( !mRootNode )
	{
		mRootNode = node;
	}
	else
	{
		mRootNode->append_node ( node );
	}
	return true;
}

inline bool CXRapidxmlWriter::Write ( const char* name )
{
	std::ofstream of ( name );
	CXASSERT_RETURN_FALSE ( !of.bad() );
	CXASSERT_RETURN_FALSE ( mRootNode );
	of << ( *mRootNode );
	of.close();
	return true;
}

inline CXRapidxmlWriter::~CXRapidxmlWriter ( void )
{

}

inline CXRapidxmlWriter::CXRapidxmlWriter()
	: mRootNode ( 0 )
{

}

#endif // XRapidxmlWriter_h__
