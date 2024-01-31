#include "detector.hh"

sensitivedetector::sensitivedetector(G4String name) : G4VSensitiveDetector(name){}
sensitivedetector::~sensitivedetector(){}


G4bool sensitivedetector:: ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist){

    G4Track* track = aStep->GetTrack();
    track->SetTrackStatus(fStopAndKill);
    G4StepPoint* preStepPoint = aStep->GetPreStepPoint();
    G4ThreeVector position = preStepPoint->GetPosition();
    
    G4AnalysisManager*man  = G4AnalysisManager::Instance();
    G4ParticleDefinition* particle = track->GetDefinition();
    G4String particleName = particle->GetParticleName();

    if(particleName == "gamma"){
        G4double energy = track->GetTotalEnergy();
        G4ThreeVector position = preStepPoint->GetPosition();
        man->FillNtupleDColumn(0,energy);
        man->FillNtupleDColumn(1,position[0]);
        man->FillNtupleDColumn(2,position[1]);
        man->FillNtupleDColumn(3,position[2]);
        man->AddNtupleRow(0);
        }

    return true;

}