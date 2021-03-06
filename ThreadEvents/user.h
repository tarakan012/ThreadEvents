#pragma once

#include <string>
#include <pqxx/pqxx>

using namespace std;
using namespace pqxx;

class User
{
public:
	User(connection* db) :_db(db) {};
	string getByName(string&);
	void update(int);
	void changeIsActive(bool);
private:
	string _login;
	string _password;
	bool _isActive;
	connection* _db;
	
};