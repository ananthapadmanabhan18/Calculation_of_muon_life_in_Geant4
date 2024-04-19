#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif



#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4Material.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4VisAttributes.hh"
#include "G4Polyhedra.hh"
#include "G4Colour.hh"
#include "G4Element.hh"
#include "G4SDManager.hh"
#include "G4RotationMatrix.hh"
#include "detector.hh"



class detectorconstruction : public G4VUserDetectorConstruction
{
    public:
        detectorconstruction();
        ~detectorconstruction();

        virtual G4VPhysicalVolume* Construct();

    private:
        virtual void ConstructSDandField();
        G4double photonEnergy[2] = {2.034*eV, 4.136*eV};
        G4double rindex_water[2] = {1.33, 1.33};
        G4double rindex_world[2] = {1.0, 1.0};
        G4double rindex_steel[2] = {0, 0};
        G4double rindex_plastic[2] = {0, 0};
        G4double reflectivity_steel = 0.7;
        G4LogicalVolume* logic_pmt;

};






#endif