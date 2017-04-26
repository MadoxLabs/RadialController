#pragma once
class DialCallback
{
public:
  virtual void onFocus() = 0;
  virtual void onLostFocus() = 0;
  virtual void onRotate() = 0;
  virtual void onClick() = 0;
};

class DialController
{
protected:
  DialCallback* obj;
  HWND hwnd;
  DWORD processID;
  DWORD threadID;

public:
  DialController();
  virtual ~DialController();

  bool init(DialCallback* obj);
  void setHWND(HWND h);
  DWORD getProcessID();
  DWORD getThreadID();
  bool ready() { return (hwnd != NULL); }
};

