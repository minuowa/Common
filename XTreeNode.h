#pragma once
template<typename T>
class CXTreeNode
{
public:
    typedef CXTreeNode<T> MyType;
    typedef CXDynaArray<T*> Array;
public:
    CXDynaArray<MyType*> mChildren;
    CXTreeNode* mParent;
private:
    T* mData;
public:
    ~CXTreeNode()
    {
        this->destroy();
    }
    CXTreeNode ( void )
        : mData ( 0 )
        , mParent ( 0 )
    {
    }
    void setData ( T* data )
    {
        mData = data;
    }
    T* getData()
    {
        return mData;
    }
    void addToArray ( Array& arr )
    {
        arr.push_back ( mData );
for ( auto i: mChildren )
            i->addToArray ( arr );
    }
    void addChild ( MyType* child )
    {
        child->mParent = this;
        mChildren.push_back ( child );
    }
    /** 查找符合条件的节点 **/
    template<typename CONDTION, typename PARA>
    bool findChild ( OUT MyType*& child, CONDTION con, PARA para )
    {
        if ( con ( this, para ) )
        {
            child = this;
            return true;
        }
        else
        {
for ( auto i: mChildren )
            {
                if ( i->findChild ( child, con, para ) )
                {
                    return true;
                }
            }
        }
        return false;
    }
    /** 递归移除指定节点 **/
    bool removeChild ( MyType* child )
    {
        if ( mChildren.remove ( child ) )
        {
            child->mParent = nullptr;
            return true;
        }
for ( auto i: mChildren )
        {
            if ( i->removeChild ( child ) )
                return true;
        }
        return false;
    }
    /** 移除符合条件的节点 **/
    template<typename CONDTION, typename PARA>
    bool removeChild ( OUT MyType*& child, CONDTION con, PARA para )
    {
        if ( con ( this, para ) )
        {
            child = this;

            if ( mParent != nullptr )
            {
                mParent->mChildren.remove ( this );
                mParent = nullptr;
            }
            return true;
        }
        else
        {
for ( auto i: mChildren )
            {
                if ( i->removeChild ( child, con, para ) )
                {
                    return true;
                }
            }
        }
        return false;
    }



    /** 销毁符合条件的节点 **/
    template<typename CONDTION, typename PARA>
    bool deleteChild ( CONDTION con, PARA para )
    {
        MyType* child = nullptr;
        if ( removeChild ( child, con, para ) )
        {
            delete child;
            child = nullptr;
            return true;
        }
        return false;
    }

    void destroy()
    {
        mParent = 0;
        mChildren.destroy();
        ondestroy();
        dSafeDelete ( mData );

        if ( mParent != nullptr )
        {
            mParent->removeChild ( this );
            mParent = nullptr;
        }
    }
    virtual void ondestroy()
    {
    }

};

template<typename T>
class CXTree
{
public:
    typedef CXTreeNode<T> Node;
    typedef CXDynaArray<T*> Array;
    typedef CXTree<T> MyType;
public:
    ~CXTree()
    {
        mNodes.destroy();
    }
    /** 查找符合条件的节点 **/
    template<typename CONDTION, typename PARA>
    bool findChild ( OUT Node*& child, CONDTION con, PARA para )
    {
for ( auto i: mNodes )
        {
            if ( i->findChild ( child, con, para ) )
            {
                return true;
            }
        }
        return false;
    }
    /** 删除符合条件的节点 **/
    template<typename CONDTION, typename PARA>
    bool deleteChild ( CONDTION con, PARA para )
    {
for ( auto i: mNodes )
        {
            Node* child = nullptr;
            if ( i->deleteChild ( con, para ) )
                return true;
        }
        return false;
    }
    /** 删除符合条件的节点 **/
    template<typename CONDTION, typename PARA>
    bool remove ( OUT Node*& child, CONDTION con, PARA para )
    {
        child = nullptr;
for ( auto i: mNodes )
        {
            if ( i->removeChild ( child, con, para ) )
                return true;
        }
        return false;
    }
    void destroy()
    {
        dSafeDeleteVector ( mNodes );
    }
    void toArray ( Array& arr )
    {
for ( auto i: mNodes )
        {
            i->addToArray ( arr );
        }
    }

    void add ( Node* child )
    {
        CXCheck ( child != nullptr );
        mNodes.push_back ( child );
    }
    void remove ( Node* child )
    {
        CXCheck ( child != nullptr );
        mNodes.remove ( child );
    }
public:
    CXDynaArray<Node*> mNodes;
};
