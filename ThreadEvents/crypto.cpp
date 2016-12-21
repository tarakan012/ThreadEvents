#include "crypt.h"

 void EncryptPassword(string& key, string& str) 
{
	uchar schedule[3][16][6],
		out[8],
		uKey[24],
		uText[8];
	strcpy((char*) (uKey), key.c_str());
	strcpy((char*)(uText), str.c_str());
	
	three_des_key_schedule(uKey, schedule, 1);
	three_des_crypt(uText,out, schedule);
	//string sOut = (char*)out;
	//strcpy((char*)(sOut.c_str()), out);

	cout << out;
}