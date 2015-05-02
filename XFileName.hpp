#ifndef XFileName_h__
#define XFileName_h__
#include "uString.h"
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
    const char* GetRelativeFileName ();
    const char* GetFullFileName();
    void GetLastPath ( uString& lastPath );
    const char* GetAbsolutePath();
    const char* getOrignalName();
    //************************************
    // Brief:	  e.g:D:\\abc\\a.txt return abc;D:\\a.txt return D:
    // Method:    GetCurPath
    // Returns:   bool
    // Parameter: const char * filename
    // Parameter: uString & curPath
    //************************************
    bool GetCurPath ( uString& curPath );
    bool GetParentPath ( uString& parentPath );
public:
    static bool GetDirectory ( const uString& path, uString& dir );
    static void ConvertToStandSpliter ( uString& path );
    /** 去掉多余的斜杠 **/
    static void deleteRedundentSpliter ( uString& path );
    static uString GetAppFullName ();
    static bool GetExt ( const char* fileName, uString& ext );
    static bool MakeRelativeFileName ( const char* fileName, uString& path );
    static bool MakeFullFileName ( const char* fileName, uString& fullFileName );
    static bool GetAbsolutePath ( const char* fileName, uString& path );
    static bool GetPath ( const char* fileName, uString& path );
    static bool GetFileName ( const char* str, uString& fileName );
    static bool AmendAbsolutePath ( const char* str, uString& path );
    static bool IsRelative ( const char* pathOrFile );
protected:
    uString	mOrignalName;
    uString	mRelativePath;
    uString mRelativeFileName;
    uString mFullFileName;
    uString	mAbsoultePath;
    uString	mFileName;
    uString	mExt;
    uString	mDirectory;
};
inline const char* CXFileName::GetRelativePath ()
{
    return mRelativePath.c_str();
}

