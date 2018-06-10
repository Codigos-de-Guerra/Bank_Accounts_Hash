/**
 * @file hash.hpp
 * @version 1.0
 * @date Jun, 09.
 * @author Daniel Guerra (daniel.guerra13@hotmail.com)
 * @title Hash Implementation
 */

#ifndef _HASH_
#define _HASH_

#include <iostream>
#include <vector>
#include <forward_list>
#include <iterator>
#include <algorithm>
#include <functional>
#include <string>

template< typename KeyType,
		  typename DataType,
		  typename KeyHash = std::hash<KeyType>,
		  typename KeyEqual = std::equal_to<KeyType> >
class HashTbl {
	class HashEntry {
		public:

		HashEntry ( KeyType k_, DataType d_ ) : m_key( k_ ), m_data( d_ )
		{ /* empty */ };
		KeyType m_key;		//!< Stores the key for an entry.
		DataType m_data;	//!< Stores the data for an entry.
	};
	public:
		using Entry = HashEntry< KeyType, DataType >; //!< Alias

		HashTbl ( size_t tbl_size_ = DEFAULT_SIZE );
		virtual ~HashTbl ();
		bool insert ( const KeyType & k_, const DataType & d_ );
		bool remove ( const KeyType & k_ );
		bool retrieve ( const KeyType & k_, DataType & d_ ) const;
		void clear ( void );
		bool empty ( void ) const;
		unsigned long int count ( void ) const;
		void print( void ) const;

	private:
		void rehash();			//!< Change Hash table size if load factor >1.0
		size_t next_prime( size_t tbl_size ); //Finds the smaller prime number greater than tbl_size.
		unsigned int m_size;	//!< Hash table size.
		unsigned int m_count;	//!< Number of elements currently stored in the table.
		//!< The table: vector of lists of Entry.
		std::vector< std::forward_list< Entry > > m_data_table;
		//! Hash table's default size: 11 table entries.
		static const short DEFAULT_SIZE = 11;

		void rehash(){
			std::vector< std::forward_list< Entry > > old_data_table = m_data_table;
			// New table size now must be at least 2 times bigger than previous.
			m_size = next_prime( 2*m_size );
			m_data_table.resize( m_size );
			m_count = 0;

			for( auto & this_data_table : m_data_table ){
				this_data_table.clear( );
			}
			// Copy table data
			for( auto &copy_data_table : old_data_table ){
				for( auto & values : copy_data_table ){
					insert( values.m_key, values.m_data );
				}
			}
		}

		size_t next_prime( size_t tbl_size ){
			for( int i = 2; i < sqrt(tbl_size); i++){
				if( tbl_size % i == 0 ) return next_prime( tbl_size + 1 );
			}
			return tbl_size;
		}
};
