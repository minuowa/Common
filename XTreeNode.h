#pragma once
template<typename T>
class CXTreeNode
{
public:
    typedef CXTreeNode<T> MyType;
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
    void addChild ( MyType* child )
    {
        child->mParent = this;
        mChildren.push_back ( child );
    }
    /** ���ҷ��������Ľڵ� **/
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
    /** �ݹ��Ƴ�ָ���ڵ� **/
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
    /** �Ƴ����������Ľڵ� **/
    template<typename CONDTION>
    bool removeChild ( OUT MyType*& child, CONDTION con )
    {
        if ( con ( this ) )
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
                if ( i.findChild ( child, con ) )
                {
                    return true;
                }
            }
        }
        return false;
    }


    /** ���ٷ��������Ľڵ� **/
    template<typename CONDTION, typename ONDESTORY>
    bool destroyChild ( CONDTION con, ONDESTORY onDestroy )
    {
        if ( con ( this ) )
        {
            onDestroy ( this );

            this->destroy();

            return true;
        }
        else
        {
for ( auto i: mChildren )
            {
                if ( i.destroyChild ( con, onDestroy ) )
                {
                    return true;
                }
            }
        }
        return false;
    }

    void destroy()
    {
for ( MyType * child: mChildren )
            child->destroy();
        if ( mParent != nullptr )
        {
            mParent->removeChild ( this );
        }

        ondestroy();
        mParent = 0;
        dSafeDelete ( mData );
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

    /** ���ҷ��������Ľڵ� **/
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
    void destroy()
    {
        dSafeDeleteVector ( mNodes );
    }
public:
    CXDynaArray<Node*> mNodes;
};
