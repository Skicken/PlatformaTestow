
#include <ptpch.h>
#include <System.h>

#ifndef DIST 

int main()
{
	
	Platform::Logger::INIT();
	System* system = new System();
	while (system->isRunning())
	{
		system->update();
		system->render();
	}
	delete system;
	return 0;
}
#else
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR lpCmdLine, INT nCmdShow)
{
	System* system = new System();
	while (system->isRunning())
	{
		system->update();
		system->render();
	}
	delete system;
	return 0;
}
#endif


