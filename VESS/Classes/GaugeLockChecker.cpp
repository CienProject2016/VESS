#include "GaugeLockChecker.h"

bool GaugeLockChecker::isGaugeLocked(int gauge, int lock_data)
{
	if (gauge >= lock_data) {
		return true;
	}
	return false;
}