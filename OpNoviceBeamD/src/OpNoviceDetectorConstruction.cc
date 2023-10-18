
#include "OpNoviceDetectorConstruction.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"

#include "G4Material.hh"
#include "G4Element.hh"
#include "G4NistManager.hh"

#include "G4SDManager.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
//#include "G4PSEnergyDeposit.hh"
//#include "G4PSTrackLength.hh"
#include "G4PSFlatSurfaceCurrent.hh"
#include "G4SDParticleFilter.hh"

#include "G4LogicalVolume.hh"
#include "G4OpticalSurface.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OpNoviceDetectorConstruction::OpNoviceDetectorConstruction()
  : G4VUserDetectorConstruction()
{
  fExpHall_x = fExpHall_y = fExpHall_z = 25.0 * m;
    //one cube 50m length

  Abs_x = Abs_y = 15.0*cm;
  Abs_z = 15.0*cm;

}

OpNoviceDetectorConstruction::~OpNoviceDetectorConstruction() {}

G4VPhysicalVolume* OpNoviceDetectorConstruction::Construct()
{
//////////////////////////////////////////////////////////////////////////////////////////// ------------- Materials & Elements -------------

// Air

  G4Material* air       = G4NistManager::Instance()->ConstructNewGasMaterial("Air", "G4_AIR", 295.15*kelvin, 1.0*atmosphere);

//////////////////////////////////////////////////////////////////////////////////////////// ------------ Generate & Add Material Properties Table ------------

  std::vector<G4double> photonEnergy = {
                                        3.10182637 * eV,
                                        3.10960622 * eV,
                                        3.130808081 * eV,
                                        3.138734177 * eV,
                                        3.147499365 * eV,
                                        3.154707379 * eV,
                                        3.158726115 * eV,
                                        3.162755102 * eV,
                                        3.17003324 * eV,
                                        3.178159446 * eV,
                                        3.195360825 * eV,
                                        3.203617571 * eV,
                                        3.211917098 * eV,
                                        3.22025974 * eV,
                                        3.228645833 * eV,
                                        3.237075718 * eV,
                                        3.245549738 * eV,
                                        3.254068241 * eV,
                                        3.262631579 * eV,
                                        3.271240106 * eV,
                                        3.27989418 * eV,
                                        3.288594164 * eV,
                                        3.297340426 * eV,
                                        3.304371002 * eV,
                                        3.314973262 * eV,
                                        3.32386059 * eV,
                                        3.332795699 * eV,
                                        3.33817986 * eV,
                                        3.347192225 * eV,
                                        3.356253384 * eV,
                                        3.369021739 * eV,
                                        3.443888889 * eV,
                                        3.453481894 * eV,
                                        3.468942361 * eV,
                                        3.48258427 * eV,
                                        3.492394366 * eV,
                                        3.502259887 * eV,
                                        3.507213579 * eV,
                                        3.517163121 * eV,
                                        3.532193732 * eV,
                                        3.543298085 * eV,
                                        3.55243553 * eV,
                                        3.668047337 * eV,
                                        3.678931751 * eV,
                                        3.689880952 * eV,
                                        3.700895522 * eV,
                                        3.71420012 * eV,
                                        3.723123123 * eV,
                                        3.734337349 * eV,
                                        3.746751284 * eV,
                                        3.756969697 * eV,
                                        3.768389058 * eV,
                                        3.785648855 * eV,
                                        3.803067485 * eV,
                                        3.874375 * eV,
                                        3.898742138 * eV,
                                        3.917219589 * eV,
                                        3.928390368 * eV,
                                        3.942130366 * eV,
                                        3.955966816 * eV,
                                        3.968629962 * eV,
                                        3.980096308 * eV,
                                        3.999354839 * eV,
                                        4.012297735 * eV,
                                        4.025324675 * eV,
                                        4.038436482 * eV,
                                        4.051633987 * eV,
                                        4.064918033 * eV,
                                        4.078289474 * eV,
                                        4.091749175 * eV,
                                        4.105298013 * eV,
                                        4.118936877 * eV,
                                        4.132666667 * eV,
                                        4.146488294 * eV,
                                        4.160402685 * eV,
                                        4.173005722 * eV,
                                        4.188513514 * eV,
                                        4.202711864 * eV,
                                        4.217006803 * eV,
                                        4.333449843 * eV,
                                        4.348649597 * eV,
                                        4.363956353 * eV,
                                        4.38556774 * eV,
                                        4.40113596 * eV,
                                        4.416815105 * eV,
                                        4.553066471 * eV,
                                        4.569848876 * eV,
                                        4.586755457 * eV,
                                        4.602078693 * eV,
                                        4.619225037 * eV,
                                        4.773969965 * eV,
                                        4.792423657 * eV,
                                        4.811020567 * eV,
                                        4.997178557 * eV,
                                        5.017401862 * eV,
                                        5.037789516 * eV,
                                        5.226812816 * eV,
                                        5.248941575 * eV,
                                        5.271258503 * eV,
                                        5.459269044 * eV,
                                        5.483414418 * eV,
                                        5.507774323 * eV,
                                        5.635454545 * eV
  };

  std::vector<G4double> opticalAbsorption = {
      1 * km, 1 * km, 1 * km, 1 * km,  1 * km, 1 * km, 1 * km, 1 * km,
      1 * km, 1 * km, 1 * km,  1 * km, 1 * km, 1 * km, 1 * km, 1 * km,
      1 * km, 1 * km, 1 * km,  1 * km, 1 * km, 1 * km, 1 * km, 1 * km,
      1 * km, 1 * km, 1 * km,  1 * km, 1 * km, 1 * km, 1 * km, 1 * km,
      1 * km, 1 * km, 1 * km,  1 * km, 1 * km, 1 * km, 1 * km, 1 * km,
      1 * km, 1 * km, 1 * km,  1 * km, 1 * km, 1 * km, 1 * km, 1 * km,
      1 * km, 1 * km, 1 * km,  1 * km, 1 * km, 1 * km, 1 * km, 1 * km,
      1 * km, 1 * km, 1 * km,  1 * km, 1 * km, 1 * km, 1 * km, 1 * km,
      1 * km, 1 * km, 1 * km,  1 * km, 1 * km, 1 * km, 1 * km, 1 * km,
      1 * km, 1 * km, 1 * km,  1 * km, 1 * km, 1 * km, 1 * km, 1 * km,
      1 * km, 1 * km, 1 * km,  1 * km, 1 * km, 1 * km, 1 * km, 1 * km,
      1 * km, 1 * km, 1 * km,  1 * km, 1 * km, 1 * km, 1 * km, 1 * km,
      1 * km, 1 * km, 1 * km,  1 * km, 1 * km, 1 * km,  1 * km
  };

  std::vector<G4double> secondPositive = {0.010024358,
                                          0,
                                          0,
                                          0,
                                          0.016640931,
                                          0,
                                          0,
                                          0,
                                          0,
                                          0,
                                          0,
                                          0,
                                          0,
                                          0,
                                          0,
                                          0,
                                          0,
                                          0,
                                          0.019131683,
                                          0,
                                          0,
                                          0,
                                          0,
                                          0.036607469,
                                          0,
                                          0,
                                          0,
                                          0,
                                          0.024799356,
                                          0,
                                          0,
                                          0,
                                          0,
                                          0.10713594,
                                          0,
                                          0,
                                          0,
                                          0.042591332,
                                          0,
                                          0,
                                          0.004185663,
                                          0,
                                          0,
                                          0.220425744,
                                          0,
                                          0,
                                          0.000497513,
                                          0,
                                          0,
                                          0.000718939,
                                          0,
                                          0,
                                          0.009909364,
                                          0,
                                          0,
                                          0,
                                          0,
                                          0.174940606,
                                          0,
                                          0.131698446,
                                          0,
                                          0.048964332,
                                          0,
                                          0,
                                          0,
                                          0,
                                          0,
                                          0,
                                          0,
                                          0,
                                          0,
                                          0,
                                          0,
                                          0,
                                          0,
                                          0.020131462,
                                          0,
                                          0,
                                          0,
                                          0,
                                          0,
                                          0,
                                          0,
                                          0.000416674,
                                          0,
                                          0,
                                          0,
                                          0,
                                          0,
                                          5.36772E-07,
                                          0,
                                          0,
                                          0,
                                          0,
                                          0,
                                          0,
                                          0,
                                          0,
                                          0,
                                          0,
                                          0,
                                          0,
                                          0
  };
  std::vector<G4double> firstNegative = {0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0.470823023,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0
  };

  std::vector<G4double> gamaNO = {0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0.001745733,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0.007245872,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0.023887553,
                                  0,
                                  0,
                                  0.055693668,
                                  0,
                                  0,
                                  0.073540687,
                                  0,
                                  0,
                                  0.031396889,
                                  0,
                                  0};
  // Air
  //
    std::vector<G4double> refractiveIndex = {
        1.000282778,
        1.000282832,
        1.000282981,
        1.000283036,
        1.000283098,
        1.000283149,
        1.000283178,
        1.000283206,
        1.000283258,
        1.000283316,
        1.00028344,
        1.0002835,
        1.00028356,
        1.000283621,
        1.000283682,
        1.000283743,
        1.000283806,
        1.000283868,
        1.000283932,
        1.000283996,
        1.00028406,
        1.000284125,
        1.000284191,
        1.000284243,
        1.000284323,
        1.000284391,
        1.000284459,
        1.0002845,
        1.000284569,
        1.000284638,
        1.000284736,
        1.000285323,
        1.000285399,
        1.000285523,
        1.000285633,
        1.000285712,
        1.000285792,
        1.000285832,
        1.000285913,
        1.000286037,
        1.000286128,
        1.000286204,
        1.000287182,
        1.000287277,
        1.000287372,
        1.000287468,
        1.000287585,
        1.000287664,
        1.000287763,
        1.000287873,
        1.000287964,
        1.000288067,
        1.000288222,
        1.00028838,
        1.000289038,
        1.000289266,
        1.000289441,
        1.000289547,
        1.000289678,
        1.000289811,
        1.000289934,
        1.000290045,
        1.000290232,
        1.000290359,
        1.000290488,
        1.000290617,
        1.000290749,
        1.000290881,
        1.000291016,
        1.000291152,
        1.000291289,
        1.000291428,
        1.000291569,
        1.000291711,
        1.000291855,
        1.000291986,
        1.000292148,
        1.000292297,
        1.000292448,
        1.000293708,
        1.000293877,
        1.000294047,
        1.00029429,
        1.000294465,
        1.000294644,
        1.000296235,
        1.000296437,
        1.000296641,
        1.000296827,
        1.000297037,
        1.00029899,
        1.000299231,
        1.000299475,
        1.000302013,
        1.0003023,
        1.000302591,
        1.0003054,
        1.000305742,
        1.000306091,
        1.000309149,
        1.000309559,
        1.000309976,
        1.000312231
    };

  G4MaterialPropertiesTable* myMPT2 = new G4MaterialPropertiesTable();
  myMPT2->AddProperty("RINDEX", photonEnergy, refractiveIndex);
  myMPT2->AddProperty("ABSLENGTH", photonEnergy, opticalAbsorption);
  myMPT2->AddProperty("SCINTILLATIONCOMPONENT1", photonEnergy, secondPositive);
  myMPT2->AddProperty("SCINTILLATIONCOMPONENT2", photonEnergy, firstNegative);
  myMPT2->AddProperty("SCINTILLATIONCOMPONENT3", photonEnergy, gamaNO);
  myMPT2->AddConstProperty("SCINTILLATIONYIELD", 19.0 / MeV);
  myMPT2->AddConstProperty("RESOLUTIONSCALE", 0);
  myMPT2->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 38.42 * ns);
  myMPT2->AddConstProperty("SCINTILLATIONTIMECONSTANT2", 62.3 * ns);
  myMPT2->AddConstProperty("SCINTILLATIONTIMECONSTANT3", 206.0 * ns);
  myMPT2->AddConstProperty("SCINTILLATIONYIELD1", 0.65);
  myMPT2->AddConstProperty("SCINTILLATIONYIELD2", 0.2);
  myMPT2->AddConstProperty("SCINTILLATIONYIELD3", 0.15);
  myMPT2->AddConstProperty("SCINTILLATIONRISETIME1", 0);
  myMPT2->AddConstProperty("SCINTILLATIONRISETIME2", 0);
  myMPT2->AddConstProperty("SCINTILLATIONRISETIME3", 0);

  G4cout << "Air G4MaterialPropertiesTable:" << G4endl;
  myMPT2->DumpTable();

  air->SetMaterialPropertiesTable(myMPT2);
 // air->GetIonisation()->SetBirksConstant(0.126 * mm / MeV);

  // ------------- Volumes --------------

  // The experimental Hall
  //
  G4Box* expHall_box = new G4Box("World", fExpHall_x, fExpHall_y, fExpHall_z);

  G4LogicalVolume* expHall_log =
    new G4LogicalVolume(expHall_box, air, "World", 0, 0, 0);

  G4VPhysicalVolume* expHall_phys =
    new G4PVPlacement(0, G4ThreeVector(), expHall_log, "World", 0, false, 0);
    
  //  The alpha Absorber
  //
   G4Box* Absorber = new G4Box("Absorber", Abs_x, Abs_y, Abs_z);

   G4LogicalVolume* Absorber_log =
    new G4LogicalVolume(Absorber, air, "Absorber", 0, 0, 0);

  //  G4VPhysicalVolume*
    Absorber_phys =
    new G4PVPlacement(0, G4ThreeVector(0, 0, 0*cm), Absorber_log, "Absorber", expHall_log, false, 0);

/*
//The Silver Plate
//
    G4Box* SilverPlate = new G4Box("SilverPlate", Ag_x, Ag_y, Ag_z);

    G4LogicalVolume* SilverPlate_log =
     new G4LogicalVolume(SilverPlate, silver, "SilverPlate", 0, 0, 0);

     SilverPlate_phys =
     new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, 0.1255*mm), SilverPlate_log, "SilverPlate", Absorber_log, false, 0);

*/
  return expHall_phys;
 }
 
 
 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
