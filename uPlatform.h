class uPlatform
{
public:
	static void sleep(u32 time);

	static bool isPath(const char* str);

	static std::string generateGUIDString();

	static std::string generateGUIDSimpleString();
};