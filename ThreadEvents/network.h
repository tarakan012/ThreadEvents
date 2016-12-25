#pragma once

#ifndef _NETWORK_H
#define _NETWORK_H

#include "Poco/FIFOBuffer.h"
#include <string>
#include <sstream>

using Poco::FIFOBuffer;
using Poco::UInt16;
using Poco::UInt32;
using Poco::UInt8;

using namespace std;

typedef basic_string<uint8_t> ustring;


const enum
{
	LittleEndian,
	BigEndian
};

class Parcer
{
public:
	Parcer(int);
	Parcer(vector<UInt8>&,int);
	Parcer* setEndian(int);
	int sizeBuffer();
	Parcer* writeUint16(UInt16,int);
	void writeString(string);
	void writeUint32(UInt32,int);
	void writeBuffer(Parcer&);
	void writeBuffer(vector<UInt8>&);
	void resetBuffer();
	void writeUint8(UInt8&);
	UInt8* ptrUint8();

	void readUint16(UInt16&, int);
	
	void readUint32(UInt32&, int);
	
	void readString(string& value);
	void readByte(ustring & str);
private:
	Poco::BasicFIFOBuffer<UInt8> _buffer;
	int _endian;
};

#endif //_NETWORK_H

