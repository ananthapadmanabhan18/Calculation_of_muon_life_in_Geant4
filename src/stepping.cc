#include "stepping.hh"
#include  "G4OpticalPhoton.hh"

steppingaction::steppingaction(eventaction *eventAction){

    fEventAction = eventAction;
}

steppingaction::~steppingaction(){}


void steppingaction::UserSteppingAction(const G4Step *step)
{
    G4ParticleDefinition* particleType = step->GetTrack()->GetDefinition();

    if(particleType == G4OpticalPhoton::OpticalPhotonDefinition()){

        fEventAction->Addflux();
    }

}