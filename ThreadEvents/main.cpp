

//#define NOMINMAX

//#include "packet.h"
//#include "user.h"


//#include "database.h"
//#include <pqxx/pqxx>
#include "crypt.h"
#include <stdio.h>
#include "server.h"



//using Poco::Timespan;






int main(int argc, char* argv[])
{
	if (argc = 1) {
		string configPath = "resource/config.ini";
	}
	string sKey = "5f4dcc3b5aa765d61d8327de";
	string sText = "[8-15 17";
	EncryptPassword(sKey, sText);
	
	Application app;
	app.run();
	//Database us;
	
	/*
	pqxx::result r = txn.exec("SELECT login from public.user;");
	string str = r[0][0].c_str();
	cout << str;*/
	//us.getByName("tarakan");
	
	
	
	//vector<UInt8> packet2;
	

	//encode(931, packet2);
	//cout << *(packet1+1);




	//client.sendBytes(&packet1[0], packet1.size());
	//vector<UInt8> outbuffer(100);
	//int firstSize = client.receiveBytes(&outbuffer[0],100);
	//cout << "First size: " << firstSize;
	//decode(outbuffer);
	//client.sendBytes(&packet2[0], packet2.size());
	////outbuffer.clear();
	//

	//int n = client.receiveBytes(&outbuffer[0], 100);
	//while (n > 0){
	//	if (n == 2)
	//	{
	//		outbuffer.clear();

	//		outbuffer.push_back(0x00);
	//		outbuffer.push_back(0x02);
	//		client.sendBytes(&outbuffer[0], 2);
	//		client.receiveBytes(&outbuffer[0], 100);
	//		Timespan span(250000);

	//	}
	//}
	return 0;
}

	 

	
