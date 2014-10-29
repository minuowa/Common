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
		void destroyPoint(T* n)
		{
			iterator i=std::find( this->begin(), this->end(), rhs );
			if (i!=this->end())
			{
				delete i;
				this->erase(i);
			}
		}
        void Destroy()
        {
			size_t cnt=this->size();
			for (size_t i=0;i<cnt;++i)
			{
				T& ptr=(*this)[i];
				delete ptr;
				ptr=0;
			}
            this->clear();
        }
};

#endif // XDynaArray_h__

