#pragma once
#include <map>
template<typename TK, typename TV>
class CXMap: public std::map<TK, TV>
{
    public:
        typedef std::map<TK, TV> Super;
        typedef typename Super::iterator iterator;

        bool Get( TK k, TV& v ) const
        {
            Super::const_iterator i = find( k );

            if ( i != end() )
            {
                v = i->second;
                return true;
            }

            return false;
        }
#include "XMap.inl"
};


