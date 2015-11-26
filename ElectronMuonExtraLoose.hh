class Electron;
class Muon;
class ElectronMuonOppChrg;
class ElectronMuonMet;

class ElectronMuonExtraLoose
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
    
  /*  struct DATAEM{
        int evtID,eID,mID;
        float ech,mch;
    };
   */
    struct DATA
    {
        int evtID,eID,mID;
        float ech,mch,electronPt,electronEta,electronPhi,muonPt,muonEta,muonPhi;
    };
    
    vector<DATA>*  v;
    int cExLoose1e1m,cExLoose2e,cExLoose2m;
    
public:
    ElectronMuonExtraLoose()
    {
        
        v= new vector<DATA>;
    }
   
    int getEWExLoose1e1m(){return cExLoose1e1m;}
    int getEWExLoose2e(){return cExLoose2e;}
    int getEWExLoose2m(){return cExLoose2m;}
    
    vector<DATA>* setData1(ElectronMuonOppChrg& em, Electron& elect, Muon& mu)
    {
        vector<DATAE>* dve;
        vector<DATAM>* dvm;
        int rejected_event = 0;
        int sselected_events = 0;
        for(unsigned int i=0;i<em.v->size();i++)
        {
            int evtID=((em.v)->at(i)).evtID;
            dve = (vector<DATAE>*) elect.v->at(evtID);
            dvm = (vector<DATAM>*) mu.v->at(evtID);
            
            bool isEventSelected=true;
            
            for(unsigned int j=0;j<dve->size();j++)
            {
                DATAE d;
                d=dve->at(j);
                
                if(!((d.tight.all==true && d.loose.all==true)  || (d.tight.all==false && d.loose.all==false)))
                {
                   // cout<<evtID<<" RejectE in 1e 1mu"<<endl<<endl<<endl;
                    rejected_event++;
                    isEventSelected=false;
                    break;
                }
                
            }
            
            for(unsigned int j=0;j<dvm->size();j++)
            {
                DATAM d;
                d=dvm->at(j);
                
                if(!((d.all==true && d.tightc==true && d.loosec==true)  || (d.all==true && d.tightc==false && d.loosec==false)))
                {
                   // cout<<evtID<<" RejectM in 1e 1mu"<<endl<<endl<<endl;
                    rejected_event++;
                    isEventSelected=false;
                    break;
                }
                
            }
            
            if (isEventSelected)
            {
                sselected_events++;
                // ElectronMuon dvem = em;
                DATA emelc;
                //  emelc = dvem.v->at(0);
                
                emelc.evtID = em.v->at(i).evtID;
                emelc.eID = em.v->at(i).eID;
                emelc.mID = em.v->at(i).mID;
                emelc.ech = em.v->at(i).ech;
                emelc.mch = em.v->at(i).mch;
                emelc.electronPt=em.v->at(i).electronPt;
                emelc.electronEta=em.v->at(i).electronEta;
                emelc.electronPhi=em.v->at(i).electronPhi;
                emelc.muonPt=em.v->at(i).muonPt;
                emelc.muonEta=em.v->at(i).muonEta;
                emelc.muonPhi=em.v->at(i).muonPhi;
                
                // cout<<"Selected (on basis of extra loose electrons & muons) EventID: "<<evtID<<", electronID:"<<emelc.eID<<", muonID:"<<emelc.mID<<", electronCharge:"<<emelc.ech<<", muonCharge:"<<emelc.mch<<endl;
                
                v->push_back(emelc);
            }
        }
     //   cout<<"total number of sselected events due to extra loose cuts in 1e 1mu : "<<sselected_events<<endl;
      //  cout<<"total number of rejected events due to extra loose cuts in 1e 1mu : "<<rejected_event<<endl;
        cExLoose1e1m = sselected_events;
        return v;
    }

    vector<DATA>* setData2(ElectronMuonOppChrg& em, Electron& elect)
    {
        vector<DATAE>* dve;
        int rejected_event = 0;
        int sselected_events = 0;
        for(unsigned int i=0;i<em.v->size();i++)
        {
            int evtID=((em.v)->at(i)).evtID;
            dve = (vector<DATAE>*) elect.v->at(evtID);
            
            bool isEventSelected=true;
            
            for(unsigned int j=0;j<dve->size();j++)
            {
                DATAE d;
                d=dve->at(j);
                
                if(!((d.tight.all==true && d.loose.all==true)  || (d.tight.all==false && d.loose.all==false)))
                {
                    //cout<<evtID<<" RejectE in 2e"<<endl<<endl<<endl;
                    rejected_event++;
                    isEventSelected=false;
                    break;
                }
                
            }
            
            if (isEventSelected)
            {
                sselected_events++;
                // ElectronMuon dvem = em;
                DATA emelc;
                //  emelc = dvem.v->at(0);
                
                emelc.evtID = em.v->at(i).evtID;
                emelc.eID = em.v->at(i).eID;
                emelc.mID = em.v->at(i).mID;
                emelc.ech = em.v->at(i).ech;
                emelc.mch = em.v->at(i).mch;
                emelc.electronPt=em.v->at(i).electronPt;
                emelc.electronEta=em.v->at(i).electronEta;
                emelc.electronPhi=em.v->at(i).electronPhi;
                emelc.muonPt=em.v->at(i).muonPt;
                emelc.muonEta=em.v->at(i).muonEta;
                emelc.muonPhi=em.v->at(i).muonPhi;
                
                // cout<<"Selected (on basis of extra loose electrons & muons) EventID: "<<evtID<<", electronID:"<<emelc.eID<<", muonID:"<<emelc.mID<<", electronCharge:"<<emelc.ech<<", muonCharge:"<<emelc.mch<<endl;
                
                v->push_back(emelc);
            }
        }
       // cout<<"total number of sselected events due to extra loose cuts in 2e : "<<sselected_events<<endl;
       // cout<<"total number of rejected events due to extra loose cuts in 2e : "<<rejected_event<<endl;
        cExLoose2e = sselected_events;
        return v;
    }

    vector<DATA>* setData3(ElectronMuonOppChrg& em, Muon& mu)
    {
        vector<DATAM>* dvm;
        int rejected_event = 0;
        int sselected_events = 0;
        for(unsigned int i=0;i<em.v->size();i++)
        {
            int evtID=((em.v)->at(i)).evtID;
            dvm = (vector<DATAM>*) mu.v->at(evtID);
            
            bool isEventSelected=true;
            
            for(unsigned int j=0;j<dvm->size();j++)
            {
                DATAM d;
                d=dvm->at(j);
                
                if(!((d.all==true && d.tightc==true && d.loosec==true)  || (d.all==true && d.tightc==false && d.loosec==false)))
                {
                  //  cout<<evtID<<" RejectM in 2mu"<<endl<<endl<<endl;
                    rejected_event++;
                    isEventSelected=false;
                    break;
                }
                
            }
            
            if (isEventSelected)
            {
                sselected_events++;
                // ElectronMuon dvem = em;
                DATA emelc;
                //  emelc = dvem.v->at(0);
                
                emelc.evtID = em.v->at(i).evtID;
                emelc.eID = em.v->at(i).eID;
                emelc.mID = em.v->at(i).mID;
                emelc.ech = em.v->at(i).ech;
                emelc.mch = em.v->at(i).mch;
                emelc.electronPt=em.v->at(i).electronPt;
                emelc.electronEta=em.v->at(i).electronEta;
                emelc.electronPhi=em.v->at(i).electronPhi;
                emelc.muonPt=em.v->at(i).muonPt;
                emelc.muonEta=em.v->at(i).muonEta;
                emelc.muonPhi=em.v->at(i).muonPhi;
                
                // cout<<"Selected (on basis of extra loose electrons & muons) EventID: "<<evtID<<", electronID:"<<emelc.eID<<", muonID:"<<emelc.mID<<", electronCharge:"<<emelc.ech<<", muonCharge:"<<emelc.mch<<endl;
                
                v->push_back(emelc);
            }
        }
 //       cout<<"total number of sselected events due to extra loose cuts in 2mu : "<<sselected_events<<endl;
   //     cout<<"total number of rejected events due to extra loose cuts in 2mu : "<<rejected_event<<endl;
        cExLoose2m = sselected_events;
        return v;
    }
    
