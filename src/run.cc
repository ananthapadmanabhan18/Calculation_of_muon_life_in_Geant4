#include "run.hh"




runaction::runaction(){} 


runaction::~runaction(){} 



void runaction::BeginOfRunAction(const G4Run*){

    G4AnalysisManager*man = G4AnalysisManager::Instance();
    man->OpenFile("output.root");
    man->CreateNtuple("Hits", "Hits");
    man->CreateNtupleDColumn("EnergyDeposit");
    man->FinishNtuple(0);

}

void runaction::EndOfRunAction(const G4Run*){

    G4AnalysisManager*man = G4AnalysisManager::Instance();
    man->Write();
    man->CloseFile();
}