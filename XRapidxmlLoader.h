#ifndef XRapidxmlLoader_h__
#define XRapidxmlLoader_h__

#include "Rapidxml\rapidxml.hpp"
#include "XFileLoader.h"
#include "Rapidxml\rapidxml_help.hpp"
//--------------------------------------------------------------------------------------------------

class CXRapidxmlLoader
{
public:
	CXRapidxmlLoader ( const char* name );
	~CXRapidxmlLoader ( void );

	bool loadFile();
	CXRapidxmlNode* getRootNode();
protected:
	bool LoadFile ( const char* name );

	const char* mFileName;

	CXRapidxmlDocument mRapidxmlDoc;

	CXFileLoader mFileLoader;

	Char* mBuffer;
};


#define xml_load(file) CXRapidxmlLoader loader(file);\
	CXASSERT(loader.loadFile());\
	CXXMLNodeStack _nodeStack;\
	CXRapidxmlNode* _node=loader.getRootNode();\

#define xml_get_node(name) \
	for(CXXMLHelper _helper(_nodeStack, _node, name);_node!=nullptr;_node=_node->next_sibling(name))

#define xml_get_attr(attr,var) _xml_get_attribute(_node,attr,var)

#endif // XRapidxmlLoader_h__