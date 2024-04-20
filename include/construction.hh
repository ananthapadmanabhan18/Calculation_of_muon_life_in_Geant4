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
#include "G4GDMLParser.hh"
#include "G4Color.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpticalSurface.hh"



class detectorconstruction : public G4VUserDetectorConstruction
{
    public:
        detectorconstruction();
        ~detectorconstruction();

        virtual G4VPhysicalVolume* Construct();

    private:
        virtual void ConstructSDandField();
        G4double energy[2] = {2.034*eV, 4.136*eV};

        G4double n_world[2] = {1.0, 1.0};

        G4double n_tape[2] = {1.1, 1.1};
        G4double R_tape[2] = {0.9, 0.9};

        G4double n_scint[2] = {1.2, 1.2};
        G4double R_scint[2] = {0.9, 0.9};
        G4LogicalVolume* logic_scint;
        G4LogicalVolume* logic_pmt_photocathode;

        // G4OpticalSurface* opticalSurface;

     
};

// class GDMLDetectorConstruction : public G4VUserDetectorConstruction
// {
//   public:
//     // GDMLDetectorConstruction(G4VPhysicalVolume *setWorld = 0)
//     GDMLDetectorConstruction(G4String gdmlFile){   
//     G4GDMLParser parser;
//     parser.SetOverlapCheck(true);
//     parser.Read(gdmlFile);
//     fWorld = parser.GetWorldVolume();
//     // logic_pmt = parser.GetVolume("GDMLBox_Box");
//     }

//     virtual G4VPhysicalVolume *Construct()
//     {
//       return fWorld;
//     }

//   private:
//     // virtual void ConstructSDandField();
//     G4LogicalVolume* logic_pmt; 
//     G4VPhysicalVolume *fWorld;
// };




#endif