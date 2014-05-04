#pragma once

class CXFileLoader
{
    public:
        CXFileLoader( void );
        ~CXFileLoader( void );

        bool	OpenFile( CChar* name );
        XI32	GetBufferSize();
        void	Close();
        void	ReadToBuffer( Char* buffer );
    protected:
        FILE* mFile;
        XI32 mFileSize;
};
