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



    G4double water_side=50*cm+0.5*cm+30*cm;
    G4double height = 0.6*m;
    G4double borated_rubber_side = water_side-30*cm;
    G4double Pb_side = borated_rubber_side-0.5*cm;


    //Defining the Water
    G4Material* water = nistManager->FindOrBuildMaterial("G4_WATER");
    G4Box* water_box = new G4Box("water", water_side, height, water_side);    
    G4LogicalVolume* logicwater = new G4LogicalVolume(water_box,water, "logicalwater");
    new G4PVPlacement(nullptr, G4ThreeVector(0,0,0), logicwater, "physicalwater", logicworld, false, 0, checkoverlap);        
    G4VisAttributes* visWater = new G4VisAttributes(G4Colour(0, 0.5, 1, 0.5));
    visWater->SetForceSolid(true);
    // logicwater->SetVisAttributes(visWater);



    //Defining the Borated Rubber
    G4Element* boron = nistManager->FindOrBuildElement("B");
    G4Material* rubber=nistManager->FindOrBuildMaterial("G4_RUBBER_NATURAL");
    G4Material* boratedRubber = new G4Material("BoratedRubber", 1.658 * g/cm3, 2);
    boratedRubber->AddMaterial(rubber, 0.6); 
    boratedRubber->AddElement(boron, 0.4); 
    G4Box* borated_rubber = new G4Box("borated_rubber", borated_rubber_side, height, borated_rubber_side);
    G4LogicalVolume* logicborated_rubber = new G4LogicalVolume(borated_rubber, boratedRubber, "logicalborated_rubber");
    new G4PVPlacement(nullptr, G4ThreeVector(0,0,0), logicborated_rubber, "physicalborated_rubber", logicwater, false, 0, checkoverlap);
    G4VisAttributes* visBoratedRubber = new G4VisAttributes(G4Colour(0.5, 0.5, 0.5, 0.75));
    visBoratedRubber->SetForceSolid(true);
    // logicborated_rubber->SetVisAttributes(visBoratedRubber);


    //Defining the Lead box
    G4Material* lead = nistManager->FindOrBuildMaterial("G4_Pb");    
    G4Box* Pb_box = new G4Box("detector", (Pb_side), (height), (Pb_side));
    G4LogicalVolume* logic_Pb_box = new G4LogicalVolume(Pb_box, lead, "logicaldetector");
    new G4PVPlacement(nullptr, G4ThreeVector(0,0,0), logic_Pb_box, "physicaldetector", logicborated_rubber, false, 0, checkoverlap);
    G4VisAttributes* visPb = new G4VisAttributes(G4Colour(0.5, 0.5, 0.5, 0.5));
    visPb->SetForceSolid(true);    
    // logic_Pb_box->SetVisAttributes(visPb);


    //air gap
    G4Material* air_gap = nistManager->FindOrBuildMaterial("G4_AIR");
    G4double air_gap_side = 40*cm;
    G4Box* air_gap_box = new G4Box("air_gap", air_gap_side, height, air_gap_side);
    G4LogicalVolume* logic_air_gap = new G4LogicalVolume(air_gap_box, air_gap, "logicalair_gap");
    new G4PVPlacement(nullptr, G4ThreeVector(0,0,0), logic_air_gap, "physicalair_gap", logic_Pb_box, false, 0, checkoverlap);
    // G4VisAttributes* visAir = new G4VisAttributes(G4Colour(0.85, 0.85, 1, 0));



    //Defining the Copper can
    G4Material* copper = nistManager->FindOrBuildMaterial("G4_Cu");
    G4double can_R_out = (60/2)*cm;
    G4double can_R_in = can_R_out-(0.1*cm);
    G4RotationMatrix* rot = new G4RotationMatrix();
    rot->rotateX(90*deg);
    G4Tubs* copper_can = new G4Tubs("copper_can", can_R_in, can_R_out,height, 0, 2*M_PI);
    logic_copper_can = new G4LogicalVolume(copper_can, copper, "logicalcopper_can");
    new G4PVPlacement(rot, G4ThreeVector(0,0,0), logic_copper_can, "physicalcopper_can", logic_air_gap, false, 0, checkoverlap);
    G4VisAttributes* visCu = new G4VisAttributes(G4Colour(184/200,115/200,51/200, 0.5));
    visCu->SetForceSolid(true);
    // logic_copper_can->SetVisAttributes(visCu);





    return physicalworld;
}



void detectorconstruction::ConstructSDandField(){
    sensitivedetector *sensdet = new sensitivedetector("SD");
    logic_copper_can->SetSensitiveDetector(sensdet);
}
