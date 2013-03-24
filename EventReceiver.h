#ifndef EventReceiver_h
#define EventReceiver_h

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace gui;
using namespace scene;
using namespace video;
using namespace io;

class EventReceiver : public IEventReceiver{
public:
	EventReceiver();
	bool OnEvent(const SEvent& ev);
};

#endif