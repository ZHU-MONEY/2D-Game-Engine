#pragma once
#include "GLib/GLib.h"

void AcceptKey2(unsigned int i_VKeyID, bool bWentDown);
class InputReader
{
	

public:
	static InputReader* Create();
	inline static InputReader* GetInstance() { return instance_; };
	static void Destroy();
	void Run();

	static bool	isKey_W_Down;
	static bool isKey_A_Down;
	static bool	isKey_S_Down;
	static bool	isKey_D_Down;
	static bool	isKey_Q_Down;

private:
	static InputReader* instance_;
	InputReader();
	~InputReader();
};