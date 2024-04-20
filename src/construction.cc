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
    // G4MaterialPropertiesTable* plasticMPT = new G4MaterialPropertiesTable();
    // plasticMPT->AddProperty("RINDEX", photonEnergy,rindex_plastic, 2);
    // plastic->SetMaterialPropertiesTable(plasticMPT);
    G4Tubs* jugouter = new G4Tubs("jugouter", (10/2)*cm, (12/2)*cm, 21*cm/2, 0, 2*M_PI);
    G4LogicalVolume* logicjugouter = new G4LogicalVolume(jugouter, plastic, "logicaljugouter");
    new G4PVPlacement(rot_mat, G4ThreeVector(0,0,0), logicjugouter, "physicaljugouter", logicworld, false, 0, checkoverlap);
    G4VisAttributes* jugouter_vis = new G4VisAttributes(G4Colour(0.5,0.5,0.5));
    jugouter_vis->SetForceSolid(true);
    logicjugouter->SetVisAttributes(jugouter_vis);

    // defining the reflective surface
    G4Material* al = nistManager->FindOrBuildMaterial("G4_Al");
    G4double reflectivity[2] = {0.9, 0.9};
    G4double rindex_al[2] = {1.0, 1.0};
    G4MaterialPropertiesTable* alMPT = new G4MaterialPropertiesTable();
    alMPT->AddProperty("REFLECTIVITY", photonEnergy, reflectivity, 2);
    al->SetMaterialPropertiesTable(alMPT);
    G4Tubs* jug_ref = new G4Tubs("jug_ref", (8/2)*cm, (10/2)*cm, 17*cm/2, 0, 2*M_PI);
    G4LogicalVolume* logicjug_ref = new G4LogicalVolume(jug_ref, al, "logicaljug_ref");
    new G4PVPlacement(rot_mat, G4ThreeVector(0,-0.5*cm,0), logicjug_ref, "physicaljug_ref", logicworld, false, 0, checkoverlap);



    // Water inside the jug
    G4Material* water = nistManager->FindOrBuildMaterial("G4_WATER");
    G4MaterialPropertiesTable* waterMPT = new G4MaterialPropertiesTable();
    waterMPT->AddProperty("RINDEX", photonEnergy, rindex_water, 2);
    water->SetMaterialPropertiesTable(waterMPT);
    G4Tubs* jugwater = new G4Tubs("juginner", 0, (8/2)*cm, 17*cm/2, 0, 2*M_PI);
    logicjugwater = new G4LogicalVolume(jugwater, water, "logicaljugwater");
    new G4PVPlacement(rot_mat, G4ThreeVector(0,-0.5*cm,0), logicjugwater, "physicaljugwater", logicworld, false, 0, checkoverlap);


    // Defining PMT Volume
    G4Material* pmt_case_mat = nistManager->FindOrBuildMaterial("G4_Al");
    G4Tubs* solid_pmt_case = new G4Tubs("pmt_case", 4*cm, 4.25*cm,16*cm/2, 0, 2*M_PI);
    G4LogicalVolume* logic_pmt_case = new G4LogicalVolume(solid_pmt_case, pmt_case_mat, "logical_pmt_case");
    new G4PVPlacement(rot_mat, G4ThreeVector(0,10.25*cm+7.5*cm,0), logic_pmt_case, "physical_pmt_case", logicworld, false, 0, checkoverlap);
    G4VisAttributes* pmt_case_vis = new G4VisAttributes(G4Colour(0.5,0.5,0.5));
    pmt_case_vis->SetForceSolid(true);

    G4Material* pmt_photocathode_mat = nistManager->FindOrBuildMaterial("G4_Bi");
    G4Tubs* solid_pmt_photocathode = new G4Tubs("pmt_photocathode", 0, 4*cm, 0.1*mm, 0, 2*M_PI);
    G4LogicalVolume* logic_pmt_photocathode = new G4LogicalVolume(solid_pmt_photocathode, pmt_photocathode_mat, "logical_pmt_photocathode");
    new G4PVPlacement(nullptr, G4ThreeVector(0,0,5.5*cm+0.1*mm/2), logic_pmt_photocathode, "physical_pmt_photocathode", logic_pmt_case, false, 0, checkoverlap);



    // Defining the lower cap
    G4Material* cap_mat = nistManager->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
    G4Tubs* solid_cap = new G4Tubs("cap", 0, 6*cm, 1.5*cm/2, 0, 2*M_PI);
    G4LogicalVolume* logic_cap = new G4LogicalVolume(solid_cap, cap_mat, "logical_cap");
    new G4PVPlacement(rot_mat, G4ThreeVector(0,-9.75*cm,0), logic_cap, "physical_cap", logicworld, false, 0, checkoverlap);
    G4VisAttributes* cap_vis = new G4VisAttributes(G4Colour(0.5,0.5,0.5));
    cap_vis->SetForceSolid(true);
    logic_cap->SetVisAttributes(cap_vis);



    return physicalworld;
}



void detectorconstruction::ConstructSDandField(){
    sensitivedetector *sensdet = new sensitivedetector("SD");
    logicjugwater->SetSensitiveDetector(sensdet);
}
