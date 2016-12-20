#include "packet.h"

void IncomingAuth::handler(Parcer& netes)
{
	netes.readString(_key);
	netes.readString(_login);
	netes.readString(_password);
	netes.readString(_mac);
	netes.readUint16(_isCheat, LittleEndian);
	netes.readUint16(_clientVersion, LittleEndian);

}

void IncomingAuth::process()
{
	//cout << "Login: " <<_login << "Version: " << _clientVersion;
}

int IncomingAuth::packet()
{
	return 0;
}

auto Packet::getPck(int opcode)
{
	return pills[opcode];
}

void OutcomingAuth::handler(Parcer& netes) {
	netes.writeUint16(_errorCode, LittleEndian); // 2
												 //_key.reserve(10);

	vector<UInt8> tempkey = { 0x00, 0x08, 0x7C, 0x35, 0x09, 0x19, 0xB2, 0x50, 0xD3, 0x49 };
	for (int i = 0; i < 10; ++i)
	{
		_key.push_back(tempkey[i]);
	}
	netes.writeBuffer(_key); // 10 ++

	UInt8 sizeCharacter = 3;
	netes.writeUint8(sizeCharacter); // 1
	for (size_t q = 0; q < 3; q++)
	{
		netes.writeUint8(_character[q]._flag); //1 ++14


		netes.writeString(_character[q]._name); // 6 23

		netes.writeString(_character[q]._job); // 6
		netes.writeUint16(_character[q]._level, LittleEndian); // 1

		netes.writeUint16(UInt16(1626), LittleEndian); // 2
		netes.writeUint8(_character[q]._look._synType); // 1
		netes.writeUint16(_character[q]._look._race, LittleEndian); //2
		netes.writeUint8(_character[q]._look._boatCheck); //1

		for (int i = 0; i < 10; ++i)
		{
			netes.writeUint16(_character[q]._look._items[i]._id, LittleEndian); // 2 * 10
																				//_character._look._items[i]._pass.reserve(160);

			for (int j = 0; j < 160; ++j) {
				_character[q]._look._items[i]._pass.push_back(0);
			}
			netes.writeBuffer(_character[q]._look._items[i]._pass); // 160 * 10
		}
		netes.writeUint16(_character[q]._look._hair, LittleEndian); // 10

	}



	netes.writeUint8(_pincode); // 1
	netes.writeUint32(_encription, LittleEndian); // 2
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

void OutcomingAuth::process()
{
	_errorCode = 0;
	_pincode = 1;
	_encription = 0;
	_dwFlag = 12820;
	_character.resize(3);
	Characters charOne, charTwo, charThree;
	_character[0] = charOne;
	_character[1] = charTwo;
	_character[2] = charThree;
}

void Packet::NewPacket() {
	shared_ptr<PacketFactory> od(new OutcomingDate());
	shared_ptr<PacketFactory> ob(new OutcomingAuth());
	shared_ptr<PacketFactory> os(new IncomingAuth());
	unordered_map<int, shared_ptr<PacketFactory>> m = {
		{ 940, od },
		{ 931, ob },
		{ 431, os }
		// ...
	};
	pills = m;
}

void encode(int opcode, vector<UInt8>& packet)
{
	Parcer netes(6000);
	Parcer t_netes(5500);
	Packet p;
	p.NewPacket();
	auto pkg = p.getPck(opcode);
	pkg->process();
	pkg->handler(t_netes);
	int Len = t_netes.sizeBuffer() + 8;
	//cout << "LEN: " << Len; // 33
	PacketHeader header = { Len,128,opcode };
	netes.writeUint16(header.Len, LittleEndian);
	netes.writeUint32(header.UniqueId, BigEndian);
	netes.writeUint16(header.Opcode, LittleEndian);
	//cout << "SizeNetes: " << netes.sizeBuffer(); //8
	netes.writeBuffer(t_netes);
	UInt8* temp = netes.ptrUint8();
	//cout << "SizeNetesOut: " << netes.sizeBuffer(); 

	for (int i = 0; i < netes.sizeBuffer(); i++)
	{
		packet.push_back(*(temp + i));
	}
	//cout << "Element: " << *(packet.begin()+1);

}

void decode(vector<UInt8>& packet)
{
	Parcer netes(packet, 6000);
	Packet p;
	p.NewPacket();
	PacketHeader header;
	netes.readUint16(header.Len, LittleEndian);
	netes.readUint32(header.UniqueId, BigEndian);
	netes.readUint16(header.Opcode, LittleEndian);
	auto pck = p.getPck(header.Opcode);
	pck->handler(netes);
	pck->process();
}