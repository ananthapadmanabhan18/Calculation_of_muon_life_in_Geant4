#ifndef RUN_HH
#define RUN_HH

#include "G4UserRunAction.hh"
#include "G4AnalysisManager.hh"
#include "G4RootFileManager.hh"
#include "G4RootNtupleManager.hh"
#include "G4RootFileManager.hh"
#include "G4RootNtupleManager.hh"
#include "G4RootFileDef.hh"
#include "g4root_defs.hh"

class runaction : public G4UserRunAction{

    public:
        runaction();
        ~runaction();


    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);


};





#endif