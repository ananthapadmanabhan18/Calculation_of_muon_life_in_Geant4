#ifndef STEPPING_HH
#define STEPPING_HH

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"
#include "construction.hh"
#include "event.hh"
#include "G4MuonPlus.hh"
#include "G4OpticalPhoton.hh"

class steppingaction : public G4UserSteppingAction
{
    public:
        steppingaction(eventaction* eventAction);
        ~steppingaction();


        virtual void UserSteppingAction(const G4Step*);

    private:
        eventaction *fEventAction;
};


#endif