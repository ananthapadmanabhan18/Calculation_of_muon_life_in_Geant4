#include "event.hh"


eventaction::eventaction(runaction*)
{
    // fEdep = 0;
    PhotonCount = 0;
}
eventaction::~eventaction(){}



void eventaction::BeginOfEventAction(const G4Event*)
{
    // fEdep=0;
    PhotonCount = 0;
}
void eventaction::EndOfEventAction(const G4Event*)
{
    // G4cout << "Number of optical photons produced: " << PhotonCount << G4endl;
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    man->FillNtupleDColumn(0, 0, PhotonCount);
    man->AddNtupleRow(0);
}