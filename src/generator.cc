#include "generator.hh"
#include <cmath>
#include <ctime>

primarygenerator::primarygenerator(){
    ecoMug = new EcoMug();
    ecoMug->SetUseSky();
    ecoMug->SetSkySize({{2*3.81*m,2*4.572*m}});
    ecoMug->SetSkyCenterPosition({{0,(1.524/2)*m,0}});
    fparticlegun = new G4ParticleGun(1);
}

primarygenerator::~primarygenerator(){
    delete fparticlegun;
}


void primarygenerator::GeneratePrimaries(G4Event *anEvent)
{
    ecoMug->Generate();

    //Setting the Particle according to charge
    int particle_charge = ecoMug->GetCharge();
    if(particle_charge == 1){
        // fparticlegun->SetParticleDefinition(G4MuonPlus::Definition());
        fparticlegun->SetParticleDefinition(G4OpticalPhoton::Definition());
        G4cout << "Muon+" << G4endl;
    }
    else if(particle_charge == -1){
        // fparticlegun->SetParticleDefinition(G4MuonMinus::Definition());
        fparticlegun->SetParticleDefinition(G4OpticalPhoton::Definition());
        G4cout << "Muon-" << G4endl;
    }
    else{
        G4cout << "Error: Particle charge not recognized" << G4endl;
    }

    // Setting polarization in x diection
    G4ThreeVector pol(1,0,0);
    fparticlegun->SetParticlePolarization(pol);

    // Setting the Position
    std::array<G4double, 3> position = ecoMug->GetGenerationPosition();
    G4ThreeVector pos(position[0]*mm, position[2]*mm, position[1]*mm);
    G4ThreeVector trial_pos(1*m,0,0);
    fparticlegun->SetParticlePosition(trial_pos);
    G4cout << "Position: " << pos << G4endl;


    //Setting the Momentum
    G4double momentum = ecoMug->GetGenerationMomentum();
    G4double theta = ecoMug->GetGenerationTheta();
    G4double phi = ecoMug->GetGenerationPhi();
    G4cout << "Momentum: " << momentum << G4endl;
    G4cout << "Theta: " << theta << G4endl;
    G4cout << "Phi: " << phi << G4endl;
    G4ThreeVector mom(momentum*sin(theta)*cos(phi)*GeV, momentum*cos(theta)*GeV, momentum*sin(theta)*sin(phi)*GeV);
    G4ThreeVector trial_mom(-1*GeV,0.01*GeV,0.01*GeV);
    fparticlegun->SetParticleMomentum(trial_mom);



    fparticlegun->GeneratePrimaryVertex(anEvent);
}


