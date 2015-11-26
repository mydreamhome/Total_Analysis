class Electron;
class Muon;
class ElectronMuonOppChrg;

class ElectronMuon
{
    
    struct CUTE
    {
        bool   etac,ptc,dxyc,vetoc,mhitsc,isoc,fullSigmaEtaEtac,dEtaInc,dPhiInc,HoverEc,ooEmooPc,d0c,dzc,all;
    };
    struct DATAE
    {
        
        float  eID,phi,eta,pt,dxy,veto,mhits,iso,charge,scEta,fullSigmaEtaEta,dEtaIn,dPhiIn,HoverE,ooEmooP,d0,dz;
        CUTE    loose,tight;
    };
  /*  struct CUTM
    {
        bool   particleFlowc,globalMuonc,trackerMuonc,etac,ptc,isoc,all;
    };*/
    struct DATAM
    {
        float  mID,eta,pt,iso,charge,phi,tight,loose;
        bool   etac,ptc,isoc,tightc,loosec,all;
        // CUT    loose,tight;
    };
    
    struct DATA{
        int evtID,eID,mID;
        float ech,mch,electronPt,electronEta,electronPhi,muonPt,muonEta,muonPhi;
    };
    
    vector<DATA>*  v;
    vector<int>* LeptMult;
    int c1E1M, c2E, C2M;
public:
    ElectronMuon()
    {
        v= new vector<DATA>;
        LeptMult = new vector<int>;
    }
    
    int getEW1E1M(){return c1E1M;}
    int getEW2E(){return c2E;}
    int getEW2M(){return C2M;}
    
    vector<DATA>* setData1(Electron& fe,Muon& fm,Electron& ufe,Muon& ufm)
    {
        int events = 0;
        for(unsigned int i=0;i<fe.v->size();i++)//loop over all events
        {
            int c=0;

            vector<DATAE>* edv = (vector<DATAE>*)fe.v->at(i); //pointer to electron's collection(1st electron) in a particular event
            vector<DATAM>* mdv = (vector<DATAM>*)fm.v->at(i);
            
            if(edv->size()!=1 || mdv->size()!=1)continue;
            
            DATA emd;

                    if( edv->size()==1 && mdv->size()==1)
                    {
                      //  LeptMult->push_back(((ufe.v->at(i))->size())+((ufm.v->at(i))->size()));
                        DATAE e = edv->at(0);
                        DATAM m = mdv->at(0);
                        
                        emd.evtID=i;
                        emd.eID=e.eID;
                        emd.mID=m.mID;
                        emd.ech=e.charge;
                        emd.mch=m.charge;
                        emd.electronPt=e.pt;
                        emd.electronEta=e.eta;
                        emd.electronPhi=e.phi;
                        emd.muonPt=m.pt;
                        emd.muonEta=m.eta;
                        emd.muonPhi=m.phi;
                        
                        c++;
                    }

            if(c==1)
            {
                events++;
                LeptMult->push_back(((ufe.v->at(i))->size())+((ufm.v->at(i))->size()));
                v->push_back(emd);
               // cout<<"Selected (on basis of opposite charge of electron & muon) EventID: "<<emd.evtID<<" ,EID: "<<emd.eID<<" ,MID "<<emd.mID<<" ,EC: "<<emd.ech<<" ,MC: "<<emd.mch<<endl;
                
            }
        }
       // cout<<"Total number of events having only one tight electron and only one tight muon: " << events <<endl;
        c1E1M = events;
        return v;
    }
    
    vector<DATA>* setData2(Electron& fe,Electron& ufe,Muon& ufm)
    {
     //   cout<<"called 2e in emu class at begining"<<endl;
        int events = 0;
        for(unsigned int i=0;i<fe.v->size();i++)//loop over all events
        {
            int c=0;
            
            vector<DATAE>* edv = (vector<DATAE>*)fe.v->at(i); //pointer to electron's collection(1st electron) in a particular event
            
            if(edv->size()!=2)continue;
            
            DATA emd;
            if( edv->size()==2)
            {
              //  LeptMult->push_back(((ufe.v->at(i))->size())+((ufm.v->at(i))->size()));
                DATAE e1 = edv->at(0);
                DATAE e2 = edv->at(1);
                
                        emd.evtID=i;
                        emd.eID=e1.eID;
                        emd.mID=e2.eID;
                        emd.ech=e1.charge;
                        emd.mch=e2.charge;
                        emd.electronPt=e1.pt;
                        emd.electronEta=e1.eta;
                        emd.electronPhi=e1.phi;
                        emd.muonPt=e2.pt;
                        emd.muonEta=e2.eta;
                        emd.muonPhi=e2.phi;
                        
                        c++;
            }
            if(c==1)
            {
                events++;
                LeptMult->push_back(((ufe.v->at(i))->size())+((ufm.v->at(i))->size()));
                v->push_back(emd);
                // cout<<"Selected (on basis of opposite charge of electron & muon) EventID: "<<emd.evtID<<" ,EID: "<<emd.eID<<" ,MID "<<emd.mID<<" ,EC: "<<emd.ech<<" ,MC: "<<emd.mch<<endl;
                
            }
        }
      //  cout<<"Total number of events having only two tight electrons: " << events <<endl;
        c2E = events;
     //   cout<<"called 2e in emu class at end"<<endl;
        return v;
    }
  
