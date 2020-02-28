#ifndef VoidState_h
#define VoidState_h

class VoidState {
public:
  virtual void singleClick() = 0;
	virtual void doubleClick() = 0;
	virtual void tripleClick() = 0;
	virtual void longClick() = 0;
};
#endif
