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

	void readUint16(UInt16& value, int endian)
	{
		UInt8 temp[2];
		if (endian == BigEndian) {
			value = static_cast<UInt16>(_buffer[0]) |
					static_cast<UInt16> (_buffer[1]) << 8;
		}
		else {
			value = static_cast<UInt16>(_buffer[0]) << 8 |
					static_cast<UInt16> (_buffer[1]);
		}
		cout << "buffer[1]=" << _buffer[1] << "Opcode: " << value;
		_buffer.read(temp, 2);
	}
	void readUint32(UInt32& value, int endian)
	{
		UInt8 temp[4];

		if (endian == BigEndian) {
			value = static_cast<UInt32>( _buffer[0] ) |
					static_cast<UInt32> ( _buffer[1] ) << 8 |
					static_cast<UInt32> ( _buffer[2] ) << 16 |
					static_cast<UInt32> ( _buffer[1] ) << 24;
		}
		else {
			value = static_cast<UInt32>(_buffer[0]) << 24 |
				static_cast<UInt32> (_buffer[1]) << 16 |
				static_cast<UInt32> (_buffer[2]) << 8 |
				static_cast<UInt32> (_buffer[1]);
		}
		_buffer.read(temp, 4);
	}
	void readString(string value);
private:
	Poco::BasicFIFOBuffer<UInt8> _buffer;
	int _endian;
};

#endif

