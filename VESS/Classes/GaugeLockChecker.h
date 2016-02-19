#pragma once
#ifndef __GAUGE_LOCK_CHECKER_H__
#define __GAUGE_LOCK_CHECKER_H__

#include <iostream>
using namespace std;
class GaugeLockChecker
{
public:
	static bool isGaugeLocked(int, int);
};

#endif