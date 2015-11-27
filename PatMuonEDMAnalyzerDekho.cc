#include <memory>
#include"stdio.h"
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

#include <TH1F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TSystem.h>
#include <TLorentzVector.h>

#include "DataFormats/FWLite/interface/Event.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/FWLite/interface/AutoLibraryLoader.h"

#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Muon.h"

#include "DataFormats/PatCandidates/interface/Electron.h"

#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "PhysicsTools/FWLite/interface/CommandLineParser.h"
using namespace std;

#include "Electron.hh"
#include "Muon.hh"
#include "ElectronMuon.hh"
#include "ElectronMuonOppChrg.hh"
#include "ElectronMuonExtraLoose.hh"
#include "Mllcut.hh"
#include "Met.hh"
#include "ElMuMet.hh"

int main(int argc, char* argv[])
{
  // ----------------------------------------------------------------------
  // First Part: 
  //
  //  * enable the AutoLibraryLoader 
  //  * book the histograms of interest 
  //  * open the input file
  // ----------------------------------------------------------------------

  // load framework libraries
  gSystem->Load( "libFWCoreFWLite" );
  AutoLibraryLoader::enable();
    
    int n=32;
    char constName[]="/afs/cern.ch/work/p/ppriyank/public/topQuark/CMSSW_7_4_7_patch2/src/Analysis/antiTopInput/crab_antiTopInput/results/B2GEDMNtuple_";
    char fname[160];
    
    Electron*  ep=0;
    Electron*  epf1=0;
    Electron*  epf2=0;
    Muon*  mp=0;
    Muon*  mpf1=0;
    Muon*  mpf2=0;
    Met* metp=0;
    Met* metpf=0;
    ElectronMuon*  emp=0;
    ElectronMuon*  emp2e=0;
    ElectronMuon*  emp2mu=0;
    ElectronMuonOppChrg* empOppChrg=0;
    ElectronMuonOppChrg* empOppChrg2e=0;
    ElectronMuonOppChrg* empOppChrg2mu=0;
    ElectronMuonExtraLoose* empel=0;
    ElectronMuonExtraLoose* empel2e=0;
    ElectronMuonExtraLoose* empel2mu=0;
    Mllcut* obpMllCut=0;
    Mllcut* obpMllCut2e=0;
    Mllcut* obpMllCut2mu=0;
    ElectronMuonMet* obpEMM=0;
    ElectronMuonMet* obpEMM2e=0;
    ElectronMuonMet* obpEMM2mu=0;
    
    fwlite::TFileService fse = fwlite::TFileService("tight_electron.root");
    fwlite::TFileService fsm = fwlite::TFileService("tight_muon.root");
   // fwlite::TFileService fsmet = fwlite::TFileService("original_met.root");
    
    fwlite::TFileService fsem = fwlite::TFileService("electronMuononeTeoneTm.root");
    fwlite::TFileService fsem2e = fwlite::TFileService("electronMuononeTeoneTm2e.root");
    fwlite::TFileService fsem2mu = fwlite::TFileService("electronMuononeTeoneTm2mu.root");
    
    fwlite::TFileService fsemOppChrg = fwlite::TFileService("electronMuonOppositeCharge.root");
    fwlite::TFileService fsemOppChrg2e = fwlite::TFileService("electronMuonOppositeCharge2e.root");
    fwlite::TFileService fsemOppChrg2mu = fwlite::TFileService("electronMuonOppositeCharge2mu.root");
    
    fwlite::TFileService fsemel = fwlite::TFileService("electronMuonExtraloose.root");
    fwlite::TFileService fsemel2e = fwlite::TFileService("electronMuonExtraloose2e.root");
    fwlite::TFileService fsemel2mu = fwlite::TFileService("electronMuonExtraloose2mu.root");
    
    fwlite::TFileService fsmll = fwlite::TFileService("mllCUt1e1m.root");
    fwlite::TFileService fsmll2e = fwlite::TFileService("mllCUt2e.root");
    fwlite::TFileService fsmll2mu = fwlite::TFileService("mllCUt2m.root");
    
    fwlite::TFileService fsEMM = fwlite::TFileService("met.root");
    fwlite::TFileService fsEMM2e = fwlite::TFileService("met2e.root");
    fwlite::TFileService fsEMM2mu = fwlite::TFileService("met2mu.root");
    
    vector<TH1F*>* hve = Electron::getHistPointers(fse);
    vector<TH1F*>* hvm = Muon::getHistPointers(fsm);
   // vector<TH1F*>* hvmet = Met::getHistPointers(fsmet);
    
    vector<TH1F*>* hvem = ElectronMuon::getHistPointers(fsem, 1);
    vector<TH1F*>* hvem2e = ElectronMuon::getHistPointers(fsem2e, 2);
    vector<TH1F*>* hvem2mu = ElectronMuon::getHistPointers(fsem2mu, 3);
    
    vector<TH1F*>* hvemOppChrg = ElectronMuonOppChrg::getHistPointers(fsemOppChrg, 1);
    vector<TH1F*>* hvemOppChrg2e = ElectronMuonOppChrg::getHistPointers(fsemOppChrg2e, 2);
    vector<TH1F*>* hvemOppChrg2mu = ElectronMuonOppChrg::getHistPointers(fsemOppChrg2mu, 3);
    
    vector<TH1F*>* hvemel = ElectronMuonExtraLoose::getHistPointers(fsemel, 1);
    vector<TH1F*>* hvemel2e = ElectronMuonExtraLoose::getHistPointers(fsemel2e, 2);
    vector<TH1F*>* hvemel2mu = ElectronMuonExtraLoose::getHistPointers(fsemel2mu, 3);
    
    vector<TH1F*>* hvmll = Mllcut::getHistPointers(fsmll, 1);
    vector<TH1F*>* hvmll2e = Mllcut::getHistPointers(fsmll2e, 2);
    vector<TH1F*>* hvmll2mu = Mllcut::getHistPointers(fsmll2mu, 3);
    
    vector<TH1F*>* hvEMM = ElectronMuonMet::getHistPointers(fsEMM, 1);
    vector<TH1F*>* hvEMM2e = ElectronMuonMet::getHistPointers(fsEMM2e, 2);
    vector<TH1F*>* hvEMM2mu = ElectronMuonMet::getHistPointers(fsEMM2mu, 3);
    
    int cTTE=0,cEW1e=0,cEW2e=0,cTTM=0,cEW1m=0,cEW2m=0,c1E1M=0,c2E=0,c2M=0,cOppChrg1e1m=0,cOppChrg2e=0,cOppChrg2m=0,cExLoose1e1m=0,cExLoose2e=0,cExLoose2m=0,cmllc1e1m=0, cmllc2e=0, cmllc2m=0, cMetCut=0,cEMuMet1e1m=0,cEMuMet2e=0,cEMuMet2m=0;
    
    for(int i=1;i<=n;i++)
    {
        
        sprintf(fname,"%s%d.root",constName,i);
        cout<<"File Name:"<<fname<<endl;
    
        ep = new Electron();
        ep->setData(fname);
        
        epf1 = new Electron(ep->selectData1());
        epf2 = new Electron(ep->selectData2());
        ep->fillHisto(hve);
                cTTE += ep->getTTE();
                cEW1e += ep->getEW1E();
                cEW2e += ep->getEW2E();
        
        
        mp = new Muon();
        mp->setData(fname);
        
        mpf1 = new Muon(mp->selectData1());
        mpf2 = new Muon(mp->selectData2());
        mp->fillHisto(hvm);
        cTTM += mp->getTTM();
        cEW1m += mp->getEW1M();
        cEW2m += mp->getEW2M();
        
        emp = new ElectronMuon();
        emp2e = new ElectronMuon();
        emp2mu = new ElectronMuon();
        emp->setData1(*epf1,*mpf1,*ep,*mp);
       // cout<<"calling 2e in emu ... from main"<<endl;
        emp2e->setData2(*epf2,*ep,*mp);
       // cout<<"calling 2m in emu ... from main"<<endl;
        emp2mu->setData3(*mpf2,*ep,*mp);
        emp->fillHisto(hvem, 1);
       // cout<<"calling fill histo 2e in emu ... from main"<<endl;
        emp2e->fillHisto(hvem2e, 2);
      //  cout<<"calling fill histo 2m in emu ... from main"<<endl;
        emp2mu->fillHisto(hvem2mu, 3);
        
        c1E1M += emp->getEW1E1M();
        c2E += emp2e->getEW2E();
        c2M += emp2mu->getEW2M();
        
        empOppChrg = new ElectronMuonOppChrg();
        empOppChrg2e = new ElectronMuonOppChrg();
        empOppChrg2mu = new ElectronMuonOppChrg();
        empOppChrg->setData(*emp,*ep,*mp);
        empOppChrg2e->setData(*emp2e,*ep,*mp);
        empOppChrg2mu->setData(*emp2mu,*ep,*mp);
        empOppChrg->fillHisto(hvemOppChrg, 1);
        empOppChrg2e->fillHisto(hvemOppChrg2e, 2);
        empOppChrg2mu->fillHisto(hvemOppChrg2mu, 3);
        
        cOppChrg1e1m += empOppChrg->getEWOppChrg();
        cOppChrg2e += empOppChrg2e->getEWOppChrg();
        cOppChrg2m += empOppChrg2mu->getEWOppChrg();
        
        empel = new ElectronMuonExtraLoose();
        empel2e = new ElectronMuonExtraLoose();
        empel2mu = new ElectronMuonExtraLoose();
        empel->setData1(*empOppChrg,*ep,*mp);
        empel2e->setData2(*empOppChrg2e,*ep,*mp);
        empel2mu->setData3(*empOppChrg2mu,*ep,*mp);
        empel->fillHisto(hvemel, 1);
        empel2e->fillHisto(hvemel2e, 2);
        empel2mu->fillHisto(hvemel2mu, 3);
        
        cExLoose1e1m += empel->getEWExLoose1e1m();
        cExLoose2e += empel2e->getEWExLoose2e();
        cExLoose2m += empel2mu->getEWExLoose2m();
        
        obpMllCut = new Mllcut();
        obpMllCut2e = new Mllcut();
        obpMllCut2mu = new Mllcut();
        obpMllCut->setData(*empel,*ep,*mp);
        obpMllCut2e->setData(*empel2e,*ep,*mp);
        obpMllCut2mu->setData(*empel2mu,*ep,*mp);
        obpMllCut->fillHisto(hvmll, 1);
        obpMllCut2e->fillHisto(hvmll2e, 2);
        obpMllCut2mu->fillHisto(hvmll2mu, 3);
        
        cmllc1e1m += obpMllCut->getEWcmllc();
        cmllc2e += obpMllCut2e->getEWcmllc();
        cmllc2m += obpMllCut2mu->getEWcmllc();
        
        metp = new Met();
        metp->setData(fname);
        metpf = new Met(metp->selectData());
        
        cMetCut += metp->getEWMetCut();
        
        obpEMM = new ElectronMuonMet();
        obpEMM2e = new ElectronMuonMet();
        obpEMM2mu = new ElectronMuonMet();
        obpEMM->setData(*obpMllCut,*metp,*ep,*mp);
        obpEMM2e->setData(*obpMllCut2e,*metpf,*ep,*mp);
        obpEMM2mu->setData(*obpMllCut2mu,*metpf,*ep,*mp);
        obpEMM->fillHisto(hvEMM, 1);
        obpEMM2e->fillHisto(hvEMM2e, 2);
        obpEMM2mu->fillHisto(hvEMM2mu, 3);
        
        cEMuMet1e1m += obpEMM->getEMuMet();
        cEMuMet2e += obpEMM2e->getEMuMet();
        cEMuMet2m += obpEMM2mu->getEMuMet();
       
        delete ep;
        delete epf1;
        delete epf2;
        delete mp;
        delete mpf1;
        delete mpf2;
        delete emp;
        delete emp2e;
        delete emp2mu;
        delete empOppChrg;
        delete empOppChrg2e;
        delete empOppChrg2mu;
        delete empel;
        delete empel2e;
        delete empel2mu;
        delete obpMllCut;
        delete obpMllCut2e;
        delete obpMllCut2mu;
        delete obpEMM;
        delete obpEMM2e;
        delete obpEMM2mu;
    }
        
    cout<<"Total number of tight electrons: "<< cTTE <<endl;
    cout<<"Total number of events having only one tight electron: "<< cEW1e <<endl;
    cout<<"Total number of events having exactly two tight electrons: "<< cEW2e <<endl;
    cout<<"Total number of tight muons: "<< cTTM << endl;
    cout<<"Total number of events having only one tight muon: "<< cEW1m << endl;
    cout<<"Total number of events having exactly two tight muons: "<< cEW2m <<endl;
    cout<<"Total number of events having only one tight electron and only one tight muon: " << c1E1M <<endl;
    cout<<"Total number of events having only two tight electrons: " << c2E <<endl;
    cout<<"Total number of events having only two tight muons: " << c2M <<endl;
    cout<<"Total number of events having ooposite charge leptons 1e1mu: " << cOppChrg1e1m <<endl;
    cout<<"Total number of events having ooposite charge leptons 2e: " << cOppChrg2e <<endl;
    cout<<"Total number of events having ooposite charge leptons 2mu: " << cOppChrg2m <<endl;
    cout<<"total number of selected events due to extra loose cuts in 1e 1mu : "<<cExLoose1e1m<<endl;
    cout<<"total number of selected events due to extra loose cuts in 2e : "<<cExLoose2e<<endl;
    cout<<"total number of selected events due to extra loose cuts in 2mu : "<<cExLoose2m<<endl;
    cout<<"total number of selected events after mll cuts in 1e 1mu : "<<cmllc1e1m<<endl;
    cout<<"total number of selected events after mll cuts in 2e : "<<cmllc2e<<endl;
    cout<<"total number of selected events after mll cuts in 2mu : "<<cmllc2m<<endl;
    cout<<"Total number of Mets passing cuts: "<< cMetCut <<endl;
    cout<<"total number of selected events due to met passing no cut 1e1mu :"<<cEMuMet1e1m<<endl;
    cout<<"total number of selected events due to met passing cut 2e :"<<cEMuMet2e<<endl;
    cout<<"total number of selected events due to met passing cut 2mu :"<<cEMuMet2m<<endl;

    return 0;
}

                        


