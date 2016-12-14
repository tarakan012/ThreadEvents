#include "Poco/DateTime.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/FIFOBuffer.h"
#include "Poco/ByteOrder.h"
#include <iostream>
#include <string>
#include <vector>
#include "packet.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Buffer.h"

using Poco::ByteOrder;
using Poco::Buffer;
using Poco::Net::SocketAddress;
using Poco::Net::ServerSocket;
using Poco::Net::StreamSocket;
using Poco::DateTime;
using Poco::DateTimeFormatter;
using Poco::FIFOBuffer;



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
	
	encode(931,packet2);
	//std::cout << *(packet1+1);
	
	
	
	
	client.sendBytes(&packet1[0], packet1.size());
	std::vector<UInt8> outbuffer(100);
	//client.receiveBytes(&outbuffer[0],100);
	client.sendBytes(&packet2[0], packet2.size());
	//outbuffer.clear();

	for (; ;) {
		client.receiveBytes(&outbuffer[0], 100);
		if (outbuffer.size() == 2)
		{
			//cout << "111111111111111";
			outbuffer.push_back(0x00);
			outbuffer.push_back(0x02);
			client.sendBytes(&outbuffer[0], 2);
			outbuffer.clear();

		}

	}
	
	 

	
}