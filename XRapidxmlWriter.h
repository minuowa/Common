#ifndef XRapidxmlWriter_h__
#define XRapidxmlWriter_h__

#include "Rapidxml\rapidxml_help.hpp"

class CXRapidxmlWriter
{
public:
	CXRapidxmlWriter();

	~CXRapidxmlWriter(void);

	bool Write(CChar* name);

	bool AppendChild(CXRapidxmlNode* node);

protected:
	CXRapidxmlNode* mRootNode;
public:
	inline CXRapidxmlNode* GetRootNode() const
	{
		return mRootNode;
	}

};



#endif // XRapidxmlWriter_h__
