#include "stdafx.h"
#include "DialController.h"

#include <windows.foundation.h>
#include <windows.foundation.numerics.h>
#include <windows.foundation.collections.h>
#include <windows.ui.input.h>
#include <windows.h>
#include <Windowsx.h>
//#include <tchar.h>
//#include <StrSafe.h>
//#include <wrl\module.h>
//#include <wrl\event.h>
//#include <wrl\implements.h>
#include <roapi.h>
#include <wrl.h>

using namespace ABI::Windows::UI::Input;
using namespace ABI::Windows::Foundation;
using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;


DialController::DialController() : obj(NULL), hwnd(NULL), processID(0), threadID(0)
{
}

DialController::~DialController()
{
}

BOOL CALLBACK EnumWindowsProc(_In_ HWND   hwnd, _In_ LPARAM lParam)
{
  DialController* dial = (DialController*)lParam;
  DWORD pid = GetWindowThreadProcessId(hwnd, NULL);
  if ((pid == dial->getProcessID()) || (pid == dial->getThreadID()))
  {
    dial->setHWND(hwnd);
    return FALSE;
  }
  return TRUE;
}

bool DialController::init(DialCallback* obj)
{
  this->obj = obj;

  // detect the window from the process id
  HANDLE hProc = GetCurrentProcess();
  processID = GetProcessId(hProc);
  threadID = GetCurrentThreadId();
  EnumWindows(EnumWindowsProc, (LPARAM)this);

  return true;
}

void DialController::setHWND(HWND h)
{
  hwnd = h;

  HRESULT hr = Windows::Foundation::Initialize(RO_INIT_MULTITHREADED);
  if (SUCCEEDED(hr))
  {
  }
}

DWORD DialController::getProcessID()
{
  return processID;
}
DWORD DialController::getThreadID()
{
  return threadID;
}
