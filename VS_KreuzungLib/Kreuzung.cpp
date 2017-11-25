#include "include/Kreuzung/Kreuzung.h"

#include<iostream>
#include <Windows.h>

#include "include/Kreuzung/Ampel.h"

using namespace std;

void Kreuzung::blinke()
{
	if(blinkeDeferred)
		cout << "==> Deferred Event: Kreuzung::blinke() state:" << stateToString() << endl;
	else
		cout << "==> Kreuzung::blinke() state:" << stateToString() << endl;

	if(state == KreuzungState::DURCHFAHRT || state == KreuzungState::AUS)
	{
		lnkA1->warne();
		lnkA2->warne();
		lnkA3->warne();

		this->setState(KreuzungState::BLINKEND);
		blinkeDeferred = false;
	}
	else if(state != KreuzungState::BLINKEND && state != KreuzungState::EINFAHRTBLINKEND)
	{
		std::cout << "Kreuzung::blinke() deferred state: " << stateToString() << std::endl;
		blinkeDeferred = true;
	}
	else
	{
		std::cout << "Kreuzung.blinke() in state " << stateToString() << " ignorieren" << std::endl;
	}
}

void Kreuzung::defect()
{
	lnkA1->warne();
	lnkA2->warne();
	lnkA3->warne();	
}

void Kreuzung::einfahrtGewaehren(){
	cout << "==> Kreuzung::einfahrtGewaehren()" << endl;
		
	if (einfahrGewaehrenDeferred)
		std::cout << "==> defered Event: Kreuzung::einfahrtGewaehren() state:" << stateToString() << std::endl;
    else
        std::cout << "Kreuzung::einfahrtGewaehren() state: " << stateToString() << endl;

    if (state == KreuzungState::DURCHFAHRT)
    {
		lnkA1->umschalten();
		lnkA2->umschalten();
		this->setState(KreuzungState::DURCHFAHRTGELB);
        einfahrGewaehrenDeferred = false;
		this->warten(Time::DURCHFAHRTGELBDAUER);
    }
    else if (state != KreuzungState::AUS
        && state != KreuzungState::BLINKEND
		&& state != KreuzungState::EINFAHRTBLINKEND)
    {
        std::cout << "==> Kreuzung::einfahrtGewaehren() defered state: " << stateToString() << std::endl;
        einfahrGewaehrenDeferred = true;
    }
	else
        std::cout << "==> Kreuzung::einfahrtGewaehren() in state: " << stateToString() << " ignorieren" << std::endl;
}

void Kreuzung::warten(int ms){
	cout << "==> Kreuzung::warten(" << ms << "ms)"<< endl;
	Sleep(ms);
	trigger();
}

void Kreuzung::ein(){
	cout << "==> Kreuzung::ein()" << endl;
	if(state == KreuzungState::BLINKEND)
	{
		lnkA1->umschalten();
		lnkA2->umschalten();

		this->setState(KreuzungState::EINFAHRTBLINKEND);
		this->warten(Time::EINFAHRTBLINKENDAUER);
	}
	else
	{
		std::cout << "Kreuzung ein in state " << stateToString() << " ignorieren" << std::endl;
	}
}

void Kreuzung::aus(){

	if(state != KreuzungState::BLINKEND)
	{
		std::cout << "Kreuzung aus in state " << stateToString() << " ignorieren" << std::endl;
		return;
	}
	lnkA3->warne();
	lnkA1->warne();
	lnkA2->warne();

	this->warten(Time::BLINKENDAUER);
	this->setState(KreuzungState::AUS);
}

Kreuzung::Kreuzung(Ampel& a1, Ampel& a2, Ampel& a3) :
		einfahrGewaehrenDeferred(false), blinkeDeferred(false),
	state(KreuzungState::AUS),
	lnkA1(&a1), lnkA2(&a2), lnkA3(&a3)
{
	this->setState(KreuzungState::AUS);
}

std::string Kreuzung::stateToString()
{
	switch(state)
	{
	case KreuzungState::AUS:
		return "AUS";
		break;
	case KreuzungState::BLINKEND:
		return "BLINKEND";
		break;
	case KreuzungState::EINFAHRTBLINKEND:
		return "EINFAHRTBLINKEND";
		break;
	case KreuzungState::EINFAHRTGELB:
		return "EINFAHRTGELB";
		break;
	case KreuzungState::DURCHFAHRTROTGELB:
		return "DURCHFAHRTROTGELB";
		break;
	case KreuzungState::WAIT:
		return "DURCHFAHRTMINDAUER";
		break;
	case KreuzungState::DURCHFAHRT:
		return "DURCHFAHRT";
		break;
	case KreuzungState::DURCHFAHRTGELB:
		return "DURCHFAHRTGELB";
		break;
	case KreuzungState::EINFAHRTROTGELB:
		return "EINFAHRTROTGELB";
		break;
	case KreuzungState::EINFAHRT:
		return "EINFAHRT";
		break;
        default: return "EXCEPTION ILLEGAL STATE";
	}
}

void Kreuzung::setState(KreuzungState::States state)
{
	this->state = state;
	std::cout << "Kreuzung state: " << stateToString() << std::endl;
}

void Kreuzung::trigger()
{
    switch (state)
    {
	case KreuzungState::EINFAHRTBLINKEND:
            lnkA1->umschalten();
            lnkA2->umschalten();
            lnkA3->umschalten();
			this->setState(KreuzungState::EINFAHRTGELB);
			this->warten(Time::EINFAHRTGELBDAUER);
            break;
        case KreuzungState::EINFAHRTGELB:
            lnkA1->umschalten();
            lnkA2->umschalten();
            lnkA3->umschalten();
			this->setState(KreuzungState::DURCHFAHRTROTGELB);
			this->warten(Time::DURCHFAHRTROTGELBDAUER);
            break;
        case KreuzungState::DURCHFAHRTROTGELB:
            lnkA1->umschalten();
            lnkA2->umschalten();
			this->setState(KreuzungState::WAIT);
			this->warten(Time::WAITDAUER);
            break;
        case KreuzungState::WAIT:
			this->setState(KreuzungState::DURCHFAHRT);
            
			// blinke mit höherer priorität
            // bearbeiten wie trigger !!!
            if (blinkeDeferred)
                blinke();
			else if (einfahrGewaehrenDeferred)
                trigger();
            break;
        case KreuzungState::DURCHFAHRT:
            // kommt hier nicht vor
            break;
        case KreuzungState::DURCHFAHRTGELB:
            lnkA1->umschalten();
            lnkA2->umschalten();
            lnkA3->umschalten();
			this->setState(KreuzungState::EINFAHRTROTGELB);
			this->warten(Time::EINFAHRTROTGELBDAUER);
            break;
        case KreuzungState::EINFAHRTROTGELB:
            lnkA3->umschalten();
			this->setState(KreuzungState::EINFAHRT);
			this->warten(Time::EINFAHRTDAUER);
            break;
        case KreuzungState::EINFAHRT:
            lnkA3->umschalten();
			this->setState(KreuzungState::EINFAHRTGELB);
			this->warten(Time::EINFAHRTGELBDAUER);
            break;
        case KreuzungState::AUS:
        case KreuzungState::BLINKEND:
        default:
        	/* nix zu turn */
        	break;
	}
}
