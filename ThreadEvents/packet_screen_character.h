#pragma once

#include "packet.h"

#ifndef PACKET_SCREEN_CHARACTER_H
#define PACKET_SCREEN_CHARACTER_H
class IncomingDeleteCharacter : public PacketFactory
{
public:
	int packet(connection* db) { _db = db; return 0; };
	int process(Player&);
	void handler(Parcer&);
private:
	string _name;
	string _secret;
	connection* _db;
};

class OutcomingDeleteCharacter : public PacketFactory
{
public:
	int packet(connection* db) { _db = db; return 0; };
	int process(Player&);
	void handler(Parcer&);
private:
	UInt16 _error_code;
	connection* _db;

};

class IncomingNewCharacter : public PacketFactory
{
public:
	int packet(connection* db) { _db = db; return 0; };
	int process(Player&);
	void handler(Parcer&);
private:
	string _map;
	UInt16 _len_look;
	CharacterLook _look;
	connection* _db;
};

class OutcomingNewCharacter : public PacketFactory
{
public:
	int packet(connection* db) { _db = db; return 0; };
	int process(Player&);
	void handler(Parcer&);
private:
	UInt16 _error_code;

	connection* _db;
};
#endif