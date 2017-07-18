#ifndef XRapidxmlLoader_h__
#define XRapidxmlLoader_h__

#include "Rapidxml\rapidxml.hpp"
#include "XFileLoader.h"
#include "Rapidxml\rapidxml_help.hpp"
//--------------------------------------------------------------------------------------------------

class CXRapidxmlLoader {
  public:
    CXRapidxmlLoader(const char* name);
    ~CXRapidxmlLoader(void);

    bool loadFile();
    CXRapidxmlNode* getRootNode();
  protected:
    bool loadFile(const char* name);

    const char* mFileName;

    CXRapidxmlDocument mRapidxmlDoc;

    CXFileLoader mFileLoader;

    Char* mBuffer;
};
inline CXRapidxmlLoader::CXRapidxmlLoader(const char* name)
    : mFileName(name) {
}

inline CXRapidxmlLoader::~CXRapidxmlLoader(void) {
    mFileLoader.Close();

    dSafeDelete(mBuffer);
}

inline bool CXRapidxmlLoader::loadFile(const char* name) {
    CXASSERT_RETURN_FALSE(mFileLoader.OpenFile(name));

    mBuffer = new Char[mFileLoader.GetBufferSize() + 1];
    memset(mBuffer, 0, mFileLoader.GetBufferSize() + 1);
    mFileLoader.ReadToBuffer(mBuffer);
    mRapidxmlDoc.parse<rapidxml::parse_default>(mBuffer);
    mFileLoader.Close();
    return true;
}

inline CXRapidxmlNode* CXRapidxmlLoader::getRootNode() {
    return mRapidxmlDoc.first_node();
}

inline bool CXRapidxmlLoader::loadFile() {
    CXASSERT_RETURN_FALSE(mFileName);
    return loadFile(mFileName);
}

inline CXXMLHelper::CXXMLHelper(CXXMLNodeStack& stack, CXRapidxmlNode*& n, const char* nodeName)
    : mNodeStack(stack)
    , mNode(n) {
    if (mNode)
        mNodeStack.push(mNode);
    mNode = mNode->first_node(nodeName);
}

inline CXXMLHelper::~CXXMLHelper() {
    mNode = mNodeStack.top();
    mNodeStack.pop();
}


#define xml_load(file) CXRapidxmlLoader loader(file);\
	CXASSERT(loader.loadFile());\
	CXXMLNodeStack _nodeStack;\
	CXRapidxmlNode* _node=loader.getRootNode();\

#define xml_get_node(name) \
	for(CXXMLHelper _helper(_nodeStack, _node, name);_node!=nullptr;_node=_node->next_sibling(name))

#define xml_get_attr(attr,var) if(!_xml_get_attribute(_node,attr,var)) return false;

#endif // XRapidxmlLoader_h__