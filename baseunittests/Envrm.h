#pragma once
// ��ʼ��base�⻷��

#include "at_exit.h"

class CEnvrm
{
public:
	CEnvrm();

	~CEnvrm();

private:
	base::AtExitManager exexit_manager;
};

