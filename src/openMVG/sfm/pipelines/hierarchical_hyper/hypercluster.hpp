#pragma once

#include <cereal/types/set.hpp>

#include "openMVG/sfm/sfm_data.hpp"
#include "openMVG/sfm/sfm_data_io_cereal.hpp"
#include "openMVG/sfm/pipelines/hierarchical_hyper/submap.hpp"
#include "openMVG/tracks/tracks.hpp"

/*
 *
 * clustering tracks sfm
 * inspired by paper :
 * [1] HyperSFM (2012)
 *
 */

namespace openMVG {
namespace sfm {

// Class for clustering sfm data using hypergraph partitioning
// (HyperSfM method)
class HyperCluster
{

public:
  HyperCluster(const sfm::SfM_Data & sfm_data, tracks::STLMAPTracks map_tracks, const int threshold_submap_tracksize);

  // create clustering tree by recursively partitioning submaps into smaller ones
  bool recursivePartitioning();

  // visualization using graphviz
  bool exportTreeGraph(std::string filename);

  // accessors
  HsfmSubmaps getSubMaps() const {return submaps_;}

private:

  // Partition a single submap into two children submaps, using a hypergraph
  // partitioning method.
  bool PartitionSubmap(const IndexT submap_id, std::vector<sfm::HsfmSubmap> & partitioned_pair);

  std::map<std::set<IndexT>, std::set<size_t>> createSubHyperGraph(IndexT submap_id);

  // input sfm data
  sfm::SfM_Data root_sfm_data_;

  // Tracks container
  tracks::STLMAPTracks map_tracks_;

  // container for submaps
  HsfmSubmaps submaps_;

  int threshold_submap_tracksize_;
};

} // namespace sfm
} // namespace openMVG
