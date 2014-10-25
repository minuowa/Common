#ifndef rapidxml_help_h__
#define rapidxml_help_h__
#include "Rapidxml\rapidxml.hpp"
#include "XStack.h"

typedef rapidxml::xml_document<Char> CXRapidxmlDocument;
typedef rapidxml::xml_node<Char> CXRapidxmlNode;
typedef rapidxml::xml_attribute<Char> CXRapidxmlAttr;

typedef CXStack<CXRapidxmlNode*> CXXMLNodeStack;

class CXXMLHelper
{
public:
	CXXMLHelper ( CXXMLNodeStack& stack, CXRapidxmlNode*& n,const char* nodeName );
    ~CXXMLHelper();
private:
    CXRapidxmlNode*& mNode;
    CXXMLNodeStack& mNodeStack;
};

template<typename T>
void _xml_get_attribute ( CXRapidxmlNode* node, const char* attr, T& var )
{
    CXRapidxmlAttr* pAttri = node->first_attribute ( attr );
    CXASSERT ( pAttri );
	const char* svar=pAttri->value();
	CXStringHelper::setValue(svar,&var);
}

//void xml_get_attribute ( CXRapidxmlNode* node, const char* attr, int& var );
//void xml_get_attribute ( CXRapidxmlNode* node, const char* attr, float& var );
//void xml_get_attribute ( CXRapidxmlNode* node, const char* attr, GString& var );
//void xml_get_attribute ( CXRapidxmlNode* node, const char* attr, GString& var );
//void xml_get_attribute ( CXRapidxmlNode* node, const char* attr, bool& var );

#endif // rapidxml_help_h__
