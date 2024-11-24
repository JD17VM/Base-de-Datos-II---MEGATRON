// Parser.h
#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <map>

class Parser
{
public:
  struct Query
  {
    std::string command;
    std::vector<std::string> columns;
    std::string table;

    // Miembros para la cláusula WHERE
    std::string condition_column;
    std::string condition_value;

    // Miembros específicos para UPDATE
    std::string update_column;
    std::string new_value;

    // Miembros específicos para JOIN
    std::string join_type;
    std::string table1;
    std::string table2;
    std::string column1;
    std::string column2;
  };

  Query parse(const std::string &query_string);

private:
  std::vector<std::string> tokenize(const std::string &query_string);
  bool isValidCommand(const std::string &command);
  std::vector<std::string> split(const std::string &str, char delimiter); // Declaración de split
};

#endif // PARSER_H
