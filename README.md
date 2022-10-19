# Character recognition
### By: Grigorii Matiukhin 

## Introduction
The objective of this laboratory work is to implement a character recognition algorithm.

## Project Structure
All of the computations needed to differentiate between charachters are done inside `CharacterRecognizer` class.

Because the problem can be stated as finding a shortest distance between two points in N-dimensional space, a big part of the calculations can be done beforehand. In its constructor `CharacterRecognizer` computes kernels of different classes and covariation matrices for each class. Charachters from a number of system fonts are used, in order to simplify kernel creation process, which is made possible by the `FreeType` library. Both kenels and user input are stored as objects of `Bitmap` class.

Fonts are also used in computation of cocariation matrices, as well as `Eigen` -- linear algebra library.

In its `Recognize` method the distance between input vector and all of the kernels is calculated. The lower the distance, the more likely that input vector belongs to this particular kernel.

Graphical component of this program is made using `olcPixelGameEngine` -- a simple game engine library. It allows user to draw charachters on the screen, and it presents the recognized kernel.
