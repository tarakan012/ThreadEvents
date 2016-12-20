#pragma once

#include <string>
#include <pqxx/pqxx>

using namespace std;
using namespace pqxx;

class User
{
public:
	void getByName(string, work&);
private:
	string _login;
	string _password;
	bool _isActive;
	
};