#include "construction.hh"

detectorconstruction::detectorconstruction(){}

detectorconstruction::~detectorconstruction(){}


G4VPhysicalVolume *detectorconstruction::Construct(){

    // Define materials
    G4NistManager* nistManager = G4NistManager::Instance();


    // Define refractive index of materials
    G4RotationMatrix* rot_mat = new G4RotationMatrix();
    rot_mat->rotateX(90*deg);

    G4bool checkoverlap = true;


    //Defining World Volume
    G4Material* air = nistManager->FindOrBuildMaterial("G4_AIR");
    G4MaterialPropertiesTable* airMPT = new G4MaterialPropertiesTable();
    airMPT->AddProperty("RINDEX", photonEnergy, rindex_world, 2);
    air->SetMaterialPropertiesTable(airMPT);
    G4Box* worldvol = new G4Box("world",3.81*m,1.524*m,4.572*m);
    G4LogicalVolume* logicworld = new G4LogicalVolume(worldvol, air, "logicalworld");
    G4VPhysicalVolume* physicalworld = new G4PVPlacement(nullptr, G4ThreeVector(0,0,0), logicworld, "physicalworld", nullptr, false, 0, checkoverlap);


    // Defining Outer part of Jug
    G4Material* plastic = nistManager->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
    G4MaterialPropertiesTable* plasticMPT = new G4MaterialPropertiesTable();
    plasticMPT->AddProperty("RINDEX", photonEnergy,rindex_plastic, 2);
    plastic->SetMaterialPropertiesTable(plasticMPT);
    G4Tubs* jugouter = new G4Tubs("jugouter", (10/2)*cm, (12/2)*cm, 20*cm, 0, 2*M_PI);
    G4LogicalVolume* logicjugouter = new G4LogicalVolume(jugouter, plastic, "logicaljugouter");
    new G4PVPlacement(rot_mat, G4ThreeVector(0,0,0), logicjugouter, "physicaljugouter", logicworld, false, 0, checkoverlap);






    return physicalworld;
}



void detectorconstruction::ConstructSDandField(){
    sensitivedetector *sensdet = new sensitivedetector("SD");
    // logic_pmt->SetSensitiveDetector(sensdet);
}
