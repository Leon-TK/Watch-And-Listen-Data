#pragma once
//#include "MainF/IApp.h"
#include "MainF/App_Impl.h"

int main()
{
	WAL::IApp* app = new WAL::AppImplementation();
	app->Init();
	app->Run();
	app->Shutdown();
	return 0;
}