/*
 * Copyright (c) 2015, Georgia Tech Research Corporation
 * All rights reserved.
 *
 * Author(s): Michael X. Grey <mxgrey@gatech.edu>
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

#ifndef DART_DYNAMICS_ENDEFFECTOR_H_
#define DART_DYNAMICS_ENDEFFECTOR_H_

#include "dart/dynamics/FixedFrame.h"

namespace dart {
namespace dynamics {

class BodyNode;
class Skeleton;

class EndEffector : public FixedFrame
{
public:

  friend class Skeleton;

  /// Constructor
  explicit EndEffector(Frame* _refFrame, const std::string& _name,
                       const Eigen::Isometry3d& _relativeTransform =
                                        Eigen::Isometry3d::Identity());

  /// Destructor
  virtual ~EndEffector();

  //----------------------------------------------------------------------------
  // Properties
  //----------------------------------------------------------------------------

  /// Set the current relative transform of this EndEffector
  void setRelativeTransform(const Eigen::Isometry3d& _newRelativeTf);

  /// Set the default relative transform of this EndEffector. The relative
  /// transform of this EndEffector will be set to _newDefaultTf the next time
  /// resetRelativeTransform() is called. If _useNow is set to true, then
  /// resetRelativeTransform() will be called at the end of this function.
  void setDefaultRelativeTransform(const Eigen::Isometry3d& _newDefaultTf,
                                   bool _useNow);

  /// Set the current relative transform of this EndEffector to the default
  /// relative transform of this EndEffector. The default relative transform can
  /// be set with setDefaultRelativeTransform()
  void resetRelativeTransform();

  //----------------------------------------------------------------------------
  // Relationships
  //----------------------------------------------------------------------------

  /// Get the BodyNode that this EndEffector is rigidly attached to
  BodyNode* getParentBodyNode();

  /// Get the BodyNode that this EndEffector is rigidly attached to
  const BodyNode* getParentBodyNode() const;

  /// Get the Skeleton that this EndEffector belongs to
  Skeleton* getSkeleton();

  /// Get the Skeleton that this EndEffector belongs to
  const Skeleton* getSkeleton() const;

  /// Get the index of this EndEffector within the Skeleton
  size_t getIndex() const;

protected:
  /// Search for the parent BodyNode that this EndEffector belongs to
  void identifyParentBodyNode(Frame* _refFrame);

  /// Inform the Skeleton of this EndEffector's existence
  void registerWithSkeleton();

  /// The BodyNode that this EndEffector is rigidly attached to
  BodyNode* mParentBodyNode;

  /// The relative transform will be set to this whenever
  /// resetRelativeTransform() is called
  Eigen::Isometry3d mDefaultTransform;

  /// The index of this EndEffector within the Skeleton
  size_t mIndexInSkeleton;
};

} // namespace dynamics
} // namespace dart


#endif // DART_DYNAMICS_ENDEFFECTOR_H_