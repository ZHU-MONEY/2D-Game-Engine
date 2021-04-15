#include "InputReader.h"

InputReader* InputReader::instance_ = nullptr;

bool InputReader::isKey_W_Down = false;
bool InputReader::isKey_A_Down = false;
bool InputReader::isKey_S_Down = false;
bool InputReader::isKey_D_Down = false;
bool InputReader::isKey_Q_Down = false;
void AcceptKey2(unsigned int i_VKeyID, bool bWentDown)
{
		//const size_t	lenBuffer = 65;
		//char			Buffer[lenBuffer];
		//sprintf_s(Buffer, lenBuffer, "000  %s\n", InputReader::isKey_A_Down ? "A is downFUCK" : "A is upFUCK");
		//OutputDebugStringA(Buffer);

	switch (i_VKeyID)
	{
		//W 57---hexadecimal   87---decimal
	case 87:
		InputReader::isKey_W_Down = bWentDown;
		break;

		//A 41---hexadecimal	65---decimal
	case 65:
		InputReader::isKey_A_Down = bWentDown;
		break;

		//S  53---hexadecimal   83---decimal
	case 83:
		InputReader::isKey_S_Down = bWentDown;
		break;

		//D   44---hexadecimal  68---decimal
	case 68:
		InputReader::isKey_D_Down = bWentDown;
		break;

		//Q 
	case 81:
		InputReader::isKey_Q_Down = bWentDown;
		break;
	}
}

InputReader::InputReader()
{
	GLib::SetKeyStateChangeCallback(AcceptKey2);
}

InputReader::~InputReader()
{
}

InputReader* InputReader::Create()
{
	if (!instance_)
	{
		instance_ = new InputReader();
	}
	return instance_;
}

void InputReader::Destroy()
{
	if (instance_)
	{
		delete instance_;
		instance_ = nullptr;
	}
}

void InputReader::Run()
{
}
