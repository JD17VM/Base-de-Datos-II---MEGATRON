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

std::vector<std::string> split(const std::string &str, char delimiter)
{
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream tokenStream(str);
  while (std::getline(tokenStream, token, delimiter))
  {
    tokens.push_back(token);
  }
  return tokens;
}

bool Parser::isValidCommand(const std::string &command)
{
  return command == "SELECT" || command == "UPDATE" || command == "JOIN";
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

  // Parse SELECT command
  if (query.command == "SELECT")
  {
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
  }

  // Parse UPDATE command
  else if (query.command == "UPDATE")
  {
    // Parse table name
    if (tokens.size() < 4)
    {
      std::cerr << "Error: Invalid UPDATE syntax!" << std::endl;
      return query;
    }
    query.table = tokens[1];

    // Ensure that "SET" is in the correct position
    size_t set_index = 2;
    if (tokens[set_index] != "SET")
    {
      std::cerr << "Error: Missing SET clause in UPDATE!" << std::endl;
      return query;
    }

    // Parse column to update and new value
    if (set_index + 3 >= tokens.size() || tokens[set_index + 2] != "=")
    {
      std::cerr << "Error: Invalid syntax in SET clause!" << std::endl;
      return query;
    }
    query.update_column = tokens[set_index + 1];
    query.new_value = tokens[set_index + 3];

    // Parse WHERE clause (required for UPDATE)
    size_t where_index = set_index + 4;
    if (where_index < tokens.size() && tokens[where_index] == "WHERE")
    {
      if (where_index + 3 >= tokens.size())
      {
        std::cerr << "Error: Invalid WHERE clause in UPDATE!" << std::endl;
        return query;
      }
      query.condition_column = tokens[where_index + 1];
      query.condition_value = tokens[where_index + 3];
    }
    else
    {
      std::cerr << "Error: UPDATE requires a WHERE clause!" << std::endl;
      return query;
    }
  }

  else if (query.command == "JOIN")
  {
    // Parse JOIN type
    if (tokens.size() < 5)
    {
      std::cerr << "Error: Invalid JOIN syntax!" << std::endl;
      return query;
    }

    query.join_type = tokens[1];

    // Parse table1 and column1
    std::string table1_column1 = tokens[2];
    size_t dot_pos = table1_column1.find('.');
    if (dot_pos == std::string::npos)
    {
      std::cerr << "Error: Invalid table.column syntax for table1!" << std::endl;
      return query;
    }
    query.table1 = table1_column1.substr(0, dot_pos);
    query.column1 = table1_column1.substr(dot_pos + 1);

    // Parse table2 and column2
    std::string table2_column2 = tokens[3];
    dot_pos = table2_column2.find('.');
    if (dot_pos == std::string::npos)
    {
      std::cerr << "Error: Invalid table.column syntax for table2!" << std::endl;
      return query;
    }
    query.table2 = table2_column2.substr(0, dot_pos);
    query.column2 = table2_column2.substr(dot_pos + 1);

    // Parse SELECT clause
    if (tokens[4] != "SELECT")
    {
      std::cerr << "Error: Missing SELECT clause in JOIN!" << std::endl;
      return query;
    }

    for (size_t i = 5; i < tokens.size(); ++i)
    {
      query.columns.push_back(tokens[i]);
    }
  }

  return query;
}
