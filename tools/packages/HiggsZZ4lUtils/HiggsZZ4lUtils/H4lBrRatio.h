#ifndef H4LBRRATIO_H
#define H4LBRRATIO_H

#include "Math/Interpolator.h"

class H4lBrRatio
{
 public:
  H4lBrRatio();
  ~H4lBrRatio();
  double getemutauBrRatio(double mass);
  double getemuBrRatio(double mass);
  double get2e2muBrRatio(double mass);
  double get4eBrRatio(double mass);

 private :
  int m_initialize();
  ROOT::Math::Interpolator* m_interemutau;
  ROOT::Math::Interpolator* m_interemu;
  ROOT::Math::Interpolator* m_inter4e;
  ROOT::Math::Interpolator* m_inter2e2mu;

};

#endif

