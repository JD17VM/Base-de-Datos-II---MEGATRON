// Parser.cpp
#include "Parser.h"
#include <algorithm> // Para std::remove_if

// Función auxiliar para quitar el ; final
std::string removeTrailingSemicolon(const std::string &query_string)
{
  if (!query_string.empty() && query_string.back() == ';')
  {
    return query_string.substr(0, query_string.size() - 1);
  }
  return query_string;
}

// Tokenize the query string by spaces
std::vector<std::string> Parser::tokenize(const std::string &query_string)
{
  std::string cleaned_query = removeTrailingSemicolon(query_string); // Llama a la función auxiliar
  std::vector<std::string> tokens;
  std::stringstream ss(cleaned_query);
  std::string token;
  while (ss >> token)
  {
    tokens.push_back(token);
  }
  return tokens;
}

// Check if the command is valid (only supports SELECT for now)
bool Parser::isValidCommand(const std::string &command)
{
  return command == "SELECT";
}

// Parse the query string and return a Query struct
Parser::Query Parser::parse(const std::string &query_string)
{
  std::vector<std::string> tokens = tokenize(query_string);
  Query query;

  if (tokens.size() < 4)
  {
    std::cerr << "Error: Query too short!" << std::endl;
    return query;
  }

  // Check if it's a valid command
  query.command = tokens[0];
  if (!isValidCommand(query.command))
  {
    std::cerr << "Error: Unsupported command!" << std::endl;
    return query;
  }

  // Parse columns
  size_t from_index = 1;
  while (from_index < tokens.size() && tokens[from_index] != "FROM")
  {
    query.columns.push_back(tokens[from_index]);
    from_index++;
  }

  if (from_index >= tokens.size() || tokens[from_index] != "FROM")
  {
    std::cerr << "Error: Missing FROM clause!" << std::endl;
    return query;
  }

  // Parse table name
  from_index++;
  if (from_index >= tokens.size())
  {
    std::cerr << "Error: Missing table name!" << std::endl;
    return query;
  }
  query.table = tokens[from_index];

  // Parse WHERE clause (optional)
  size_t where_index = from_index + 1;
  if (where_index < tokens.size() && tokens[where_index] == "WHERE")
  {
    where_index++;
    if (where_index + 2 >= tokens.size())
    {
      std::cerr << "Error: Invalid WHERE clause!" << std::endl;
      return query;
    }
    query.condition_column = tokens[where_index];
    query.condition_value = tokens[where_index + 2];
  }

  return query;
}
