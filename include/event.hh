#ifndef EVENT_HH
#define EVENT_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "G4RootFileManager.hh"
#include "G4RootNtupleManager.hh"
#include "run.hh"
#include"G4AnalysisManager.hh"

class eventaction : public G4UserEventAction{
    public:
        eventaction(runaction*);
        ~eventaction();

        virtual void BeginOfEventAction(const G4Event*);
        virtual void EndOfEventAction(const G4Event*);


        void AddEdep(G4double edep){fEdep += edep;}
        void AddPhotonCount(){PhotonCount++;}

    private:
        G4double fEdep;
        G4int PhotonCount;
};






#endif