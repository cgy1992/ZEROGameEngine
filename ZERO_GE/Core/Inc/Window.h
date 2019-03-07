//==============================================================================
//Filename: Window.h
//Created By: Erick Tavares
//==============================================================================

#ifndef INCLUDED_CORE_WINDOW_H
#define INCLUDED_CORE_WINDOW_H


namespace ZERO
{
namespace Core	
{
class Window
{

public:
	Window();
	~Window();

	void Initialize(HINSTANCE instance, LPCSTR appName, uint32_t width, uint32_t height);
	void Terminate();
	bool ProcessMessage();
	uint32_t GetWindowWidth() { return mWidth; }
	uint32_t GetWindowHeight() { return mHeight; }

	HWND GetWindowHandle() const { return mWindow; }

private:
	HINSTANCE mInstance;
	HWND mWindow;
	std::string mAppName;
	uint32_t mWidth;
	uint32_t mHeight;

};
}
}

#endif // !INCLUDED_CORE_WINDOW_H
