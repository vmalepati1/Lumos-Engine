#include "Platform/Window.h"
#include "Platform/Timer.h"

#include "System/Memory/Memory.h"
#include "System/Memory/PoolAllocator.h"
#include "System/Memory/MemoryManager.h"

#include "Platform/Application.h"
#include "System/VFS.h"

using namespace lumos;
using namespace maths;
using namespace platform;
using namespace internal;

class Sandbox : public Application {

public:
	Sandbox()
		: Application("Sandbox", { 960, 540, false, false })
	{
	}

	~Sandbox()
	{
	}

	void Initialize() override
	{
		Application::Initialize();
	}

};

int main() {
	Sandbox sandbox;
	sandbox.Start();
	return 0;
}