#include "server.h"


Application::Application()
{
	_db = new connection("dbname=noterius host=localhost user=nota password=notadefault");
	//sql = new work(*db);
}

void Application::run()
{
	SocketAddress Address("127.0.0.1:1973");
	ServerSocket Listen(Address);
	for (; ;)
	{
		StreamSocket client = Listen.acceptConnection();
		//ConnectHundler ch(_db, client);
		//Thread thread;
		//thread.start(ch);

	}

}


