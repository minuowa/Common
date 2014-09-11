#ifndef XDynaArray_h__
#define XDynaArray_h__
#include <vector>
#include <algorithm>
//--------------------------------------------------------------------------------------------------
template<typename T>
class CXDynaArray : public std::vector<T>
{
    public:
        bool Find( const T& rhs )
        {
            return this->end() !=std::find( this->begin(), this->end(), rhs );
        }
        void Destroy()
        {
            iterator i( this->begin() ), iEnd( this->end() );

            for ( ; i != iEnd; ++i )
            {
                CXSafeDelete( *i );
            }

            clear();
        }
};

#endif // XDynaArray_h__

