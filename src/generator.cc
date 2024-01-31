#include "generator.hh"
#include <cmath>
#include <ctime>

primarygenerator::primarygenerator(){

    fparticlesource = new G4GeneralParticleSource();
    fparticlesource->SetParticleDefinition(G4Gamma::Definition());  
    G4ThreeVector pos(0*m,0*m,0*m);
    fparticlesource->SetParticlePosition(pos);
}

primarygenerator::~primarygenerator(){
    delete fparticlesource;
}


void primarygenerator::GeneratePrimaries(G4Event *anEvent)
{
    G4Random::setTheSeed(time(time_t(0)));
    G4double randomNumber1 = G4UniformRand();
    G4double randomNumber2 = G4UniformRand();
    G4double randomNumber3 = G4UniformRand();
    G4double x0 = (randomNumber1-0.5);
    G4double y0 = (randomNumber2-0.5);
    G4double z0 = (randomNumber3-0.5);
    G4ThreeVector pos(x0*m,y0*m,z0*m);
    
    fparticlesource->GeneratePrimaryVertex(anEvent);

}


