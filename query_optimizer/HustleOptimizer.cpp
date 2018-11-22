#include "query_optimizer/HustleOptimizer.hpp"

#include "query_optimizer/ExecutionGenerator.hpp"
#include "query_optimizer/LogicalGenerator.hpp"
#include "query_optimizer/OptimizerContext.hpp"
#include "query_optimizer/resolver/Resolver.hpp"
#include "query_optimizer/Optimizer.hpp"
#include "query_optimizer/HustleOptimizer.hpp"
#include "parser/SqlParserWrapper.hpp"
#include "HustleOptimizer.hpp"
#include "parser/ParseStatement.hpp"

#include "query_optimizer/LogicalGenerator.hpp"
#include "query_optimizer/OptimizerContext.hpp"
#include "query_optimizer/resolver/Resolver.hpp"
#include "gflags/gflags.h"
#include "query_optimizer/tests/TestDatabaseLoader.hpp"
#include "glog/logging.h"


namespace quickstep {
namespace optimizer {


std::string hustle_getPhysicalPlan(const ParseStatement &parse_statement,
                                       CatalogDatabase *catalog_database,
                                       OptimizerContext *optimizer_context) {
  LogicalGenerator logical_generator(optimizer_context);
  PhysicalGenerator physical_generator(optimizer_context);

  physical::PhysicalPtr physical_plan =
      physical_generator.generatePlan(
          logical_generator.generatePlan(*catalog_database, parse_statement),
          catalog_database);

  return physical_plan->toString();
}

//
//extern "C" void execute_plan(char*);


void hustle_testopt(char const * q) {

  std::cout << "opt in " << q << std::endl;
  SqlParserWrapper sql_parser_;
  Optimizer optimizer_;
  std::string* query = new std::string(q);

  sql_parser_.feedNextBuffer(query);
  quickstep::ParseResult result = sql_parser_.getNextStatement();

  std::cout << "2 \n";
  quickstep::optimizer::OptimizerContext optimizer_context;
  const quickstep::ParseStatement &parse_statement = *result.parsed_statement;

  std::cout << "3 \n";

  quickstep::optimizer::TestDatabaseLoader test_database_loader_;

  test_database_loader_.createTestRelation(false /* allow_vchar */);
  test_database_loader_.loadTestRelation();

  std::cout << "4 \n";
  std::string pplan =
      hustle_getPhysicalPlan(parse_statement,
                             test_database_loader_.catalog_database(),
                             &optimizer_context);
  std::cout << "5 \n";
  std::cout << "opt out" << pplan << std::endl;

//  execute_plan(pplan);
}


}  // namespace optimizer
}  // namespace quickstep