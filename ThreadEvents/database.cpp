#include "database.h"

Database::Database()
{
	db = new connection("dbname=noterius host=localhost user=nota password=notadefault");
	//sql = new work(*db);
}

void Database::getByName(const string& login)
{
	work sql(*db);
	result r = sql.exec("SELECT * from public.user WHERE login='tarakan'");

	cout << r[0][0].as<string>();
	//cout << r[0][1].as<string>();
	//cout << r[0][2].as<string>();
}