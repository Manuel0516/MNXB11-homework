#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H
#include <TObject.h>


#pragma once
#include <TObject.h>

class MovingObject : public TObject {

public:
    // Constructors
    MovingObject();
    MovingObject(Double_t vx, Double_t vy, Double_t vz);

    // Destructor
    ~MovingObject() override;

    // Functions to get velocities
    Double_t Vx() const;
    Double_t Vy() const;
    Double_t Vz() const;

    // Functions to calculate speeds
    Double_t Speed() const;
    Double_t HorizontalSpeed() const;

    // Function to change velocity
    void SetVelocity(Double_t vx, Double_t vy, Double_t vz);

private:
    // Variables belonging to the object
    Double_t fVx;
    Double_t fVy;
    Double_t fVz;

    ClassDef(MovingObject, 1);
};

#endif