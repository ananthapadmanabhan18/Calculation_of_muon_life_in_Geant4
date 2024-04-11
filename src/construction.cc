#include "construction.hh"

detectorconstruction::detectorconstruction(){}

detectorconstruction::~detectorconstruction(){}

G4VPhysicalVolume *detectorconstruction::Construct(){

    // Define materials
    G4NistManager* nistManager = G4NistManager::Instance();
    

    G4bool checkoverlap = true;


    // //Defining World Volume
    G4Material* air = nistManager->FindOrBuildMaterial("G4_AIR");
    G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
    mptWorld->AddProperty("RINDEX", energy, rindexWorld, 2);  
    air->SetMaterialPropertiesTable(mptWorld);    
    G4Box* worldvol = new G4Box("world",3.81*m,1.524*m,4.572*m);
    G4LogicalVolume* logicworld = new G4LogicalVolume(worldvol, air, "logicalworld");
    G4VPhysicalVolume* physicalworld = new G4PVPlacement(nullptr, G4ThreeVector(0,0,0), logicworld, "physicalworld", nullptr, false, 0, checkoverlap);
    G4VisAttributes* WW = new G4VisAttributes(G4Colour(0.85, 0.85, 1, 0));
    // WW->SetForceSolid(true);    
    // // logicworld->SetVisAttributes(WW);


    // //Defining the Scintillator
    G4Material* Scintillator_mat = nistManager->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
    G4MaterialPropertiesTable *scintillator_mpt = new G4MaterialPropertiesTable();
    scintillator_mpt->AddProperty("RINDEX", energy, rindexSchintillation, 2);
    Scintillator_mat->SetMaterialPropertiesTable(scintillator_mpt);
    G4Box* Scintillator = new G4Box("Scintillator", 13.25*cm, 7.25*cm, 13.25*cm);
    G4LogicalVolume* logicScintillator = new G4LogicalVolume(Scintillator, Scintillator_mat, "logicalScintillator");
    new G4PVPlacement(nullptr, G4ThreeVector(0,0,0), logicScintillator, "physicalScintillator", logicworld, false, 0, checkoverlap);
    G4VisAttributes* visScint = new G4VisAttributes(G4Colour(0.5, 0.5, 0.5, 0.5));
    visScint->SetForceSolid(true);
    logicScintillator->SetVisAttributes(visScint);


    // //Defining the Photon Multiplier Detector
    G4Material* glass = nistManager->FindOrBuildMaterial("G4_GLASS_PLATE");
    //Defining the Steel Material
    G4Material* steel = nistManager->FindOrBuildMaterial("G4_STAINLESS-STEEL");
    G4double* height_pmt_support_1 = new G4double(0.5*cm);
    G4double* radius_out_pmt_support_1 = new G4double(4.5*cm);
    G4double* radius_in_pmt_support_1 = new G4double(4*cm);
    G4RotationMatrix* rot = new G4RotationMatrix();
    rot->rotateX(90*deg);
    G4Tubs* pmt_support_1 = new G4Tubs("pmt", *radius_in_pmt_support_1, *radius_out_pmt_support_1, *height_pmt_support_1, 0, 2*M_PI);
    logic_pmt_support_1 = new G4LogicalVolume(pmt_support_1, steel, "logical_pmt");
    new G4PVPlacement(rot, G4ThreeVector(0,7.75*cm,0), logic_pmt_support_1, "physical_pmt", logicworld, false, 0, checkoverlap);
    G4VisAttributes* vis_pmt_support_1 = new G4VisAttributes(G4Colour(0.5, 0.5, 0.5, 0.5));
    vis_pmt_support_1->SetForceSolid(true);
    logic_pmt_support_1->SetVisAttributes(vis_pmt_support_1);


    return physicalworld;
}


void detectorconstruction::ConstructSDandField(){
    sensitivedetector *sensdet = new sensitivedetector("SD");
    logic_pmt_support_1->SetSensitiveDetector(sensdet);
}








