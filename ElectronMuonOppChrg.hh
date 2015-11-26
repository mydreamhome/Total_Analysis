class Electron;
class Muon;
class ElectronMuon;
class ElectronMuonExtraLoose;

class ElectronMuonOppChrg
{
    struct DATA{
        int evtID,eID,mID;
        float ech,mch,electronPt,electronEta,electronPhi,muonPt,muonEta,muonPhi;
    };
    
    vector<DATA>*  v;
    vector<int>* LeptMult;
    int cOppChrg;
    
public:
    ElectronMuonOppChrg()
    {
        v= new vector<DATA>;
        LeptMult = new vector<int>;
    }
    
    int getEWOppChrg(){return cOppChrg;}
    
    vector<DATA>* setData(ElectronMuon& em,Electron& ufe,Muon& ufm)
    {
        int events = 0;
            DATA emd;
            for(unsigned int i=0;i<em.v->size();i++)
            {
                int c =0 ;
                if( (((em.v)->at(i)).ech * ((em.v)->at(i)).mch) < 0 )
                    {
                      //  LeptMult->push_back(((ufe.v->at(i))->size())+((ufm.v->at(i))->size()));
                        emd.evtID=((em.v)->at(i)).evtID;
                        emd.eID=((em.v)->at(i)).eID;
                        emd.mID=((em.v)->at(i)).mID;
                        emd.ech=((em.v)->at(i)).ech;
                        emd.mch=((em.v)->at(i)).mch;
                        emd.electronPt=((em.v)->at(i)).electronPt;
                        emd.electronEta=((em.v)->at(i)).electronEta;
                        emd.electronPhi=((em.v)->at(i)).electronPhi;
                        emd.muonPt=((em.v)->at(i)).muonPt;
                        emd.muonEta=((em.v)->at(i)).muonEta;
                        emd.muonPhi=((em.v)->at(i)).muonPhi;
                        events++;
                        c++;
 
                    }
                if(c == 1)
                {
                LeptMult->push_back(((ufe.v->at(emd.evtID))->size())+((ufm.v->at(emd.evtID))->size()));
                v->push_back(emd);
                // cout<<"Selected (on basis of opposite charge of electron & muon) EventID: "<<emd.evtID<<" ,EID: "<<emd.eID<<" ,MID "<<emd.mID<<" ,EC: "<<emd.ech<<" ,MC: "<<emd.mch<<endl;
                }

                }
     //   cout<<"Total number of events having ooposite charge leptons: " << events <<endl;
        cOppChrg = events;
        return v;
    }
    
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
    
    ~ElectronMuonOppChrg()
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
    
    friend class ElectronMuonExtraLoose;
};
