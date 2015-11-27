class ElectronMuon;
class ElectronMuonExtraLoose;

class Muon
{
   /* struct CUT
    {
        bool   etac,ptc,isoc,tightc,all;
    };*/
    struct DATA
    {
        
        float  mID,eta,pt,iso,charge,phi,tight;
        bool   etac,ptc,isoc,tightc,all;
       // CUT    loose,tight;
    };
    
    vector<vector<DATA>*>*  v;
    int cTTM;
public:
    Muon()
    {
        v = new vector<vector<DATA>*>;
    }
    Muon(vector<vector<DATA>*>* uv)
    {
        
        v=uv;
    }
    int getTTM(){return cTTM;}
   // int getEW1M(){return cEW1M;}
   // int getEW2M(){return cEW2M;}
    
    void setData(const char* fname)
    {
        TFile* inFile = TFile::Open(fname);
        
        if(!inFile)
        {
            cout<<"Input Root File not open in muon class for processing"<<endl;
            return;
        }
        
        fwlite::Event ev(inFile);
        int evtID=0;
        
        for(ev.toBegin(); !ev.atEnd(); ++ev, evtID++)
        {
            edm::EventBase const & event = ev;
            
        /*    // Handle to the muon ParticleFlow
            edm::Handle<std::vector<float> > ParticleFlow;
            event.getByLabel(std::string("muons:muIsPFMuon"), ParticleFlow);
            // Handle to the muon GlobalMuon
            edm::Handle<std::vector<float> > GlobalMuon;
            event.getByLabel(std::string("muons:muIsGlobalMuon"), GlobalMuon);
            // Handle to the muon TrackerMuon
            edm::Handle<std::vector<float> > TrackerMuon;
            event.getByLabel(std::string("muons:muIsTrackerMuon"), TrackerMuon);*/
            // Handle to the muon muonPt
            edm::Handle<std::vector<float> > muonPt;
            event.getByLabel(std::string("muons:muPt"), muonPt);
            // Handle to the muon muonEta
            edm::Handle<std::vector<float> > muonEta;
            event.getByLabel(std::string("muons:muEta"), muonEta);
            // Handle to the muon muonIso04
            edm::Handle<std::vector<float> > muonIso04;
            event.getByLabel(std::string("muons:muIso04"), muonIso04);
            // Handle to the muon charge
            edm::Handle<std::vector<float> > muonCharge;
            event.getByLabel(std::string("muons:muCharge"), muonCharge);
            // Handle to the muon charge
            edm::Handle<std::vector<float> > muonPhi;
            event.getByLabel(std::string("muons:muPhi"), muonPhi);
            // Handle to the muon tight
            edm::Handle<std::vector<float> > muonTight;
            event.getByLabel(std::string("muons:muIsTightMuon"), muonTight);
            
            vector<DATA>* dv = new vector<DATA>;
            DATA d;
            
            for(unsigned int i=0;i<muonPt->size();i++)
            {
                d.mID = i;
             /*   d.particleFlow = ParticleFlow->at(i);
                d.globalMuon = GlobalMuon->at(i);
                d.trackerMuon = TrackerMuon->at(i);*/
                d.pt = muonPt->at(i);
                d.eta = muonEta->at(i);
                d.iso  = muonIso04->at(i);
                d.charge = muonCharge->at(i);
                d.phi = muonPhi->at(i);
                d.tight = muonTight->at(i);
                dv->push_back(d);
                
            }
            
            
            v->push_back(dv);
            
        }
        inFile->Close();
        
        setCuts();
        
        return;
    }
    
