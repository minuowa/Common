#ifndef CXBase_h__
#define CXBase_h__
//--------------------------------------------------------------------------------------------------
#include "base.h"
#include "XSingleton.h"
#include "XString.h"
#include "XMap.h"
#include "XMultiMap.h"
#include "XList.h"
#include "XDynaArray.h"
#include "XStaticArray.h"
#include "XStack.h"
#include "XBuffer.h"
#include "XBiTree.h"
#include "XRapidxmlLoader.h"
#include "XRapidxmlWriter.h"
#include "XIDGenerator.h"
#include "XFileName.hpp"
#include "XMath.h"
#include "XDelegate.h"
#include "XProp.h"
#include "XBuffer.h"
#include "XIndex.h"
#include "XString.h"
#include "XRandom.h"

/** @brief 查找一个数组或vector中cur之后的第一个符合条件的元素 **/
template<typename Array, typename T, typename CondtionObj>
T* dFindNextElementInArray ( Array&  arr, T* cur, CondtionObj& funObj )
{
    bool existCur = false;
for ( auto & e: arr )
    {
        if ( existCur && funObj ( e ) )
        {
            return e;
        }
        if ( e == cur )
        {
            existCur = true;
        }
    }
    return nullptr;
}
/** @brief
	find the
	查找一棵树中(中序遍历)cur之后的第一个符合条件的元素
	the tree has children with Array<T*> pattern
	**/
template<typename T, typename CondtionObj>
T* dFindNextElementInTree ( T*  parent, T* cur, CondtionObj& funObj )
{
    CXASSERT ( parent );
    CXASSERT ( cur );
    bool existCur = parent == cur;
    auto& children = parent->getChildren();
for ( auto & e: children )
    {
        if ( existCur && funObj ( e ) )
        {
            return e;
        }
        if ( e == cur )
        {
            existCur = true;
        }
        T* tar = dFindNextElementInTree ( e, cur, funObj );
        if ( tar != nullptr )
            return tar;
    }
    return nullptr;
}
template<typename T, typename CondtionObj>
T* dFindNextElementInTreeCycle ( T*  parent, T* cur, CondtionObj& funObj )
{
    CXDynaArray<T*> dstArray;
    bool begin = parent == cur;
    bool end = parent == cur;
    takeElementToTopFromTreeToVector ( dstArray, parent, cur, begin );
    takeElementToVectorUntil ( dstArray, parent, cur, end );
    return dFindNextElementInArray ( dstArray, cur, funObj );
}
template<typename T>
void takeElementToTopFromTreeToVector ( CXDynaArray<T*>& dstArray, T* parent, T* cur, bool& begin )
{
    if ( parent == cur )
        begin = true;
    if ( begin )
        dstArray.push_back ( parent );
    auto& children = parent->getChildren();
for ( auto & a: children )
        takeElementToTopFromTreeToVector ( dstArray, a, cur, begin );
}
template<typename T>
void takeElementToVectorUntil ( CXDynaArray<T*>& dstArray, T* parent, T* cur, bool& end )
{
    if ( parent == cur )
    {
        end = true;
        return;
    }
    if ( !end )
        dstArray.push_back ( parent );
    auto& children = parent->getChildren();
for ( auto & a: children )
        takeElementToVectorUntil ( dstArray, a, cur, end );

}
//--------------------------------------------------------------------------------------------------
#endif // CXBase_h__
