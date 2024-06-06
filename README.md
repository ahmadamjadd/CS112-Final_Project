# CS112 Clustering Project - Unsupervised Learning

This project was developed as the final semester project for the CS112 Object-Oriented Programming course. It implements a clustering technique using an unsupervised learning algorithm, leveraging the power of C++/CLI and an Object-Oriented Programming (OOP) approach.

## Project Description

The project encompasses three main tasks:

1. **Calculation of Correlation Matrix and Discretization**:
   - Calculate the correlation matrix from the given data set using Pearson's correlation coefficient.
   - Discretize the correlation matrix by calculating the mean of each column and setting values above the mean to 1 and the rest to 0.
   - Visualize the discretized matrix as a bitmap image with zooming functionality.
   - Display a color-coded image of the similarity matrix by scaling the values and applying a green shade.

2. **Permutation and Signature Technique**:
   - Permute the data matrix by shuffling individual rows.
   - Display the color-coded image of the permuted data matrix.
   - Recover image clusters using the signature technique, which involves summing row values, calculating the mean, and multiplying the sum by the mean.
   - Rearrange (sort) the similarity matrix based on the signature values of each row.
   - Apply the correlation matrix calculation, discretization, and visualization techniques to the rearranged matrix.

3. **Write-up and Documentation**:
   - Provide a detailed write-up explaining each step of the project.
   - Include screenshots and work distribution among team members.

## Getting Started

To run this project on your local machine, follow these steps:

1. Clone the repository:

2. Open the project in Visual Studio (or your preferred C++ IDE).

3. Build the project to resolve any dependencies.

4. Run the project, and you should see the main application window.

5. Use the "File" menu to open the desired input data set (in the required format).

6. Follow the menu options to perform the tasks mentioned above, such as calculating the correlation matrix, discretization, permutation, signature technique, and visualization.

7. Explore the code in the `Form1.h` and `Form1.cpp` files to understand the implementation details.

## Input Data Format

The input data set should follow the specified format:

- The first row contains the number of rows in the data set.
- The second row contains the number of columns in the data set.
- The third row is an empty line.
- The remaining rows contain the actual data, with each row representing a data point and each column representing a feature.

## Dependencies

This project was developed using Visual Studio and the C++/CLI language. Ensure that you have the following dependencies installed:

- Visual Studio (or any compatible C++ IDE)
- C++/CLI compiler

## Contributing

Contributions to this project are welcome! If you find any issues or have suggestions for improvements, please open an issue or submit a pull request.

## Acknowledgements

We would like to express our sincere gratitude to our instructor, Dr. Zahid Halim, for his guidance and support throughout this project. His mentorship enabled us to push the boundaries of our knowledge and skills, resulting in a successful and rewarding learning experience.

## Team Members

This project was a collaborative effort between two team members:

1. **Muhammad Ahmad Amjad (2023361)**

2. **Abdullah Ejaz Janjua (2023038)**
   - [GitHub](https://github.com/abdullahejazjanjua)
