// 'runPracticeClass.C'
// Derek Anderson
// 10.10.2022
//
// A simple macro to test running
// a compiled class in sPHENIX world.

#ifndef RUNPRACTICECLASS_C
#define RUNPRACTICECLASS_C

// user include
#include "/sphenix/u/danderson/install/include/spracticeclass/SPracticeClass.h"

// root includes
#include <TString.h>

// load libraries
R__LOAD_LIBRARY(/sphenix/u/danderson/install/lib/libspracticeclass.so)



void runPracticeClass() {

  // input/output
  const TString k_sTree("JetTree");
  const TString k_sInput("./input/pp200r9pt9rff.forUnfolding_Det.noTrigger.r02rm1chrg.d5m3y2020.root");
  const TString k_sOutput("./output/test.root");

  // run test class
  SPracticeClass *practice = new SPracticeClass(k_sTree.Data(), k_sInput.Data(), k_sOutput.Data());
  practice -> Init();
  practice -> Analyze();
  practice -> End();

}  // end runPracticeClass()

#endif

// end ------------------------------------------------------------------------
