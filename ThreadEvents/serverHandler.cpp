#include "serverHandler.h"

ConnectHundler::ConnectHundler(connection* db, StreamSocket& client) :_db(db), _client(client)
{
}

void ConnectHundler::run()
{
	vector<UInt8> packet1;
	vector<UInt8> outbuffer(100);
	encode(940, packet1);
	_client.sendBytes(&packet1[0], packet1.size());
	int firstSize = _client.receiveBytes(&outbuffer[0],100);
}