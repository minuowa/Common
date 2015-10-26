#pragma once
class uPathFinder
{
public:
	uPathFinder(void);
	~uPathFinder(void);
	typedef void (*CallBack)(const char* /*filename*/);

	void find(const char* path,const char* ext,CallBack call);
protected:
};

