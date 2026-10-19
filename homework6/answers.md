# Homework 6 — ROOT

### Question 0: Header guards vs. `#pragma once`

Both prevent a header file from being included multiple times, avoiding redefinition errors.

Header guards use three directives: `#ifndef`, `#define`, and `#endif`, while `#pragma once` uses a single directive. They have the same purpose.

### Question 1: Difference between `struct` and `class`

The main difference is their default access level. In a `struct`, variables and methods are public by default, while in a `class`, variables and methods are private by default.

### Question 2: Why do we inherit from `TObject`?

We inherit from `TObject` because it provides useful ROOT functionality for working with objects. It also helps integrate our `MovingObject` class with ROOT, this allows us to store `MovingObject` objects in a `TTree`.

### Question 3: Implementing and compiling the class

I implemented the `MovingObject` class in `MovingObject.h` and `MovingObject.cxx`, with the constructors, destructor, velocity functions, and `ClassDef`/`ClassImp`. I compiled it successfully using `.L MovingObject.cxx+`.

### Question 4: Velocity components

The default constructor initializes the three velocity components to zero, while the other constructor initializes them using the values passed as arguments.

The getter functions `Vx()`, `Vy()`, and `Vz()` return the corresponding velocity components, while `SetVelocity()` changes their values. 

### Question 5: Speed calculations

The total and horizontal speeds are calculated using:

$$
v = \sqrt{v_x^2 + v_y^2 + v_z^2}
$$

$$
v_{xy} = \sqrt{v_x^2 + v_y^2}
$$

**Example A:** (0.30, 0.40, 0.00) m/s

- Total speed: 0.5000 m/s
- Horizontal speed: 0.5000 m/s

**Example B:** (0.30, 0.40, 0.50) m/s

- Total speed: 0.7071 m/s
- Horizontal speed: 0.5000 m/s

Changing $v_z$ affects the total speed because it is included in the calculation, while the horizontal speed only depends on $v_x$ and $v_y$.

The horizontal speed cannot be greater than the total speed because the total speed includes the additional non-negative term $v_z^2$. Therefore, $0 \leq v_{xy} \leq v$.

### Question 6: Generating and storing measurements

I generated 10,000 independent velocity measurements using a Gaussian distribution for each velocity component.

The parameters used were:

- Mean: 0.0 m/s
- Standard deviation: 0.30 m/s
- Random seed: 12345

I saved the measurements in `tree_file.root`, using a `TTree` named `tree` and a branch named `object`. I used `tree->GetEntries()` to check that it contained 10,000 entries.

### Question 7: Plots

For the velocity components, I created a two-dimensional histogram of $v_y$ versus $v_x$, using 100 bins on each axis and a range from -1.5 to 1.5 m/s. I used `COLZ` to represent the number of measurements in each bin and saved the plot as `velocity_components.pdf`.

The plot shows a concentration of measurements around (0, 0), since both velocity components follow Gaussian distributions with a mean of zero.

For the selected velocities, I used `TTree::Draw()` to plot horizontal speed $v_{xy}$ against $v_z$, selecting only measurements with total speed $v > 0.50$ m/s. I saved the scatter plot as `selected_velocities.pdf`.

The plot shows an empty semicircular region with radius 0.50 m/s at the origin, because measurements with total speed less than or equal to 0.50 m/s were excluded.

### Commands used

To generate the data:

```cpp
.L MovingObject.cxx+
.x write.C
```

To read the data in a new ROOT session and generate the plots:

```cpp
.L MovingObject.cxx+
.x read.C
```