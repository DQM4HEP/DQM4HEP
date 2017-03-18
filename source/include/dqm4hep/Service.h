/// \file Service.h
/*
 *
 * Service.h header template automatically generated by a class generator
 * Creation date : sam. d�c. 3 2016
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


#ifndef SERVICE_H
#define SERVICE_H

// -- std headers
#include <string>
#include <typeinfo>

// -- dim headers
#include "dis.hxx"

// -- dqm4hep headers
#include "dqm4hep/DQMNet.h"

namespace dqm4hep {

  namespace net {

    class Server;

    class Service
    {
      friend class Server;
    public:
      /**
       * Get the service name
       */
      const std::string &name() const;

      /**
       * Get the server in which the service is declared
       */
      Server *server() const;

      /**
       *
       */
      template <typename T>
      void update(const T &value);

      /**
       *
       */
      template <typename T>
      void update(const T &value, int clientId);

      /**
       *
       */
      template <typename T>
      void update(const T &value, const std::vector<int> &clientIds);

    private:
      /**
       * Constructor with service name
       *
       * @param pServer the server that owns the service instance
       * @param name the service name
       */
      Service(Server *pServer, const std::string &name);

      /**
       * Destructor
       */
      virtual ~Service();

      /**
       * Create the actual service connection
       */
      void connectService();

      /**
       * Remove the actual service connection
       */
      void disconnectService();

      /**
       * Whether the service is connected
       */
      bool isServiceConnected() const;

    private:
      DimService           *m_pService;         ///< The service implementation
      std::string           m_name;             ///< The service name
      Server               *m_pServer;          ///< The server in which the service is declared
      std::string           m_content;
      char *                m_charContent;
    };

    //-------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------

    template <typename T>
    inline void Service::update(const T &value)
    {
      this->update(value, std::vector<int>());
    }

    //-------------------------------------------------------------------------------------------------

    template <typename T>
    inline void Service::update(const T &value, int clientId)
    {
      this->update(value, std::vector<int>(1, clientId));
    }

    //-------------------------------------------------------------------------------------------------

    template <typename T>
    inline void Service::update(const T &value, const std::vector<int> &clientIds)
    {
      if(!this->isServiceConnected())
        throw; // TODO implement exceptions

      if(!convert<T>::encode(m_content, value))
        throw; // TODO implement exceptions

      m_charContent = (char*)m_content.c_str();

      if(clientIds.empty())
      {
        m_pService->updateService((void*)m_charContent, m_content.size());
      }
      else
      {
        std::vector<int> clientIdList(clientIds);

        if(clientIdList.back() != 0)
          clientIdList.push_back(0);

        int *clientIdsArray = &clientIdList[0];
        m_pService->selectiveUpdateService((void*)m_charContent, m_content.size(), clientIdsArray);
      }

    }

  }

}

#endif  //  SERVICE_H
