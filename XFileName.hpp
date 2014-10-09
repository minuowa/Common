#ifndef XFileName_h__
#define XFileName_h__
#include "XString.h"
#include "XDynaArray.h"

class CXFileName
{
public:
    static const char PathSpliter = '\\';
    static const char PathSpliterEx = '/';
    static const char Directory = ':';
    static const char Dot = '.';

    CXFileName ( const char* fileName );
    const char* GetRelativePath ();
    const char* GetFileName ();
    void GetRelativeFileName ( String& name );
public:
    static bool GetDirectory ( const String& path, String& dir );
    static void ConvertToStandSpliter ( String& path );
    static String GetAppFullName ();
    static bool GetExt ( const char* fileName, String& ext );
    static bool GetRelativePath ( const char* fileName, String& path );
    static bool GetPath ( const char* fileName, String& path );
    static bool GetFileName ( const char* str, String& fileName );
    static bool AmendAbsolutePath ( const char* str, String& path );
	static bool IsRelative(const char* pathOrFile);
protected:
    String	mOrignalName;
    String	mRelativePath;
    String	mAbsoultePath;
    String	mFileName;
    String	mExt;
    String	mDirectory;
};
inline const char* CXFileName::GetRelativePath ()
{
    return mRelativePath.c_str();
}

inline bool CXFileName::GetRelativePath ( const char* fileName, String& path )
{
	if (IsRelative(fileName))
	{
		return GetPath(fileName,path);
	}
    String appname = GetAppFullName();
    String fullname ( fileName );
    CXDynaArray<String>  eles0;
    CXDynaArray<String>  eles1;
    appname.Splite ( PathSpliter, eles0 );
    fullname.Splite ( PathSpliter, eles1 );
    int cnt = dMin ( eles0.size(), eles1.size() );
    int idx = 0;
    for ( ; idx < cnt - 1; ++idx )
    {
        if ( eles0[idx] != eles1[idx] )
            break;
    }
    int size0 = eles0.size();
    int size1 = eles1.size();
    CXASSERT ( size0 >= 2 );
    CXASSERT ( size1 >= 2 );
    String commonpath;
    //-------------------------------------------------------------------------
    // directroy not equal
    if ( idx == 0 )
        return false;
    if ( idx >= size0 - 2 )
    {
        for ( int i = 0; i < size0 - idx; i++ )
        {
            commonpath.appendChar ( Dot );
            commonpath.appendChar ( Dot );
            commonpath.appendChar ( PathSpliter );
        }
    }
    for ( int i = 0; i < size1 - idx - 1; ++i )
        commonpath.append ( eles1[i] );
    return true;
}

//************************************
// Method:    AmendAbsolutePath,修正带有".."的绝对路径
// FullName:  CXFileName::AmendAbsolutePath
// Access:    public static
// Returns:   bool
// Qualifier:
// Parameter: const char * str
// Parameter: String & path
//************************************
inline bool CXFileName::AmendAbsolutePath ( const char* str, String& path )
{
    String dir;
    CXASSERT_RETURN_FALSE ( GetDirectory ( str, dir ) );
    String fullName = str;
    CXASSERT_RETURN_FALSE ( fullName.length() >= 2  );
    CXDynaArray<String> stack;
    String ele;
    for ( String::size_type i = 0; i < fullName.length() - 2; ++i )
    {
        char ch = fullName.at ( i );
        if ( ch == PathSpliter )
        {
            stack.push_back ( ele );
            ele.clear();
        }
        else if ( ch == Dot && fullName.at ( i + 1 ) == Dot )
        {
            stack.pop_back();
            i += 2; //".\"
        }
        else
        {
            ele.append ( 1, ch );
        }
    }
    ele.append ( 1, fullName[fullName.length() - 2] );
    ele.append ( 1, fullName[fullName.length() - 1] );
    stack.push_back ( ele );
    for ( CXDynaArray<String>::iterator walk = stack.begin(); walk != stack.end(); ++walk )
    {
        path.append ( *walk );
        path.appendChar ( PathSpliter );
    }
    path = path.substr ( 0, path.length() - 1 );
    return true;
}

//************************************
// Method:    ConvertToStandSpliter:'/'换成'\\'
// FullName:  CXFileName::ConvertToStandSpliter
// Access:    public static
// Returns:   void
// Qualifier:
// Parameter: String & path
//************************************
inline void CXFileName::ConvertToStandSpliter ( String& path )
{
    for ( String::size_type i = 0; i < path.length(); ++i )
    {
        char& ch = path[i];
        if ( ch == PathSpliterEx )
            ch = PathSpliter;
    }
}
inline String CXFileName::GetAppFullName()
{
    char* modulename = 0;
    _get_pgmptr ( &modulename );
    String rawname;
    AmendAbsolutePath ( modulename, rawname );
    return rawname;
}

inline bool CXFileName::GetPath ( const char* fileName, String& path )
{
    String name ( fileName );
    path.clear();
    String::size_type pos = name.find_last_of ( PathSpliter );
    if ( pos == String::npos )
        return false;
    path = name.substr ( 0, pos );
    return true;
}


inline bool CXFileName::GetExt ( const char* fileName, String& ext )
{
    String name = fileName;
    ext.clear();
    String::size_type pos = name.find_last_of ( Dot );
    if ( pos == String::npos )
        return false;
    ext = name.substr ( pos + 1 );
    return true;
}



inline bool CXFileName::GetFileName ( const char* str, String& fileName )
{
    String name = str;
    fileName.clear();
    String::size_type pos = name.find_last_of ( PathSpliter );
    if ( pos == String::npos )
        return false;
    fileName = name.substr ( pos + 1 );
    return true;
}

inline const char* CXFileName::GetFileName()
{
    return mFileName.c_str();
}



inline CXFileName::CXFileName ( const char* fileName )
    : mOrignalName ( fileName )
{
    ConvertToStandSpliter ( mOrignalName );
    GetExt ( mOrignalName, mExt );
    GetFileName ( mOrignalName, mFileName );
    GetDirectory ( mOrignalName, mDirectory );
    GetRelativePath ( mOrignalName, mRelativePath );
}

inline bool CXFileName::GetDirectory ( const String& path, String& dir )
{
    String::size_type pos = path.find ( Directory );
    if ( pos == String::npos )
        return false;
    dir = path.substr ( 0, pos + 1 );
    return true;
}

inline void CXFileName::GetRelativeFileName ( String& name )
{
    name += mRelativePath;
    name += mFileName;
}

inline bool CXFileName::IsRelative( const char* pathOrFile )
{
	String file(pathOrFile);
	String dirFlag;
	dirFlag+=Directory;
	return file.Find(dirFlag.c_str())==String::npos;
}



#endif // XPath_h__
