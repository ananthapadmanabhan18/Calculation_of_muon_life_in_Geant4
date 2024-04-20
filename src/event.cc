#include "event.hh"

//beginning of the event, the muonflux is set to 0
eventaction::eventaction(runaction*)
{
    photonflux = 0;
}
eventaction::~eventaction(){}

//whenever a new event starts, the muonflux is set to 0
void eventaction::BeginOfEventAction(const G4Event*)
{
    photonflux=0;
}
void eventaction::EndOfEventAction(const G4Event*)
{
    // G4cout << "muon flux: " << photonflux << G4endl;
    G4AnalysisManager* man= G4AnalysisManager::Instance();
    man->FillNtupleDColumn(0,0, photonflux);
    man->AddNtupleRow(0);
}