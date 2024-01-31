#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4MuonMinus.hh"
#include "G4MuonPlus.hh"
#include "G4Proton.hh"
#include "G4Gamma.hh"
#include "G4AnalysisManager.hh"
#include "G4RootAnalysisManager.hh"
#include "Randomize.hh"
#include "G4GeneralParticleSource.hh"
#include <array>
#include <fstream>
#include <iostream>
#include <vector>

class primarygenerator : public G4VUserPrimaryGeneratorAction
{
    public:
        primarygenerator ();
        ~primarygenerator();
        virtual void GeneratePrimaries(G4Event*);
    private:    
        G4GeneralParticleSource* fparticlesource;

};

#endif