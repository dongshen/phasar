/******************************************************************************
 * Copyright (c) 2017 Philipp Schubert.
 * All rights reserved. This program and the accompanying materials are made
 * available under the terms of LICENSE.txt.
 *
 * Contributors:
 *     Philipp Schubert and others
 *****************************************************************************/

/*
 * LazyLazyTypeGraph.cpp
 *
 *  Created on: 28.06.2018
 *      Author: nicolas bellec
 */

#include "boost/graph/depth_first_search.hpp"
#include "boost/graph/graph_utility.hpp"
#include "boost/graph/graphviz.hpp"
#include "boost/property_map/dynamic_property_map.hpp"

#include "llvm/IR/DerivedTypes.h"

#include "phasar/PhasarLLVM/Pointer/TypeGraphs/LazyTypeGraph.h"

#include "phasar/Utils/Logger.h"
#include "phasar/Utils/Utilities.h"

using namespace std;
using namespace psr;

namespace psr {

struct LazyTypeGraph::dfs_visitor : public boost::default_dfs_visitor {
  dfs_visitor(std::set<const llvm::StructType *> &Result) : Result(Result) {}

  void finish_edge(edge_t E, graph_t const &U) {
    LazyTypeGraph::vertex_t src = boost::source(E, U);
    LazyTypeGraph::vertex_t target = boost::target(E, U);

    Result.insert(U[target].type);
  }

  std::set<const llvm::StructType *> &Result;
};

LazyTypeGraph::vertex_t
LazyTypeGraph::addType(const llvm::StructType *NewType) {
  auto name = NewType->getName().str();

  if (type_vertex_map.find(name) == type_vertex_map.end()) {
    auto vertex = boost::add_vertex(g);
    type_vertex_map[name] = vertex;
    g[vertex].name = name;
    g[vertex].type = NewType;
  }

  return type_vertex_map[name];
}

bool LazyTypeGraph::addLink(const llvm::StructType *From,
                            const llvm::StructType *To) {
  if (already_visited)
    return false;

  already_visited = true;

  auto from_vertex = addType(From);
  auto to_vertex = addType(To);

  auto result_edge = boost::add_edge(from_vertex, to_vertex, g);

  already_visited = false;
  return result_edge.second;
}

void LazyTypeGraph::printAsDot(const std::string &Path) const {
  std::ofstream ofs(Path);
  boost::write_graphviz(ofs, g,
                        boost::make_label_writer(boost::get(
                            &LazyTypeGraph::VertexProperties::name, g)));
}

std::set<const llvm::StructType *>
LazyTypeGraph::getTypes(const llvm::StructType *StructType) {
  auto struct_ty_vertex = addType(StructType);

  std::vector<boost::default_color_type> color_map(boost::num_vertices(g));

  std::set<const llvm::StructType *> results;
  results.insert(StructType);

  dfs_visitor vis(results);

  boost::depth_first_visit(
      g, struct_ty_vertex, vis,
      boost::make_iterator_property_map(
          color_map.begin(), boost::get(boost::vertex_index, g), color_map[0]));

  return results;
}

} // namespace psr
