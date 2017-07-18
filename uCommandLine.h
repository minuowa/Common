#pragma once
#include "uString.h"
#include "uArray.h"
#include "uMap.h"
class uCommandLine {
  public:
    uCommandLine(int narg, const char** args);
    ~uCommandLine();

    template<typename T>
    void get(const char* key, T& v) {
        if (mArgs.findkey(key))
            CXStringHelper::setValue(mArgs[key].c_str(), &v);
    }
    size_t arg_count();
  private:
    uMap<uString, uString> mArgs;
};

