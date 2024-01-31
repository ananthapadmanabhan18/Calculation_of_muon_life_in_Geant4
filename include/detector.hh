#ifndef DETECTOR_HH
#define DETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include <fstream>
#include "G4MuonMinus.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4ParticleTable.hh"
#include "G4MuonMinus.hh"
#include "G4Proton.hh"
#include "G4AnalysisManager.hh"
#include "G4RootFileManager.hh"
#include "G4RootNtupleManager.hh"
#include "run.hh"
#include "G4RunManager.hh"
#include "g4root_defs.hh"
#include"Randomize.hh"


class sensitivedetector : public G4VSensitiveDetector{

    public:
        sensitivedetector(G4String);
        ~sensitivedetector();
    private:
        virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);


};



#endif