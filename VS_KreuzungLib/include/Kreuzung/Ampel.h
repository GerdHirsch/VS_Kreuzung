#ifndef AMPEL_H
#define AMPEL_H

#include "ProtocolViolationException.h"

/**
 * Responsibility:
 * steuert die Lampen
 * implementiert ein 4 Phasen Protokoll
 * Stehen, StartVorbereiten, Fahren, Anhalten
 */
class Ampel {
public:
	virtual ~Ampel(){}

    virtual void aus() = 0;

    virtual void warne() = 0;

    virtual void umschalten() = 0;
};
#endif //AMPEL_H
