#pragma once

#include <cassert>

// An inverse travel cost function, which decreases (rather than increases) as the flow increases.
// It should model the costs for operating public transit. The more people use public transit, the
// lower the costs per person are. However, a traffic assignment minimizing solely the operational
// cost may result in long detours for some passengers. Therefore, the (static) travel time also
// contributes to the travel cost.
template <typename GraphT>
class InverseFunction {
 public:
  // Constructs an inverse travel cost function.
  InverseFunction(const GraphT& graph) : graph(graph) {}

  // Returns the travel cost on edge e, given the traffic flow x on e.
  float operator()(const int e, const float x) const {
    assert(x >= 0);
    return 1.0 * graph.length(e) * (155 / (x + 1) + 0.85) + 0.0 * graph.travelTime(e);
  }

  // Returns the derivative of e's travel cost function at x.
  float derivative(const int e, const float x) const {
    assert(x >= 0);
    const float tmp = x + 1;
    return 1.0 * graph.length(e) * -155 / (tmp * tmp);
  }

 private:
  const GraphT& graph; // The graph on whose edges we operate.
};