#include "MovingObject.h"
#include <TFile.h>
#include <TTree.h>
#include <iostream>
#include <TRandom.h>

void write() {
    // Create the ROOT file
    TFile *file = new TFile("tree_file.root", "RECREATE");

    // Create the tree
    TTree *tree = new TTree("moving_objects", "Velocity measurements");

    // Create our object 
    MovingObject *obj = new MovingObject();

    // Connect the object to the tree
    tree->Branch("object", &obj);


    // Set the random seed
    gRandom->SetSeed(12345);

    // Generate 10000 random measurements
    for (int i = 0; i < 10000; ++i) {
        Double_t vx = gRandom->Gaus(0, 0.3);
        Double_t vy = gRandom->Gaus(0, 0.3);
        Double_t vz = gRandom->Gaus(0, 0.3);
        obj->SetVelocity(vx, vy, vz);
        tree->Fill();
    }

    // Check the number of measurments 
    std::cout << "Number of measurements: " << tree->GetEntries() << std::endl;

    // Save and close
    tree->Write();
    file->Close();
    
    delete obj;
    delete file;
}
