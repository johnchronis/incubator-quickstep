#ifndef QUICKSTEP_HUSTLEOPTIMIZER_H
#define QUICKSTEP_HUSTLEOPTIMIZER_H

#include "query_optimizer/PhysicalGenerator.hpp"
#include "utility/Macros.hpp"

namespace quickstep {

class CatalogDatabase;
class ParseStatement;
class QueryHandle;

namespace optimizer {

class OptimizerContext;

const char* hustle_getPhysicalPlan(const ParseStatement &parse_statement,
                              CatalogDatabase *catalog_database,
                              OptimizerContext *optimizer_context);


}  // namespace optimizer
}  // namespace quickstep


#endif //QUICKSTEP_HUSTLEOPTIMIZER_H
