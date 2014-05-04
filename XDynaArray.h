#ifndef XDynaArray_h__
#define XDynaArray_h__
#include <vector>
//--------------------------------------------------------------------------------------------------
template<typename T>
class CXDynaArray : public std::vector<T>
{
    public:
        bool Find( const T& rhs )
        {
            return end() !=::find( begin(), end(), rhs );
        }
        void Destroy()
        {
            iterator i( begin() ), iEnd( end() );

            for ( ; i != iEnd; ++i )
            {
                CXSafeDelete( *i );
            }

            clear();
        }
};

#endif // XDynaArray_h__

