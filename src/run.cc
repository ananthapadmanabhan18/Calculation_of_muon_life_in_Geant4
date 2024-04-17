#include "run.hh"
runaction::runaction(){} 


runaction::~runaction(){} 



void runaction::BeginOfRunAction(const G4Run*){

    G4AnalysisManager*man = G4AnalysisManager::Instance();
    man->OpenFile("final.root");
    G4int num = man->GetNofNtuples();
    if(num==0){
    man->CreateNtuple("Energy","Energy");
    man->CreateNtupleDColumn("Energy");
    man->CreateNtupleDColumn("fX");
    man->CreateNtupleDColumn("fY");
    man->CreateNtupleDColumn("fZ");
    man->FinishNtuple(0);
    }
}

void runaction::EndOfRunAction(const G4Run*){

    G4AnalysisManager*man = G4AnalysisManager::Instance();
    man->Write();
    man->CloseFile();
}