#pragma once

#include <vector>

#include <phasar/DB/ProjectIRDB.h>
#include <phasar/PhasarLLVM/Utils/DataFlowAnalysisType.h>

namespace psr {

void analyzeCoreUtilsUsingPreAnalysis(ProjectIRDB &&IRDB,
                                      std::vector<DataFlowAnalysisType> Analyses);

void analyzeCoreUtilsWithoutUsingPreAnalysis(
    ProjectIRDB &&IRDB, std::vector<DataFlowAnalysisType> Analyses);

} // namespace psr
