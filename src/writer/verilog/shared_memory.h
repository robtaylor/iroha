// -*- C++ -*-
#ifndef _writer_verilog_shared_memory_h_
#define _writer_verilog_shared_memory_h_

#include "writer/verilog/resource.h"

namespace iroha {
namespace writer {
namespace verilog {

class SharedMemory : public Resource {
public:
  SharedMemory(const IResource &res, const Table &table);

  virtual void BuildResource() override;
  virtual void BuildInsn(IInsn *insn, State *st) override;

  static string MemoryAddrPin(const IResource &res, int nth_port, const IResource *accessor);
  static string MemoryRdataPin(const IResource &res, int nth_port);
  static string MemoryWdataPin(const IResource &res, int nth_port,
			       const IResource *accessor);
  static string MemoryWenPin(const IResource &res, int nth_port,
			     const IResource *accessor);

private:
  void BuildMemoryAccessorResource(bool is_writer);
  void BuildMemoryResource();
  void BuildMemoryInstance();
  void BuildAccessWireAll(vector<const IResource *> &acccessors);
  void AddAccessPort(const IModule *imod, const IResource *accessor, bool upward);
  void AddRdataPort(const IModule *imod, const IResource *accessor, bool upward);
  void AddWire(const IModule *imod, const IResource *accessor);
  void AddRdataWire(const IModule *imod, const IResource *accessor);

  static string MemoryPinPrefix(const IResource &res,
				const IResource *accessor);
  static string MemoryReqPin(const IResource &res, const IResource *accessor);
  static string MemoryAckPin(const IResource &res, const IResource *accessor);
};

}  // namespace verilog
}  // namespace writer
}  // namespace iroha

#endif  // _writer_verilog_shared_memory_h_