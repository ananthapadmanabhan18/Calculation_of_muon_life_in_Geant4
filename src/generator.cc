#include "generator.hh"
#include <cmath>
#include <ctime>

primarygenerator::primarygenerator(){

    fparticlegun = new G4ParticleGun(1);
    fparticlegun->SetParticleDefinition(G4MuonMinus::Definition());  
    G4ThreeVector pos(0*m,0*m,1*m);
    fparticlegun->SetParticlePosition(pos);
    fparticlegun->SetParticleEnergy(200*MeV);
    G4ThreeVector mom(0,0,-1);
    fparticlegun->SetParticleMomentumDirection(mom);
}

primarygenerator::~primarygenerator(){
    delete fparticlegun;
}


void primarygenerator::GeneratePrimaries(G4Event *anEvent)
{
    fparticlegun->GeneratePrimaryVertex(anEvent);
}


