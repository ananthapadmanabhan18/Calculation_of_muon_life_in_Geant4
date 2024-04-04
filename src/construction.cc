#include "construction.hh"

detectorconstruction::detectorconstruction(){}

detectorconstruction::~detectorconstruction(){}


G4VPhysicalVolume *detectorconstruction::Construct(){

    // Define materials
    G4NistManager* nistManager = G4NistManager::Instance();


    G4bool checkoverlap = true;


    //Defining World Volume
    G4Material* air = nistManager->FindOrBuildMaterial("G4_AIR");
    G4Box* worldvol = new G4Box("world",7.5*m,7.5*m,7.5*m);
    G4LogicalVolume* logicworld = new G4LogicalVolume(worldvol, air, "logicalworld");
    G4VPhysicalVolume* physicalworld = new G4PVPlacement(nullptr, G4ThreeVector(0,0,0), logicworld, "physicalworld", nullptr, false, 0, checkoverlap);
    G4VisAttributes* WW = new G4VisAttributes(G4Colour(0.85, 0.85, 1, 0));
    WW->SetForceSolid(true);    
    // logicworld->SetVisAttributes(WW);





    // G4Material* Scintillator_mat = nistManager->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
    // G4Box* Scintillator = new G4Box("Scintillator", 7.5*cm, 7.5*cm, 7.5*cm);
    // G4LogicalVolume* logicScintillator = new G4LogicalVolume(Scintillator, Scintillator_mat, "logicalScintillator");
    // new G4PVPlacement(nullptr, G4ThreeVector(0,0,0), logicScintillator, "physicalScintillator", logicworld, false, 0, checkoverlap);
    // G4VisAttributes* visScint = new G4VisAttributes(G4Colour(0.5, 0.5, 0.5, 0.5));
    // visScint->SetForceSolid(true);
    // logicScintillator->SetVisAttributes(visScint);

    G4Material* jug_mat = nistManager->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
    G4RotationMatrix* rot_jug = new G4RotationMatrix();
    rot_jug->rotateX(90*deg);
    G4Tubs* jug_out = new G4Tubs("jugout", 9*cm, 12*cm, 20*cm, 0, 2*M_PI);
    G4LogicalVolume* logicjugout = new G4LogicalVolume(jug_out, jug_mat, "logicaljugout");
    new G4PVPlacement(rot_jug, G4ThreeVector(0,0,0), logicjugout, "physicaljugout", logicworld, false, 0, checkoverlap);
    G4VisAttributes* visjugout = new G4VisAttributes(G4Colour(1, 0.5, 0.5, 0.5));
    logicjugout->SetVisAttributes(visjugout);
    visjugout->SetForceSolid(true);

    G4Element* elFe = nistManager->FindOrBuildElement("Fe");
    G4Element* elC = nistManager->FindOrBuildElement("C");
    G4double density = 7.8;
    G4Material* steel = new G4Material("Steel", density, 2);
    steel->AddElement(elFe, 99.5*perCent); // Specify proportion of iron
    steel->AddElement(elC, 0.5*perCent);   // Specify proportion of carbon
    G4Tubs* jug_in = new G4Tubs("jugin", 8.5*cm, 9*cm, 20*cm, 0, 2*M_PI);
    G4LogicalVolume* logicjugin = new G4LogicalVolume(jug_in, steel, "logicaljugin");
    new G4PVPlacement(rot_jug, G4ThreeVector(0,0,0), logicjugin, "physicaljugin", logicworld, false, 0, checkoverlap);
    G4VisAttributes* visjugin = new G4VisAttributes(G4Colour(0.5, 0.5, 0.5, 0.5));
    logicjugin->SetVisAttributes(visjugin);
    visjugin->SetForceSolid(true);

    G4Material* water = nistManager->FindOrBuildMaterial("G4_WATER");
    G4Tubs* jug_water = new G4Tubs("jugwater", 0, 8.5*cm, 20*cm, 0, 2*M_PI);
    G4LogicalVolume* logicjugwater = new G4LogicalVolume(jug_water, water, "logicaljugwater");
    new G4PVPlacement(rot_jug, G4ThreeVector(0,0,0), logicjugwater, "physicaljugwater", logicworld, false, 0, checkoverlap);
    G4VisAttributes* visjugwater = new G4VisAttributes(G4Colour(0, 0, 1, 0.5));
    logicjugwater->SetVisAttributes(visjugwater);
    visjugwater->SetForceSolid(true);




    //Defining the Photon Multiplier Detector
    G4Material* glass = nistManager->FindOrBuildMaterial("G4_GLASS_PLATE");
    G4double* height_pmt = new G4double(16*cm);
    G4double* radius_pmt = new G4double(7.5*cm);
    G4RotationMatrix* rot = new G4RotationMatrix();
    rot->rotateX(90*deg);
    G4Tubs* pmt = new G4Tubs("pmt", 0, *radius_pmt, *height_pmt, 0, 2*M_PI);
    logic_pmt = new G4LogicalVolume(pmt, glass, "logical_pmt");
    new G4PVPlacement(rot, G4ThreeVector(0,30*cm,0), logic_pmt, "physical_pmt", logicworld, false, 0, checkoverlap);
    G4VisAttributes* vis_pmt = new G4VisAttributes(G4Colour(0.5, 1, 0.5, 1));
    vis_pmt->SetForceSolid(true);
    logic_pmt->SetVisAttributes(vis_pmt);



    return physicalworld;
}



void detectorconstruction::ConstructSDandField(){
    sensitivedetector *sensdet = new sensitivedetector("SD");
    logic_pmt->SetSensitiveDetector(sensdet);
}
