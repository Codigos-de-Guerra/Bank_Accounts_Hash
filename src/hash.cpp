#include "../include/hash.hpp"

template < class KeyType, class DataType, class KeyHash, class KeyEqual >
/*Constructor{{{*/
HashTbl::HashTbl( size_t tbl_size_ = DEFAULT_SIZE )
{
	tbl_size_ = next_prime( tbl_size_ );
	m_data_table = new std::forward_list<Entry>[tbl_size_];

	m_size = tbl_size_;
	m_count = 0;
}
/*}}}*/

template < class KeyType, class DataType, class KeyHash, class KeyEqual >
/*Destructor{{{*/
HashTbl::~HashTbl()
{
	for( auto &each_list : m_data_table ) delete[] each_list;
	delete[] m_data_table;
}
/*}}}*/

template < class KeyType, class DataType, class KeyHash, class KeyEqual >
/*insert method{{{*/
bool HashTbl<KeyType, DataType,
			 KeyHash, KeyEqual>::insert ( const KeyType & key_,
										  const DataType & data_item_ )
{
	auto & whichList = m_data_table[ hashFunc( key_ ) % m_size ];
	Entry new_entry ( key_, data_item_ ); //Create a new entry.

	for( auto it( whichList.begin() ); it != whichList.end(); it++ ){
		if( true == equalFunc( (*it).m_key , new_entry.m_key ) ){
			(*it).m_data = new_entry.m_data;
			return false;
		}
	}

	whichList.push_front( new_entry );
	if( ++m_count > m_size ) rehash( );
	
	return true;
}
/*}}}*/

template < class KeyType, class DataType, class KeyHash, class KeyEqual >
/*remove method{{{*/
bool HashTbl<KeyType, DataType,
			 KeyHash, KeyEqual>::remove ( const KeyType & key_ )
{
	auto & whichList = m_data_table[ hashFunc( key_ ) % m_size ];
	auto itr = find( begin( whichList ), end( whichList ), key_ );
	if( itr == end( whichList ) ) return false;
	whichList.erase( itr );
	--m_count;
	return true;

}
/*}}}*/

template < class KeyType, class DataType, class KeyHash, class KeyEqual >
/*retrieve method{{{*/
bool HashTbl<KeyType, DataType,
			 KeyHash, KeyEqual>::retrieve ( const KeyType & key_,
											DataType & d_ ) const
{
	auto & whichList = m_data_table[ hashFunc( key_ ) % m_size ];	
	auto itr = find( whichList.begin(), whichList.end(), key_ );
	if( itr == whichList.end() ) return false;

	d_ = (*itr).m_data;
	return true;
}
/*}}}*/
	
template < class KeyType, class DataType, class KeyHash, class KeyEqual >
/*clear method{{{*/
void HashTbl<KeyType, DataType,
			 KeyHash, KeyEqual>::clear ( void )
{
	m_data_table.clear();
}
/*}}}*/

template < class KeyType, class DataType, class KeyHash, class KeyEqual >
/*empty method{{{*/
bool HashTbl<KeyType, DataType,
			 KeyHash, KeyEqual>::empty ( void ) const
{
	return m_count == 0;
}
/*}}}*/

template < class KeyType, class DataType, class KeyHash, class KeyEqual >
/*count method{{{*/
unsigned long int HashTbl<KeyType, DataType,
						  KeyHash, KeyEqual>::count ( void ) const
{
	return m_count;
}
/*}}}*/

template < class KeyType, class DataType, class KeyHash, class KeyEqual >
/*print method{{{*/
void HashTbl<KeyType, DataType,
			 KeyHash, KeyEqual>::print ( void ) const
{
	if( !m_data_table.empty() ){
		auto eachList = m_data_table.begin();
		for( ; eachList != m_data_table.end(); eachList++ ){
		// Loop to check each List inside our vector os Lists.(Hash Table).
			if( !(*eachList).empty() ){
				auto itr = *eachList.begin();
				for( ; itr != *eachList.end(); itr++ ){
					std::cout << ">>> Key: " << *itr.m_key << " Data: ";
					std::cout << *itr.m_data << "\n";
				}
			}
		}
	}
}
/*}}}*/


