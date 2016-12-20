#pragma once

#ifndef _PACKET_H
#define _PACKET_H



#include "Poco/DateTime.h"
#include "Poco/DateTimeFormatter.h"

#include "Poco/FIFOBuffer.h"

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#include "network.h"

using Poco::DateTime;
using Poco::DateTimeFormatter;
using Poco::UInt16;
using Poco::UInt32;
using Poco::UInt8;
using Poco::FIFOBuffer;

using namespace std;


class PacketFactory {
public:
	virtual int packet() = 0;
	virtual void process() = 0;
	virtual void handler(Parcer&) = 0;
};

class IncomingAuth : public PacketFactory
{
public:
	int packet();
	void process();
	void handler(Parcer&);
private:
	string _key;
	string _login;
	string _password;
	string _mac;
	UInt16 _isCheat;
	UInt16 _clientVersion;
};



class Packet
{
public:
	auto getPck(int);
	void NewPacket();
private:
	unordered_map<int, shared_ptr<PacketFactory>> pills;
};


class OutcomingDate : public PacketFactory
{
public:
	int packet();
	void process();
	void handler(Parcer&);
private:
	string _time;
};

class Items
{
public:
	
	UInt16 _id = 0;
	vector<UInt8> _pass;
};

class CharacterLook
{
public:
	UInt8 _synType = 0;
	UInt16 _race;
	UInt8 _boatCheck = 0;
	Items _items[10];
	UInt16 _hair = 0;

};

class Characters
{
public:
	Characters() {
		_flag = 1;
		_name = "Haruki";
		_job = "golang-ru.slack.com";
		_level = 1000;
		_look._race = 806;
	}
	UInt8 _flag;
	string _name;
	string _job;
	UInt16 _level;
	CharacterLook _look;
};

class OutcomingAuth : public PacketFactory
{
public:
	
	int packet();
	void process();
	void handler(Parcer&);
private:
	UInt16 _errorCode;
	UInt8 _pincode;
	UInt32 _encription;
	UInt32 _dwFlag;
	vector<UInt8> _key;
	vector<Characters> _character;
};





struct PacketHeader
{
	UInt16 Len;
	UInt32 UniqueId;
	UInt16 Opcode;
};



#endif // _PACKET_H

