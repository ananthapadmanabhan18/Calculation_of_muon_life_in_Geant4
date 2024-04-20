#include "run.hh"
runaction::runaction(){} 


runaction::~runaction(){} 



void runaction::BeginOfRunAction(const G4Run*){

    G4AnalysisManager*man = G4AnalysisManager::Instance();
    man->OpenFile("final.root");
    // G4int num = man->GetNofNtuples();
    man->CreateNtuple("Counts","counts");
    man->CreateNtupleDColumn("Counts");
    man->FinishNtuple(0);
}

void runaction::EndOfRunAction(const G4Run*){

    G4AnalysisManager*man = G4AnalysisManager::Instance();
    man->Write();
    man->CloseFile();
}