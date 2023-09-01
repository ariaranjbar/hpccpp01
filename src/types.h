#ifndef MD_TYPES_H
#define MD_TYPES_H
#include <Eigen/Dense>

using Positions_t = Eigen::Array3Xd;
using Velocities_t = Eigen::Array3Xd;
using Forces_t = Eigen::Array3Xd;
using Names_t = Eigen::ArrayX<uint8_t>;
using Masses_t = Eigen::ArrayXd;

#endif // __MD_TYPES_H