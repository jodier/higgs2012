#include "HiggsZZ4lUtils/HiggsCrossSection.h"
#include "HiggsZZ4lUtils/H4lBrRatio.h"
#include <iostream> 


int main (int /*argc*/, char* */*argv[]*/)  
{  

    HiggsCrossSection hcs;


    std::cout<<"====================================================="<<std::endl;
    std::cout << "$" << hcs.higgsprodxsecGGF(125, CrossSections::SevenTeV)/1000 << "^{"
              << hcs.higgsprodxsecuncGGF(125, CrossSections::SevenTeV).first*hcs.higgsprodxsecGGF(125, CrossSections::SevenTeV)/100000<< "}"
              << "_{" << hcs.higgsprodxsecuncGGF(125, CrossSections::SevenTeV).second*hcs.higgsprodxsecGGF(125, CrossSections::SevenTeV)/100000<<"}$"<< std::endl;

    std::cout << "$" << hcs.higgsprodxsecGGF(130, CrossSections::SevenTeV)/1000 << "^{"
              << hcs.higgsprodxsecuncGGF(130, CrossSections::SevenTeV).first *hcs.higgsprodxsecGGF(130, CrossSections::SevenTeV)/100000<< "}"
              << "_{" << hcs.higgsprodxsecuncGGF(130, CrossSections::SevenTeV).second*hcs.higgsprodxsecGGF(130, CrossSections::SevenTeV)/100000<<"}$"<< std::endl;

    std::cout << "$" << hcs.higgsprodxsecGGF(190, CrossSections::SevenTeV)/1000 << "^{"
              << hcs.higgsprodxsecuncGGF(190, CrossSections::SevenTeV).first *hcs.higgsprodxsecGGF(190, CrossSections::SevenTeV)/100000<< "}"
              << "_{" << hcs.higgsprodxsecuncGGF(190, CrossSections::SevenTeV).second*hcs.higgsprodxsecGGF(190, CrossSections::SevenTeV)/100000<<"}$"<< std::endl;

    std::cout << "$" << hcs.higgsprodxsecGGF(400, CrossSections::SevenTeV)/1000 << "^{"
              << hcs.higgsprodxsecuncGGF(400, CrossSections::SevenTeV).first *hcs.higgsprodxsecGGF(400, CrossSections::SevenTeV)/100000<< "}"
              << "_{" << hcs.higgsprodxsecuncGGF(400, CrossSections::SevenTeV).second*hcs.higgsprodxsecGGF(400, CrossSections::SevenTeV)/100000<<"}$"<< std::endl;

    std::cout << "$" << hcs.higgsprodxsecGGF(600, CrossSections::SevenTeV)/1000 << "^{"
              << hcs.higgsprodxsecuncGGF(600, CrossSections::SevenTeV).first *hcs.higgsprodxsecGGF(600, CrossSections::SevenTeV)/100000<< "}"
              << "_{" << hcs.higgsprodxsecuncGGF(600, CrossSections::SevenTeV).second*hcs.higgsprodxsecGGF(600, CrossSections::SevenTeV)/100000<<"}$"<< std::endl;
                                                                                       
    std::cout<<"====================================================="<<std::endl;

    std::cout<<"====================================================="<<std::endl;
    std::cout << "$" << hcs.higgsprodxsecVBF(125, CrossSections::SevenTeV)/1000 << "^{"
              << hcs.higgsprodxsecuncVBF(125, CrossSections::SevenTeV).first *hcs.higgsprodxsecVBF(125, CrossSections::SevenTeV)/100000<< "}"
              << "_{" << hcs.higgsprodxsecuncVBF(125, CrossSections::SevenTeV).second*hcs.higgsprodxsecVBF(125, CrossSections::SevenTeV)/100000<<"}$"<< std::endl;

    std::cout << "$" << hcs.higgsprodxsecVBF(130, CrossSections::SevenTeV)/1000 << "^{"
              << hcs.higgsprodxsecuncVBF(130, CrossSections::SevenTeV).first *hcs.higgsprodxsecVBF(130, CrossSections::SevenTeV)/100000<< "}"
              << "_{" << hcs.higgsprodxsecuncVBF(130, CrossSections::SevenTeV).second*hcs.higgsprodxsecVBF(130, CrossSections::SevenTeV)/100000<<"}$"<< std::endl;

    std::cout << "$" << hcs.higgsprodxsecVBF(190, CrossSections::SevenTeV)/1000 << "^{"
              << hcs.higgsprodxsecuncVBF(190, CrossSections::SevenTeV).first *hcs.higgsprodxsecVBF(190, CrossSections::SevenTeV)/100000<< "}"
              << "_{" << hcs.higgsprodxsecuncVBF(190, CrossSections::SevenTeV).second*hcs.higgsprodxsecVBF(190, CrossSections::SevenTeV)/100000<<"}$"<< std::endl;

    std::cout << "$" << hcs.higgsprodxsecVBF(400, CrossSections::SevenTeV)/1000 << "^{"
              << hcs.higgsprodxsecuncVBF(400, CrossSections::SevenTeV).first *hcs.higgsprodxsecVBF(400, CrossSections::SevenTeV)/100000<< "}"
              << "_{" << hcs.higgsprodxsecuncVBF(400, CrossSections::SevenTeV).second*hcs.higgsprodxsecVBF(400, CrossSections::SevenTeV)/100000<<"}$"<< std::endl;

    std::cout << "$" << hcs.higgsprodxsecVBF(600, CrossSections::SevenTeV)/1000 << "^{"
              << hcs.higgsprodxsecuncVBF(600, CrossSections::SevenTeV).first *hcs.higgsprodxsecVBF(600, CrossSections::SevenTeV)/100000<< "}"
              << "_{" << hcs.higgsprodxsecuncVBF(600, CrossSections::SevenTeV).second*hcs.higgsprodxsecVBF(600, CrossSections::SevenTeV)/100000<<"}$"<< std::endl;
    std::cout<<"====================================================="<<std::endl;

    std::cout<<"====================================================="<<std::endl;
    std::cout << "$" << hcs.higgsprodxsecWH(125, CrossSections::SevenTeV)/1000 << "^{"
              << hcs.higgsprodxsecuncWH(125, CrossSections::SevenTeV).first *hcs.higgsprodxsecWH(125, CrossSections::SevenTeV)/100000<< "}"
              << "_{" << hcs.higgsprodxsecuncWH(125, CrossSections::SevenTeV).second*hcs.higgsprodxsecWH(125, CrossSections::SevenTeV)/100000<<"}$"<< std::endl;

    std::cout << "$" << hcs.higgsprodxsecWH(130, CrossSections::SevenTeV)/1000 << "^{"
              << hcs.higgsprodxsecuncWH(130, CrossSections::SevenTeV).first *hcs.higgsprodxsecWH(130, CrossSections::SevenTeV)/100000<< "}"
              << "_{" << hcs.higgsprodxsecuncWH(130, CrossSections::SevenTeV).second*hcs.higgsprodxsecWH(130, CrossSections::SevenTeV)/100000<<"}$"<< std::endl;

    std::cout << "$" << hcs.higgsprodxsecWH(190, CrossSections::SevenTeV)/1000 << "^{"
              << hcs.higgsprodxsecuncWH(190, CrossSections::SevenTeV).first *hcs.higgsprodxsecWH(190, CrossSections::SevenTeV)/100000<< "}"
              << "_{" << hcs.higgsprodxsecuncWH(190, CrossSections::SevenTeV).second*hcs.higgsprodxsecWH(190, CrossSections::SevenTeV)/100000<<"}$"<< std::endl;

    std::cout << "$" << hcs.higgsprodxsecWH(400, CrossSections::SevenTeV)/1000 << "^{"
              << hcs.higgsprodxsecuncWH(400, CrossSections::SevenTeV).first *hcs.higgsprodxsecWH(400, CrossSections::SevenTeV)/100000<< "}"
              << "_{" << hcs.higgsprodxsecuncWH(400, CrossSections::SevenTeV).second*hcs.higgsprodxsecWH(400, CrossSections::SevenTeV)/100000<<"}$"<< std::endl;

    std::cout << "$" << hcs.higgsprodxsecWH(600, CrossSections::SevenTeV)/1000 << "^{"
              << hcs.higgsprodxsecuncWH(600, CrossSections::SevenTeV).first *hcs.higgsprodxsecWH(600, CrossSections::SevenTeV)/100000<< "}"
              << "_{" << hcs.higgsprodxsecuncWH(600, CrossSections::SevenTeV).second*hcs.higgsprodxsecWH(600, CrossSections::SevenTeV)/100000<<"}$"<< std::endl;
    std::cout<<"====================================================="<<std::endl;

    std::cout << "$" << hcs.higgsprodxsecZH(125, CrossSections::SevenTeV)/1000 << "^{"
              << hcs.higgsprodxsecuncZH(125, CrossSections::SevenTeV).first *hcs.higgsprodxsecZH(125, CrossSections::SevenTeV)/100000<< "}"
              << "_{" << hcs.higgsprodxsecuncZH(125, CrossSections::SevenTeV).second*hcs.higgsprodxsecZH(125, CrossSections::SevenTeV)/100000<<"}$"<< std::endl;

    std::cout << "$" << hcs.higgsprodxsecZH(130, CrossSections::SevenTeV)/1000 << "^{"
              << hcs.higgsprodxsecuncZH(130, CrossSections::SevenTeV).first *hcs.higgsprodxsecZH(130, CrossSections::SevenTeV)/100000<< "}"
              << "_{" << hcs.higgsprodxsecuncZH(130, CrossSections::SevenTeV).second*hcs.higgsprodxsecZH(130, CrossSections::SevenTeV)/100000<<"}$"<< std::endl;

    std::cout << "$" << hcs.higgsprodxsecZH(190, CrossSections::SevenTeV)/1000 << "^{"
              << hcs.higgsprodxsecuncZH(190, CrossSections::SevenTeV).first *hcs.higgsprodxsecZH(190, CrossSections::SevenTeV)/100000<< "}"
              << "_{" << hcs.higgsprodxsecuncZH(190, CrossSections::SevenTeV).second*hcs.higgsprodxsecZH(190, CrossSections::SevenTeV)/100000<<"}$"<< std::endl;

    std::cout << "$" << hcs.higgsprodxsecZH(400, CrossSections::SevenTeV)/1000 << "^{"
              << hcs.higgsprodxsecuncZH(400, CrossSections::SevenTeV).first *hcs.higgsprodxsecZH(400, CrossSections::SevenTeV)/100000<< "}"
              << "_{" << hcs.higgsprodxsecuncZH(400, CrossSections::SevenTeV).second*hcs.higgsprodxsecZH(400, CrossSections::SevenTeV)/100000<<"}$"<< std::endl;

    std::cout << "$" << hcs.higgsprodxsecZH(600, CrossSections::SevenTeV)/1000 << "^{"
              << hcs.higgsprodxsecuncZH(600, CrossSections::SevenTeV).first *hcs.higgsprodxsecZH(600, CrossSections::SevenTeV)/100000<< "}"
              << "_{" << hcs.higgsprodxsecuncZH(600, CrossSections::SevenTeV).second*hcs.higgsprodxsecZH(600, CrossSections::SevenTeV)/100000<<"}$"<< std::endl;


    std::cout<<"====================================================="<<std::endl;

    H4lBrRatio br;
    std::cout<<br.getemutauBrRatio(126)<<std::endl;
    std::cout<<br.getemuBrRatio(126)<<std::endl;
    std::cout<<br.get4eBrRatio(126)<<std::endl;
    std::cout<<br.get2e2muBrRatio(126)<<std::endl;

    std::cout<<br.getemutauBrRatio(124)<<std::endl;
    std::cout<<br.getemuBrRatio(124)<<std::endl;
    std::cout<<br.get4eBrRatio(124)<<std::endl;
    std::cout<<br.get2e2muBrRatio(124)<<std::endl;

    std::cout<<br.getemutauBrRatio(125)<<std::endl;
    std::cout<<br.getemuBrRatio(125)<<std::endl;
    std::cout<<br.get4eBrRatio(125)<<std::endl;
    std::cout<<br.get2e2muBrRatio(125)<<std::endl;


}

    
