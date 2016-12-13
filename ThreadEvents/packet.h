#pragma once
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/FIFOBuffer.h"
#include "Poco/ByteOrder.h"
#include <iostream>
#include <string>
#include <vector>
#include "Poco/Any.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Buffer.h"
#include "network.h"

using namespace std;

using Poco::Any;
using Poco::ByteOrder;
using Poco::Buffer;
using Poco::Net::SocketAddress;
using Poco::Net::ServerSocket;
using Poco::Net::StreamSocket;
using Poco::DateTime;
using Poco::DateTimeFormatter;
using Poco::UInt16;
using Poco::UInt32;
using Poco::UInt8;
using Poco::FIFOBuffer;
#include <unordered_map>
#include <memory>
class PacketFactory {
public:
	virtual int packet() = 0;
	virtual void process() = 0;
	virtual void handler(Parcer&) = 0;
};
class Packet
{
public:
	auto getPck(int);
	void NewPacket();
private:
	//std::unordered_map<int, std::shared_ptr<PacketFactory>> pills;
	std::unordered_map<int, std::shared_ptr<PacketFactory>> pills;
};

auto Packet::getPck(int opcode)
{
	
	
	return pills[opcode];
}



class OutcomingDate : public PacketFactory
{
public:
	int packet();
	void process();
	void handler(Parcer&);
private:
	std::string _time;
};

class Items
{
public:
	
	UInt16 _id = 0;
	std::vector<UInt8> _pass;
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
	UInt8 _flag;
	std::string _name;
	std::string _job;
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
	std::vector<UInt8> _key;
	Characters _character;
};

void OutcomingAuth::process()
{
	_errorCode = 0;
	_pincode = 1;
	_encription = 0;
	_dwFlag = 12800;
	_character._flag = 1;
	_character._name = "Pupkin";
	_character._job = "voujer";
	_character._level = 45;
	_character._look._race = 806;

	
}

void OutcomingAuth::handler(Parcer& netes) {
	netes.writeUint16(_errorCode, LittleEndian); // 2
	//_key.reserve(10);

	std::vector<UInt8> tempkey = { 0x00, 0x08, 0x7C, 0x35, 0x09, 0x19, 0xB2, 0x50, 0xD3, 0x49 };
	for (int i = 0; i < 10; ++i)
	{
		_key.push_back(tempkey[i]);
	}
	netes.writeBuffer(_key); // 10 ++

	UInt8 sizeCharacter = 1;
	netes.writeUint8(sizeCharacter); // 1
	netes.writeUint8(_character._flag); //1 ++14
	

	netes.writeString(_character._name); // 6 23

	netes.writeString(_character._job); // 6
	netes.writeUint8(_character._flag); // 1
	

	netes.writeUint16(UInt16(1626), LittleEndian); // 2
	netes.writeUint8(_character._look._synType); // 1
	netes.writeUint16(_character._look._race, LittleEndian); //2
	netes.writeUint8(_character._look._boatCheck); //1
	std::cout << netes.sizeBuffer() << "qweweqwewqe";
	for (int i = 0; i < 10; ++i)
	{
		netes.writeUint16(_character._look._items[i]._id, LittleEndian); // 2 * 10
		//_character._look._items[i]._pass.reserve(160);
		
		for (int j = 0; j < 160; ++j) {
			_character._look._items[i]._pass.push_back(0);
		}
		netes.writeBuffer(_character._look._items[i]._pass); // 160 * 10
	}
	std::cout << netes.sizeBuffer() << "qweweqwewqe";

	netes.writeUint16(_character._look._hair, LittleEndian); // 10
	netes.writeUint8(_pincode); // 1
	netes.writeUint16(_encription, LittleEndian); // 2
	netes.writeUint32(_dwFlag, LittleEndian); // 4
}

int OutcomingAuth::packet()
{
	return 0;
}

void OutcomingDate::process()
{
	DateTime now;
	now.makeUTC(10800);
	_time = DateTimeFormatter::format(now, "[%m - %d %H:%M:%S:%i]");
}

void OutcomingDate::handler(Parcer& netes)
{
	netes.writeString(_time);
}
int OutcomingDate::packet()
{
	return 0;
}


void Packet::NewPacket() {
	std::shared_ptr<PacketFactory> od(new OutcomingDate());
	std::shared_ptr<PacketFactory> ob(new OutcomingAuth());
	std::unordered_map<int, std::shared_ptr<PacketFactory>> m = {
		{ 940, od },
		{ 931, ob }
		// ...
	};
	pills = m;
}


struct PacketHeader
{
	UInt16 Len;
	UInt32 UniqueId;
	UInt16 Opcode;
};

void encode(int opcode, vector<UInt8>& packet)
{
	Parcer netes(2100);
	Parcer t_netes(2000);
	Packet p;
	p.NewPacket();
	auto pkg = p.getPck(opcode);
	pkg->process();
	pkg->handler(t_netes);
	int Len = t_netes.sizeBuffer() + 8;
	PacketHeader header = { Len,128,940 };
	netes.writeUint16(header.Len,LittleEndian);
	netes.writeUint32(header.UniqueId,BigEndian);
	netes.writeUint16(header.Opcode,LittleEndian);
	//std::cout << netes.ptrUint8()[1];
	netes.writeBuffer(t_netes);
	UInt8* temp = netes.ptrUint8();
	std::cout << netes.sizeBuffer();
	
	for (int i = 0; i < netes.sizeBuffer(); i++)
	{
		packet.push_back(temp[i]);
	}
		
}

void decode(){}

