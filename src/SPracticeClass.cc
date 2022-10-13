// SPracticeClass.cc
// Derek Anderson
// 10.11.2022
//
// Small class to test compiling and running
// in sPHENIX world.

#define SPracticeClass_cc

// header file
#include "SPracticeClass.h"



// Init definition ------------------------------------------------------------

int SPracticeClass::Init() {

  // announce start
  cout << "\n  Beginning practice class exection.\n"
       << "    Initializing:"
       << endl;

  // open files
  m_fInput  = new TFile(m_sInput.Data(), "read");
  m_fOutput = new TFile(m_sOutput.Data(), "recreate");
  if (!m_fInput || !m_fOutput) {
    cerr << "PANIC: couldn't open input or output file!\n"
         << "       m_fInput = " << m_fInput << ", m_fOutput = " << m_fOutput << "\n"
         << endl;
    assert(m_fInput && m_fOutput);
  }
  cout << "      Opened files." << endl;

  // grab input tree
  m_fInput -> GetObject(m_sTree.Data(), m_tInput);
  if (!m_tInput) {
    cerr << "PANIC: couldn't grab input tree!" << endl;
    assert(m_tInput);
  }
  cout << "      Grabbed tree." << endl;

  // initialize input tree
  m_tInput -> SetMakeClass(1);
  m_tInput -> SetBranchAddress("eventIndex", &m_eventIndex, &m_brEventIndex);
  m_tInput -> SetBranchAddress("Refmult",    &m_refmult,    &m_brRefmult);
  m_tInput -> SetBranchAddress("NJets",      &m_numJets,    &m_brNumJets);
  m_tInput -> SetBranchAddress("RunId",      &m_runId,      &m_brRunId);
  m_tInput -> SetBranchAddress("PartonicPt", &m_partonicPt, &m_brPartonicPt);
  m_tInput -> SetBranchAddress("TSP",        &m_tsp,        &m_brTsp);
  m_tInput -> SetBranchAddress("TrgEta",     &m_trgEta,     &m_brTrgEta);
  m_tInput -> SetBranchAddress("TrgPhi",     &m_trgPhi,     &m_brTrgPhi);
  m_tInput -> SetBranchAddress("TrgEt",      &m_trgEt,      &m_brTrgEt);
  m_tInput -> SetBranchAddress("Rho",        &m_rho,        &m_brRho);
  m_tInput -> SetBranchAddress("Sigma",      &m_sigma,      &m_brSigma);
  m_tInput -> SetBranchAddress("JetIndex",   &m_jetIndex,   &m_brJetIndex);
  m_tInput -> SetBranchAddress("JetNCons",   &m_jetNumCons, &m_brJetNumCons);
  m_tInput -> SetBranchAddress("JetPt",      &m_jetPt,      &m_brJetPt);
  m_tInput -> SetBranchAddress("JetPtCorr",  &m_jetPtCorr,  &m_brJetPtCorr);
  m_tInput -> SetBranchAddress("JetEta",     &m_jetEta,     &m_brJetEta);
  m_tInput -> SetBranchAddress("JetPhi",     &m_jetPhi,     &m_brJetPhi);
  m_tInput -> SetBranchAddress("JetE",       &m_jetEne,     &m_brJetEne);
  m_tInput -> SetBranchAddress("JetArea",    &m_jetArea,    &m_brJetArea);
  m_tInput -> SetBranchAddress("JetConsPt",  &m_cstPt,      &m_brCstPt);
  m_tInput -> SetBranchAddress("JetConsEta", &m_cstEta,     &m_brCstEta);
  m_tInput -> SetBranchAddress("JetConsPhi", &m_cstPhi,     &m_brCstPhi);
  m_tInput -> SetBranchAddress("JetConsE",   &m_cstEne,     &m_brCstEne);
  cout << "      Initialized input tree." << endl;

  // initialize output histograms
  const UInt_t  kNumEtaBins(20);
  const UInt_t  kNumEneBins(100);
  const UInt_t  kNumPtBins(100);
  const UInt_t  kNumAreaBins(25);
  const UInt_t  kNumCstBins(50);
  const Float_t kEtaBins[sk_nBins]  = {-2., 2.};
  const Float_t kEneBins[sk_nBins]  = {0., 100.};
  const Float_t kPtBins[sk_nBins]   = {-50., 50.};
  const Float_t kAreaBins[sk_nBins] = {0., 5.};
  const Float_t kCstBins[sk_nBins]  = {0., 50.};
  m_hTrgEta    = new TH1D("hTrgEta",    "Trigger #eta",      kNumEtaBins,  kEtaBins[0],  kEtaBins[1]);
  m_hTrgEne    = new TH1D("hTrgEne",    "Trigger energy",    kNumEneBins,  kEneBins[0],  kEneBins[1]);
  m_hJetPtCorr = new TH1D("hJetPtCorr", "Jet p_{T}^{corr}",  kNumPtBins,   kPtBins[0],   kPtBins[1]);
  m_hJetArea   = new TH1D("hJetArea",   "Jet area",          kNumAreaBins, kAreaBins[0], kAreaBins[1]);
  m_hJetNumCst = new TH1D("hJetNumCst", "Jet N_{cst}",       kNumCstBins,  kCstBins[0],  kCstBins[1]);
  m_hCstEta    = new TH1D("hCstEta",    "Constituent #eta",  kNumEtaBins,  kEtaBins[0],  kEtaBins[1]);
  m_hCstPt     = new TH1D("hCstPt",     "Constituent p_{T}", kNumPtBins,   kPtBins[0],   kPtBins[1]);
  m_hTrgEta    -> Sumw2();
  m_hTrgEne    -> Sumw2();
  m_hJetPtCorr -> Sumw2();
  m_hJetArea   -> Sumw2();
  m_hJetNumCst -> Sumw2();
  m_hCstEta    -> Sumw2();
  m_hCstPt     -> Sumw2();
  cout << "      Initialized output histograms." << endl;

  // exit initialization
  cout << "    Finished initialization." << endl;
  return 1;

}  // end Init()



