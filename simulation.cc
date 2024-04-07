#include "G4RunManagerFactory.hh"
#include "G4SteppingVerbose.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "Randomize.hh"
#include "G4VUserDetectorConstruction.hh"
#include "construction.hh"
#include "physics.hh"
#include "action.hh"
#include "stepping.hh"
#include "detector.hh"
#include "run.hh"
#include "event.hh"
#include "generator.hh"


int main(int argc,char** argv)
{
  G4UIExecutive* ui = nullptr;
  if ( argc == 1 ) { ui = new G4UIExecutive(argc, argv); }

  G4int precision = 4;
  G4SteppingVerbose::UseBestUnit(precision);


  auto* runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);


  // runManager->SetUserInitialization(new detectorconstruction());

  G4GDMLParser parser;
  parser.SetOverlapCheck(true);
  parser.Read("C:\\Users\\apmna\\OneDrive\\Documents\\GitHub\\Calculation_of_muon_life_in_Geant4\\Geometry\\ScintillatorSetup-worldVOL\\ScintillatorSetup-worldVOL.gdml");

  runManager->SetUserInitialization(new GDMLDetectorConstruction(parser.GetWorldVolume()));



  runManager->SetUserInitialization(new physicslist());
  runManager->SetUserInitialization(new actioninitialization());

  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if ( ! ui ) {
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else {
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
  }


  delete visManager;
  delete runManager;
}

