#include "cppMan.h"
#include <iostream>
#include <string>



int main()
{
	do
	{
		Session MySession;
		// MySession.playCppMan();
		MySession.playHangMan();
	} while (playAgain());
}
