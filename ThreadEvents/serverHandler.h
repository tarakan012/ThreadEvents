#pragma once

#ifndef _SERVER_HANDLER_H
#define _SERVER_HANDLER_H
#define NOMINMAX

#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "packet.h"
//#include <pqxx/pqxx>

#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/SocketAddress.h"

using Poco::Net::SocketAddress;
using Poco::Net::ServerSocket;
using Poco::Net::StreamSocket;
using Poco::Thread;

//using namespace pqxx;

class ConnectHundler : public Poco::Runnable
{
public:
	ConnectHundler(connection*, StreamSocket&);
	void run();
public:
	connection* _db;
	StreamSocket _client;
};

#endif //_SERVER_HANDLER_H