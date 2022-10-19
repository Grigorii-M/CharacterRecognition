#pragma once

#include <eigen3/Eigen/Dense>
const uint32_t CELL_SIZE = 16;

/// Calculate Eucledian-Mahalanobis distance
double CalculateEMD(Eigen::VectorXd observation, Eigen::VectorXd kernel,
                    Eigen::MatrixXd covariance);

Eigen::MatrixXd CovarianceMahalanobis(std::vector<Eigen::VectorXd> objects,
                                      Eigen::VectorXd kernel);
