# Efficient and Adaptive Triangulation of 3D Point Clouds for Machining Sculptured Surfaces

# Abstract

Parts with sculptured surfaces play a vital role across diverse industrial sectors and are often manufactured using multiaxis Computer Numerical Control (CNC) milling machines. Reverse Engineering (RE) is commonly employed to replicate such parts from 3D point clouds. However, reconstructing continuous smooth surfaces from point clouds remains challenging. To address this, triangulated models are frequently utilized as an alternative. This paper presents a novel, practical, and efficient approach for generating a 3D triangulation with a reduced number of triangles while maintaining predefined accuracy from a 3D unstructured point cloud. This approach combines both regular and adaptive triangulations for maximum efficiency and explicitly integrates approximation accuracy, adaptive subdivision, point distributions within triangles, and triangle quality. The approach involves four main steps: (1) generating an initial regular 3D triangulation; (2) adaptively and recursively subdividing triangles based on point distribution until the desired accuracy is achieved; (3) verifying triangle qualities to retrieve surface boundaries efficiently; and (4) generating the associated Standard Tessellation Language (STL) model for use in 3-axis machining. The proposed approach is validated across various 3D point clouds of complex sculptured surfaces, demonstrating superior performance in terms of both triangulation accuracy and processing time.

# Running environment

The software is developed using C++ under the IDE Embarcadero and Windows 10.

# Launching the software

To run the software, open the project file "Adaptive_Triangulation_3D_Point_Clouds_Sculptured_Surfaces.cbproj". Then, all associated files will be charged. 

Inside embarcadero, compile, link, and then launch the execution of the developed software. 

The required actions to generate the STL file are numbered from 0 to 7.

The sequence of actions are described below:

     0. Import point clouds : read the point coordinates of the point clouds.
     1. Adaptive triangulation : open the window to run the proposed approach.
     2. Create Cells : creation of cells.
     3. Generate regular triangulation : generation of the initial regular triangulation.
     4. Generate adaptive triangulation : adaptive subdivision of triangles to satisfy the required precision.
     5. Filter bad triangles (optional) : the bad triangles are filtred in this step.
     6. Generate STL file : STL file is generated and saved to be used for machining.
     7. Show triangulation results (optional) : show the results for regular and adaptive triangulations 

# Testing Data

The two point clouds used for the experimental tests in the paper can be downloaded from the following link:     

https://drive.google.com/drive/folders/1zgFLfEvdymhQyj50Bk4iiIe56RzphjSX?usp=sharing

# Citation

If you use our work or find it useful in your research, please cite our paper:

Bey, M. and Azouaoui, K. (2025) Efficient and Adaptive Triangulation of 3D Point Clouds for Machining Sculptured Surfaces. Visual Computer, Vol. , pages.
