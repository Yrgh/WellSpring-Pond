#pragma once

class GenericRenderDevice {
protected:
  int _nothing;
  virtual void doesNothing() = 0;
public:
  virtual void initSystem() = 0;
  virtual void cleanupSystem() = 0;
};