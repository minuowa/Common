bool Insert( TK k, TV v )
{
    std::pair<Super::iterator, bool> res = Super::insert( std::make_pair<TK, TV>( k, v ) );
    return res.second;
}
void Destroy()
{
    iterator i( begin() ), iEnd( end() );

    for ( ; i != iEnd; ++i )
    {
        CXSafeDelete( i->second );
    }

    clear();
}