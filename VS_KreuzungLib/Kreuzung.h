#ifndef KREUZUNG_H
#define KREUZUNG_H

#include <string>

#include "Ampel.h"
/**
 * Responsibility: steuert die Ampeln gem‰ﬂ einer ordentlichen Kreuzung
 * basiert auf einem 4 Phasen Protokoll: Fahren, Anhalten, Stehen, StartVorbereiten 
 */
class Kreuzung {
public:
	struct Time{
		enum Times {
			DURCHFAHRTGELBDAUER=2000,
			EINFAHRTROTGELBDAUER=2000,
			EINFAHRTDAUER=2000,
			EINFAHRTGELBDAUER=3000,
			DURCHFAHRTROTGELBDAUER=2000,
			BLINKENDAUER=2000,
			EINFAHRTBLINKENDAUER=5000,
			WAITDAUER=10000 };
	};

	struct KreuzungState{
		enum States {
			AUS,
			BLINKEND,
			EINFAHRTBLINKEND,
			EINFAHRTGELB,
			DURCHFAHRTROTGELB,
			WAIT,
			DURCHFAHRT,
			DURCHFAHRTGELB,
			EINFAHRTROTGELB,
			EINFAHRT };
	};

	virtual ~Kreuzung() {}
    Kreuzung(Ampel& a1, Ampel& a2, Ampel& a3);

	void blinke();
	void defect();

    void aus();

    void ein();

    void einfahrtGewaehren();

private:
	bool einfahrGewaehrenDeferred;
	bool blinkeDeferred;

	KreuzungState::States state;
	Kreuzung(const Kreuzung&);
    void warten(int ms);
	std::string stateToString();
	void trigger();
	void setState(KreuzungState::States state);
    /**
     * @directed
     * @supplierCardinality 1 
     * @supplierRole a1
     */
    Ampel * lnkA1;
    /**
     * @directed
     * @supplierCardinality 1 
     * @supplierRole a2
     */
    Ampel * lnkA2;
    /**
     * @directed
     * @supplierCardinality 1 
     * @supplierRole a3
     */
    Ampel * lnkA3;
};
#endif //KREUZUNG_H
