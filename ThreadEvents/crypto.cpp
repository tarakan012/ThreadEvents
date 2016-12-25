#include "crypt.h"
#include <algorithm>

 ustring EncryptPassword(string& key, string& str)

{
	 //std::transform(key.begin(), key.end(), ::toupper);
	 for (auto& c : key) c = toupper(c);
	
	 string substr;
	uchar schedule[3][16][6],
		out[25] = "",
		uKey[25]="",
		uText[9] = "";
	strcpy((char*) (uKey), key.c_str());

	 for (size_t i = 0; i < 3; i++)

	 {
		 
		 substr = str.substr(i * 8, 8);
		 for (size_t i = 0; i < 9; i++)
		 {
			 uText[i] = uchar(0);
		 }
	strcpy((char*)(uText), &substr[0]);

	
	three_des_key_schedule(uKey, schedule, ENCRYPT);
	three_des_crypt(uText,(out+8*i), schedule);


	 }
	//copy(str.begin(), str.end(), uText);
	
	ustring sOut(out);
	 char testchar[]= "qwerty";
	string teststr(testchar);

	//copy(&out[0], &out[9], sOut);
	//strcpy(sOut.c_str(), (char*)out);

	return sOut;
}