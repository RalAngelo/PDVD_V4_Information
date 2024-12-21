#include <TGeoManager.h>
#include <TGeoVolume.h>
#include <TGeoNode.h>
#include <TGeoMatrix.h>
#include <TPolyLine3D.h>
#include <iostream>

void PDVD_V4_with_axes(TString volName = "")
{
    gSystem->Load("libGeom");
    gSystem->Load("libGdml");

    // Import the GDML file
    TGeoManager::Import("PDVD_V4_Geometry.gdml");

    TGeoIterator next(gGeoManager->GetTopVolume());
    TGeoNode* node = nullptr;

    // Print positions of all nodes
    std::cout << "Volume positions:" << std::endl;

    while ((node = (TGeoNode*)next())) {
        const char* name = node->GetName();
        TGeoMatrix* matrix = node->GetMatrix();

        if (matrix) {
            // Extract translation vector
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

    // Create custom axes using TPolyLine3D
    TPolyLine3D* xAxis = new TPolyLine3D(2);
    TPolyLine3D* yAxis = new TPolyLine3D(2);
    TPolyLine3D* zAxis = new TPolyLine3D(2);

    xAxis->SetPoint(0, 0.0, 0.0, 0.0);
xAxis->SetPoint(1, 1000.0, 0.0, 0.0);  // Increased length for X axis
xAxis->SetLineColor(kRed);           // Set a very visible color (yellow)
xAxis->SetLineWidth(5);                 // Set thicker line width for better visibility

yAxis->SetPoint(0, 0.0, 0.0, 0.0);
yAxis->SetPoint(1, 0.0, 1000.0, 0.0);  // Increased length for Y axis
yAxis->SetLineColor(kBlack);            // Set Y axis color to black
yAxis->SetLineWidth(5);                 // Set thicker line width for better visibility

zAxis->SetPoint(0, 0.0, 0.0, 0.0);
zAxis->SetPoint(1, 0.0, 0.0, 1000.0);  // Increased length for Z axis
zAxis->SetLineColor(kBlue);          // Set a very visible color (magenta)
zAxis->SetLineWidth(5);                 // Set thicker line width for better visibility



    // Draw the geometry with axes
    gGeoManager->GetTopVolume()->Draw("X3D");

    // Draw axes on top of the geometry
    xAxis->Draw("same");
    yAxis->Draw("same");
    zAxis->Draw("same");
}