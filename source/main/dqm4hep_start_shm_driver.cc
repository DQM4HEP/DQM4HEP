/// \file dqm4hep_start_shm_driver.cc
/*
 *
 * dqm4hep_start_shm_driver.cc main source file template automatically generated
 * Creation date : mer. nov. 5 2014
 *
 * This file is part of DQM4HEP libraries.
 *
 * DQM4HEP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * based upon these libraries are permitted. Any copy of these libraries
 * must include this copyright notice.
 *
 * DQM4HEP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with DQM4HEP.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @author Remi Ete
 * @copyright CNRS , IPNL
 */

// -- dqm4hep headers
#include "dqm4hep/DQM4HEP.h"
#include "dqm4hep/Logging.h"
#include "dqm4hep/PluginManager.h"
#include "dqm4hep/evb/DQMShmProxyApplication.h"

// -- tclap headers
#include "tclap/CmdLine.h"
#include "tclap/Arg.h"

// -- std headers
#include <iostream>
#include <signal.h>

// -- root headers
#include "TObject.h"

using namespace std;
using namespace dqm4hep::core;

ShmProxyApplication *pApplication = NULL;

// simple function to exit the program
void exit_application(int returnCode)
{
  LOG4CXX_WARN( dqmMainLogger , "Exiting analysis module application !" );

  if(NULL != pApplication)
    pApplication->exit( returnCode );
  else
    exit(0);
}

//-------------------------------------------------------------------------------------------------

// key interrupt signal handling
void int_key_signal_handler(int signal)
{
  if(NULL == pApplication)
    exit(0);

  LOG4CXX_WARN( dqmMainLogger , "*** SIGN INT ***" );
  LOG4CXX_WARN( dqmMainLogger , "Caught signal " << signal << ". Stopping the application." );
  exit_application( static_cast<int>(STATUS_CODE_SUCCESS) );
}

//-------------------------------------------------------------------------------------------------

// segmentation violation signal handling
void seg_viol_signal_handling(int signal)
{
  if(NULL == pApplication)
    exit(1);

  LOG4CXX_WARN( dqmMainLogger , "*** SIGN VIOL ***" );
  LOG4CXX_WARN( dqmMainLogger , "Caught signal " << signal << ". Stopping the application." );
  exit_application( static_cast<int>(STATUS_CODE_INVALID_PTR) );
}

//-------------------------------------------------------------------------------------------------

void parseParameterArg(const std::vector<std::string> &args, ParameterMap &parametersMap)
{
  for(auto iter = args.begin(), endIter = args.end() ; endIter != iter ; ++iter)
  {
    std::string arg(*iter);
    size_t pos = arg.find_first_of("=");

    if(pos == std::string::npos)
    {
      LOG4CXX_WARN( dqmMainLogger, "Parameter '" << arg << "' : wrong parsing !" );
      continue;
    }

    std::string key = arg.substr(0, pos);
    std::string value = arg.substr(pos+1);

    parametersMap[ key ] = value;

    LOG4CXX_DEBUG( dqmMainLogger, "Read key '" << key << "' , value '" << value << "'" );
  }
}

//-------------------------------------------------------------------------------------------------

