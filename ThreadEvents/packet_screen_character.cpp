#include "packet_screen_character.h"

int IncomingDeleteCharacter::process(Player &)
{
	return OP_SERVER_DELCHA;
}

void IncomingDeleteCharacter::handler(Parcer & netes)
{
	netes.readString(_name);
	netes.readString(_secret);

}

int OutcomingDeleteCharacter::process(Player &)
{
	return 0;
}

void OutcomingDeleteCharacter::handler(Parcer & netes)
{
	_error_code = 0;
	netes.writeUint16(_error_code, LittleEndian);
}

int IncomingNewCharacter::process(Player &)
{
	return OP_SERVER_NEWCHA;
}

void IncomingNewCharacter::handler(Parcer & netes)
{
}

int OutcomingNewCharacter::process(Player &)
{
	return 0;
}

void OutcomingNewCharacter::handler(Parcer & netes)
{
	_error_code = 0;
	netes.writeUint16(_error_code, LittleEndian);
}
