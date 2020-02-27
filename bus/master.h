#ifndef __MASTER__
#define __MASTER__

#include "bus/addr.h"
#include "bus/datatype.h"
#include <stdint.h>

class Bus;

typedef Bus *pBus;

class Master {
  static uint8_t num;
  static void _cnt_num();

protected:
  uint8_t m_id;
  pBus p_bus;
  bool connected;
  virtual void _init() = 0;
  virtual bool write(const Addr &addr, const DataType &data_type,
                     const uint64_t &wdata);
  virtual bool read(const Addr &addr, const DataType &data_type,
                    uint64_t &rdata);

public:
  Master();
  ~Master();
  void connect(pBus bus);
};

#endif