// Analyze definition ---------------------------------------------------------

int SPracticeClass::Analyze() {

  // check for tree and announce method
  if (m_tInput == 0) {
    cerr << "PANIC: no input tree!" << endl;
    assert(m_tInput);
  }
  cout << "    Analyzing:" <<endl;

  // grab no. of events
  const Long64_t k_nEvts = m_tInput -> GetEntriesFast();
  cout << "      " << k_nEvts << " events to process:" << endl;

  // event loop
  UInt_t   nTrg(0);
  UInt_t   nJet(0);
  Long64_t nBytes(0);
  for (Long64_t iEvt = 0; iEvt < k_nEvts; iEvt++) {

    // grab entry
    const Long64_t bytes = m_tInput -> GetEntry(iEvt);
    if (bytes < 0) {
      break;
    } else {
      nBytes += bytes;
      cout << "        processing event " << iEvt + 1 << "/" << k_nEvts << "...\r" << flush;
      if ((iEvt + 1) == k_nEvts) cout << endl;
    }
 
    // fill trigger histograms
    m_hTrgEta -> Fill(m_trgEta);
    m_hTrgEne -> Fill(m_trgEt);
    ++nTrg;

    /* jet loop would go here */

  }  // end event loop
  cout << "      Finished event loop:\n"
       << "        nTrg = " << nTrg << ", nJet = " << nJet
       << endl;

  // normalize histograms
  const Double_t k_trgScale = 1. / (Double_t) nTrg;
  const Double_t k_jetScale = 1. / (Double_t) nTrg;
  const Double_t k_cstScale = 1. / (Double_t) (nTrg * nJet);
  m_hTrgEta    -> Scale(k_trgScale);
  m_hTrgEne    -> Scale(k_trgScale);
  m_hJetPtCorr -> Scale(k_jetScale);
  m_hJetArea   -> Scale(k_jetScale);
  m_hJetNumCst -> Scale(k_jetScale);
  m_hCstEta    -> Scale(k_cstScale);
  m_hCstPt     -> Scale(k_cstScale);
  cout << "      Normalized histograms." << endl;

  // exit analysis
  cout << "    Finished analysis." << endl;
  return 1;

}  // end Analyze()



// End definition -------------------------------------------------------------

int SPracticeClass::End() {

  // announce method
  cout << "    Ending:" << endl;

  // save histograms
  m_fOutput    -> cd();
  m_hTrgEta    -> Write();
  m_hTrgEne    -> Write();
  m_hJetPtCorr -> Write();
  m_hJetArea   -> Write();
  m_hJetNumCst -> Write();
  m_hCstEta    -> Write();
  m_hCstPt     -> Write();
  cout << "      Saved output histograms." << endl;

  // close files
  m_fOutput -> cd();
  m_fOutput -> Close();
  m_fInput  -> cd();
  m_fInput  -> Close();
  cout << "      Closed files." << endl;

  // exit ending
  cout << "    Finished ending.\n"
       << "  Practice class execution done!\n"
       << endl;
  return 1;

}  // end End()

// end ------------------------------------------------------------------------
