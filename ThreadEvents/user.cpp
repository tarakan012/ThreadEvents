#include "user.h"
#include <iostream>

string User::getByName(string& login)
{
	cout << "LOGIN: " << login << endl;
	work sql(*_db);

	result r = sql.exec("SELECT password from public.user WHERE login='"+login+"'");
	if (r.empty())
	{
		return "empty";
	}
	string password = r[0][0].as<string>();

	cout << "PASSWORD:" << r[0][0].as<string>() << endl;
	return password;
	
	
}
