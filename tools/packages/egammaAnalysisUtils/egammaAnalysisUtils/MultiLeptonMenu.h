#ifndef MULTILEPTONMENU_H
#define MULTILEPTONMENU_H
//-------------------------------------------------------------------------------------------------------
class MultiLeptonMenu{

public:
    //These will be set to 1-> if it Fails. so the & with all set at one (16383) should be 0.  
    enum BitMask{
        CoverageBit=0,
        SiliconBit=1,
        PixelBit=2,
        BlayerBit=3,
        RhadBit=4,
        F3Bit=5,
        RetaBit=6,
        W2Bit=7,
        WstotBit=8,
        EratioBit=9,
        DeltaEtaBit=10,
        DeltaPhiResBit=11,
        TRBit=12,
        MaskForZXX = ( 0x1 << CoverageBit) | ( 0x1 << SiliconBit) | ( 0x1 << PixelBit) | 
        ( 0x1 << BlayerBit) | ( 0x1 << RhadBit) | ( 0x1 << F3Bit) | ( 0x1 << RetaBit)  |
        ( 0x1 << W2Bit) | ( 0x1 << WstotBit) | ( 0x1 << DeltaPhiResBit) | ( 0x1 << TRBit)
    };

    MultiLeptonMenu();
    MultiLeptonMenu(bool doDebug);
    ~MultiLeptonMenu(); 
    bool passMultiLepton(double eta, double eT,
                         double rHad, double rHad1, double Reta, double w2, 
                         double f1, double f3, double wstot, double DEmaxs1, 
                         double deltaEta, int nSi, int nSiDeadSensors, int nPix, 
                         int nPixDeadSensors, double deltaPhiRes, double dpOverp, 
                         double TRratio,  int nTRTTotal,  int nBlayerHits, bool expectBlayer) const;
    unsigned int getmask() const;
    void         printMask(unsigned int mask) const;
    void         setDoDebug(bool doDebug) {m_doDebug = doDebug;}
    bool         doDebug() {return m_doDebug;}


private :
    mutable unsigned int m_mask; //This would be 0 if all pass
    bool m_doDebug;
    

    bool passCoverage(double eta) const;
    bool passSilicon(int nSi, int nSiDeadSensors) const;
    bool passPixel(int nPix, int nPixDeadSensors, unsigned int etabin) const;
    bool passBlayer(int nBlayerHits, bool expectBlayer, unsigned int etabin) const;
    bool passRHad(double rhad, double rhad1, unsigned int etbin, unsigned int etabin) const;
    bool passF3(double f3, unsigned int etbin, unsigned int etabin) const;
    bool passReta(double reta, unsigned int etbin, unsigned int etabin) const;
    bool passW2(double w2, unsigned int etbin, unsigned int etabin) const;
    bool passWstot(double wstot, unsigned int etbin, unsigned int etabin) const;
    bool passEratio(double DEmaxs1, unsigned int etbin, unsigned int etabin) const;
    bool passDeltaEta(double deltaEta, unsigned int etbin, unsigned int etabin) const;
    bool passDeltaPhiRes(double deltaPhiRes, bool isBrem, unsigned int etbin, unsigned int etabin) const;
    bool passTR(double TRratio, double eta, unsigned int  nTRTTotal ) const;
    unsigned int getEtaBinH4l(double eta) const;
    unsigned int getEtBinH4l(double eT) const;
    bool getBremCategoryH4l(double dpOverp, unsigned int etbin, unsigned int etabin) const;
};
//----------------------------------------------------------------------------------------
#endif
