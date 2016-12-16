


#include "packet.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/SocketAddress.h"


#include <sstream>


using Poco::Timespan;

using Poco::Net::SocketAddress;
using Poco::Net::ServerSocket;
using Poco::Net::StreamSocket;




void main()
{
	
	

	SocketAddress Address("127.0.0.1:1973");
	ServerSocket Listen(Address);
	StreamSocket client = Listen.acceptConnection();
	const int size = 2100;
	const int size2 = 2100;
	vector<UInt8> packet2;
	vector<UInt8> packet1;
	encode(940, packet1);

	encode(931, packet2);
	//cout << *(packet1+1);




	client.sendBytes(&packet1[0], packet1.size());
	vector<UInt8> outbuffer(100);
	int firstSize = client.receiveBytes(&outbuffer[0],100);
	cout << "First size: " << firstSize;
	decode(outbuffer);
	client.sendBytes(&packet2[0], packet2.size());
	//outbuffer.clear();
	

	int n = client.receiveBytes(&outbuffer[0], 100);
	while (n > 0){
		if (n == 2)
		{
			outbuffer.clear();

			outbuffer.push_back(0x00);
			outbuffer.push_back(0x02);
			client.sendBytes(&outbuffer[0], 2);
			client.receiveBytes(&outbuffer[0], 100);
			Timespan span(250000);

		}
	}
}

	 

	
