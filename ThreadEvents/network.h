#pragma once
#include "Poco/ByteOrder.h"
#include "Poco/FIFOBuffer.h"

using Poco::ByteOrder;
using Poco::FIFOBuffer;
using Poco::UInt16;
using Poco::UInt32;
using Poco::UInt8;
const enum
{
	LittleEndian,
	BigEndian
};

class Parcer
{
public:
	Parcer(int);
	Parcer* setEndian(int);
	int sizeBuffer();
	Parcer* writeUint16(UInt16,int);
	void writeString(std::string);
	void writeUint32(UInt32,int);
	void writeBuffer(Parcer&);
	void writeBuffer(std::vector<UInt8>&);
	void resetBuffer();
	void writeUint8(UInt8&);
	UInt8* ptrUint8();
private:
	Poco::BasicFIFOBuffer<UInt8> _buffer;
	int _endian;
};
