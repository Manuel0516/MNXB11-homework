#include "MovingObject.h"
#include <TFile.h>
#include <TTree.h>
#include <iostream>
#include <TRandom.h>
#include <TH2D.h>
#include <TCanvas.h>

void read() {
    // Open the file 
    TFile *file = TFile::Open("tree_file.root", "READ");

    if (!file || file->IsZombie()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    // Tretrive the tree
    TTree *tree = nullptr;
    file->GetObject("tree", tree);

    if (!tree) {
        std::cerr << "Tree not found" << std::endl;
        file->Close();
        delete file;
        return;
    }

    tree->Print();

    // Connect out object to the branch 
    MovingObject *obj = new MovingObject();
    tree->SetBranchAddress("object", &obj);

    // Get number of entries
    Long64_t nEntries = tree->GetEntries();

    // First plot: vy vs vx
    TH2D *h2 = new TH2D(
        "hist", 
        "Velocity components;Vx (m/s);Vy (m/s)", 
        100, -1.5, 1.5,
        100, -1.5, 1.5);
    
    for (Long64_t i = 0; i < nEntries; ++i) {
        tree->GetEntry(i);
        h2->Fill(obj->Vx(), obj->Vy());
    }

    TCanvas *c1 = new TCanvas("c1", "Velocity components", 800, 600);
    h2->Draw("COLZ");
    c1->SaveAs("velocity_components.pdf");

    // Second plot: speed distribution
    TCanvas *c2 = new TCanvas("c2", "Speed distribution", 800, 600);

    tree->Draw(
        "sqrt(object.Vx()*object.Vx()+object.Vy()*object.Vy()):object.Vz()", 
        "sqrt(object.Vx()*object.Vx()+object.Vy()*object.Vy()+object.Vz()*object.Vz())>0.50", 
        "P"
    ); 

    if (tree->GetHistogram()) {
        tree->GetHistogram()->SetTitle(
            "Selected velocities (v > 0.50 m/s);vz (m/s);vxy (m/s)"
        );
        c2->Modified();
        c2->Update();
        c2->SaveAs("selected_velocities.pdf");
    }

    // Clean up
    tree->ResetBranchAddresses();
    delete obj;
    file->Close();
    delete file;
} 