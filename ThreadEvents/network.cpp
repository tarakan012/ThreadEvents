#include "network.h"

UInt8* Parcer::ptrUint8()
{
	return _buffer.begin();
}

void Parcer::writeBuffer(Parcer& parcer)
{
	_buffer.write(parcer._buffer.begin(), parcer._buffer.size());
}

void Parcer::writeBuffer(std::vector<UInt8>& ptr)
{
	_buffer.write(&ptr[0], ptr.size());
}

void Parcer::resetBuffer()
{

}

void Parcer::writeUint8(UInt8& value)
{
	_buffer.write(&value, 1);
}

int Parcer::sizeBuffer()
{
	//std::cout << _buffer.used();
	return _buffer.used();
}

Parcer::Parcer(int size) : _endian(LittleEndian),
_buffer(size, true)
{

}
Parcer* Parcer::setEndian(int endian)
{
	_endian = endian; // _endian(endian) ?
	return this;
}

Parcer* Parcer::writeUint16(UInt16 value, int endian)
{
	_endian = endian;
	UInt8 buf[2];
	//std::cout << value << "**";
	if (_endian == BigEndian) {
		buf[0] = value;
		buf[1] = value >> 8;
	}
	else {
		buf[0] = value >> 8;
		buf[1] = value;
	}
	//std::cout << int(buf[0]) << "| |" << int(buf[1]) << "| |";
	_buffer.write(buf, 2);

	return this;
}

void Parcer::writeString(std::string value)
{
	value += char(0);

	UInt16 ln = value.size();
	//std::cout << ln;
	UInt8 buf[2];

	if (_endian == BigEndian) {
		buf[0] = ln;
		buf[1] = ln >> 8;
	}
	else {
		buf[0] = ln >> 8;
		buf[1] = ln;
	}

	_buffer.write(&buf[0], 2);
	//std::cout << _buffer.size();
	std::vector<UInt8> ints(std::begin(value), std::end(value)); // ¬роде бы пишет \0
	for(int i = 0; i < ln;i++)
	{
		//std::cout << ints[i];
	}

	_buffer.write(&ints[0], ints.size());
	for (int i = 0; i < ln; i++)
	{
		//std::cout << int(_buffer[i]);
	}
	
}

void Parcer::writeUint32(UInt32 value, int endian)
{
	_endian = endian;
	UInt8 buf[4];

	if (_endian == BigEndian) {
		buf[0] = value;
		buf[1] = value >> 8;
		buf[2] = value >> 16;
		buf[3] = value >> 24;
	}
	else {
		buf[0] = value >> 24;
		buf[1] = value >> 16;
		buf[2] = value >> 8;
		buf[3] = value;
	}

	_buffer.write(buf, 4);
}