 /*   void printData(int p,string msg)
    {
        vector<DATA>* dv;
        DATA d;
        int tmu=0;
        int tevt=0;
        
        cout<<msg<<endl;
        for(unsigned int i=0; i < v->size(); i++)
        {
            dv=v->at(i);
            //cout<<i<<","<<dv->size()<<endl;
            if(dv->size()!=0)tevt++;
            for(unsigned int j=0;j<dv->size();j++)
            {
                d=dv->at(j);
                if(p==1 || p==0) cout<<"Event ID:"<<i<<", Muon ID:"<<j<<","<<" ParticleFlow:"<<d.particleFlow<<", GlobalMuon:"<<d.globalMuon<<", trackerMuon:"<<d.trackerMuon<<", Pt:"<<d.pt<<", Eta:"<<d.eta<<", ISO:"<<d.iso<<", charge:"<<d.charge<<endl;
                
                if(p==2||p==0)
                {
                    cout<<"TCEvent ID:"<<i<<", Muon ID:"<<j<<","<<" ParticleFlowc:"<<d.tight.particleFlowc<<", GlobalMuonc:"<<d.tight.globalMuonc<<", trackerMuonc:"<<d.tight.trackerMuonc<<", Ptc:"<<d.tight.ptc<<", Etac:"<<d.tight.etac<<", ISOc:"<<d.tight.isoc<<",allc:"<<d.loose.all<<endl;
                }
                if(p==3||p==0)
                {
                    cout<<"LCEvent ID:"<<i<<", Muon ID:"<<j<<","<<" ParticleFlowc:"<<d.tight.particleFlowc<<", GlobalMuonc:"<<d.tight.globalMuonc<<", trackerMuonc:"<<d.tight.trackerMuonc<<", Ptc:"<<d.tight.ptc<<", Etac:"<<d.tight.etac<<", ISOc:"<<d.tight.isoc<<",allc:"<<d.loose.all<<endl;
                }
                tmu++;
            }
            
        }
        
        cout<<"Total muons:"<<tmu<<" Total non empty events:"<<tevt<<endl;
        return;
    }
   */
    vector<vector<DATA>*>* selectData()
    {
        vector<DATA>* dv;
        DATA d;
        int tightCount=0;
        vector<vector<DATA>*>* fv = new vector<vector<DATA>*>;
        
        for(unsigned int i=0; i < v->size(); i++)
        {
            vector<DATA>* fdv= new vector<DATA>;
            
            dv=v->at(i);
            
          //  bool isEventSelected=false;
            for(unsigned int j=0;j<dv->size();j++)
            {
                d=dv->at(j);
                
                if(d.all)
                {
                  //  muon_number = j;
                    fdv->push_back(d);
                    tightCount++;
                }
            }
            
            fv->push_back(fdv);
        }
        
        cTTM=tightCount;
        return fv;
    }
  /*
    vector<vector<DATA>*>* selectData1()
    {
        vector<DATA>* dv;
        DATA d;
        
        vector<vector<DATA>*>* fv = new vector<vector<DATA>*>;
        int events = 0;
        int muonSelection = 0;
        for(unsigned int i=0; i < v->size(); i++)
        {
            int muon_number = 0;
            vector<DATA>* fdv= new vector<DATA>;
            
            dv=v->at(i);
            
            bool isEventSelected=false;
          //  int tightCount=0;
            
            for(unsigned int j=0;j<dv->size();j++)
            {
                d=dv->at(j);
                
                if(d.all)
                {
                    muonSelection++;
                    muon_number = j;
                //  tightCount++;
                }
            }
            
         //   if(tightCount==1){isEventSelected=true;//cout<<i<<" Reject2"<<endl;
            if(tightCount >= 1){isEventSelected=true;//cout<<i<<" Reject2"<<endl;
            }
            //-----------------------
            if(isEventSelected)
            {
                events++;
                    d=dv->at(muon_number);
                    
                      //  cout<<"Selected (on basis of only 1 tight muon) EventID: "<<i<<"  S MuonID: "<<muon_number<<endl;
                        fdv->push_back(d);
                        // only fill one tight muon's information
                
            }
            //-------------------------
            fv->push_back(fdv);
        }
    //    cout<<"Total number of tight muons: "<< muonSelection << endl;
      //  cout<<"Total number of events having only one tight muon: "<< events << endl;
        cTTM=muonSelection;
        cEW1M=events;
        return fv;
    }
    
    vector<vector<DATA>*>* selectData2()
    {
        vector<DATA>* dv;
        DATA d;
        
        vector<vector<DATA>*>* fv = new vector<vector<DATA>*>;
        int events =0;
        int muonSelection =0;
        for(unsigned int i=0; i < v->size(); i++)
        {
            int muon_number1 = 0;
            int muon_number2 = 0;
            
            vector<DATA>* fdv= new vector<DATA>;
            
            dv=v->at(i);
            
            bool isEventSelected=false;
            int tightCount=0;
            
            for(unsigned int j=0;j<dv->size();j++)
            {
                d=dv->at(j);
                
                if(d.tight.all)
                {
                    muonSelection++;
                    if(tightCount==0) muon_number1 = j;
                    if(tightCount==1) muon_number2 = j;
                    tightCount++;
                }
            }
            
            if(tightCount==2){isEventSelected=true;//cout<<i<<" Reject2"<<endl;
            }
            //-----------------------
            if(isEventSelected)
            {
                events++;
                d=dv->at(muon_number1);
                fdv->push_back(d);
                d=dv->at(muon_number2);
                //  cout<<"Selected (on basis of only 1 tight electron) EventID: "<<i<<"  S ElectronID: "<<elctron_number<<endl;
                fdv->push_back(d);
                // only fill one tight electron's information
                
            }
            //-------------------------
            fv->push_back(fdv);
        }
       // cout<<"Total number of tight muons: "<< muonSelection <<endl;
    //    cout<<"Total number of events having exactly two tight muons: "<< events <<endl;
        cEW2M=events;
        return fv;
    }
    */
  /*  void fillHisto(const char* outputFile)
    {
        vector<DATA>* dv;
        DATA d;
        
        fwlite::TFileService fs = fwlite::TFileService("tight_muon.root");
       // TFileDirectory dir = fs.mkdir("tight_muon");
        TH1F* muonPt_  = fs.make<TH1F>("muonPt_"  , "pt"  ,   100,   0., 400.);
        TH1F* exactlyOneMuonPt_  = fs.make<TH1F>("exactlyOneMuonPt_"  , "pt"  ,   100,   0., 400.);
        TH1F* exactlyOneMuonEta_  = fs.make<TH1F>("exactlyOneMuonEta_"  , "eta"  ,   100,   -3.0, 3.0);
        TH1F* exactlyOneMuonPhi_  = fs.make<TH1F>("exactlyOneMuonPhi_"  , "phi"  ,   100,  -3.5, 3.5);

        for(unsigned int i=0; i < v->size(); i++)
        {
            dv=v->at(i);
            int tightCount=0;
            int muon_number = 0;
            for(unsigned int j=0;j<dv->size();j++)
            {
                d=dv->at(j);
                if(d.tight.all)
                {
                    muonPt_->Fill(d.pt);
                    muon_number = j;
                    tightCount++;
                }
                
            }
            if(tightCount==1)
            {
                d=dv->at(muon_number);
                exactlyOneMuonPt_->Fill(d.pt);
                exactlyOneMuonEta_->Fill(d.eta);
                exactlyOneMuonPhi_->Fill(d.phi);
            }
        }
        return;
    }*/
    
