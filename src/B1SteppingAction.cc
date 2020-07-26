//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file B1SteppingAction.cc
/// \brief Implementation of the B1SteppingAction class

#include "B1SteppingAction.hh"
#include "B1EventAction.hh"
#include "B1DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1SteppingAction::B1SteppingAction(B1EventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fScoringVolume(0)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1SteppingAction::~B1SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1SteppingAction::UserSteppingAction(const G4Step* step)
{
  if (!fScoringVolume) { 
    const B1DetectorConstruction* detectorConstruction
      = static_cast<const B1DetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume = detectorConstruction->GetScoringVolume();   
  }

  // get volume of the current step
  G4LogicalVolume* volume 
    = step->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();
      
  // check if we are in scoring volume
  if (volume != fScoringVolume) return;

  // collect properties of step: energy deposited, energy total, mass, position, and post step volume
  G4double edepStep = step->GetTotalEnergyDeposit();
  G4double energy = step->GetPreStepPoint()->GetTotalEnergy();
  G4double mass = step->GetPreStepPoint()->GetMass();
  G4ThreeVector xyzStep = step->GetPreStepPoint()->GetPosition();
  G4String preVolName = step->GetPreStepPoint()->GetPhysicalVolume()->GetName();
  G4String postVolName = step->GetPostStepPoint()->GetPhysicalVolume()->GetName();

  // Only record energy depositions
  if (edepStep == 0) return;

  G4cout << "Line of interest: " << edepStep << " " << energy << " " << mass << " ";
  G4cout << " " << xyzStep.getX() << " " << xyzStep.getY() << " " << xyzStep.getZ() << " ";
  G4cout << preVolName << " " << postVolName << G4endl;
	
  double postVol = 0;

  if (postVolName == "Tracker1"){
	postVol = 1;
	}
  if (postVolName == "Tracker2"){
	postVol = 2;
	}	

  //fEventAction->AddEnergy(energy);
  //fEventAction->AddMass(mass);
  //fEventAction->AddVolNo(postVol);
  //fEventAction->AddPosX(xyzStep.getX());
  //fEventAction->AddPosY(xyzStep.getY());
  //fEventAction->AddPosZ(xyzStep.getZ());
  //fEventAction->AddEdep(edepStep);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

