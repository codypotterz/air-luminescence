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
/// \file OpNovice/include/OpNoviceDetectorConstruction.hh
/// \brief Definition of the OpNoviceDetectorConstruction class
//
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef OpNoviceDetectorConstruction_h
#define OpNoviceDetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class G4VPhysicalVolume;

class OpNoviceDetectorConstruction : public G4VUserDetectorConstruction
{
 public:
  OpNoviceDetectorConstruction();
  ~OpNoviceDetectorConstruction();

  G4VPhysicalVolume* Construct() override;
  const G4VPhysicalVolume* GetAbsorber_phys() const;

 private:
  G4double fExpHall_x;
  G4double fExpHall_y;
  G4double fExpHall_z;
  
  G4double Ag_x;
  G4double Ag_y;
  G4double Ag_z;

  G4double Au_x;
  G4double Au_y;
  G4double Au_z;

  G4double Abs_x;
  G4double Abs_y;
  G4double Abs_z;

  
  G4VPhysicalVolume* Absorber_phys;
  G4VPhysicalVolume* SilverPlate_phys;
  G4VPhysicalVolume* GoldCover_phys;
  
};

inline const G4VPhysicalVolume* OpNoviceDetectorConstruction::GetAbsorber_phys() const {
    return Absorber_phys;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif /*OpNoviceDetectorConstruction_h*/
