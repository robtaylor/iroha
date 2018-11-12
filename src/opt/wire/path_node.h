// -*- C++ -*-
#ifndef _opt_wire_path_node_h_
#define _opt_wire_path_node_h_

#include "opt/wire/common.h"

namespace iroha {
namespace opt {
namespace wire {

// Represents an IRegister flows from its source insn to sink.
class PathEdge {
public:
  PathEdge(int id, PathNode *source_node, PathNode *sink_node,
	   int source_reg_index);

  int GetId();
  IRegister *GetSourceReg();

  PathNode *source_node_;
  PathNode *sink_node_;
  int source_reg_index_;

private:
  int id_;
};

// Represents an IInsn and connected to other insns via PathEdge-s.
class PathNode {
public:
  PathNode(BBDataPath *path, int st_index, IInsn *insn);

  int GetId();
  void Dump(ostream &os);
  IInsn *GetInsn();

  int final_st_index_;
  int node_delay_;
  int state_local_delay_;
  int accumlated_delay_;
  // key-ed by source node id.
  map<int, PathEdge *> source_edges_;
  // key-ed by node id.
  map<int, PathEdge *> sink_edges_;

private:
  BBDataPath *path_;
  int initial_st_index_;
  IInsn *insn_;
};

}  // namespace wire
}  // namespace opt
}  // namespace iroha

#endif  // _opt_wire_path_node_h_