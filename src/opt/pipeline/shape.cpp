#include "opt/pipeline/shape.h"

#include "opt/pipeline/stage_scheduler.h"

namespace iroha {
namespace opt {
namespace pipeline {

Shape::Shape(StageScheduler *ssch) : ssch_(ssch) {}

vector<pair<int, int>> &Shape::GetPipelineLocation() {
  if (locs_.size() != 0) {
    return locs_;
  }
  // s0
  // s0 s1
  // s0 s1 s2
  // .. ..
  // s0 .. .. s{n-1}
  int ns = ssch_->GetMacroStageCount();
  for (int i = 0; i < ns; ++i) {
    for (int j = 0; j <= i; ++j) {
      locs_.push_back(make_pair(i, j));
    }
  }
  // -- s1 s2 .. s{n-1}
  // -- -- s2 .. s{n-1}
  //             ..
  //             s{n-1}
  for (int i = 1; i < ns; ++i) {
    for (int j = i; j < ns; ++j) {
      locs_.push_back(make_pair(i + ns - 1, j));
    }
  }

  return locs_;
}

}  // namespace pipeline
}  // namespace opt
}  // namespace iroha
