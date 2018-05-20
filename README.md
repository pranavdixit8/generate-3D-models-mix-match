# Mix-and-Match

This is the repository for CMPT 764 course project.
Authors: Pranav Dixit, Ravi Agrawal, Hamid Homapour

Date: December 15, 2017

## Abstract
This  repository implements mix and match of part collections to generate new 3D models from existing 3D models. We create new 3D models of chairs from given test chairs using mix and match. We implement part correspondence using hausdorff distance for better alignment of the parts in the new chairs generated from a given set of plausible chairs. We create multiple generations of chairs from test chairs, with new chairs becoming the basis for next generation chair creation. We use a plausible score to understand if the new generated chair is plausible or not. We implement a plausible scorer for the new chairs using SVM. We train 3 SVM models for 3 different views of the chair: TOP, FRONT, SIDE. 

The aim of the project was to create interesting chairs, however the training data provided for the SVM model, to check plausibility,  was of simple chairs. Due to the contraction, we build a 'pruner' using k-mean clustering to create new chairs using chairs from different clusters, ignoring mating between similar chairs to create interesting chairs.



## Setup

### Prerequisites
- OpenGL Mathematics (GLM) library for matrix and vector calculations.
- CGAL (mesh, primitives)
- OpenCV
- LIBSVM
- GLM
- OSMesa
- Boost

### Clone the Repository

`git clone https://github.com/pranavdixit8/Mix-and-Match.git`

### Download the data and unzip it
<a href="https://drive.google.com/open?id=12fP5CIgBKFtWcK9bHqEDG6mbSDAiR7Oz" target="_blank">https://drive.google.com/open?id=12fP5CIgBKFtWcK9bHqEDG6mbSDAiR7Oz</a>


### Instructions
- Run `make` to build the executable
- Run `./mcaq` to launch the program
- Run `make clean` to clean build files
- Once you have your `./mcaq` executable ready and all the data downloaded, unzipped in the project home folder. Run `./mcaq train ./training_data/training` to train the SVM models for the 3 views.
- Make sure you train the model first before you create new chairs using the GUI.
- Run `./mcaq` to get the GUI for the project to create new chairs from the given sample chairs.
- Select `Open Dir` to load the test chair downloaded above: real_test_models#3.positive,  real_test_models#3.negative. You can check the score of their plausibility as you load them along with the clusters they belong to.
- To create new chair, you are supposed to load the postive test chairs and swap parts to create new chairs using the swap buttons on the GUI.
