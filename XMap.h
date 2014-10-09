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
		bool Insert( TK k, TV v )
		{
			std::pair<Super::iterator, bool> res = this->insert( std::make_pair( k, v ) );
			return res.second;
		}
		void Destroy()
		{
			iterator i( this->begin() ), iEnd( this->end() );

			for ( ; i != iEnd; ++i )
			{
				dSafeDelete( i->second );
			}

			clear();
		}
#include "XMap.inl"
};


