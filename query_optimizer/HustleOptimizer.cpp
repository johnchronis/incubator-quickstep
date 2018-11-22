#include "query_optimizer/HustleOptimizer.hpp"
#include "query_optimizer/Optimizer.hpp"
#include "query_optimizer/ExecutionGenerator.hpp"
#include "query_optimizer/LogicalGenerator.hpp"
#include "query_optimizer/OptimizerContext.hpp"
#include "query_optimizer/resolver/Resolver.hpp"
#include "query_optimizer/PhysicalGenerator.hpp"
#include "utility/Macros.hpp"
#include "parser/SqlParserWrapper.hpp"
#include "query_optimizer/tests/TestDatabaseLoader.hpp"


namespace quickstep {
namespace optimizer {
//using namespace quickstep;
//using namespace quickstep::optimizer;

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

const char* hustle_optimize() {
  std::cout << "1 \n";
  SqlParserWrapper sql_parser_;
  Optimizer optimizer_;
  std::string* query = new std::string("select t from t;");

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
  const char * pplan =
      hustle_getPhysicalPlan(parse_statement,
                             test_database_loader_.catalog_database(),
                             &optimizer_context);
  std::cout << "5 \n";
  std::cout << pplan << std::endl;

  return pplan;
}

}  // namespace optimizer
}  // namespace quickstep

//
