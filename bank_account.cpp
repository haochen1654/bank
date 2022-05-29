#include "bank_account.h"

namespace {
	using bank::entity::BankAccount;
} // namespace

namespace bank {
	namespace entity {
		void BankAccount::set_account_number(const int account_number)
		{
			account_number_ = account_number;
		}

		void BankAccount::set_last_name(std::string_view last_name)
		{
			last_name_ = last_name;
		}
		void BankAccount::set_first_name(std::string_view first_name)
		{
			first_name_ = first_name;
		}
		void BankAccount::set_balance(const double balance)
		{
			balance_ = balance;
		}
		int BankAccount::account_numer() const
		{
			return account_number_;
		}
		std::string BankAccount::first_name() const
		{
			return first_name_;
		}
		std::string BankAccount::last_name() const
		{
			return last_name_;
		}
		double BankAccount::balance() const
		{
			return balance_;
		}
	} // namespace enity
} // namespace bank