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

std::string hustle_getPhysicalPlan(const ParseStatement &parse_statement,
                              CatalogDatabase *catalog_database,
                              OptimizerContext *optimizer_context);

void hustle_testopt(char const* query);

}  // namespace optimizer
}  // namespace quickstep
//
//#ifdef __cplusplus
//extern "C" {
//#endif
//void hustle_testopt(char * query);
//#ifdef __cplusplus
//}
//#endif

#endif //QUICKSTEP_HUSTLEOPTIMIZER_H
