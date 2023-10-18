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
/// \file OpNovice/src/OpNoviceRunAction.cc
/// \brief Implementation of the OpNoviceRunAction class
//
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "OpNoviceRunAction.hh"
#include "OpNovicePrimaryGeneratorAction.hh"
#include "OpNoviceRun.hh"

#include "G4ParticleDefinition.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "Analysis.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OpNoviceRunAction::OpNoviceRunAction(OpNovicePrimaryGeneratorAction* prim)
  : G4UserRunAction()
  , fRun(nullptr)
  , fPrimary(prim)
{
      G4RunManager::GetRunManager()->SetPrintProgress(100);
      
      auto analysisManager = G4AnalysisManager::Instance();
      analysisManager->SetVerboseLevel(1);
      
      analysisManager->CreateH1("Eabs", "Deposited energy of alpha particles in the absorber", 100, 0.*MeV, 6*MeV, "MeV");
      analysisManager->CreateH1("Labs", "Track length of alpha particles in the absorber", 100, 0.*mm, 60*mm, "mm");
      analysisManager->CreateH1("Bragg", "BraggPeak", 100, 0*cm, 10*cm);
      analysisManager->CreateH1("Spectrum", "Radioluminescence Spectrum", 250, 3.1*eV, 6.2*eV, "eV");

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OpNoviceRunAction::~OpNoviceRunAction() {
    delete G4AnalysisManager::Instance();
}

G4Run* OpNoviceRunAction::GenerateRun()
{
  fRun = new OpNoviceRun();
  return fRun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void OpNoviceRunAction::BeginOfRunAction(const G4Run* run)
{ 
  if(fPrimary)
  {
    G4ParticleDefinition* particle =
      fPrimary->GetParticleGun()->GetParticleDefinition();
      fRun->SetPrimary(particle);
  }  
    
  G4cout << "### Run " << run->GetRunID() << " start." << G4endl;

  // Get analysis manager & Open an output file
  auto analysisManager = G4AnalysisManager::Instance();
  G4String fileName = "OpN.csv";
  analysisManager->OpenFile(fileName);
  
}

void OpNoviceRunAction::EndOfRunAction(const G4Run* )
{
  // print histogram statistics
  //
  auto analysisManager = G4AnalysisManager::Instance();
  
    if(!isMaster)
    fRun->EndOfRun();
  
  if ( analysisManager->GetH1(1) ) {
    G4cout << G4endl << " ----> print histograms statistic ";
    if(!isMaster) {
      G4cout << "for the entire run " << G4endl << G4endl; 
    }
    else {
      G4cout << "for the local thread " << G4endl << G4endl; 
    }
    
    G4cout << " EAbs : mean = " 
       << G4BestUnit(analysisManager->GetH1(0)->mean(), "Energy") 
       << " rms = " 
       << G4BestUnit(analysisManager->GetH1(0)->rms(),  "Energy") << G4endl;
    G4cout << " LAbs : mean = " 
      << G4BestUnit(analysisManager->GetH1(1)->mean(), "Length") 
      << " rms = " 
      << G4BestUnit(analysisManager->GetH1(1)->rms(),  "Length") << G4endl;

  }

  // save histograms
  //
  analysisManager->Write();
  analysisManager->CloseFile();

}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
