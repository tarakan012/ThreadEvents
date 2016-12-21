#include "server.h"


Application::Application()
{
	AutoPtr<IniFileConfiguration> pConf(new IniFileConfiguration("config.ini"));
	string dbname = pConf->getString("database.name");
	string host = pConf->getString("database.ip");
	string user = pConf->getString("database.user");
	string password = pConf->getString("database.password");


	_db = new connection("dbname=" + dbname + " host=" + host + " user=" + user+ " password=" + password);
	//sql = new work(*db);
}

void Application::run()
{
	SocketAddress Address("127.0.0.1:1973");
	ServerSocket Listen(Address);
	for (; ;)
	{
		StreamSocket client = Listen.acceptConnection();
		ConnectHundler ch(_db, client);
		
		Thread thread;
		thread.start(ch);
		thread.join();

	}

}


