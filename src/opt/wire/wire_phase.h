// -*- C++ -*-
#ifndef _opt_wire_wire_phase_h_
#define _opt_wire_wire_phase_h_

#include "opt/common.h"
#include "opt/phase.h"

namespace iroha {
namespace opt {
namespace wire {

class WirePhase : public Phase {
public:
  virtual ~WirePhase();

  static Phase *Create();

private:
  virtual bool ApplyForTable(const string &key, ITable *table);
};

class SimpleShrinkPhase : public Phase {
public:
  virtual ~SimpleShrinkPhase();

  static Phase *Create();

private:
  virtual bool ApplyForTable(const string &key, ITable *table);
};

}  // namespace wire
}  // namespace opt
}  // namespace iroha

#endif  // _opt_wire_wire_phase_h_