#pragma once

#ifndef _SERVER_H
#define _SERVER_H
//#include "serverHandler.h"
#include <pqxx/pqxx>
#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "packet.h"


#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/SocketAddress.h"

using Poco::Net::SocketAddress;
using Poco::Net::ServerSocket;
using Poco::Net::StreamSocket;
using Poco::Thread;

using namespace pqxx;

class Application
{
public:
	Application();
	void run();
	//void NewDatabaseInfo()
private:
	connection* _db;
};



#endif //_SERVER_H