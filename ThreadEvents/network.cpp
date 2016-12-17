#include "network.h"

void Parcer::readUint16(UInt16& value, int endian)
{
	endian = LittleEndian;
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
void Parcer::readUint32(UInt32& value, int endian)
{
	endian = BigEndian;
	UInt8 temp[4];

	if (endian == BigEndian) {
		value = static_cast<UInt32>(_buffer[0]) |
			static_cast<UInt32> (_buffer[1]) << 8 |
			static_cast<UInt32> (_buffer[2]) << 16 |
			static_cast<UInt32> (_buffer[1]) << 24;
	}
	else {
		value = static_cast<UInt32>(_buffer[0]) << 24 |
			static_cast<UInt32> (_buffer[1]) << 16 |
			static_cast<UInt32> (_buffer[2]) << 8 |
			static_cast<UInt32> (_buffer[1]);
	}
	_buffer.read(temp, 4);
}

void Parcer::readString(string value)
{
	UInt8 temp[2];

	stringstream stream("");
	UInt8 array[100];
	UInt16 lnString;
	if (_endian == BigEndian) {
		lnString = static_cast<UInt16>(_buffer[0]) |
			static_cast<UInt16> (_buffer[1]) << 8;
	}
	else {
		lnString = static_cast<UInt16>(_buffer[0]) << 8 |
			static_cast<UInt16> (_buffer[1]);
	}
	cout << " buffer[0]= " << int(_buffer[0]) << " buffer[1]= " << int(_buffer[1]);
	_buffer.read(temp, 2);

	_buffer.read(array, lnString);
	for (size_t i = 0; i < lnString; i++)
	{
		stream << array[i];
	}
	value = stream.str();
	cout << " String: " << value;
	
}


UInt8* Parcer::ptrUint8()
{
	return _buffer.begin();
}

void Parcer::writeBuffer(Parcer& parcer)
{
	_buffer.write(parcer._buffer.begin(), parcer._buffer.used());
}

void Parcer::writeBuffer(vector<UInt8>& ptr)
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
	//cout << _buffer.used();
	return _buffer.used();
}

Parcer::Parcer(int size) : _endian(LittleEndian),
_buffer(size, true)
{

}

Parcer::Parcer(vector<UInt8>& packet, int size) : _endian(LittleEndian),
_buffer(size, true)
{
	_buffer.write(&packet[0], packet.size());
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
	//cout << value << "**";
	if (_endian == BigEndian) {
		buf[0] = value;
		buf[1] = value >> 8;
	}
	else {
		buf[0] = value >> 8;
		buf[1] = value;
	}
	//cout << int(buf[0]) << "| |" << int(buf[1]) << "| |";
	_buffer.write(buf, 2);

	return this;
}

void Parcer::writeString(string value)
{
	value += char(0);

	UInt16 ln = value.size();
	//cout << ln;
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
	//cout << _buffer.size();
	vector<UInt8> ints(begin(value), end(value)); // ¬роде бы пишет \0
	for(int i = 0; i < ln;i++)
	{
		//cout << ints[i];
	}

	_buffer.write(&ints[0], ints.size());
	for (int i = 0; i < ln; i++)
	{
		//cout << int(_buffer[i]);
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
