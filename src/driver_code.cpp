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

	Account( std::string nome = "Alfredo" , int b_c = 7, int ag_n = 13, int ac_n = 25, float bal = 100 )
	{
		client_name_ = nome;
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

	HashTbl< Account::AcctKey, Account > contas(15);

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
		std::cout << " Removal Sucess!";
	}
	else {
		std::cout << " Account not found!";
	}

	contas.print();
	assert( contas.count() == 4 );

	Account acc1;
	contas.retrieve( myAccounts[3].get_key(),  acc1);
	assert( myAccounts[3].get_key() ==  acc1.get_key() );
	assert( myAccounts[3].client_name_ ==  acc1.client_name_ );
	assert( myAccounts[3].agency_num_ ==  acc1.agency_num_ );

	//myAccounts[2] was removed, retrieve needs to be false
	assert( contas.retrieve( myAccounts[1].get_key(),  acc1) == false );




	std::cout << "\e[34;4m>>> SUCESS ACHIEVED!!\e[0m\n";
	return 0;
}
