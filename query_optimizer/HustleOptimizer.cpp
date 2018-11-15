#include "query_optimizer/HustleOptimizer.hpp"

#include "query_optimizer/ExecutionGenerator.hpp"
#include "query_optimizer/LogicalGenerator.hpp"
#include "query_optimizer/OptimizerContext.hpp"
#include "query_optimizer/resolver/Resolver.hpp"

namespace quickstep {
namespace optimizer {


const char* hustle_getPhysicalPlan(const ParseStatement &parse_statement,
                                       CatalogDatabase *catalog_database,
                                       OptimizerContext *optimizer_context) {
  LogicalGenerator logical_generator(optimizer_context);
  PhysicalGenerator physical_generator(optimizer_context);

  physical::PhysicalPtr physical_plan =
      physical_generator.generatePlan(
          logical_generator.generatePlan(*catalog_database, parse_statement),
          catalog_database);

  return physical_plan->toString().c_str();
}

}  // namespace optimizer
}  // namespace quickstep


