#ifndef XStaticArray_h__
#define XStaticArray_h__

template<typename T, unsigned int N>
class CXStaticArray
{
    public:
        unsigned int GetSize() {
            return N;
        }
        T& operator[] ( unsigned int i ) {
            CHECK ( ISIN ( i, 0, N ) );
            return Elements[i];
        }
        T& Get ( unsigned int i ) {
            CHECK ( ISIN ( i, 0, N ) );
            return Elements[i];
        }
    private:
        T Elements[N];
};

#endif // XStaticArray_h__


