#include <iostream>
#include <cassert>
#include <functional>
#include <fstream>
#include <tuple>

#include "hash.hpp"

struct Account{

	using AcctKey = int;

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
		return account_num_;
	}

	//! @brief Prints an Account.
	inline friend std::ostream &operator<< ( std::ostream & _os, const Account & _acc )
    {
        _os << "\n\tClient: < " << _acc.client_name_ <<
            " >\n\tBank: < "   << _acc.bank_code_ <<
            " >\n\tBranch: < " << _acc.agency_num_ <<
            " >\n\tNumber: < " << _acc.account_num_ <<
            " >\n\tBalance: < " << _acc.balance_ << " >\n";
            
        return _os;
	}
};

struct KeyHash {

	std::size_t operator()( const Account::AcctKey& key_ ) const
	{
		return std::hash<int>()( key_ );
	}
};

struct KeyEqual {

	bool operator()( const Account::AcctKey & lhs_,
					 const Account::AcctKey & rhs_ ) const
	{
		return lhs_ == rhs_;
	}
};
/*
struct KeyHash2 {

	std::size_t operator()( const Account::AcctKey& key_ ) const
	{
		return std::hash<std::string>()( key_.first ) xor
			   std::hash<int>()( key_.second );
	}
};

struct KeyEqual2 {

	bool operator()( const Account::AcctKey& lhs_,
					 const Account::AcctKey& rhs_ ) const
	{
		return lhs_.first == rhs_.first and lhs_.second == rhs_.second;
	}
};

struct KeyHash3 {

	std::size_t operator()( const Account::AcctKey& key_ ) const
	{
		return std::hash<std::string>()( std::get<0>(key_) ) xor
			   std::hash<int>()( std::get<1>(key_) ) xor
			   std::hash<int>()( std::get<2>(key_) ) xor
			   std::hash<int>()( std::get<3>(key_) );
	}
};

struct KeyEqual3 {

	bool operator()( const Account::AcctKey& lhs_,
					 const Account::AcctKey& rhs_ ) const
	{
		return std::get<0>(lhs_) == std::get<0>(rhs_) and
			   std::get<1>(lhs_) == std::get<1>(rhs_) and
			   std::get<2>(lhs_) == std::get<2>(rhs_) and
			   std::get<3>(lhs_) == std::get<3>(rhs_);
	}
};
*/

int main( int argc, char **argv ) {
	std::cout << "\e[32;4m>>> Bank Account Management Implemenation\e[0m\n";
	
	Account acct( "Nino", 1, 1682, 5, 10000 );

	Account myAccounts[] =
		{
                {"Carla Bruni", 1, 1999, 44876, 10000.f},
                {"Elis Regina", 1, 1999, 45794, 0.f},
                {"Jorge Ben jor", 2, 557, 87629, 1050.f},
                {"Benito de Paula", 12, 331, 1231, 850.f},
                {"Hans Otto", 4, 666, 5, 530.f}
		};

	HashTbl< Account::AcctKey, Account > contas(15);

	assert( contas.count() == 0 );

	contas.insert( myAccounts[2].get_key(), myAccounts[2] );
	contas.insert( myAccounts[0].get_key(), myAccounts[0] );
	contas.insert( myAccounts[3].get_key(), myAccounts[3] );
	contas.insert( myAccounts[1].get_key(), myAccounts[1] );
	contas.insert( myAccounts[4].get_key(), myAccounts[4] );

	contas.print();

	std::cout << "\e[34;4m>>> SUCESS ACHIEVED!!\e[0m\n";
	return 0;
}