    vector<DATA>* setData3(Muon& fm,Electron& ufe,Muon& ufm)
    {
      //  cout<<"called 2m in emu class at beginning"<<endl;
        int events = 0;
        for(unsigned int i=0;i<fm.v->size();i++)//loop over all events
        {
            vector<DATAM>* mdv = (vector<DATAM>*)fm.v->at(i); //pointer to electron's collection(1st electron) in a particular event
            
            if(mdv->size()!=2)continue;
            
            int c=0;
            DATA emd;
            if( mdv->size()==2)
            {
              //  LeptMult->push_back(((ufe.v->at(i))->size())+((ufm.v->at(i))->size()));
                DATAM m1 = mdv->at(0);
                DATAM m2 = mdv->at(1);
                
                emd.evtID=i;
                emd.eID=m1.mID;
                emd.mID=m2.mID;
                emd.ech=m1.charge;
                emd.mch=m2.charge;
                emd.electronPt=m1.pt;
                emd.electronEta=m1.eta;
                emd.electronPhi=m1.phi;
                emd.muonPt=m2.pt;
                emd.muonEta=m2.eta;
                emd.muonPhi=m2.phi;
                
                c++;
            }
            if(c==1)
            {
                events++;
                LeptMult->push_back(((ufe.v->at(i))->size())+((ufm.v->at(i))->size()));
                v->push_back(emd);
                // cout<<"Selected (on basis of opposite charge of electron & muon) EventID: "<<emd.evtID<<" ,EID: "<<emd.eID<<" ,MID "<<emd.mID<<" ,EC: "<<emd.ech<<" ,MC: "<<emd.mch<<endl;
                
            }
        }
       // cout<<"Total number of events having only two tight muons: " << events <<endl;
        C2M = events;
       // cout<<"called 2m in emu class at end "<<endl;
        return v;
    }
    
    void fillHisto(vector<TH1F*>* hv,int Case)
    {
        DATA d;
      //  cout<<"case: "<< Case <<endl;
      //  cout<<"emu class v size: "<<v->size() <<endl;
      //  cout<<"emu class lept size: "<<LeptMult->size()<<endl;
        for(unsigned int i=0; i < v->size(); i++)
        {
            d=v->at(i);
            if(Case==1)
            {
                (hv->at(0))->Fill(d.electronPt);
                (hv->at(1))->Fill(d.electronEta);
                (hv->at(2))->Fill(d.electronPhi);
                (hv->at(3))->Fill(d.muonPt);
                (hv->at(4))->Fill(d.muonEta);
                (hv->at(5))->Fill(d.muonPhi);
                if(LeptMult->at(i)){(hv->at(6))->Fill(LeptMult->at(i));}
            }
            if(Case==2)
            {
                (hv->at(0))->Fill(d.electronPt);
                (hv->at(1))->Fill(d.electronEta);
                (hv->at(2))->Fill(d.electronPhi);
                
                (hv->at(0))->Fill(d.muonPt);
                (hv->at(1))->Fill(d.muonEta);
                (hv->at(2))->Fill(d.muonPhi);
                if(LeptMult->at(i)){(hv->at(3))->Fill(LeptMult->at(i));}
            }
            
            if(Case==3)
            {
                (hv->at(0))->Fill(d.electronPt);
                (hv->at(1))->Fill(d.electronEta);
                (hv->at(2))->Fill(d.electronPhi);
                
                (hv->at(0))->Fill(d.muonPt);
                (hv->at(1))->Fill(d.muonEta);
                (hv->at(2))->Fill(d.muonPhi);
                if(LeptMult->at(i)){(hv->at(3))->Fill(LeptMult->at(i));}
            }
        }
        return;
    }
    
    ~ElectronMuon()
    {
        delete v;
        v=0;
    }
    
    static vector<TH1F*>* getHistPointers(fwlite::TFileService& fs, int Case)
    {
        vector<TH1F*>* hv = new vector<TH1F*>;
        
        TH1F* electronPt_ = 0;
        TH1F* electronEta_ = 0;
        TH1F* electronPhi_ = 0;
        
        TH1F* muonPt_ = 0;
        TH1F* muonEta_ = 0;
        TH1F* muonPhi_ = 0;
        
        TH1F* LeptonMult_ = 0;
        
        if(Case==1 || Case==2)
        {
            electronPt_  = fs.make<TH1F>("electronPt_"  , "pt"  ,   100,   0., 400.);
            electronEta_  = fs.make<TH1F>("electronEta_"  , "eta"  ,   100,   -3.0, 3.0);
            electronPhi_  = fs.make<TH1F>("electronPhi_"  , "phi"  ,   100,  -3.5, 3.5);
            
            hv->push_back(electronPt_);
            hv->push_back(electronEta_);
            hv->push_back(electronPhi_);
        }
        if(Case==1 || Case==3)
        {
            muonPt_  = fs.make<TH1F>("muonPt_"  ,"pt"  ,   100,   0., 400.);
            muonEta_  = fs.make<TH1F>("muonEta_"  ,"eta"  ,   100,   -3.0, 3.0);
            muonPhi_  = fs.make<TH1F>("muonPhi_"  , "phi"  ,   100,  -3.5, 3.5);
            
            hv->push_back(muonPt_);
            hv->push_back(muonEta_);
            hv->push_back(muonPhi_);
        }
        if(Case==1 || Case==2 || Case==3)
        {
            LeptonMult_  = fs.make<TH1F>("LeptonMult_"  , "LeptonMultiplcity"  ,   20,  0.0, 20.0);
            hv->push_back(LeptonMult_);
        }
        return hv;
    }
    
    friend class ElectronMuonOppChrg;
};
