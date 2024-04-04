
#include "generator.hh"
#include <cmath>
#include <ctime>

primarygenerator::primarygenerator(){

    fparticlegun = new G4ParticleGun(1);
    int numParticles = 100;
            // Loop over the number of particles
    for (int i = 0; i < numParticles; i++) {
        // Set the particle definition (e.g., gamma ray)
        fparticlegun->SetParticleDefinition(G4MuonMinus::Definition());

        // Set the particle position (e.g., origin)
        G4ThreeVector pos(0*m,0*m,0*m);
        fparticlegun->SetParticlePosition(pos);

        // Set the particle energy (e.g., 1 MeV)
        fparticlegun->SetParticleEnergy(1*MeV);

        // Set the particle momentum direction (e.g., random direction)
        G4ThreeVector mom(G4UniformRand(), G4UniformRand(), G4UniformRand());
        fparticlegun->SetParticleMomentumDirection(mom);
    }
}

primarygenerator::~primarygenerator(){
    delete fparticlegun;
}
   
void primarygenerator::GeneratePrimaries(G4Event *anEvent)
{
    fparticlegun->GeneratePrimaryVertex(anEvent);
}