#pragma once

#ifndef PLAYER_H
#define PLAYER_H



#include <string>

using namespace std;

//type Player struct {
//	ID       int64
//		Stats    Stats
//		Position Position
//
//		Buffers *core.Buffers
//		Error   *support.CustomError
//		Time    string
//}

class Player
{
public:
	void changeTime(string&);
private:
	int _id;
	string _time;
};

#endif // !PLAYER_H
