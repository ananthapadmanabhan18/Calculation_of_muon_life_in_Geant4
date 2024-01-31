#ifndef PHYSICS_HH
#define PHYSICS_HH
#include "G4VUserPhysicsList.hh"
#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4OpticalPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4GenericIon.hh"
#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"
#include "G4Decay.hh"
#include "G4SystemOfUnits.hh"
#include "G4MuonMinus.hh"

class physicslist : public G4VModularPhysicsList{
    public:
        physicslist();
        ~physicslist();
};




#endif