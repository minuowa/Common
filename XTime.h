#pragma once
typedef unsigned int TYPEN;
template<TYPEN N>
class CXTimeDim {
  public:
    static const TYPEN DIM = N;

    CXTimeDim(void) {
        mValue = 0;
    }

    CXTimeDim(TYPEN v) {
        mValue = v;
    }

    template<TYPEN N2>
    CXTimeDim(CXTimeDim<N2>& rhs) {
        mValue = rhs.DIM * rhs.mValue / DIM;
    }
    operator TYPEN() {
        return getMillSecond();
    }
    template<TYPEN N2>
    bool operator== (CXTimeDim<N2>& rhs) {
        return getMillSecond() == rhs.getMillSecond();
    }
    template<TYPEN N2>
    bool operator<= (const CXTimeDim<N2>& rhs) {
        return getMillSecond() <= rhs.getMillSecond();
    }
    //template<TYPEN N2>
    //CXTimeDim& opeator = ( const CXTimeDim<N2>& rhs )
    //{
    //    mValue = rhs.DIM * rhs.mValue / DIM;
    //    return *this;
    //}

    inline TYPEN getSeconds() const {
        return DIM * 0.001 * mValue;
    }
    inline TYPEN getMillSecond() const {
        return DIM * mValue;
    }
  protected:
    TYPEN mValue;
};



typedef CXTimeDim<1> CXMillSecond;
typedef CXTimeDim<1000> CXSecond;
typedef CXTimeDim<1000 * 60> CXMinute;
typedef CXTimeDim<1000 * 60 * 60> CXHour;
typedef CXTimeDim<1000 * 60 * 60 * 24> CXDay;
