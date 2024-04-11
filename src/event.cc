#include "event.hh"


eventaction::eventaction(runaction*)
{
    fEdep = 0;
}
eventaction::~eventaction(){}



void eventaction::BeginOfEventAction(const G4Event*)
{
    fEdep=0;
}
void eventaction::EndOfEventAction(const G4Event*)
{
    // G4cout << "Energy deposition: " << fEdep << G4endl;
    // G4AnalysisManager *man = G4AnalysisManager::Instance();
    // man->FillNtupleDColumn(0, 0, fEdep);
    // man->AddNtupleRow(0);
}