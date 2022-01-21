#pragma once
#include "MainF/App_Impl.h"

int main()
{
	WAL::Apps::Interface::IApp* app = new WAL::Apps::AppImplementation();
	app->Init();
	app->Run();
	app->Shutdown();
	return 0;
}