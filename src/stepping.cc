#include "stepping.hh"


steppingaction::steppingaction(eventaction *eventAction){

    fEventAction = eventAction;
}

steppingaction::~steppingaction(){}


void steppingaction::UserSteppingAction(const G4Step *step)
{
    G4double edep=step->GetTotalEnergyDeposit();
    fEventAction->AddEdep(edep);
}