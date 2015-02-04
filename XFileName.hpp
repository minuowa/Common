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
    void GetRelativeFileName ( GString& name );
    void GetLastPath ( GString& lastPath );
    const char* GetAbsolutePath();
    const char* GetOrignalName();
    //************************************
    // Brief:	  e.g:D:\\abc\\a.txt return abc;D:\\a.txt return D:
    // Method:    GetCurPath
    // Returns:   bool
    // Parameter: const char * filename
    // Parameter: GString & curPath
    //************************************
    bool GetCurPath ( GString& curPath );
    bool GetParentPath ( GString& parentPath );
public:
    static bool GetDirectory ( const GString& path, GString& dir );
    static void ConvertToStandSpliter ( GString& path );
    static GString GetAppFullName ();
    static bool GetExt ( const char* fileName, GString& ext );
    static bool GetRelativePath ( const char* fileName, GString& path );
    static bool GetAbsolutePath ( const char* fileName, GString& path );
    static bool GetPath ( const char* fileName, GString& path );
    static bool GetFileName ( const char* str, GString& fileName );
    static bool AmendAbsolutePath ( const char* str, GString& path );
    static bool IsRelative ( const char* pathOrFile );
protected:
    GString	mOrignalName;
    GString	mRelativePath;
    GString	mAbsoultePath;
    GString	mFileName;
    GString	mExt;
    GString	mDirectory;
};
inline const char* CXFileName::GetRelativePath ()
{
    return mRelativePath.c_str();
}

inline bool CXFileName::GetRelativePath ( const char* fileName, GString& path )
{
    if ( IsRelative ( fileName ) )
    {
        return GetPath ( fileName, path );
    }
    GString appname = GetAppFullName();
    GString fullname ( fileName );
    CXDynaArray<GString>  eles0;
    CXDynaArray<GString>  eles1;
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
    GString commonpath;
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
inline bool CXFileName::AmendAbsolutePath ( const char* str, GString& path )
{
    GString dir;
    CXASSERT_RETURN_FALSE ( GetDirectory ( str, dir ) );
    GString fullName = str;
    CXASSERT_RETURN_FALSE ( fullName.length() >= 2  );
    CXDynaArray<GString> stack;
    GString ele;
    for ( GString::size_type i = 0; i < fullName.length() - 2; ++i )
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
    for ( CXDynaArray<GString>::iterator walk = stack.begin(); walk != stack.end(); ++walk )
    {
        path.append ( *walk );
        path.appendChar ( PathSpliter );
    }
    path = path.substr ( 0, path.length() - 1 );
    return true;
}

//************************************
// Method:    ConvertToStandSpliter:'/'换成'\\',去掉最后的斜杠
// FullName:  CXFileName::ConvertToStandSpliter
// Access:    public static
// Returns:   void
// Qualifier:
// Parameter: String & path
//************************************
inline void CXFileName::ConvertToStandSpliter ( GString& path )
{
    for ( GString::size_type i = 0; i < path.length(); ++i )
    {
        char& ch = path[i];
        if ( ch == PathSpliterEx )
            ch = PathSpliter;
    }

    GString::size_type len = path.length();
    if ( len > 0 )
    {
        int i = len;
        while ( ( --i ) > 0 )
        {
            const char& ch = path.at ( i );
            if ( ch != PathSpliter )
                break;
        }
        path = path.substr ( 0, i + 1 );
    }
}
inline GString CXFileName::GetAppFullName()
{
    char* modulename = 0;
    _get_pgmptr ( &modulename );
    GString rawname;
    AmendAbsolutePath ( modulename, rawname );
    return rawname;
}

inline bool CXFileName::GetPath ( const char* fileName, GString& path )
{
    GString name ( fileName );
    path.clear();
    GString::size_type pos = name.find_last_of ( PathSpliter );
    if ( pos == GString::npos )
        return false;
    path = name.substr ( 0, pos );
    return true;
}


inline bool CXFileName::GetExt ( const char* fileName, GString& ext )
{
    GString name = fileName;
    ext.clear();
    GString::size_type pos = name.find_last_of ( Dot );
    GString::size_type posPathSpliter = name.find_last_of ( PathSpliter );
    if ( pos == GString::npos || posPathSpliter > pos )
        return false;
    ext = name.substr ( pos + 1 );
    return true;
}



inline bool CXFileName::GetFileName ( const char* str, GString& fileName )
{
    GString name = str;
    fileName.clear();
    GString::size_type pos = name.find_last_of ( PathSpliter );
    if ( pos == GString::npos )
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
    GetAbsolutePath ( mOrignalName, mAbsoultePath );
    GetRelativePath ( mOrignalName, mRelativePath );
}

inline bool CXFileName::GetDirectory ( const GString& path, GString& dir )
{
    GString::size_type pos = path.find ( Directory );
    if ( pos == GString::npos )
        return false;
    dir = path.substr ( 0, pos + 1 );
    return true;
}

inline void CXFileName::GetRelativeFileName ( GString& name )
{
    name += mRelativePath;
    name += mFileName;
}

inline bool CXFileName::IsRelative ( const char* pathOrFile )
{
    GString file ( pathOrFile );
    GString dirFlag;
    dirFlag += Directory;
    return file.Find ( dirFlag.c_str() ) == GString::npos;
}

inline bool CXFileName::GetCurPath ( GString& curPath )
{
    GString::size_type pos = mAbsoultePath.find_last_of ( PathSpliter );
    if ( pos != GString::npos )
    {
        curPath = mAbsoultePath.substr ( pos + 1 );
        return true;
    }
    return false;
}

inline bool CXFileName::GetParentPath ( GString& parentPath )
{
    GString stmp = mAbsoultePath;
    GString::size_type pos = stmp.find_last_of ( PathSpliter );
    int i = 0;
    do
    {
        stmp = stmp.substr ( 0, pos );
        parentPath = stmp;
        i++;
    }
    while ( pos != GString::npos && i < 2 );
    return true;
}

inline bool CXFileName::GetAbsolutePath ( const char* fileName, GString& path )
{
    GString name = fileName;
    GString::size_type pos = name.find_last_of ( PathSpliter );
    if ( pos == GString::npos )
        return false;
    path = name.substr ( 0, pos );
    return true;
}

inline const char* CXFileName::GetAbsolutePath()
{
    return mAbsoultePath.c_str();
}

inline const char* CXFileName::GetOrignalName()
{
    return mOrignalName.c_str();
}





#endif // XPath_h__
