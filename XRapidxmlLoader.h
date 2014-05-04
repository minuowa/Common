#pragma once
#include "Rapidxml\rapidxml.hpp"
#include "XFileLoader.h"
#include "Rapidxml\rapidxml_help.hpp"
//--------------------------------------------------------------------------------------------------

class CXRapidxmlLoader
{
public:
	CXRapidxmlLoader(CChar* name);
	~CXRapidxmlLoader(void);

	CXRapidxmlNode* GetRootNode();
protected:
	bool LoadFile(CChar* name);

	CXRapidxmlDocument mRapidxmlDoc;

	CXFileLoader mFileLoader;

	Char* mBuffer;
};
