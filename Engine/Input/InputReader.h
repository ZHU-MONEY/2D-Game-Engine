#pragma once

class InputReader
{
public:
	static InputReader* Create();
	inline static InputReader* GetInstance() { return instance_; };
	static void Destroy();
	void Run();

private:
	static InputReader* instance_;
	InputReader();
	~InputReader();
};