    void setCuts()
    {
        
        vector<DATA>* dv;
        
       /* int tParticle_Flow_Muon_Cut = 1;
        int tGlobal_Muon_Cut = 1;
        int tTracker_Muon_Cut = 1;*/
        float tMuon_Tight_Cut_pt = 20.0;
        float tMuon_Tight_Cut_eta = 2.4;
        float tMuon_Relative_Isolation_Cut = 0.12;
        float tightMuon = 1;
        
       /* int lParticle_Flow_Muon_Cut = 1;
        int lGlobal_Muon_Cut = 1;
        int lTracker_Muon_Cut = 1;
        float lMuon_Tight_Cut_pt = 20.0;
        float lMuon_Tight_Cut_eta = 2.4;
        float lMuon_Relative_Isolation_Cut = 0.20;*/
        
        for(unsigned int i=0; i < v->size(); i++)
        {
            dv=v->at(i);
            for(unsigned int j=0;j<dv->size();j++)
            {
                DATA& d=dv->at(j);
                
          //      d.tight.particleFlowc = (d.particleFlow == tParticle_Flow_Muon_Cut)?true:false;
            //    d.tight.globalMuonc = (d.globalMuon == tGlobal_Muon_Cut)?true:false;
              //  d.tight.trackerMuonc = (d.trackerMuon == tTracker_Muon_Cut)?true:false;
                d.ptc = (d.pt > tMuon_Tight_Cut_pt)?true:false;
                d.etac = (fabs( d.eta ) < tMuon_Tight_Cut_eta)?true:false;
                d.isoc = (d.iso < tMuon_Relative_Isolation_Cut)?true:false;
                d.tightc = (d.tight == tightMuon)?true:false;
                d.all = d.ptc && d.etac && d.isoc && d.tightc;
                
            /*    d.loose.particleFlowc = (d.particleFlow == lParticle_Flow_Muon_Cut)?true:false;
                d.loose.globalMuonc = (d.globalMuon == lGlobal_Muon_Cut)?true:false;
                d.loose.trackerMuonc = (d.trackerMuon == lTracker_Muon_Cut)?true:false;
                d.loose.ptc = (d.pt > lMuon_Tight_Cut_pt)?true:false;
                d.loose.etac = (fabs( d.eta ) < lMuon_Tight_Cut_eta)?true:false;
                d.loose.isoc = (d.iso < lMuon_Relative_Isolation_Cut)?true:false;
                d.loose.all = d.loose.particleFlowc && d.loose.globalMuonc && d.loose.trackerMuonc && d.loose.ptc && d.loose.etac && d.loose.isoc;*/
            }
        }
        
        return;
    }
    
