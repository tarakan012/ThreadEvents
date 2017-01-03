#include "serverHandler.h"

ConnectHundler::ConnectHundler(connection* db, StreamSocket& client) :_db(db), _client(client)
{
}

void ConnectHundler::run()
{
	vector<UInt8> packet1;
	vector<UInt8> outbuffer(5000);
	Packet p(_db);
	vector<UInt8> pong = { 0x00,0x02 };
	p.encode(940, packet1);
	_client.sendBytes(&packet1[0], packet1.size());
	for (;;) {
		int n = _client.receiveBytes(&outbuffer[0], 5000);
		if (n == 2)
		{
						
			_client.sendBytes(&pong[0], 2);
		}
		else {
			int opcode = p.decode(outbuffer);
			//outbuffer.clear();
			packet1.clear();
			p.encode(opcode, packet1);
			_client.sendBytes(&packet1[0], packet1.size());

		}
	}
}