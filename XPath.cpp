#include "base.h"
#include "XPath.h"



bool CXPath::GetPath( CharString& path ) const
{
	path.clear();
	CharString::size_type pos=mFileName.find_last_of(PathSpliter);
	if (pos==CharString::npos)
		return false;
	path=mFileName.substr(0,pos);
	return true;
}

bool CXPath::GetExt( CharString& ext ) const
{
	ext.clear();
	CharString::size_type pos=mFileName.find_last_of(Dot);
	if (pos==CharString::npos)
		return false;
	ext=mFileName.substr(pos);
	return true;
}

bool CXPath::GetFileName( CharString& fileName ) const
{
	fileName.clear();
	CharString::size_type pos=mFileName.find_last_of(PathSpliter);
	if (pos==CharString::npos)
		return false;
	fileName=mFileName.substr(pos);
	return true;
}

CXPath::CXPath( const char* fileName )
	:mFileName(fileName)
{

}
