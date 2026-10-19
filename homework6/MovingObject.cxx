#include "MovingObject.h"
#include <cmath>

ClassImp(MovingObject);

// Default constructor
MovingObject::MovingObject() {
    fVx = 0;
    fVy = 0;
    fVz = 0;
}

// Constructor with arguments
MovingObject::MovingObject(Double_t vx, Double_t vy, Double_t vz) {
    fVx = vx;
    fVy = vy;
    fVz = vz;
}

// Destructor
MovingObject::~MovingObject() {
}

// Get velocity components
Double_t MovingObject::Vx() const {
    return fVx;
}

Double_t MovingObject::Vy() const {
    return fVy;
}

Double_t MovingObject::Vz() const {
    return fVz;
}

// Change velocity
void MovingObject::SetVelocity(Double_t vx, Double_t vy, Double_t vz) {
    fVx = vx;
    fVy = vy;
    fVz = vz;
}

// Calculate total speed
Double_t MovingObject::Speed() const {
    return sqrt(fVx*fVx + fVy*fVy + fVz*fVz);
}

// Calculate horizontal speed
Double_t MovingObject::HorizontalSpeed() const {
    return sqrt(fVx*fVx + fVy*fVy);
}