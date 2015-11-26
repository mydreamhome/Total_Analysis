class Electron;
class Muon;
class Met;
class ElectronMuonExtraLoose;

class ElectronMuonMet
{
    struct MetDATA
    {
        
        float  pt;
        bool   ptc;
    };
 
	struct DATA{
		int evtID;
		float metPt,electronPt,electronEta,electronPhi,muonPt,muonEta,muonPhi;

	};

	vector<DATA>* v;
    vector<int>* LeptMult;
    int cEMuMet;
    
public:
	ElectronMuonMet()
	{
		v = new vector<DATA>;
        LeptMult = new vector<int>;
	}

    int getEMuMet(){return cEMuMet;}
    
    vector<DATA>* setData(ElectronMuonExtraLoose& emel, Met& met,Electron& ufe,Muon& ufm)
    {
        int rejected_met = 0;
        int events = 0;
        for(unsigned int i=0;i<emel.v->size();i++)
        {
            int evtID=((emel.v)->at(i)).evtID;
            vector<MetDATA>* dv = (vector<MetDATA>*) met.v->at(evtID);
            if(dv->size() == 0)
            {
               rejected_met++;
              continue;
            }
            
	   for(unsigned int j=0;j<dv->size();j++)
            {
                events++;
                MetDATA metd =(MetDATA) dv->at(j);
               // cout <<"i:   "<<i<<"j:   "<<j<<endl;
                DATA d ={evtID,metd.pt,emel.v->at(i).electronPt,emel.v->at(i).electronEta,emel.v->at(i).electronPhi,emel.v->at(i).muonPt,emel.v->at(i).muonEta,emel.v->at(i).muonPhi};
                v->push_back(d);
                //cout<<"MET:EventID"<<evtID<<", MetID:"<<j<<"PT:"<<metd.pt<<", ptc:"<<metd.ptc<<endl;
            }
           LeptMult->push_back(((ufe.v->at(evtID))->size())+((ufm.v->at(evtID))->size()));
        }
      //  cout<<"total number of selected events due to no met passing cut"<<events<<endl;
     //   cout<<"total number of rejected events due to no met passing cut"<<rejected_met<<endl;
        cEMuMet = events;
        return v;
    }
    
/*    void fillHisto(const char* outputFile, const char* fileName,int Case)
    {
        DATA d;
        char fName[70];
        
        sprintf(fName,"%s.root",fileName);
        
        fwlite::TFileService fs = fwlite::TFileService(fName);
        //   TFileDirectory dir = fs.mkdir(fileName);
        
        TH1F* electronPt_ = 0;
        TH1F* electronEta_ = 0;
        TH1F* electronPhi_ = 0;
        
        TH1F* muonPt_ = 0;
        TH1F* muonEta_ = 0;
        TH1F* muonPhi_ = 0;
        TH1F* metPt_ = 0;
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
        if(Case==1 || Case==2 || Case==3)
        {
            metPt_  = fs.make<TH1F>("metPt_"  , "pt"  ,   100,   0., 400.);
        }
        
        for(unsigned int i=0; i < v->size(); i++)
        {
            d=v->at(i);
            if(Case==1)
            {
                metPt_->Fill(d.metPt);
                electronPt_->Fill(d.electronPt);
                electronEta_->Fill(d.electronEta);
                electronPhi_->Fill(d.electronPhi);
                muonPt_->Fill(d.muonPt);
                muonEta_->Fill(d.muonEta);
                muonPhi_->Fill(d.muonPhi);
            }
            if(Case==2)
            {
                metPt_->Fill(d.metPt);
                electronPt_->Fill(d.electronPt);
                electronEta_->Fill(d.electronEta);
                electronPhi_->Fill(d.electronPhi);
                
                electronPt_->Fill(d.muonPt);
                electronEta_->Fill(d.muonEta);
                electronPhi_->Fill(d.muonPhi);
                
            }
            
            if(Case==3)
            {
                metPt_->Fill(d.metPt);
                muonPt_->Fill(d.electronPt);
                muonEta_->Fill(d.electronEta);
                muonPhi_->Fill(d.electronPhi);
                
                muonPt_->Fill(d.muonPt);
                muonEta_->Fill(d.muonEta);
                muonPhi_->Fill(d.muonPhi);
                
            }
        }
        return;
    }
 */
    
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
                (hv->at(6))->Fill(d.metPt);
                if(LeptMult->at(i)){(hv->at(7))->Fill(LeptMult->at(i));}
            }
            if(Case==2)
            {
                (hv->at(0))->Fill(d.electronPt);
                (hv->at(1))->Fill(d.electronEta);
                (hv->at(2))->Fill(d.electronPhi);
                
                (hv->at(0))->Fill(d.muonPt);
                (hv->at(1))->Fill(d.muonEta);
                (hv->at(2))->Fill(d.muonPhi);
                (hv->at(3))->Fill(d.metPt);
                if(LeptMult->at(i)){(hv->at(4))->Fill(LeptMult->at(i));}
            }
            
            if(Case==3)
            {
                (hv->at(0))->Fill(d.electronPt);
                (hv->at(1))->Fill(d.electronEta);
                (hv->at(2))->Fill(d.electronPhi);
                
                (hv->at(0))->Fill(d.muonPt);
                (hv->at(1))->Fill(d.muonEta);
                (hv->at(2))->Fill(d.muonPhi);
                (hv->at(3))->Fill(d.metPt);
                if(LeptMult->at(i)){(hv->at(4))->Fill(LeptMult->at(i));}
            }
        }
        return;
    }
    
    ~ElectronMuonMet()
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
        TH1F* metPt_ = 0;
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
            metPt_  = fs.make<TH1F>("metPt_"  , "pt"  ,   100,   0., 400.);
            hv->push_back(metPt_);
        }
        if(Case==1 || Case==2 || Case==3)
        {
            LeptonMult_  = fs.make<TH1F>("LeptonMult_"  , "LeptonMultiplcity"  ,   20,  0.0, 20.0);
            hv->push_back(LeptonMult_);
        }
        return hv;
    }
    
};
