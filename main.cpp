#pragma once
#include "MainF/App_Impl.h"
#include <string>
#include "Typedefs.h"

int main()
{
	WAL::Apps::AppImplementation::AppSettings settings("E:\\games\\SHENZHEN IO", "E:\\Garbage", WAL::Resolution_t(1920, 1080));

	WAL::Apps::Interface::IApp* app = new WAL::Apps::AppImplementation(settings);
	app->Init();
	app->Run();
	app->Shutdown();
	return 0;
}