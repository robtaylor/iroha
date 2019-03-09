// -*- C++ -*-
#ifndef _writer_verilog_wire_wire_set_h_
#define _writer_verilog_wire_wire_set_h_

#include "writer/verilog/common.h"

#include <map>

namespace iroha {
namespace writer {
namespace verilog {
namespace wire {

class Names {
public:
  static string AccessorName(const string &resource_name,
			     const IResource *res);
  static string AccessorResourceName(const IResource *res);
  static string AccessorSignalBase(const string &resource_name, const IResource *res, const char *name);
  static string AccessorWire(const string &resource_name, const IResource *res, const char *name);

  static string ResourceSignalBase(const string &resource_name, const char *name);
  static string ResourceWire(const string &resource_name, const char *name);
};

enum AccessorSignalType : int {
  ACCESSOR_REQ,
  ACCESSOR_ACK,
  ACCESSOR_READ_ARG,
  ACCESSOR_WRITE_ARG,
  ACCESSOR_NOTIFY_PARENT,
  ACCESSOR_NOTIFY_ACCESSOR,
};

class SignalDescription {
public:
  // e.g. ack, req...
  string name_;
  AccessorSignalType type_;
  int width_;
};

class AccessorInfo;

// Per accessor and signal.
class AccessorSignal {
public:
  SignalDescription *sig_desc_;
  IResource *accessor_res_;
  AccessorInfo *accessor_info_;
};

class WireSet;

class AccessorInfo {
public:
  AccessorInfo(WireSet *wire_set, IResource *accessor);

  void AddSignal(const string &name, AccessorSignalType type, int width);
  const vector<AccessorSignal> &GetSignals();
  AccessorSignal *FindSignal(const SignalDescription &sig);

private:
  WireSet *wire_set_;
  IResource *accessor_;
  string accessor_name_;
  vector<AccessorSignal> accessor_signals_;
};

class WireSet {
public:
  WireSet(Resource &res, const string &resource_name);
  ~WireSet();

  AccessorInfo *AddAccessor(IResource *accessor);
  SignalDescription *GetSignalDescription(const string &name, AccessorSignalType type, int width);
  string GetResourceName() const;

  void Build();

private:
  void BuildAccessorWire(const SignalDescription &sig_desc);
  void BuildResourceWire();
  void BuildArbitration(const SignalDescription &rsig_desc, const SignalDescription &asig_desc);
  void BuildRegisteredReq(const SignalDescription &rsig_desc,
			  vector<AccessorInfo *> &handshake_accessors);
  void BuildAccessorAck(const SignalDescription &rsig_desc, const SignalDescription &asig_desc,
			vector<AccessorInfo *> &handshake_accessors);
  void BuildWriteArg(const SignalDescription &sig_desc, const SignalDescription &req_sig_desc);
  void BuildReadArg(const SignalDescription &sig_desc);
  string ResourceWireName(const SignalDescription &sig_desc);
  string AccessorWireName(const AccessorSignal &sig);
  string AccessorWireNameWithReg(const AccessorSignal &sig);

  Resource &res_;
  string resource_name_;
  vector<AccessorInfo *> accessors_;
  map<string, SignalDescription *> signal_desc_;
};

}  // namespace wire
}  // namespace verilog
}  // namespace writer
}  // namespace iroha

#endif  // _writer_verilog_wire_wire_set_h_