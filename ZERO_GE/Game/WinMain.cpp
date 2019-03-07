#include <Engine/Inc/GameApp.h>
#include <Core/Inc/Core.h>

//Include States
#include "FrontEnd.h"
#include "Scene_1.h"

//class Car
//{
//public:
//	META_CLASS_DECLARE
//	int position;
//	float fuel;
//};
//
//class Ferrari : public Car
//{
//public:
//	META_CLASS_DECLARE
//	bool turbo;
//};
//
//META_CLASS_BEGIN(Car)
//	META_FIELD_BEGIN
//		META_FIELD(position, "Position")
//		META_FIELD(fuel, "Fuel")
//	META_FIELD_END
//META_CLASS_END
//
//META_DERIVED_BEGIN(Ferrari, Car)
//	META_FIELD_BEGIN
//	META_FIELD(turbo, "Turbo")
//	META_FIELD_END
//META_CLASS_END

using namespace ZERO;
using namespace ZERO::Engine;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	/*Car::StaticGetMetaClass()->Dump();
	Ferrari::StaticGetMetaClass()->Dump();*/

	GameApp myApp;

	myApp.AddState<FrontEnd>();
	myApp.AddState<Scene1>();
	
	myApp.Initialize(hInstance, "Hello State && XML_Component!");

	while (myApp.IsRunning())
	{
		myApp.Update();
	}

	myApp.Terminate();

	return 0;
}