int main(int argc, char* argv[])
{
  DQM4HEP::screenSplash();
  TObject::SetObjectStat(false);

  std::string cmdLineFooter = "Please report bug to <rete@ipnl.in2p3.fr>";
  TCLAP::CmdLine *pCommandLine = new TCLAP::CmdLine(cmdLineFooter, ' ', DQM4HEP_VERSION_STR);
  std::string log4cxx_file = std::string(DQMCore_DIR) + "/conf/defaultLoggerConfig.xml";

  TCLAP::ValueArg<std::string> steeringFileNameArg(
      "f"
      , "steering-file"
      , "The xml steering file for the module application"
      , true
      , ""
      , "string");
  pCommandLine->add(steeringFileNameArg);

  TCLAP::ValueArg<std::string> applicationNameArg(
      "n"
      , "application-name"
      , "The shm proxy name to declare on the network"
      , false
      , "DQMShmProxy-DEFAULT"
      , "string");
  pCommandLine->add(applicationNameArg);

  TCLAP::MultiArg<std::string> parameterArg(
      "p"
      , "parameter"
      , "A parameter to replace in the application (see DQMXmlHelper)"
      , false
      , "");
  pCommandLine->add(parameterArg);

  TCLAP::ValueArg<std::string> loggerConfigArg(
      "l"
      , "logger-config"
      , "The xml logger file to configure log4cxx"
      , false
      , log4cxx_file
      , "string");
  pCommandLine->add(loggerConfigArg);

  std::vector<std::string> allowedLevels;
  allowedLevels.push_back("INFO");
  allowedLevels.push_back("WARN");
  allowedLevels.push_back("DEBUG");
  allowedLevels.push_back("TRACE");
  allowedLevels.push_back("ERROR");
  allowedLevels.push_back("FATAL");
  allowedLevels.push_back("OFF");
  allowedLevels.push_back("ALL");
  TCLAP::ValuesConstraint<std::string> allowedLevelsContraint( allowedLevels );

  TCLAP::ValueArg<std::string> verbosityArg(
      "v"
      , "verbosity"
      , "The verbosity level used for this application"
      , false
      , "INFO"
      , &allowedLevelsContraint);
  pCommandLine->add(verbosityArg);

  // parse command line
  std::cout << "dqm4hep_start_shm_driver: Parsing command line ..." << std::endl;
  pCommandLine->parse(argc, argv);

  log4cxx_file = loggerConfigArg.getValue();
  log4cxx::xml::DOMConfigurator::configure(log4cxx_file);

  if( verbosityArg.isSet() )
    dqmMainLogger->setLevel( log4cxx::Level::toLevel( verbosityArg.getValue() ) );

  ParameterMap parametersMap;
  parseParameterArg( parameterArg.getValue() , parametersMap );

  // install signal handlers
  LOG4CXX_INFO( dqmMainLogger , "Installing signal handlers ..." );
  signal(SIGINT,  int_key_signal_handler);

  LOG4CXX_INFO( dqmMainLogger , "Creating shm proxy application ..." );

  try
  {
    // load plugins if env var is set
    THROW_RESULT_IF(STATUS_CODE_SUCCESS, !=, PluginManager::instance()->loadLibraries());

    pApplication = new ShmProxyApplication();
  }
  catch(StatusCodeException &exception)
  {
    LOG4CXX_FATAL( dqmMainLogger , "StatusCodeException caught : " << exception.toString() );
    exit_application( exception.getStatusCode() );
  }

  LOG4CXX_INFO( dqmMainLogger , "Creating shm proxy application ... OK" );
  LOG4CXX_INFO( dqmMainLogger , "Shm proxy application read settings ..." );

  try
  {
    if(applicationNameArg.isSet())
      pApplication->setName(applicationNameArg.getValue());

    pApplication->setReplacementParameters( parametersMap );
    THROW_RESULT_IF(STATUS_CODE_SUCCESS, !=, pApplication->readSettings(steeringFileNameArg.getValue()));
  }
  catch(StatusCodeException &exception)
  {
    LOG4CXX_FATAL( dqmMainLogger , "StatusCodeException caught : " << exception.toString() );
    exit_application( exception.getStatusCode() );
  }

  LOG4CXX_INFO( dqmMainLogger , "Shm proxy application read settings ... OK" );
  LOG4CXX_INFO( dqmMainLogger , "Running shm proxy application ..." );

  try
  {
    THROW_RESULT_IF(STATUS_CODE_SUCCESS, !=, pApplication->run());
  }
  catch(StatusCodeException &exception)
  {
    LOG4CXX_FATAL( dqmMainLogger , "StatusCodeException caught : " << exception.toString() );
    exit_application( exception.getStatusCode() );
  }

  delete pCommandLine;
  exit_application( static_cast<int>(STATUS_CODE_SUCCESS) );
}
