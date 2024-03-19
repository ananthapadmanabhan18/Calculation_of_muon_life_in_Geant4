#include "construction.hh"

detectorconstruction::detectorconstruction(){}

detectorconstruction::~detectorconstruction(){}


G4VPhysicalVolume *detectorconstruction::Construct(){

    // Define materials
    G4NistManager* nistManager = G4NistManager::Instance();


    G4bool checkoverlap = true;


    //Defining World Volume
    G4Material* air = nistManager->FindOrBuildMaterial("G4_AIR");
    G4Box* worldvol = new G4Box("world",5*m,5*m,5*m);
    G4LogicalVolume* logicworld = new G4LogicalVolume(worldvol, air, "logicalworld");
    G4VPhysicalVolume* physicalworld = new G4PVPlacement(nullptr, G4ThreeVector(0,0,0), logicworld, "physicalworld", nullptr, false, 0, checkoverlap);
    G4VisAttributes* WW = new G4VisAttributes(G4Colour(0.85, 0.85, 1, 0));
    WW->SetForceSolid(true);    
    // logicworld->SetVisAttributes(WW);

    G4double height = 0.125*m;





    //Defining the Copper can
    G4Material* copper = nistManager->FindOrBuildMaterial("G4_Cu");
    G4double can_R_out = (15/2)*cm;
    G4double can_R_in = can_R_out-(0.1*cm);
    G4RotationMatrix* rot = new G4RotationMatrix();
    rot->rotateX(90*deg);
    G4Tubs* copper_can = new G4Tubs("copper_can", can_R_in, can_R_out,height, 0, 2*M_PI);
    logic_copper_can = new G4LogicalVolume(copper_can, copper, "logicalcopper_can");
    new G4PVPlacement(rot, G4ThreeVector(0,0,0), logic_copper_can, "physicalcopper_can", logicworld, false, 0, checkoverlap);
    G4VisAttributes* visCu = new G4VisAttributes(G4Colour(184/200,115/200,51/200, 0.5));
    visCu->SetForceSolid(true);

    return physicalworld;
}



void detectorconstruction::ConstructSDandField(){
    sensitivedetector *sensdet = new sensitivedetector("SD");
    logic_copper_can->SetSensitiveDetector(sensdet);
}
