/**
 * @file hash.hpp
 * @version 1.0
 * @date Jun, 09.
 * @author Daniel Guerra (daniel.guerra13@hotmail.com)
 * @title Hash Implementation
 */

#ifndef _HASH_BANK_
#define _HASH_BANK_

#include <iostream>
#include <vector>
#include <forward_list>
#include <iterator>
#include <cmath>
#include <functional>
#include <string>

template< typename KeyType,
		  typename DataType,
		  typename KeyHash = std::hash<KeyType>,
		  typename KeyEqual = std::equal_to<KeyType> >
class HashTbl {

	class HashEntry {

		public:
			//! @brief HashEntry Constructor.
			HashEntry ( KeyType k_, DataType d_ ) : m_key( k_ ), m_data( d_ )
			{ /* empty */ };
			KeyType m_key;		//!< Stores the key for an entry.
			DataType m_data;	//!< Stores the data for an entry.
	};

	public:
		using Entry = HashEntry/*< KeyType, DataType >*/; //!< Alias

		//! @brief Hash Table Constructor with passed size.
		HashTbl ( size_t tbl_size_ );

		//! @brief Hash Table Default Constructor.
		HashTbl ( void );
	
		//! @brief Hash Table Destructor.
		//virtual ~HashTbl ();
	
		/** @brief Inserts information 'data_item_' related to 'key_', onto table.
		 *	@returns True if insertion was successful. False if 'key_' already existed on table. In this case we overwrite previous data with new.
		 */
		bool insert ( const KeyType & key_, const DataType & data_item_ );

		/** @brief Removes element and data related to 'key_'.
		 *	@return True if 'key_' was found; False otherwise.
		 */
		bool remove ( const KeyType & key_ );

		/** @brief Retrieves data related to 'key_'.
		 *  @return True if data is found; False otherwise.
		 */
		bool retrieve ( const KeyType & key_, DataType & d_ ) const;

		//! @brief Clear all memory and info related to collision lists.
		void clear ( void );

		//! @return True if Hash Table is empty; False otherwise.
		bool empty ( void ) const;

		//! @return Current number of elements stored in table.
		unsigned long int count ( void ) const;

		//! @brief Prints onto terminal the Hash Table.
		void print( void ) const;

	private:

		unsigned int m_size;	//!< Hash table current size.
		unsigned int m_count;	//!< Number of elements currently stored in the table.

		//!< The table: vector of lists of Entry.
		std::vector< std::forward_list< Entry > > m_data_table;
		
		//! Hash table's default size: 13 table entries.
		static const short DEFAULT_SIZE = 13;
	
		// Auxiliary functions
		KeyHash hashFunc;	// Instantiate the "functor" for primary hash.
		KeyEqual equalFunc;	// Instantiate the "functor" for the equal to test.

		//! @brief Resizes the Hash Table if  load factor > 1.
		void rehash( void ){
		/*{{{*/
			std::vector< std::forward_list< Entry > > old_data_table = m_data_table;
			// New table size now must be at least 2 times bigger than previous.
			m_size = next_prime( 2 * m_size );
			m_data_table.resize( m_size );
			m_count = 0;

			for( auto & this_data_table : m_data_table ){
				this_data_table.clear();
			}

			// Copy table data
			for( auto & copy_data_table : old_data_table ){
				for( auto & values : copy_data_table ){
					insert( values.m_key, values.m_data );
				}
			}
		}
		/*}}}*/

		//! @brief Auxiliary function for finding a valid size for table.
		// First smaller number greater than tbl_size
		size_t next_prime( size_t tbl_size ){
		/*{{{*/
			for( int i = 2; i < sqrt( tbl_size ); i++){
				if( tbl_size % i == 0 ) return next_prime( tbl_size + 1 );
			}
			return tbl_size;
		}
		/*}}}*/
};

template < class KeyType, class DataType, class KeyHash, class KeyEqual >
/*Constructor{{{*/
HashTbl<KeyType, DataType, KeyHash, KeyEqual>::HashTbl( size_t tbl_size_ )
{
	m_size = next_prime( tbl_size_ );
	m_data_table.resize( m_size );

	m_count = 0;
}
/*}}}*/

template < class KeyType, class DataType, class KeyHash, class KeyEqual >
/*Default Constructor{{{*/
HashTbl<KeyType, DataType, KeyHash, KeyEqual>::HashTbl( void )
{
	m_size = DEFAULT_SIZE;
	m_data_table.resize( DEFAULT_SIZE );

	m_count = 0;
}
/*}}}*/

//template < class KeyType, class DataType, class KeyHash, class KeyEqual >
/*Destructor{{{*/
//HashTbl<KeyType, DataType, KeyHash, KeyEqual>::~HashTbl()
//{
//	for( auto &each_list : m_data_table ) delete[] each_list;
//	delete[] m_data_table;
//}
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
	auto prev = whichList.before_begin();
	for( auto it( whichList.begin() ); it != whichList.end(); it++ ){
		if( true == equalFunc( (*it).m_key, key_ ) ){
			whichList.erase_after( prev );
			--m_count;
			return true;
		}
		prev++;
	}

	return false;
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
				auto itr = (*eachList).begin();
				for( ; itr != (*eachList).end(); itr++ ){
					std::cout << ">>> Key: " << (*itr).m_key << " Data: ";
					std::cout << (*itr).m_data << "\n";
				}
			}
		}
	}
}
/*}}}*/

#endif
