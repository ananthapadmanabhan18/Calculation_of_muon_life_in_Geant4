#include "stepping.hh"


steppingaction::steppingaction(eventaction *eventAction){

    fEventAction = eventAction;
}

steppingaction::~steppingaction(){}


void steppingaction::UserSteppingAction(const G4Step *step)
{
    G4double edep=step->GetTotalEnergyDeposit();
    G4Track* track = step->GetTrack();
    G4ParticleDefinition* particle = track->GetDefinition();
    if(particle==G4OpticalPhoton::Definition()){
    fEventAction->AddPhotonCount();
    }    
    fEventAction->AddEdep(edep);
}