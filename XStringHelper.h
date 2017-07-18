#ifndef CXStringHelper_h__
#define CXStringHelper_h__
#include "uString.h"
#include <xstring>
namespace CXStringHelper {
template<typename T>
void toString(std::string& dst, T* var) {
    dst = to_string(*var);
}
void toString(std::string& dst, uString* var);
void toString(std::string& dst, string* var);
void toString(std::string& dst, bool* var);


void setValue(const char* val, string* var);
void setValue(const char* val, uString* var);
void setValue(const char* val, int* var);
void setValue(const char* val, float* var);
void setValue(const char* val, bool* var);
void setValue(const char* val, unsigned int* var);
void setValue(const char* val, long* var);
}
#pragma warning(push)
#pragma warning(disable:4996)
inline void CXStringHelper::toString(std::string& dst, uString* var) {
    CXASSERT(var);
    dst = var->c_str();
}

inline void toString(std::string& dst, string* var) {
    CXASSERT(var);
    dst = var->c_str();
}



inline void CXStringHelper::toString(std::string& dst, bool* var) {
    dst = (*var) ? "true" : "false";
}


inline void CXStringHelper::setValue(const char* val, uString* var) {
    CXASSERT(val);
    *var = val;
}
inline void CXStringHelper::setValue(const char* val, string* var) {
    CXASSERT(val);
    *var = val;
}

inline void CXStringHelper::setValue(const char* val, int* var) {
    *var = stoi(val);
}

inline void CXStringHelper::setValue(const char* val, float* var) {
    *var = stof(val);
}

inline void CXStringHelper::setValue(const char* val, bool* var) {
    *var = !strcmp("True", val) || !strcmp("true", val);
}

inline void CXStringHelper::setValue(const char* val, unsigned int* var) {
    CXASSERT(val);
    sscanf_s(val, "%u", var);
}

inline void CXStringHelper::setValue(const char* val, long* var) {
    *var = stol(val);
}

#pragma warning(pop)
#endif // CXStringHelper_h__
