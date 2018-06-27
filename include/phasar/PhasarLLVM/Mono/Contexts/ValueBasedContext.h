/******************************************************************************
 * Copyright (c) 2017 Philipp Schubert.
 * All rights reserved. This program and the accompanying materials are made
 * available under the terms of LICENSE.txt.
 *
 * Contributors:
 *     Nicolas Bellec and others
 *****************************************************************************/

/*
 * ValueBasedContext.h
 *
 *  Created on: 19.06.2018
 *      Author: nicolas
 */

#pragma once

#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <phasar/Config/ContainerConfiguration.h>
#include <phasar/Utils/Macros.h>
#include <phasar/PhasarLLVM/Mono/Values/ValueBase.h>

#include "ContextBase.h"


namespace psr {

/*  N = Node in the CFG
 *  Value = Values inside the monotone sets (must be a sub class of ValueBase<Id,V>)
 */
template <typename N, typename Value>
class ValueBasedContext : public ContextBase<N, Value, ValueBasedContext<N,Value>> {
protected:
  std::set<Value> args;

public:
  ValueBasedContext() = default;

  virtual void enterFunction(N src, N dest, MonoSet<Value> &In) override {
    //TODO
  }

  virtual void exitFunction(N src, N dest, MonoSet<Value> &In) override {
    //TODO
  }

  virtual bool isUnsure() override {
    return false;
  }

  virtual bool isEqual(const ValueBasedContext &rhs) const override {
    //TODO
    return false;
  }

  virtual bool isDifferent(const ValueBasedContext &rhs) const override {
    //TODO
    return !isEqual(rhs);
  }

  virtual bool isLessThan(const ValueBasedContext &rhs) const override {
    //TODO
    return true;
  }

  virtual void print(std::ostream &os) const override {
    //TODO
  }
};

} // namespace psr
