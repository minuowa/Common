#include "base.h"
#include "XBase.h"
#include <sys\stat.h>


BASE_API bool dIsPath ( const char* str )
{
    struct stat info;
    stat ( str, &info );
    return ( ( ( info.st_mode ) & S_IFMT ) == S_IFDIR );
}
