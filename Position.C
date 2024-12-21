#include <iostream>

void PDVD_V4_with_positions(TString volName="")
{
    gSystem->Load("libGeom");
    gSystem->Load("libGdml");

    TGeoManager::Import("PDVD_V4.gdml");

    TGeoIterator next(gGeoManager->GetTopVolume());
    TGeoNode* node = nullptr;

    std::cout << "Volume positions:" << std::endl;

    while ((node = (TGeoNode*)next())) {
        const char* name = node->GetName();
        TGeoMatrix* matrix = node->GetMatrix();

        if (matrix) {
            // Get the translation vector
            const Double_t* translation = matrix->GetTranslation();
            std::cout << "Volume: " << name
                      << " Position: (" << translation[0] 
                      << ", " << translation[1] 
                      << ", " << translation[2] << ")" 
                      << std::endl;
        } else {
            std::cout << "Volume: " << name << " has no transformation matrix." << std::endl;
        }
    }
}