#ifndef CXSingleton_h__
#define CXSingleton_h__

//template<typename T>
//class CXSingleton
//{
//public:
//	typedef CXSingleton<T> MyType;
//private:
//	CXSingleton()
//	{
//	}
//	CXSingleton ( const CXSingleton& );
//	CXSingleton& operator= ( const CXSingleton& );
//public:
//	virtual ~CXSingleton()
//	{
//	}
//	static T*& getInstance()
//	{
//		static T* mInstance=nullptr;
//		if ( !mInstance )
//		{
//			mInstance = new T;
//		}
//		return mInstance;
//	}
//	static  T& getSingleton()
//	{
//		return *getInstance();
//	}
//	static void destoryInstance()
//	{
//		T*& p=getInstance();
//		dSafeDelete ( p );
//	}
//	//static T* mInstance;
//};

//template<typename T>
//__declspec ( selectany )
//	T* CXSingleton<T>::mInstance = nullptr;
#endif // CXSingleton_h__
