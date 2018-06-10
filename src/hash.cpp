#include "../include/hash.hpp"

template < class KeyType, class DataType, class KeyHash, class KeyEqual >
HashTbl::HashTbl( int tbl_size_ )
{
	tbl_size_ = next_prime( tbl_size_ );
	m_data_table = new std::forward_list<Entry>[tbl_size_];
}

template < class KeyType, class DataType, class KeyHash, class KeyEqual >
HashTbl::~HashTbl()
{
	for( auto &each_list : m_data_table ) delete[] each_list;
	delete[] m_data_table;
}

template < class KeyType, class DataType, class KeyHash, class KeyEqual >
bool HashTbl<KeyType, DataType,
			 KeyHash, KeyEqual>::insert ( const KeyType & key_,
										  const DataType & data_item_ )
{
	KeyHash hashFunc;	// Instantiate the "functor" for primary hash.
	KeyEqual equalFunc; // Instantiate the "functor" for the equal to test.
	Entry new_entry ( key_, data_item_ );	//Create a new entry.

	// Apply double hashing method, one functor and the other with modulo function.
	auto end( hashFunc( key_ ) % m_size );
	m_data_table[end];
		// Comparing keys inside the collision list.
		if( true == equalFunc( m_key, new_entry.m_key ) ){
			
	//TODO...
}
template < class KeyType, class DataType, class KeyHash, class KeyEqual >
bool HashTbl<KeyType, DataType,
			 KeyHash, KeyEqual>::remove ( const KeyType & k_ )
{
	auto & whichList = m_data_table[ hashFunc( k_ ) ];
	auto itr = find( begin( whichList ), end( whichList ), k_ );
	if( itr == end( whichList ) ) return false;
	whichList.erase( itr );
	--m_count;
	return true;
}
template < class KeyType, class DataType, class KeyHash, class KeyEqual >

template < class KeyType, class DataType, class KeyHash, class KeyEqual >
void HashTbl<KeyType, DataType,
			 KeyHash, KeyEqual>::clear ( void
template < class KeyType, class DataType, class KeyHash, class KeyEqual >

template < class KeyType, class DataType, class KeyHash, class KeyEqual >

template < class KeyType, class DataType, class KeyHash, class KeyEqual >
