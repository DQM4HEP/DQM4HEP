/// \file Archiver.h
/*
 *
 * Archiver.h header template automatically generated by a class generator
 * Creation date : mar. oct. 7 2014
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

#ifndef DQM4HEP_ARCHIVER_H
#define DQM4HEP_ARCHIVER_H

// -- dqm4hep headers
#include "dqm4hep/Internal.h"
#include "dqm4hep/StatusCodes.h"

class TFile;
class TDirectory;

namespace dqm4hep {

  namespace core {

    template <typename T>
    class Directory;
    template <typename T>
    class Storage;

    /** 
     *  @brief  Archiver class
     */
    class Archiver {
    public:
      Archiver() = default;
      Archiver(const Archiver &) = delete;
      Archiver& operator=(const Archiver &) = delete;

      /** 
       *  @brief  Constructor
       *          See open() for argument explanation
       *
       *  @param  archiveFileName the root file name
       *  @param  openingMode the ROOT file opening mode
       *  @param  overwrite whether to allow to overwrite previous archive
       */
      Archiver(const std::string &fname, const std::string &openingMode = "RECREATE", bool overwrite = false);

      /** 
       *  @brief  Destructor
       */
      ~Archiver();

      /** 
       *  @brief  Open a new archive.
       *          Close the current file if opened. Supported opening mode are the 
       *          TFile opening mode option (see TFile). If overwrite is set to false,
       *          an id is appended before the .root extension to ensure the file name
       *          is unique and no archive is overwritten
       *
       *  @param  fname the ROOT file name to open
       *  @param  openingMode the ROOT file opening mode
       *  @param  overwrite whether to allow for overwrite
       */
      StatusCode open(const std::string &fname, const std::string &openingMode = "RECREATE",
                      bool overwrite = true);

      /** 
       *  @brief  Close the current archive
       */
      StatusCode close();

      /** 
       *  @brief  Archive the monitor element storage in the ROOT file.
       *          The result can be written in a specific directory using the dirName argument.
       *          By default, the content is written directly in the top-level directory
       *
       *  @param  storage the storage to archive
       *  @param  dirName the directory in which to archive the storage (optional)
       */
      StatusCode archive(const Storage<MonitorElement> &storage, const std::string &dirName = "");
      
      /** 
       *  @brief  Archive the monitor element storage in the ROOT file.
       *          Also archive the references along with the monitor object in the same directory.
       *          The reference is written with the same name as the object plus a suffix (default "_ref").
       *          The result can be written in a specific directory using the dirName argument.
       *          By default, the content is written directly in the top-level directory.
       *
       *  @param  storage the storage to archive
       *  @param  dirName the directory in which to archive the storage (optional)
       *  @param  refSuffix the reference name suffix (optional)
       */
      StatusCode archiveWithReferences(const Storage<MonitorElement> &storage, const std::string &dirName = "", const std::string &refSuffix = "_ref");

      /** 
       *  @brief  Get the file name
       */
      const std::string &fileName() const;

      /** 
       *  @brief  Whether the archive is opened
       */
      bool isOpened() const;

      /** 
       *  @brief  Get the opening mode of this archive
       */
      const std::string &openingMode() const;

    private:
      /**
       *  @brief  Prepare the ROOT file for archiving
       *   
       *  @param  dirName the top-level root directory in which the elements will be archived
       *  @param  directory the top-level directory pointer to receive
       */
      StatusCode prepareForAchiving(const std::string &dirName, TDirectory *&directory);
      
      /** 
       *  @brief  Fill recursively the TDirectory with the Directory
       *
       *  @param  directory the monitor element storage directory
       *  @param  rootDirectory the corresponding ROOT directory
       *  @param  refSuffix the suffix to add for object references
       */
      static StatusCode recursiveWrite(MonitorElementDir directory, TDirectory *rootDirectory, const std::string &refSuffix = "");

      /** 
       *  @brief  Write the monitor elements contained in the Directory in the TDirectory
       *
       *  @param  directory the monitor element storage directory
       *  @param  rootDirectory the corresponding ROOT directory
       *  @param  refSuffix the suffix to add for object references
       */
      static StatusCode writeMonitorElements(MonitorElementDir directory, TDirectory *rootDirectory, const std::string &refSuffix = "");

    private:
      /// The archive file name
      std::string                    m_fileName = {""};
      /// The root file opening mode
      std::string                    m_openingMode = {"RECREATE"};
      ///< Whether the archive is opened
      bool                           m_isOpened = {false};
      ///< The actual archive implementation (root file)
      std::unique_ptr<TFile>         m_file = {nullptr};
    };
  }
}

#endif //  DQM4HEP_ARCHIVER_H
