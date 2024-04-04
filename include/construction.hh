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
        G4LogicalVolume* logic_pmt;

};






#endif