#include "user.h"
#include <iostream>

string User::getByName(string& login)
{
	work sql(*_db);

	result r = sql.exec("SELECT * from public.user WHERE login="+sql.quote(login));
	if (r.empty())
	{
		return "empty";
	}
	string password = r[0]["password"].as<string>();
	_isActive = r[0]["is_active"].as<bool>();
	cout << "PASSWORD:" << r[0][2].as<string>() << endl;
	return password;
	
	
}

void User::update(int id)
{
	work sqll(*_db);
	auto convert = [](bool b) -> string {return b ? "true" : "false"; };
	string str = "UPDATE public.user SET is_active='" + convert(_isActive) + "'" + " WHERE id=" + sqll.quote(id);
	result r = sqll.exec("UPDATE public.user SET is_active='false' WHERE id='1'");
	sqll.commit();
	cout << str;
}

void User::changeIsActive(bool b)
{
	_isActive = b;
}
