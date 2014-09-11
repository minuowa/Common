#pragma once
#include "XString.h"

class CXBuffer
{
    public:
        struct Iterator
        {
            int Pos;
            char* src;
            Iterator& operator++()
            {
                char* tmp = &src[Pos];

                if ( IS_WIDE_CHAR( *tmp ) )
                {
                    Pos += 2;
                }
                else
                {
                    Pos++;
                }

                return *this;
            }
        };
        CXBuffer( void );
        ~CXBuffer( void );
        bool	Create( XI32 size );
        XI32	GetBufferSize();
        Char*	GetBufferPoint();
        void	CopyMem( void* p );
        void	CopyStr( CChar* p );
        void	Clear();
        void	Destroy();
        char&	operator[]( XI32 idx );

        Iterator  Begin();

        String GetChar( int start, int wordNum );
    protected:
        char* mBuffer;
        XI32 mSize;
};
