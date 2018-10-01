// -*- C++ -*-
#ifndef _opt_wire_scheduler_h_
#define _opt_wire_scheduler_h_

#include "opt/wire/common.h"

namespace iroha {
namespace opt {
namespace wire {

class SchedulerCore {
public:
  SchedulerCore(DataPathSet *data_path_set, DelayInfo *delay_info);

  void Schedule();

private:
  DataPathSet *data_path_set_;
  DelayInfo *delay_info_;
};

class Scheduler {
public:
  Scheduler(DataPath *data_path, DelayInfo *delay_info);

  void Schedule();

private:
  bool ScheduleEdge(PathEdge *e);
  void ClearSchedule();
  void ScheduleExclusive(PathEdge *e, int min_index);
  void ScheduleNonExclusive(PathEdge *e, int min_index);

  DataPath *data_path_;
  DelayInfo *delay_info_;
  // latency to edges.
  map<int, vector<PathEdge *> > sorted_edges_;
};

}  // namespace wire
}  // namespace opt
}  // namespace iroha

#endif  // _opt_wire_scheduler_h_