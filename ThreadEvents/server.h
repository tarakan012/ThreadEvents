#pragma once

#ifndef _SERVER_H
#define _SERVER_H
#define NOMINMAX

#include "serverHandler.h"
#include "Poco/Thread.h"
#include "Poco/Runnable.h"

#include"Poco/Logger.h"
#include "Poco/ConsoleChannel.h"
#include "Poco/AutoPtr.h"


#include "Poco/PatternFormatter.h"
#include "Poco/FormattingChannel.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Util/IniFileConfiguration.h"
#include "Poco/Net/SocketAddress.h"

using Poco::Net::SocketAddress;
using Poco::AutoPtr;
using  Poco::PatternFormatter;
using Poco::FormattingChannel;
using Poco::ConsoleChannel;
using Poco::Util::IniFileConfiguration;
using Poco::Net::ServerSocket;
using Poco::Net::StreamSocket;
using Poco::Thread;
using Poco::Logger;

//using namespace pqxx;


struct ConfigBase
{
	string _ip;
	string _port;
	string _debuge;
};

struct ConfigDatabase
{
	string _ip;
	string _user;
	string _password;
	string _name;
	string _timeOutSave;
	
};

class Config
{
private:

	ConfigBase _base;
	ConfigDatabase _database;
};


class Application
{
public:
	Application();
	void run();
	//void NewDatabaseInfo()
private:
	connection* _db;
	Config _config;
};



#endif //_SERVER_H