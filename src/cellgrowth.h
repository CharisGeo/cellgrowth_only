// -----------------------------------------------------------------------------
//
// Copyright (C) The BioDynaMo Project.
// All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
//
// See the LICENSE file distributed with this work for details.
// See the NOTICE file distributed with this work for additional information
// regarding copyright ownership.
//
// -----------------------------------------------------------------------------
#ifndef CELLGROWTH_H_
#define CELLGROWTH_H_

#include "biodynamo.h"

namespace bdm {

struct GrowthModule : public BaseBiologyModule {
   GrowthModule() : BaseBiologyModule(gAllBmEvents) {}

template <typename T, typename TSimulation = Simulation<>>
  void Run(T* cell) {
  if (cell->GetDiameter() < 60) {
      cell->ChangeVolume(4000);
    }
   }
    ClassDefNV(GrowthModule, 1);
   };

// Define compile time parameter
template <typename Backend>
struct CompileTimeParam : public DefaultCompileTimeParam<Backend> {
  using BiologyModules = Variant<GrowthModule>;
};
 	
inline int Simulate(int argc, const char** argv) {
  Simulation<> simulation(argc, argv);

  // Define initial model - in this example: single cell at origin
  auto* rm = simulation.GetResourceManager();
  auto&& cell = rm->New<Cell>(30);
  cell.AddBiologyModule(GrowthModule());

  simulation.GetScheduler()->Simulate(3000);

  std::cout << "Simulation completed successfully!" << std::endl;
  return 0;
}

}  // namespace bdm

#endif  // CELLGROWTH_H_
