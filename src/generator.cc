
#include "generator.hh"
#include <cmath>
#include <ctime>

primarygenerator::primarygenerator(){
    EcoMug gen_muons;
    gen_muons.SetUseSky();
    gen_muons.SetSkySize({{15.,15.}});
    gen_muons.SetSkyCenterPosition({{0.,7.5,0.}});
    fparticlegun=new G4ParticleGun(1);
    mu_minus=G4MuonMinus::MuonMinusDefinition();
    mu_plus=G4MuonPlus::MuonPlusDefinition();
}

primarygenerator::~primarygenerator(){
    delete fparticlegun;
}
   
void primarygenerator::GeneratePrimaries(G4Event *anEvent)
{
    EcoMug gen_muons;
        gen_muons.Generate();
        std::array<double,3> muon_position=gen_muons.GetGenerationPosition();
        G4double muon_p=gen_muons.GetGenerationMomentum();
        G4double muon_theta=gen_muons.GetGenerationTheta();
        G4double muon_phi=gen_muons.GetGenerationPhi();
        G4double muon_charge=gen_muons.GetCharge();
        fparticlegun->SetParticlePosition(G4ThreeVector(muon_position[0]*mm,muon_position[1]*mm,muon_position[2]*mm));
        fparticlegun->SetParticleMomentum(G4ParticleMomentum(muon_p*sin(muon_theta)*cos(muon_phi)*GeV,muon_p*sin(muon_theta)*sin(muon_phi)*GeV,muon_p*cos(muon_theta)*GeV));
        if (gen_muons.GetCharge()<0){
            fparticlegun->SetParticleDefinition(mu_minus);
        }else{
            fparticlegun->SetParticleDefinition(mu_plus);
        }

    fparticlegun->GeneratePrimaryVertex(anEvent);
}