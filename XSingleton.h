#ifndef CXSingleton_h__
#define CXSingleton_h__

template<typename T>
class CXSingleton
{
private:
    CXSingleton()
    {
    }
    CXSingleton (const CXSingleton& );
    CXSingleton& operator=(const CXSingleton&);
public:
    virtual ~CXSingleton()
    {
    }
    static T* GetSingletonPtr()
    {
        static T* instance=0;
        if ( !instance )
        {
            static T t;
            instance =&t;
        }
        return instance;
    }
    static  T& GetSingleton()
    {
        return *GetSingletonPtr();
    }
};
#endif // CXSingleton_h__
