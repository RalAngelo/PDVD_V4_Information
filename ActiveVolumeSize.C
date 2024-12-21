#include <TGeoManager.h>
#include <TGeoVolume.h>
#include <TGeoShape.h>
#include <TGeoBBox.h>
#include <iostream>

void GetActiveVolumeSize(TString volumeName)
{
    gSystem->Load("libGeom");

    // Import the geometry (assuming it is already loaded)
    TGeoManager::Import("PDVD_V4_Geometry.gdml");

    // Get the volume
    TGeoVolume* volume = gGeoManager->GetVolume(volumeName);
    
    if (!volume) {
        std::cout << "Volume not found!" << std::endl;
        return;
    }

    // Get the shape of the volume
    TGeoShape* shape = volume->GetShape();

    if (!shape) {
        std::cout << "Shape not found!" << std::endl;
        return;
    }

    // Check if it's a box and extract its dimensions
    if (TGeoBBox* boxShape = dynamic_cast<TGeoBBox*>(shape)) {
        Double_t dx = boxShape->GetDX();  // Get half-length in X direction
        Double_t dy = boxShape->GetDY();  // Get half-length in Y direction
        Double_t dz = boxShape->GetDZ();  // Get half-length in Z direction

        std::cout << "Volume: " << volumeName
                  << " Size: (" << 2 * dx << ", " << 2 * dy << ", " << 2 * dz << ")" << std::endl;
    } else {
        std::cout << "Volume shape is not a box. Shape type: " << shape->IsA()->GetName() << std::endl;
    }
}
