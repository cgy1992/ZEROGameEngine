#ifndef INCLUDED_GRAPHICS_GUI_H
#define INCLUDED_GRAPHICS_GUI_H

namespace ZERO
{
namespace Gui
{

void Initialize(HWND window);
void Terminate();
void BeginRender(float deltaTime);
void EndRender();

}//!namespace Graphics
}//!namespace ZERO

#endif //!INCLUDED_GRAPHICS_GUI_H