#include "EVENT.h"


void EventReciever::send(EVENT::All e) {
	log("Unit_cpp_Event");
}

void EventSender::setReciever(EventReciever* reciever) {
	this->reciever = reciever;
}