/*
 * Copyright (c) 2014, Georgia Tech Research Corporation
 * All rights reserved.
 *
 * Author(s): Jeongseok Lee <jslee02@gmail.com>
 *
 * Georgia Tech Graphics Lab and Humanoid Robotics Lab
 *
 * Directed by Prof. C. Karen Liu and Prof. Mike Stilman
 * <karenliu@cc.gatech.edu> <mstilman@cc.gatech.edu>
 *
 * This file is provided under the following "BSD-style" License:
 *   Redistribution and use in source and binary forms, with or
 *   without modification, are permitted provided that the following
 *   conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 *   CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 *   INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *   MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 *   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 *   USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *   AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *   ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *   POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DART_DYNAMICS_PLANARRJOINT_H_
#define DART_DYNAMICS_PLANARRJOINT_H_

#include <string>

#include "dart/common/Factory.h"
#include "dart/dynamics/MultiDofJoint.h"

namespace dart {
namespace dynamics {

/// PlanarJoint represents a 3-dof joint, which has two orthogonal translational
/// axes and one rotational axis.
///
/// First and second coordiantes represent translation along first and second
/// translational axese, respectively. Third coordinate represents rotation
/// along rotational axis.
class PlanarJoint : public MultiDofJoint<3>
{
public:
  /// Plane type
  enum PlaneType
  {
    PT_XY,
    PT_YZ,
    PT_ZX,
    PT_ARBITRARY
  };

  /// \brief Constructor
  /// \warning This function will turn to protected member since DART 5.0.
  /// Please use Skeleton::createJoint() to create joint.
  explicit PlanarJoint(const std::string& _name = "PlanarJoint");

  /// brief Destructor
  /// \warning This function will turn to protected member since DART 5.0.
  virtual ~PlanarJoint();

  /// Set plane type as XY-plane
  void setXYPlane();

  /// Set plane type as YZ-plane
  void setYZPlane();

  /// Set plane type as ZX-plane
  void setZXPlane();

  /// Set plane type as arbitrary plane with two orthogonal translational axes
  void setArbitraryPlane(const Eigen::Vector3d& _transAxis1,
                         const Eigen::Vector3d& _transAxis2);

  /// Return plane type
  PlaneType getPlaneType() const;

  /// Return rotational axis
  const Eigen::Vector3d& getRotationalAxis() const;

  /// Return first translational axis
  const Eigen::Vector3d& getTranslationalAxis1() const;

  /// Return second translational axis
  const Eigen::Vector3d& getTranslationalAxis2() const;

  // Documentation inherited
  virtual Eigen::Vector6d getBodyConstraintWrench() const
  {
    return mWrench - mJacobian * mForces;
  }

protected:
  // Documentation inherited
  virtual void updateLocalTransform();

  // Documentation inherited
  virtual void updateLocalJacobian();

  // Documentation inherited
  virtual void updateLocalJacobianTimeDeriv();

protected:
  /// Plane type
  PlaneType mPlaneType;

  /// Rotational axis
  Eigen::Vector3d mRotAxis;

  /// First translational axis
  Eigen::Vector3d mTransAxis1;

  /// Second translational axis
  Eigen::Vector3d mTransAxis2;

public:
  // To get byte-aligned Eigen vectors
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};

// Register to the joint factory
DART_FACTORY_REGISTER(Joint, PlanarJoint, "PlanarJoint")

}  // namespace dynamics
}  // namespace dart

#endif  // DART_DYNAMICS_PLANARRJOINT_H_

