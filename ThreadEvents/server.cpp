#include "server.h"


Application::Application()
{
	AutoPtr<IniFileConfiguration> pConf(new IniFileConfiguration("config.ini"));
	string dbname = pConf->getString("database.name");
	string host = pConf->getString("database.ip");
	string user = pConf->getString("database.user");
	string password = pConf->getString("database.password");


	_db = new connection("dbname=" + dbname + " host=" + host + " user=" + user+ " password=" + password);
}

void Application::run()
{
	SocketAddress Address("127.0.0.1:1973");
	ServerSocket Listen(Address);
	
	for (; ;)
	{
		StreamSocket client = Listen.acceptConnection();

		AutoPtr<ConsoleChannel> console(new ConsoleChannel);
		AutoPtr<PatternFormatter> formater(new PatternFormatter);
		formater->setProperty("pattern", "%Y-%m-%d %H:%M:%S %s: %t");
		AutoPtr<FormattingChannel> formatingChannel(new FormattingChannel(formater, console));
		Logger::root().setChannel(formatingChannel);

		Logger::get("Console").information("Connection from " + client.peerAddress().toString());
		
		ConnectHundler ch(_db, client);
		
		Thread thread;
		thread.start(ch);
		thread.join();

	}

}


