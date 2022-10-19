#include "calc.h"

#include <math.h>

#include <iostream>

double CalculateEMD(Eigen::VectorXd observation, Eigen::VectorXd kernel,
                    Eigen::MatrixXd covariance) {
  auto part1 = (observation - kernel).transpose();
  auto part2 = (covariance + Eigen::MatrixXd::Identity(CELL_SIZE * CELL_SIZE,
                                                       CELL_SIZE * CELL_SIZE))
                   .inverse();
  auto part3 = (observation - kernel);
  auto output = sqrt(part1 * part2 * part3);

  return output;
}

Eigen::MatrixXd CovarianceMahalanobis(std::vector<Eigen::VectorXd> objects,
                                      Eigen::VectorXd kernel) {
  Eigen::MatrixXd output(CELL_SIZE * CELL_SIZE, CELL_SIZE * CELL_SIZE);
  for (int i = 0; i < CELL_SIZE * CELL_SIZE; i++) {
    for (int j = 0; j < CELL_SIZE * CELL_SIZE; j++) {
      double sum = 0;
      for (int k = 0; k < objects.size(); k++) {
        sum += (objects[k][i] - kernel[i]) * (objects[k][j] - kernel[j]);
      }

      output(i, j) = sum / ((double)objects.size() - 1);
    }
  }

  return output;
}