/*    void fillHisto(const char* outputFile, const char* fileName,int Case)
    {
        DATA d;
        char fName[70];
        
        sprintf(fName,"%s.root",fileName);
        
        fwlite::TFileService fs = fwlite::TFileService(fName);
    //    TFileDirectory dir = fs.mkdir(fileName);
        
        TH1F* electronPt_ = 0;
        TH1F* electronEta_ = 0;
        TH1F* electronPhi_ = 0;
        
        TH1F* muonPt_ = 0;
        TH1F* muonEta_ = 0;
        TH1F* muonPhi_ =0;
        
        if(Case==1 || Case==2)
        {
            electronPt_  = fs.make<TH1F>("electronPt_"  , "pt"  ,   100,   0., 400.);
            electronEta_  = fs.make<TH1F>("electronEta_"  , "eta"  ,   100,   -3.0, 3.0);
            electronPhi_  = fs.make<TH1F>("electronPhi_"  , "phi"  ,   100,  -3.5, 3.5);
        }
        if(Case==1 || Case==3)
        {
            muonPt_  = fs.make<TH1F>("muonPt_"  ,"pt"  ,   100,   0., 400.);
            muonEta_  = fs.make<TH1F>("muonEta_"  ,"eta"  ,   100,   -3.0, 3.0);
            muonPhi_  = fs.make<TH1F>("muonPhi_"  , "phi"  ,   100,  -3.5, 3.5);
        }
        
        for(unsigned int i=0; i < v->size(); i++)
        {
            d=v->at(i);
            if(Case==1)
            {
                electronPt_->Fill(d.electronPt);
                electronEta_->Fill(d.electronEta);
                electronPhi_->Fill(d.electronPhi);
                muonPt_->Fill(d.muonPt);
                muonEta_->Fill(d.muonEta);
                muonPhi_->Fill(d.muonPhi);
            }
            if(Case==2)
            {
                electronPt_->Fill(d.electronPt);
                electronEta_->Fill(d.electronEta);
                electronPhi_->Fill(d.electronPhi);
                
                electronPt_->Fill(d.muonPt);
                electronEta_->Fill(d.muonEta);
                electronPhi_->Fill(d.muonPhi);
                
            }
            
            if(Case==3)
            {
                muonPt_->Fill(d.electronPt);
                muonEta_->Fill(d.electronEta);
                muonPhi_->Fill(d.electronPhi);
                
                muonPt_->Fill(d.muonPt);
                muonEta_->Fill(d.muonEta);
                muonPhi_->Fill(d.muonPhi);
                
            }
        }
        return;
    }*/
    
    void fillHisto(vector<TH1F*>* hv, int Case)
    {
        DATA d;
        
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
            }
            if(Case==2)
            {
                (hv->at(0))->Fill(d.electronPt);
                (hv->at(1))->Fill(d.electronEta);
                (hv->at(2))->Fill(d.electronPhi);
                
                (hv->at(0))->Fill(d.muonPt);
                (hv->at(1))->Fill(d.muonEta);
                (hv->at(2))->Fill(d.muonPhi);
                
            }
            
            if(Case==3)
            {
                (hv->at(0))->Fill(d.electronPt);
                (hv->at(1))->Fill(d.electronEta);
                (hv->at(2))->Fill(d.electronPhi);
                
                (hv->at(0))->Fill(d.muonPt);
                (hv->at(1))->Fill(d.muonEta);
                (hv->at(2))->Fill(d.muonPhi);
                
            }
        }
        return;
    }
    
    ~ElectronMuonExtraLoose()
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
        
        return hv;
    }

    friend class ElectronMuonMet;
};
