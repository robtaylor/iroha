// -*- C++ -*-
#ifndef _design_resource_attr_h_
#define _design_resource_attr_h_
#include "iroha/common.h"

namespace iroha {

class ResourceAttr {
public:
  static bool IsMultiCycleInsn(IInsn *insn);
  static int NumMultiCycleInsn(IState *st);
};

}  // namespace iroha

#endif  // _design_resource_attr_h_
