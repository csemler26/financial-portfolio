#ifndef PARAMETER_MANAGER_H
#define PARAMETER_MANAGER_H

#include <string>
#include <fstream>
#include <iostream>

const std::string ENV_PATH = ".env";

class ParameterManager {
public:
  ParameterManager();
  ~ParameterManager();

  // Function to load environment variables from a .env file
  void load_env_file();

private:
  // Helper function to trim spaces and quotes
  std::string trim(const std::string& str);

};

#endif // PARAMETER_MANAGER_H