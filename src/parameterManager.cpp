#include "parameterManager.h"

ParameterManager::ParameterManager() 
{
}

ParameterManager::~ParameterManager() 
{
}

std::string ParameterManager::trim(const std::string& str) 
{
  size_t first = str.find_first_not_of(' ');
  size_t last = str.find_last_not_of(' ');
  return str.substr(first, (last - first + 1));
}

void ParameterManager::load_env_file() 
{
  std::ifstream file(ENV_PATH);
  if (!file.is_open()) 
  {
    std::cerr << "Could not open .env file" << std::endl;
    return;
  }

  std::string line;
  while (std::getline(file, line)) 
  {
    // Ignore empty lines and comments
    if (line.empty() || line[0] == '#') continue;

    size_t delimiter_pos = line.find('=');
    if (delimiter_pos == std::string::npos) continue;

    std::string key = trim(line.substr(0, delimiter_pos));
    std::string value = trim(line.substr(delimiter_pos + 1));

    // Remove any quotes around the value
    if (value.front() == '"' && value.back() == '"') 
    {
      value = value.substr(1, value.size() - 2);
    }

    // Set the environment variable (on POSIX systems)
    setenv(key.c_str(), value.c_str(), 1);
  }
  file.close();
}
