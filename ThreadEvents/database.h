#pragma once
#include <pqxx/pqxx>
#include <string>
#include <iostream>

using namespace std;
using namespace pqxx;

class Database
{
public:
	Database();
	void getByName(const string&);
private:
	connection* db;
	//work* sql;

};
