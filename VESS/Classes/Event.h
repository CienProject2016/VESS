
#include "cocos2d.h"
#ifndef __EVENT_H__
#define __EVENT_H__

USING_NS_CC;

class EVENT {
public:
	enum All {
		HeroAttack, 
		MonsterDead
	};
};

class EventReciever {
public:
	virtual void send(EVENT::All e);
};

class EventSender {
public:
	EventReciever* reciever;
	void setReciever(EventReciever* reciever);
};

#endif // __EVENT_H__