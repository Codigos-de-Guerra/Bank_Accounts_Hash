#include <iostream>
#include <cassert>
#include <functional>
#include <fstream>
#include <tuple>

#include "hash.hpp"

struct Account{

	using AcctKey = std::tuple< std::string, int, int, int >;

	std::string client_name_;
	int bank_code_;
	int agency_num_;
	int account_num_;
	float balance_;

	Account( std::string name = "John Doe" , int b_c = 0,
			 int ag_n = 0, int ac_n = 0, float bal = 0 )
	{
		client_name_ = name;
		bank_code_ = b_c;
		agency_num_ = ag_n;
		account_num_ = ac_n;
		balance_ = bal;
	}

	//! @brief Returns the key related to account.
	AcctKey get_key( void ) {
		return std::make_tuple( client_name_, bank_code_,
								agency_num_, account_num_ );
	}

	//! @brief Prints an Account.
	inline friend std::ostream &operator<< ( std::ostream & os_, const Account & acc_ )
    {
        os_ << "\n\tClient: < " << acc_.client_name_ <<
            " >\n\tBank: < "   << acc_.bank_code_ <<
            " >\n\tBranch: < " << acc_.agency_num_ <<
            " >\n\tNumber: < " << acc_.account_num_ <<
            " >\n\tBalance: < " << acc_.balance_ << " >\n";
            
        return os_;
	}
};

//! @brief Functor for 1st Hash Function.
struct KeyHash {

	std::size_t operator()( const Account::AcctKey& key_ ) const
	{
		std::size_t hash_val = std::hash< int >()( std::get<1>( key_ ) );
		hash_val += std::hash< int >()( std::get<2>( key_ ) );
		hash_val += std::hash< int >()( std::get<3>( key_ ) );
		for( char c_ : std::get<0>( key_ ) ){
			hash_val += c_;
		}

		return hash_val;
	}
};

//! @brief Functor for Comparing 'keys'.
struct KeyEqual {

	bool operator()( const Account::AcctKey & lhs_,
					 const Account::AcctKey & rhs_ ) const
	{
		return std::get<0>( lhs_ ) == std::get<0>( rhs_ ) and
			   std::get<1>( lhs_ ) == std::get<1>( rhs_ ) and
			   std::get<2>( lhs_ ) == std::get<2>( rhs_ ) and
			   std::get<3>( lhs_ ) == std::get<3>( rhs_ );

	}
};

int main( void ) {
	std::cout << "\e[32;4m>>> Bank Account Management Implemenation\e[0m\n";
	
	Account myAccounts[] =
		{
                {"Altair", 1, 1191, 44876, 10000.f},
                {"Ezio Audi", 2, 1476, 45794, 650000.f},
                {"Haytham Ken", 3, 1754, 87629, 305500.f},
                {"Connor Ken", 3, 1783, 1231, 1850.f},
                {"Edward Ken", 4, 1715, 5, 230.f}
		};

	HashTbl< Account::AcctKey, Account, KeyHash, KeyEqual > contas(15);

	assert( contas.count() == 0 );

	contas.insert( myAccounts[4].get_key(), myAccounts[4] );
	contas.insert( myAccounts[3].get_key(), myAccounts[3] );
	contas.insert( myAccounts[2].get_key(), myAccounts[2] );
	contas.insert( myAccounts[1].get_key(), myAccounts[1] );
	contas.insert( myAccounts[0].get_key(), myAccounts[0] );

	// Showing Accounts
	contas.print();

	assert( contas.count() == 5 );

	std::cout << "\e[32;4m>>> Deleting Connor's Account...\e[0m\n";
	if( contas.remove( myAccounts[3].get_key() ) ){
		std::cout << "\e[32;4m>REMOVAL SUCCESS!\e[0m\n";
	}
	else {
		std::cout << "\e[32;4m>ACCOUNT NOT FOUND!\e[0m\n";
	}

	contas.print();
	assert( contas.count() == 4 );

	Account acc1;
	contas.retrieve( myAccounts[1].get_key(),  acc1);
	assert( myAccounts[1].get_key() == acc1.get_key() );
	assert( myAccounts[1].client_name_ ==  acc1.client_name_ );
	assert( myAccounts[1].agency_num_ ==  acc1.agency_num_ );

	// If it reaches here, then retrieval was a success.

	//myAccounts[3] was removed, retrieve needs to be false
	assert( contas.retrieve( myAccounts[3].get_key(),  acc1) == false );


	std::cout << "\e[33;4m>>> Testing Rehash efficacy\e[0m\n";

	Account bb[] = {
		{"Jaime", 1, 16683, 222, 10000000.f},
		{"Adamastor", 4, 16683, 222, 5831.f},
		{"Mustafar", 4, 16683, 21322, 111.f},
		{"Simba", 4, 16683, 21332, 543210.f},
		{"Joel Santana", 9, 42, 909, 9009.f},
		{"Zero Criatividade", 1, 2, 3, 12.f},
		{"Encher Linguiça", 10, 12, 13, 0.f},
		{"AAAAAAAAAA", 61, 7134, 81, 8121.f}
	};

	// Hash Table with capacity of 2.
	HashTbl< Account::AcctKey, Account, KeyHash, KeyEqual > tabela(2);

	assert( tabela.count() == 0 );

	for( int i=0; i < 8; i++ ){
		// Insertions here will require a total of 2 rehashes.
		// From size 2 -> 5 -> 11.
		tabela.insert( bb[i].get_key(), bb[i] );
	}
	tabela.print();

	assert( tabela.count() == 8 );
	assert( tabela.size() == 11 );

	std::cout << "\e[36;1m>>> Rehashes were successful\e[0m\n";
	std::cout << "\e[36;4m>>> SUCCESS ACHIEVED!!\e[0m\n\n";
	return 0;
}
