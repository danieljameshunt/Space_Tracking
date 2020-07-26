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
/// \file B1RunAction.hh
/// \brief Definition of the B1RunAction class

#ifndef B1RunAction_h
#define B1RunAction_h 1

#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"
#include <vector>

class G4Run;

/// Run action class
///
/// In EndOfRunAction(), it calculates the dose in the selected volume 
/// from the energy deposit accumulated via stepping and event actions.
/// The computed dose is then printed on the screen.

class B1RunAction : public G4UserRunAction
{
public:
  B1RunAction();
  virtual ~B1RunAction();

  // virtual G4Run* GenerateRun();
  virtual void BeginOfRunAction(const G4Run*);
  virtual void   EndOfRunAction(const G4Run*);

  void AddEdep (std::vector<G4double> *edep){fEdep->insert(fEdep->end(), edep->begin(), edep->end());};
  void AddEnergy (std::vector<G4double> *energy){fEnergy->insert(fEnergy->end(), energy->begin(), energy->end());};
  void AddMass (std::vector<G4double> *mass){fMass->insert(fMass->end(), mass->begin(), mass->end());};
  void AddVolName (std::vector<G4String> *volname){fVolName->insert(fVolName->end(), volname->begin(), volname->end());};
  void AddPosX (std::vector<G4double> *posX){fPosX->insert(fPosX->end(), posX->begin(), posX->end());}; 
  void AddPosY (std::vector<G4double> *posY){fPosY->insert(fPosY->end(), posY->begin(), posY->end());};
  void AddPosZ (std::vector<G4double> *posZ){fPosZ->insert(fPosZ->end(), posZ->begin(), posZ->end());}; 
private:
  std::vector<G4double> *fEdep;
  std::vector<G4double> *fEnergy;
  std::vector<G4double> *fMass;
  std::vector<G4String> *fVolName;
  std::vector<G4double> *fPosX;
  std::vector<G4double> *fPosY;
  std::vector<G4double> *fPosZ;
};

#endif

