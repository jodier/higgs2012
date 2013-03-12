#ifndef HIGGSCROSSSECTION_H
#define HIGGSCROSSSECTION_H
#include "HiggsZZ4lUtils/CrossSection.h"
#include <iostream>
#include <vector>

class HiggsCrossSection
{
public:

  HiggsCrossSection();
    
  double higgsBRZZ4lemutau(double mass);
  double higgsFBBRZZ4lemutau(double mass);

  double higgsprodxsecGGF(double mass, CrossSections::LHCEnergy energy);
  double higgsprodxsecVBF(double mass, CrossSections::LHCEnergy energy);
  double higgsprodxsecWH(double mass, CrossSections::LHCEnergy energy);
  double higgsprodxsecZH(double mass, CrossSections::LHCEnergy energy);
  double higgsprodxsecttH(double mass, CrossSections::LHCEnergy energy);

  std::pair<double,double> higgsprodxsecuncGGF(double mass, CrossSections::LHCEnergy energy);
  std::pair<double,double> higgsprodxsecuncVBF(double mass, CrossSections::LHCEnergy energy);
  std::pair<double,double> higgsprodxsecuncWH(double mass, CrossSections::LHCEnergy energy);
  std::pair<double,double> higgsprodxsecuncZH(double mass, CrossSections::LHCEnergy energy);
  std::pair<double,double> higgsprodxsecuncttH(double mass, CrossSections::LHCEnergy energy);

  double higgs4lxsecGGF(double mass, CrossSections::LHCEnergy energy);
  double higgs4lxsecVBF(double mass, CrossSections::LHCEnergy energy);
  double higgs4lxsecWH(double mass, CrossSections::LHCEnergy energy);
  double higgs4lxsecZH(double mass, CrossSections::LHCEnergy energy);
  double higgs4lxsecttH(double mass, CrossSections::LHCEnergy energy);
  double higgsFP4lxsecVBF(double mass, CrossSections::LHCEnergy energy);

  double interpolate(unsigned int n, 
                     const std::vector<double>& x, 
                     const std::vector<double>& y, 
                     double mass);

  // backwards compatibility -- obsolete
  double higgsxsecGGF(double mass);
  double higgsxsecVBF(double mass);
  double higgsxsecWH(double mass);
  double higgsxsecZH(double mass);

private:

  void initializeH();
    
  bool                m_isInitializedH;
  std::vector<double> m_signalmasses;
  std::vector<double> m_signalggxsec;
  std::vector<double> m_signalvbfxsec;
  std::vector<double> m_signalwhxsec;
  std::vector<double> m_signalzhxsec;
  std::vector<double> m_signaltthxsec;
  std::vector<double> m_signalggxsecuncP;
  std::vector<double> m_signalvbfxsecuncP;
  std::vector<double> m_signalwhxsecuncP;
  std::vector<double> m_signalzhxsecuncP;
  std::vector<double> m_signaltthxsecuncP;
  std::vector<double> m_signalggxsecuncN;
  std::vector<double> m_signalvbfxsecuncN;
  std::vector<double> m_signalwhxsecuncN;
  std::vector<double> m_signalzhxsecuncN;
  std::vector<double> m_signaltthxsecuncN;

  std::vector<double> m_signalmasses_8TeV;
  std::vector<double> m_signalggxsec_8TeV;
  std::vector<double> m_signalvbfxsec_8TeV;
  std::vector<double> m_signalwhxsec_8TeV;
  std::vector<double> m_signalzhxsec_8TeV;
  std::vector<double> m_signaltthxsec_8TeV;
  std::vector<double> m_signalggxsecuncP_8TeV;
  std::vector<double> m_signalvbfxsecuncP_8TeV;
  std::vector<double> m_signalwhxsecuncP_8TeV;
  std::vector<double> m_signalzhxsecuncP_8TeV;
  std::vector<double> m_signaltthxsecuncP_8TeV;
  std::vector<double> m_signalggxsecuncN_8TeV;
  std::vector<double> m_signalvbfxsecuncN_8TeV;
  std::vector<double> m_signalwhxsecuncN_8TeV;
  std::vector<double> m_signalzhxsecuncN_8TeV;
  std::vector<double> m_signaltthxsecuncN_8TeV;

};

#endif
