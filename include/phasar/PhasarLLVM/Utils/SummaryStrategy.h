/******************************************************************************
 * Copyright (c) 2017 Philipp Schubert.
 * All rights reserved. This program and the accompanying materials are made
 * available under the terms of LICENSE.txt.
 *
 * Contributors:
 *     Philipp Schubert and others
 *****************************************************************************/

#pragma once

#include <iosfwd>
#include <map>
#include <string>

namespace psr {

enum class SummaryGenerationStrategy {
  always_all = 0,
  powerset,
  all_and_none,
  all_observed,
  always_none
};

extern const std::map<SummaryGenerationStrategy, std::string>
    SummaryGenerationStrategyToString;

extern const std::map<std::string, SummaryGenerationStrategy>
    StringToSummaryGenerationStrategy;

std::ostream &operator<<(std::ostream &os, const SummaryGenerationStrategy &s);

} // namespace psr
