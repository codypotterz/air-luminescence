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
/// \file OpNovice/src/OpNoviceRun.cc
/// \brief Implementation of the OpNoviceRun class
//
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "OpNoviceRun.hh"
#include "Analysis.hh"
#include "OpNoviceRunAction.hh"

#include "G4ParticleDefinition.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OpNoviceRun::OpNoviceRun()
  : G4Run(),
  fVolumeNames{ {"Absorber"}}
{
  for (auto& edep : fEdep){
      edep = 0.;
  }
  for (auto& trackLength : fTrackLength){
      trackLength = 0.;
  }
    
    
  fParticle             = nullptr;
 // fEnergy               = -1.;
 
  fScintEnergy          = 0.;
  fScintCount           = 0.;

  fScintillationCounter = 0.;
  fScintillation2       = 0.;
}


OpNoviceRun::~OpNoviceRun() {}

//void OpNoviceRun::SetPrimary(G4ParticleDefinition* particle, G4double energy)
void OpNoviceRun::SetPrimary(G4ParticleDefinition* particle)
{
  fParticle = particle;
 // fEnergy   = energy;
}

void OpNoviceRun::Merge(const G4Run* run)
{
  const OpNoviceRun* localRun = static_cast<const OpNoviceRun*>(run);

  fParticle = localRun->fParticle;
 // fEnergy   = localRun->fEnergy;
 
  fScintEnergy += localRun->fScintEnergy;
  fScintCount  += localRun->fScintCount;

  fScintillationCounter += localRun->fScintillationCounter;
  fScintillation2 += localRun->fScintillation2;

  G4Run::Merge(run);
}


void OpNoviceRun::FillPerEvent()
{
    auto analysisManager = G4AnalysisManager::Instance();
    
    G4int counter = 0;
  for ( auto edep : fEdep ) {
    analysisManager->FillH1(counter, edep);
    analysisManager->FillNtupleDColumn(counter++, edep);
  }
  for ( auto trackLength : fTrackLength ) {
    analysisManager->FillH1(counter, trackLength);
    analysisManager->FillNtupleDColumn(counter++, trackLength);
  }  
  analysisManager->AddNtupleRow();  
}

void OpNoviceRun::Reset()
{ 
  for ( auto& edep : fEdep ) { 
    edep = 0.; 
  }
  for ( auto& trackLength : fTrackLength ) {
    trackLength = 0.; 
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void OpNoviceRun::EndOfRun()
{
  if(numberOfEvent == 0)
    return;
  G4double TotNbofEvents = G4double(numberOfEvent);

  fScintillationCounter /= TotNbofEvents;
  fScintillation2 /= TotNbofEvents;
  G4double rmsScint =
    fScintillation2 - fScintillationCounter * fScintillationCounter;
  if(rmsScint > 0.)
    rmsScint = std::sqrt(rmsScint);
  else
    rmsScint = 0.;
    

  G4int prec = G4cout.precision(3);
  G4cout << "\n ======================== run summary ======================\n";

  G4cout << "Primary particle was: " << fParticle->GetParticleName() << G4endl;
       //  << " with energy " << G4BestUnit(fEnergy, "Energy") << "." << G4endl;
  G4cout << "Number of events: " << numberOfEvent << G4endl;
  G4cout << "Average number of scintillation photons created per event: "
         << fScintillationCounter << " +- " << rmsScint << G4endl;
  G4cout << "Average energy of scintillation photons created per event: "
         << (fScintEnergy / eV) / TotNbofEvents << " eV." << G4endl;

  G4cout << G4endl;
  G4cout.precision(prec);
}

