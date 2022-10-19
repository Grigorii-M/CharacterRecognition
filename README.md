# Character recognition
### By: Grigorii Matiukhin 

## Introduction
The objective of this laboratory work is to implement a character recognition algorithm.

## Project Structure
All of the computations needed to differentiate between charachters are done inside `CharacterRecognizer` class.

Because the problem can be stated as finding a shortest distance between two points in N-dimensional space, a big part of the calculations can be done beforehand. In its constructor `CharacterRecognizer` computes kernels of different classes and covariation matrices for each class, using system fonts as its data.

In its `Recognize` method the distance between input vector and all of the kernels is calculated. The lower the distance, the more likely that input vector belongs to this particular kernel.
