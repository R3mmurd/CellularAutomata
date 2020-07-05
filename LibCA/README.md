# Lib CA

This is a basic template library to build cellular automata models.

## What this provides

The main elements that this library provides are the following:

- **N-dimensional lattice**: That allows you to build one-dimensional,
  two-dimensional, three-dimensional, or even higher dimensional
  cellular automata.

- **Boundary conditions**: Implementation of some basic boundary conditions
  that you can set to cellular automata independently of their dimensionality.
  This contains periodic, reflection, and fixed boundary conditions.

- **Neighborhoods**: Implementation of some basic neighborhood rules that you
  can set to cellular automata independently of their dimensionality.
  This contains the elementary neighborhood for one-dimensional lattice, and
  Moore and von Neumann neighborhoods for higher-dimensional lattices.

## Requirements

- C++ v14 or higher.
- [DeSiGNAR](https://github.com/R3mmurd/DeSiGNAR) library.
