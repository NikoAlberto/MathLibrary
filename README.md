# MathLibrary
**Class Matrix**
Contains three types of constructors, object of this type represents tne matrix (vector<vector> of doubles) with dimensions M*N. Contains several methods:
  1. Adamara multiplication - arg is the second matrix, the result - the multiplication
  2. Transpose - returns transposed matrix, no arguments
  3. Load_file and save_file - loads/saves the matrix from/in the file; arg - string, the name of the new or existing file
  Also there are different friend functions defining rank of the matrix and inverse matrix; their work and pecularities are obvious;
  
  **Class RCA**
  The object of the class is the matrix, which is extracted from the file, which is given into constructor. 
  Methods:
  1. new_matrix_RCA - carries out centring and scaling of the matrix; arg - object of class matrix
  2. Nipals - implements approximation of given matrix returns three matrices depending on a parameter - matrices of weights, abacus and remains. Args - matrix from (1) and int param
  3. Scope - returns vector of double, no args
  4. dispersion_av - no args, counts deviation from mean in each row, returns vector of double
  5. ERV and TRV - computation of complete and explained variance of the residuals in training, return double values
