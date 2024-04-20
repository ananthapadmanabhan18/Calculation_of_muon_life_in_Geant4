#include "construction.hh"

detectorconstruction::detectorconstruction(){}

detectorconstruction::~detectorconstruction(){}

G4VPhysicalVolume *detectorconstruction::Construct(){

    // Define materials
    G4NistManager* nistManager = G4NistManager::Instance();
    G4RotationMatrix* rot = new G4RotationMatrix();
    rot->rotateX(90*deg);

    G4bool checkoverlap = true;


    //Defining World Volume
    G4Material* air = nistManager->FindOrBuildMaterial("G4_AIR");
    G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
    mptWorld->AddProperty("RINDEX", energy, n_world, 2);     
    air->SetMaterialPropertiesTable(mptWorld);    
    G4Box* worldvol = new G4Box("world",3.81*m,1.524*m,4.572*m);
    G4LogicalVolume* logicworld = new G4LogicalVolume(worldvol, air, "logicalworld");
    G4VPhysicalVolume* physicalworld = new G4PVPlacement(nullptr, G4ThreeVector(0,0,0), logicworld, "physicalworld", nullptr, false, 0, checkoverlap);
    G4VisAttributes* WW = new G4VisAttributes(G4Colour(0.85, 0.85, 1, 0));


    // Defining Scintillator covering Volume 
    G4Material* tape_mat = nistManager->FindOrBuildMaterial("G4_POLYETHYLENE");
    G4MaterialPropertiesTable *tape_table = new G4MaterialPropertiesTable();
    // tape_table->AddProperty("RINDEX", energy, n_tape, 2);
    tape_table->AddProperty("REFLECTIVITY", energy, R_tape, 2);
    tape_mat->SetMaterialPropertiesTable(tape_table);
    G4Box* solid_tape = new G4Box("tape", 13.25*cm+0.25*cm, 7.25*cm+0.25*cm, 13.25*cm+0.25*cm);
    G4LogicalVolume* logic_tape = new G4LogicalVolume(solid_tape, tape_mat, "logical_tape");
    new G4PVPlacement(nullptr, G4ThreeVector(0,0,0), logic_tape, "physical_tape", logicworld, false, 0, checkoverlap);


    G4OpticalSurface* opticalSurface = new G4OpticalSurface("opticalSurface");
    opticalSurface->SetType(dielectric_dielectric);
    opticalSurface->SetFinish(polished);
    opticalSurface->SetModel(unified);
    new G4LogicalSkinSurface("opticalSurface", logic_tape, opticalSurface);



    // Defining Scintillator Volume
    G4Material* scint_mat = nistManager->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
    G4MaterialPropertiesTable *scint_table = new G4MaterialPropertiesTable();
    scint_table->AddProperty("RINDEX", energy, n_scint, 2);
    scint_mat->SetMaterialPropertiesTable(scint_table);
    G4Box* solid_scint = new G4Box("scint", 13.25*cm, 7.25*cm, 13.25*cm);
    logic_scint = new G4LogicalVolume(solid_scint, scint_mat, "logical_scint");
    new G4PVPlacement(nullptr, G4ThreeVector(0,0,0), logic_scint, "physical_scint", logic_tape, false, 0, checkoverlap);


    // Defining PMT Volume
    G4Material* pmt_case_mat = nistManager->FindOrBuildMaterial("G4_Al");
    G4Tubs* solid_pmt_case = new G4Tubs("pmt_case", 4*cm, 4.25*cm, 7.5*cm+12*cm/2, 0, 2*M_PI);
    G4LogicalVolume* logic_pmt_case = new G4LogicalVolume(solid_pmt_case, pmt_case_mat, "logical_pmt_case");
    new G4PVPlacement(rot, G4ThreeVector(0,13.25*cm+7.5*cm,0), logic_pmt_case, "physical_pmt_case", logicworld, false, 0, checkoverlap);

    G4Material* pmt_photocathode_mat = nistManager->FindOrBuildMaterial("G4_Bi");
    G4Tubs* solid_pmt_photocathode = new G4Tubs("pmt_photocathode", 0, 4*cm, 0.1*mm, 0, 2*M_PI);
    logic_pmt_photocathode = new G4LogicalVolume(solid_pmt_photocathode, pmt_photocathode_mat, "logical_pmt_photocathode");
    new G4PVPlacement(rot, G4ThreeVector(0,0,7.5*cm+0.1*mm/2), logic_pmt_photocathode, "physical_pmt_photocathode", logic_pmt_case, false, 0, checkoverlap);




    return physicalworld;
}


void detectorconstruction::ConstructSDandField(){
    sensitivedetector *sensdet = new sensitivedetector("SD");
    logic_pmt_photocathode->SetSensitiveDetector(sensdet);
}