inline bool CXFileName::MakeRelativeFileName ( const char* fileName, uString& path )
{
    if ( dStrLen ( fileName ) == 0 )
    {
        path.clear();
        return false;
    }
    if ( IsRelative ( fileName ) )
    {
        path = fileName;
        return true;
    }
    uString appname = GetAppFullName();
    uString apppath;
    CXASSERT_RETURN_FALSE ( GetAbsolutePath ( appname, apppath ) );

    uString fullname ( fileName );
    CXDynaArray<uString>  eles0;
    CXDynaArray<uString>  eles1;

    apppath.split ( PathSpliter, eles0 );
    fullname.split ( PathSpliter, eles1 );

    u32 cnt = dMin ( eles0.size(), eles1.size() );
    u32 idx = 0;
    for ( ; idx < cnt ; ++idx )
    {
        uString str0 = eles0[idx];
        uString str1 = eles1[idx];
        //transform ( str0.begin(), str0.end(), str0.begin(), tolower );
        //transform ( str1.begin(), str1.end(), str1.begin(), tolower );
        if ( str0 != str1 )
            break;
    }
    int size0 = eles0.size();
    int size1 = eles1.size();
    CXASSERT ( size0 >= 2 );
    CXASSERT ( size1 >= 2 );
    //-------------------------------------------------------------------------
    // directroy not equal
    int left0 = size0 - idx ;
    int left1 = size1 - idx ;
    for ( int i = 0; i < left0 && left1 > left0; i++ )
    {
        path.append ( 1, Dot );
        path.append ( 1, Dot );
        path.append ( 1, PathSpliter );
    }
    int leftcnt = eles1.size();
    for ( u32 i = idx; ( int ) i < leftcnt; ++i )
    {
        path.append ( eles1[i] );
        if ( i != leftcnt - 1 )
            path.append ( 1, PathSpliter );
    }

    deleteRedundentSpliter ( path );
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
inline bool CXFileName::AmendAbsolutePath ( const char* str, uString& path )
{
    uString dir;
    CXASSERT_RETURN_FALSE ( GetDirectory ( str, dir ) );
    uString fullName = str;
    CXASSERT_RETURN_FALSE ( fullName.length() >= 2  );
    CXDynaArray<uString> stack;
    uString ele;
    for ( uString::size_type i = 0; i < fullName.length() - 2; ++i )
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
    for ( CXDynaArray<uString>::iterator walk = stack.begin(); walk != stack.end(); ++walk )
    {
        path.append ( *walk );
        path.append ( 1, PathSpliter );
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
inline void CXFileName::ConvertToStandSpliter ( uString& path )
{
    for ( uString::size_type i = 0; i < path.length(); ++i )
    {
        char ch = path[i];
        if ( ch == PathSpliterEx )
            ch = PathSpliter;
    }

    uString::size_type len = path.length();
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
inline uString CXFileName::GetAppFullName()
{
    char* modulename = 0;
    _get_pgmptr ( &modulename );
    uString rawname;
    AmendAbsolutePath ( modulename, rawname );
    return rawname;
}

inline bool CXFileName::GetPath ( const char* fileName, uString& path )
{
    uString name ( fileName );
    uString::size_type pos = name.find_last_of ( PathSpliter );
    if ( pos == uString::npos )
        return false;
    path = name.substr ( 0, pos );
    return true;
}


inline bool CXFileName::GetExt ( const char* fileName, uString& ext )
{
    uString name = fileName;
    ext.clear();
    uString::size_type pos = name.find_last_of ( Dot );
    uString::size_type posPathSpliter = name.find_last_of ( PathSpliter );
    if ( pos == uString::npos || posPathSpliter > pos )
        return false;
    ext = name.substr ( pos + 1 );
    return true;
}



inline bool CXFileName::GetFileName ( const char* str, uString& fileName )
{
    uString name = str;
    fileName.clear();
    uString::size_type pos = name.find_last_of ( PathSpliter );
    if ( pos == uString::npos )
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
    if ( IsRelative ( mOrignalName ) )
    {
        CXASSERT ( MakeFullFileName ( mOrignalName, mFullFileName ) );
    }
    else
    {
        mFullFileName = mOrignalName;
    }
    GetExt ( mFullFileName, mExt );
    GetFileName ( mFullFileName, mFileName );
    GetDirectory ( mFullFileName, mDirectory );
    GetAbsolutePath ( mFullFileName, mAbsoultePath );
    if ( MakeRelativeFileName ( mFullFileName, mRelativeFileName ) )
        GetPath ( mRelativeFileName, mRelativePath );
}

inline bool CXFileName::GetDirectory ( const uString& path, uString& dir )
{
    uString::size_type pos = path.find ( Directory );
    if ( pos == uString::npos )
        return false;
    dir = path.substr ( 0, 2 );
    return true;
}

inline const char* CXFileName::GetRelativeFileName()
{
    return mRelativeFileName.c_str();
}

inline bool CXFileName::IsRelative ( const char* pathOrFile )
{
    uString file ( pathOrFile );
    uString dirFlag;
    dirFlag += Directory;
    return file.find ( dirFlag.c_str() ) == uString::npos;
}

inline bool CXFileName::GetCurPath ( uString& curPath )
{
    uString::size_type pos = mAbsoultePath.find_last_of ( PathSpliter );
    if ( pos != uString::npos )
    {
        curPath = mAbsoultePath.substr ( pos + 1 );
        return true;
    }
    return false;
}

inline bool CXFileName::GetParentPath ( uString& parentPath )
{
    uString stmp = mOrignalName;
    uString::size_type pos = stmp.find_last_of ( PathSpliter );
    int i = 0;
    do
    {
        stmp = stmp.substr ( 0, pos );
        parentPath = stmp;
        i++;
    }
    while ( pos != uString::npos && i < 2 );
    return true;
}

inline bool CXFileName::GetAbsolutePath ( const char* fileName, uString& path )
{
    if ( !IsRelative ( fileName ) )
    {
        uString name = fileName;
        uString::size_type pos = name.find_last_of ( PathSpliter );
        if ( pos == uString::npos )
            return false;
        path = name.substr ( 0, pos );
        return true;
    }
    return false;
}

inline const char* CXFileName::GetAbsolutePath()
{
    return mAbsoultePath.c_str();
}

inline const char* CXFileName::getOrignalName()
{
    return mOrignalName.c_str();
}

inline void CXFileName::deleteRedundentSpliter ( uString& path )
{
    path.replace ( "\\\\", "\\" );
}

inline bool CXFileName::MakeFullFileName ( const char* fileName, uString& fullFileName )
{
    CXASSERT ( IsRelative ( fileName ) );
    CXASSERT ( fileName );
    char buffer[_MAX_FNAME];
    _fullpath ( buffer, fileName, _MAX_FNAME );
    fullFileName = buffer;
    return true;
}

inline const char* CXFileName::GetFullFileName()
{
    return mFullFileName;
}





#endif // XPath_h__
