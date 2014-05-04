#pragma once
template<typename T>
class BiTreeNode
{
    public:
        typedef BiTreeNode<T> ThisNode;

        BiTreeNode()
            : Data( 0 ), Left( 0 ), Right( 0 )
        {

        }
        void Clear()
        {
            Data = 0;
        }
    protected:
        T* Data;
        ThisNode* Left;
        ThisNode* Right;
};
template<typename T>
class CXBiTree
{
    public:
        typedef BiTreeNode<T> ThisBiTreeNode;
        ~CXBiTree()
        {
            CXSafeDelete( mRoot );
        }
        CXBiTree( void )
            : mRoot( 0 )
        {
            mRoot = new ThisBiTreeNode;
        }

        ThisBiTreeNode* GetLeftest() const
        {
            ThisBiTreeNode* next = mRoot->Left;
            ThisBiTreeNode* last = 0;

            while ( next )
            {
                last = next;
                next = next->Left;
            }

            return last;
        }
        ThisBiTreeNode* GetRightest() const
        {
            ThisBiTreeNode* next = mRoot->Right;
            ThisBiTreeNode* last = 0;

            while ( next )
            {
                last = next;
                next = next->Right;
            }

            return last;
        }

        ThisBiTreeNode*  mRoot;
};