    void fillHisto(vector<TH1F*>* hv)
    {
        vector<DATA>* dv;
        DATA d;
        
        
        for(unsigned int i=0; i < v->size(); i++)
        {
            dv=v->at(i);
            int tightCount=0;
            int muon_number = 0;
            for(unsigned int j=0;j<dv->size();j++)
            {
                d=dv->at(j);
                if(d.tight.all)
                {
                    (hv->at(0))->Fill(d.pt);
                    muon_number = j;
                    tightCount++;
                }
                
            }
            if(tightCount==1)
            {
                d=dv->at(muon_number);
                (hv->at(1))->Fill(d.pt);
                (hv->at(2))->Fill(d.eta);
                (hv->at(3))->Fill(d.phi);
            }
        }
        return;
    }
    
    ~Muon()
    {
        
        delete v;
        v=0;
    }
    
    static vector<TH1F*>* getHistPointers(fwlite::TFileService& fs)
    {
        vector<TH1F*>* hv = new vector<TH1F*>;
        
        // TFileDirectory dir = fs.mkdir("tight_muon");
        TH1F* muonPt_  = fs.make<TH1F>("muonPt_"  , "pt"  ,   100,   0., 400.);
        TH1F* exactlyOneMuonPt_  = fs.make<TH1F>("exactlyOneMuonPt_"  , "pt"  ,   100,   0., 400.);
        TH1F* exactlyOneMuonEta_  = fs.make<TH1F>("exactlyOneMuonEta_"  , "eta"  ,   100,   -3.0, 3.0);
        TH1F* exactlyOneMuonPhi_  = fs.make<TH1F>("exactlyOneMuonPhi_"  , "phi"  ,   100,  -3.5, 3.5);
        
        hv->push_back(muonPt_);
        hv->push_back(exactlyOneMuonPt_);
        hv->push_back(exactlyOneMuonEta_);
        hv->push_back(exactlyOneMuonPhi_);
        
        return hv;
    }
    
    friend class ElectronMuon;
    friend class ElectronMuonExtraLoose;
};

