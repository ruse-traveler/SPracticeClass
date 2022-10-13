// 'SPracticeClass.h'
// Derek Anderson
// 10.11.2022
//
// Small class to test compiling and running
// in sPHENIX world.

#ifndef SPracticeClass_h
#define SPracticeClass_h

// standard c includes
#include <vector>
#include <cassert>
#include <iostream>

// class declarations
#include <TH1.h>
#include <TFile.h>
#include <TTree.h>
#include <TString.h>

using namespace std;

// global constants
static const UInt_t sk_nBins(2);



// SPracticeClass definition --------------------------------------------------

class SPracticeClass {

  // public elements
  public:

    // ctor/dtor
    SPracticeClass(const TString sTree="", const TString sInput="oops.root", const TString sOutput="test.root");
    ~SPracticeClass();

    // analysis methods
    int Init();
    int Analyze();
    int End();

  // private elements
  private:

    // io members
    TFile   *m_fInput;
    TFile   *m_fOutput;
    TTree   *m_tInput;
    TString  m_sTree;
    TString  m_sInput;
    TString  m_sOutput;

    // output histograms
    TH1D *m_hTrgEta;
    TH1D *m_hTrgEne;
    TH1D *m_hJetPtCorr;
    TH1D *m_hJetArea;
    TH1D *m_hJetNumCst;
    TH1D *m_hCstEta;
    TH1D *m_hCstPt;

    // input tree leaves (event level)
    Int_t    m_eventIndex;
    Int_t    m_numJets;
    Int_t    m_runId;
    Double_t m_refmult;
    Double_t m_partonicPt;
    Double_t m_tsp;
    Double_t m_trgEta;
    Double_t m_trgPhi;
    Double_t m_trgEt;
    Double_t m_rho;
    Double_t m_sigma;
    Double_t m_vz;
    // input tree leaves (jet level)
    vector<Int_t>    m_jetIndex;
    vector<Int_t>    m_jetNumCons;
    vector<Double_t> m_jetPt;
    vector<Double_t> m_jetPtCorr;
    vector<Double_t> m_jetEta;
    vector<Double_t> m_jetPhi;
    vector<Double_t> m_jetEne;
    vector<Double_t> m_jetArea;
    // input tree leaves (constituent level)
    vector<vector<Double_t>> m_cstPt;
    vector<vector<Double_t>> m_cstEta;
    vector<vector<Double_t>> m_cstPhi;
    vector<vector<Double_t>> m_cstEne;

    // input tree leaves
    TBranch *m_brEventIndex;
    TBranch *m_brNumJets;
    TBranch *m_brRunId;
    TBranch *m_brRefmult;
    TBranch *m_brPartonicPt;
    TBranch *m_brTsp;
    TBranch *m_brTrgEta;
    TBranch *m_brTrgPhi;
    TBranch *m_brTrgEt;
    TBranch *m_brRho;
    TBranch *m_brSigma;
    TBranch *m_brVz;
    TBranch *m_brJetIndex;
    TBranch *m_brJetNumCons;
    TBranch *m_brJetPt;
    TBranch *m_brJetPtCorr;
    TBranch *m_brJetEta;
    TBranch *m_brJetPhi;
    TBranch *m_brJetEne;
    TBranch *m_brJetArea;
    TBranch *m_brCstPt;
    TBranch *m_brCstEta;
    TBranch *m_brCstPhi;
    TBranch *m_brCstEne;

};  // end SPracticeClass definition

#endif
#ifdef SPracticeClass_cc

// ctor/dtor definitions ------------------------------------------------------

SPracticeClass::SPracticeClass(const TString sTree, const TString sInput, const TString sOutput) {

  m_sTree   = sTree;
  m_sInput  = sInput;
  m_sOutput = sOutput;

}  // end ctor

SPracticeClass::~SPracticeClass() {

  if (!m_tInput) {
    return;
  } else {
    delete m_tInput -> GetCurrentFile();
  }

}  // end dtor

#endif

// end ------------------------------------------------------------------------
