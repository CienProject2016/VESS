#pragma once
#ifndef __SAVE_CONTROLLER_H__
#define __SAVE_COTNROLLER_H__

class SaveController {
public:
	static void save();
private:
	static void saveSword();
	static void saveShield();
	static void saveGold();
	static void saveTopStage();
};

#endif // !__SAVE_CONTROLLER_H__
