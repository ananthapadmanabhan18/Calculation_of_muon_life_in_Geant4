
#include "generator.hh"
#include <cmath>
#include <ctime>

primarygenerator::primarygenerator(){

    ecoMug = new EcoMug();
    ecoMug->SetUseSky();

    ecoMug->SetSkySize({{2*3.81*m,2*4.572*m}});
    ecoMug->SetSkyCenterPosition({{0,1.524*m,0}});

    fparticlegun = new G4ParticleGun(1);
    // EcoMug gen_muons;
    // gen_muons.SetUseSky();
    // gen_muons.SetSkySize({{15.,15.}});
    // gen_muons.SetSkyCenterPosition({{0.,7.5,0.}});
    // fparticlegun=new G4ParticleGun(1);
    // mu_minus=G4MuonMinus::MuonMinusDefinition();
    // mu_plus=G4MuonPlus::MuonPlusDefinition();
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
        fparticlegun->SetParticleDefinition(G4MuonPlus::Definition());
    }
    else if(particle_charge == -1){
        fparticlegun->SetParticleDefinition(G4MuonMinus::Definition());
    }
    else{
        G4cout << "Error: Particle charge not recognized" << G4endl;
    }



    // Setting the Position
    std::array<G4double, 3> position = ecoMug->GetGenerationPosition();
    G4ThreeVector pos(position[0]*mm, position[2]*mm, position[1]*mm);
    // G4ThreeVector trial_pos(1*m,0,0);
    fparticlegun->SetParticlePosition(pos);


    //Setting the Momentum
    G4double momentum = ecoMug->GetGenerationMomentum();
    G4double theta = ecoMug->GetGenerationTheta();
    G4double phi = ecoMug->GetGenerationPhi();
    G4ThreeVector mom(momentum*sin(theta)*cos(phi)*GeV, momentum*cos(theta)*GeV, momentum*sin(theta)*sin(phi)*GeV);
    // G4ThreeVector trial_mom(-1*GeV,0.01*GeV,0.01*GeV);
    fparticlegun->SetParticleMomentum(mom);



    fparticlegun->GeneratePrimaryVertex(anEvent);


    // EcoMug gen_muons;
    //     gen_muons.Generate();
    //     std::array<double,3> muon_position=gen_muons.GetGenerationPosition();
    //     G4double muon_p=gen_muons.GetGenerationMomentum();
    //     G4double muon_theta=gen_muons.GetGenerationTheta();
    //     G4double muon_phi=gen_muons.GetGenerationPhi();
    //     G4double muon_charge=gen_muons.GetCharge();
    //     fparticlegun->SetParticlePosition(G4ThreeVector(muon_position[0]*mm,muon_position[1]*mm,muon_position[2]*mm));
    //     fparticlegun->SetParticleMomentum(G4ParticleMomentum(muon_p*sin(muon_theta)*cos(muon_phi)*GeV,muon_p*sin(muon_theta)*sin(muon_phi)*GeV,muon_p*cos(muon_theta)*GeV));
    //     if (gen_muons.GetCharge()<0){
    //         fparticlegun->SetParticleDefinition(mu_minus);
    //     }else{
    //         fparticlegun->SetParticleDefinition(mu_plus);
    //     }

    // fparticlegun->GeneratePrimaryVertex(anEvent);
}