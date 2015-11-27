class ElectronMuonMet;

class Met
{
    struct DATA
    {
        
        float  pt;
        bool   ptc;
    };
    
    vector<vector<DATA>*>* v;
    int cMetCut;
    
public:
    Met()
    {
       v = new vector<vector<DATA>*>;
    }
    Met(vector<vector<DATA>*>* uv)
    {
     v=uv;
    }
    
    int getEWMetCut(){return cMetCut;}
    
    void setData(const char* fname)
    {
        TFile* inFile = TFile::Open(fname);
        
        if(!inFile)
        {
            cout<<"Input Root File not open for processing\n";
            return;
        }
        
        fwlite::Event ev(inFile);
        int evtID=0;
        
        for(ev.toBegin(); !ev.atEnd(); ++ev, evtID++)
        {
            edm::EventBase const & event = ev;
            
            edm::Handle<std::vector<float> > MetPt;
            event.getByLabel(std::string("met:metPt"), MetPt);
            
            vector<DATA>* dv = new vector<DATA>;
            DATA d;
            
            for(unsigned int i=0;i<MetPt->size();i++)
            {
                d.pt = MetPt->at(i);
                
                dv->push_back(d);
                
            }
            
            
            v->push_back(dv);
            
        }
        inFile->Close();
        
        setCuts();
        
        return;
    }
    
    void printData(int p)
    {
        vector<DATA>* dv;
        DATA d;
        
        for(unsigned int i=0; i < v->size(); i++)
        {
            dv=v->at(i);
            for(unsigned int j=0;j<dv->size();j++)
            {
                d=dv->at(j);
               // if(p==1 || p==0) cout<<"Event ID:"<<i<<", Met ID:"<<j<<","<<" Pt:"<<d.pt<<endl;
                
                //if(p==2||p==0)
                 //   cout<<"Event ID:"<<i<<", Met ID:"<<j<<","<<" Ptc:"<<d.ptc<<endl;
              //  if(d.ptc){
               //   if(p==3||p==0) cout<<"Event ID:"<<i<<", Met ID:"<<j<<","<<" Pt:"<<d.pt<<", Ptc:"<<d.ptc<<endl;
               // }
            }
        }
        return;
    }
    
    vector<vector<DATA>*>* selectData()
    {
        vector<DATA>* dv;
        DATA d;
        
        vector<vector<DATA>*>* fv = new vector<vector<DATA>*>;
        int events =0;
        int totalPassingMets =0;
        
        for(unsigned int i=0; i < v->size(); i++)
        {
            int met_number = 0;
            vector<DATA>* fdv= new vector<DATA>;
            
            dv=v->at(i);
            
            bool isEventSelected=false;
            int cutPassingCount=0;
            
            for(unsigned int j=0;j<dv->size();j++)
            {
                d=dv->at(j);
                
                if(d.ptc)
                {
                    totalPassingMets++;
                    met_number = j;
                    cutPassingCount++;
                }
            }
            
            if(cutPassingCount==1){isEventSelected=true;//cout<<i<<" Reject2"<<endl;
            }
            //-----------------------
            if(isEventSelected)
            {
                events++;
                d=dv->at(met_number);
                
                //  cout<<"Selected (on basis of cut passing Mets) EventID: "<<i<<"  S MetID: "<<met_number<<endl;
                fdv->push_back(d);
                // only fill cut passing Met's information
                
            }
            //-------------------------
            fv->push_back(fdv);
        }
     //   cout<<"Total number of Mets passing cuts: "<< totalPassingMets <<endl;
      //  cout<<"Total number of events having cut passing Mets: "<< events <<endl;
        cMetCut = totalPassingMets;
        return fv;
    }
/*
    void fillHisto(const char* outputFile)
    {
        vector<DATA>* dv;
        DATA d;
        
        fwlite::TFileService fs = fwlite::TFileService(outputFile);
       // TFileDirectory dir = fs.mkdir("analyzePatMuon");
        TH1F* MetPt_  = fs.make<TH1F>("MetPt_"  , "pt"  ,   100,   0., 400.);
        
        for(unsigned int i=0; i < v->size(); i++)
        {
            dv=v->at(i);
            for(unsigned int j=0;j<dv->size();j++)
            {
                d=dv->at(j);
                if(d.ptc)
                    MetPt_->Fill(d.pt);
                
            }
            
        }
        return;
    }
 */
    
    void fillHisto(vector<TH1F*>* hv)
    {
        vector<DATA>* dv;
        DATA d;
        
        for(unsigned int i=0; i < v->size(); i++)
        {
            dv=v->at(i);
            for(unsigned int j=0;j<dv->size();j++)
            {
                d=dv->at(j);
                if(d.ptc)
                    (hv->at(0))->Fill(d.pt);
                
            }
            
        }
        return;
    }
    
    void setCuts()
    {
        vector<DATA>* dv;
        float Met_Cut_pt = 50.0;
        
        for(unsigned int i=0; i < v->size(); i++)
        {
            dv=v->at(i);
            for(unsigned int j=0;j<dv->size();j++)
            {
                DATA& d=dv->at(j);
                d.ptc = (d.pt > Met_Cut_pt)?true:false;
                
            }
        }
        return;
    }
    
    static vector<TH1F*>* getHistPointers(fwlite::TFileService& fs)
    {
        vector<TH1F*>* hv = new vector<TH1F*>;
        
        TH1F* MetPt_  = fs.make<TH1F>("MetPt_"  , "pt"  ,   100,   0., 400.);
        
        hv->push_back(MetPt_);
        
        return hv;
    }
    
    friend class ElectronMuonMet;
};

