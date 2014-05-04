#ifndef XPath_h__
#define XPath_h__
#include "XString.h"

class CXPath
{
public:
	static const char PathSpliter='\\';
	static const char Dot='.';

	CXPath(const char* fileName);

	bool GetPath(CharString& path) const;
	bool GetExt(CharString& ext) const;
	bool GetFileName(CharString& fileName) const;
protected:
	CharString	mFileName;
};
#endif // XPath_h__
