#ifndef CXBase_h__
#define CXBase_h__
//--------------------------------------------------------------------------------------------------
#include "base.h"
#include "XSingleton.h"
#include "uString.h"
#include "uMap.h"

#ifndef CPP1999
#include "XHashMap.h"
#include "XStrongPtr.h"
#include "XWeakPtr.h"
#include "XMultiMap.h"
#endif

#include "XList.h"
#include "uArray.h"
#include "XStaticArray.h"
#include "XStack.h"
#include "XBiTree.h"
#include "XRapidxmlLoader.h"
#include "XRapidxmlWriter.h"
#include "XFileName.hpp"
#include "XMath.h"
#include "uDelegate.h"
#include "XProp.h"
#include "uBuffer.h"
#include "XIndex.h"
#include "ustring.h"
#include "XRandom.h"
#include "XEaser.h"
#include "XTime.h"
#include "XVector3.h"
#include "XColor.h"
#include "XObjectPool.h"
#include "XBitArray.h"
#include "XIDObjectManager.h"
#include "XRect.h"
#include "XPoint2.h"
#include "XLexer.h"

#include "Tree.h"
#include "uString.h"
#include "uPathFinder.h"
#include "uPlatform.h"
#include "uCommandLine.h"

#define DeclareFilmObj(type)
#define DeclareFilmObjBase(type,parentType)
#define DeclareFilmTool
#define DeclareFilmToolGlobal

/** @brief 查找一个数组或vector中cur之后的第一个符合条件的元素 **/
template<typename uArray, typename T, typename CondtionObj>
T* dFindNextElementInArray ( uArray&  arr, T* cur, CondtionObj& funObj ) {
    bool existCur = false;
    for ( auto & e : arr ) {
        if ( existCur && funObj ( e ) ) {
            return e;
        }
        if ( e == cur ) {
            existCur = true;
        }
    }
    return nullptr;
}
/** @brief
查找一棵树中(中序遍历)cur之后的第一个符合条件的元素
**/
template<typename T, typename CondtionObj>
T* dFindNextElementInTree ( T*  parent, T* cur, CondtionObj& funObj ) {
    CXASSERT ( parent );
    CXASSERT ( cur );
    bool existCur = parent == cur;
    auto& children = parent->getChildren();
    for ( auto & e : children ) {
        if ( existCur && funObj ( e ) ) {
            return e;
        }
        if ( e == cur ) {
            existCur = true;
        }
        T* tar = dFindNextElementInTree ( e, cur, funObj );
        if ( tar != nullptr )
            return tar;
    }
    return nullptr;
}
template<typename T, typename CondtionObj>
T* dFindNextElementInTreeCycle ( T*  parent, T* cur, CondtionObj& funObj ) {
    uArray<T*> dstArray;
    bool begin = parent == cur;
    bool end = parent == cur;
    takeElementToTopFromTreeToVector ( dstArray, parent, cur, begin );
    takeElementToVectorUntil ( dstArray, parent, cur, end );
    return dFindNextElementInArray ( dstArray, cur, funObj );
}
template<typename T>
void takeElementToTopFromTreeToVector ( uArray<T*>& dstArray, T* parent, T* cur, bool& begin ) {
    if ( parent == cur )
        begin = true;
    if ( begin )
        dstArray.push_back ( parent );
    auto& children = parent->getChildren();
    for ( auto & a : children )
        takeElementToTopFromTreeToVector ( dstArray, a, cur, begin );
}
template<typename T>
void takeElementToVectorUntil ( uArray<T*>& dstArray, T* parent, T* cur, bool& end ) {
    if ( parent == cur ) {
        end = true;
        return;
    }
    if ( !end )
        dstArray.push_back ( parent );
    auto& children = parent->getChildren();
    for ( auto & a : children )
        takeElementToVectorUntil ( dstArray, a, cur, end );

}



//--------------------------------------------------------------------------------------------------
#endif // CXBase_h__
