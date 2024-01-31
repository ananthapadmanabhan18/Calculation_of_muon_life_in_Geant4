#include "stepping.hh"


steppingaction::steppingaction(eventaction *eventAction){

    fEventAction = eventAction;
}

steppingaction::~steppingaction(){}


void steppingaction::UserSteppingAction(const G4Step *step)
{
}