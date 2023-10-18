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
/// \file OpNoviceSteppingAction.cc
/// \brief Implementation of the OpNoviceSteppingAction class

#include "OpNoviceSteppingAction.hh"
#include "OpNoviceRun.hh"
#include "OpNoviceDetectorConstruction.hh"
#include "OpNoviceEventAction.hh"

#include "G4Cerenkov.hh"
#include "G4Scintillation.hh"
#include "G4EventManager.hh"
#include "G4ProcessManager.hh"
#include "G4SteppingManager.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4OpticalPhoton.hh"
#include "G4Alpha.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleDefinition.hh"
#include "G4Ions.hh"
#include "G4StepPoint.hh"

#include "Analysis.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OpNoviceSteppingAction::OpNoviceSteppingAction(OpNoviceEventAction* event, const OpNoviceDetectorConstruction* detConstruction)
  : G4UserSteppingAction()
  , fEventAction(event)
  , fDetConstruction(detConstruction)
  , fVerbose(0)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OpNoviceSteppingAction::~OpNoviceSteppingAction() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void OpNoviceSteppingAction::UserSteppingAction(const G4Step* step)
{

  const G4ParticleDefinition* particleDef = step->GetTrack()->GetDynamicParticle()->GetParticleDefinition();
  static G4ParticleDefinition* opticalphoton = G4OpticalPhoton::OpticalPhotonDefinition();
  static G4ParticleDefinition* alpha = G4Alpha::AlphaDefinition();

  G4Track* track          = step->GetTrack();

  auto volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
  auto runData = static_cast<OpNoviceRun*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());
    
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    
    
      if (particleDef == alpha)
        {   

            if (volume == fDetConstruction->GetAbsorber_phys())
            {
                G4double edep = step->GetTotalEnergyDeposit();
                if (edep <= 0.) return;
      
            G4double stepLength = 0.;
            stepLength = step->GetStepLength();
            
            runData->Add(kAbs, edep, stepLength); 
            analysisManager->FillH1(2,stepLength,edep);

            }
        }
        
       else if(particleDef == opticalphoton)
        {

            G4double en = track->GetKineticEnergy();
            runData->AddScintillationEnergy(en);
            runData->AddScintillationNo();
            analysisManager->FillH1(3, en);

         }


    

    return;
}
