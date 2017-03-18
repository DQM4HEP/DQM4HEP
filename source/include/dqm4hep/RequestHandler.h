/// \file RequestHandler.h
/*
 *
 * RequestHandler.h header template automatically generated by a class generator
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


#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

// -- std headers
#include <string>

// -- json headers
#include "json/json.h"

// -- dim headers
#include "dis.hxx"

// -- dqm4hep headers
#include "dqm4hep/DQMNet.h"

namespace dqm4hep {

  namespace net {

    class Server;

    class RequestHandler
    {
      friend class Server;
    public:
      typedef Signal<const std::string &, std::string &> RequestSignal;

      /**
       * Get the request name
       */
      const std::string &name() const;

      /**
       * Get the server in which the request handler is declared
       */
      Server *server() const;

    private:
      /**
       * Constructor
       *
       * @param pServer the server managing the request handler
       * @param name the request handler name
       */
      template <typename Controller>
      RequestHandler(Server *pServer, const std::string &name, Controller *pController, void (Controller::*function)(const std::string &request, std::string &response));

      /**
       * Destructor
       */
      ~RequestHandler();

      /**
       * Create the actual request handler connection
       */
      void startHandlingRequest();

      /**
       * Remove the actual request handler connection
       */
      void stopHandlingRequest();

      /**
       * Whether the request handler is connected
       */
      bool isHandlingRequest() const;

      /**
       * [onRequest description]
       * @return [description]
       */
      RequestSignal &onRequest();

    private:
     /** Rpc class.
     *
     *  The concrete dim rpc implementation
     */
     class Rpc : public DimRpc
     {
     public:
       /**
        * Contructor
        */
       Rpc(RequestHandler *pHandler);

       /**
        * The dim rpc handler
        */
       void rpcHandler();

     private:
       RequestHandler        *m_pHandler;     ///< The request handler owner instance
     };

     friend class Rpc;

    private:
      /**
       * [handleRequest description]
       * @param request  [description]
       * @param response [description]
       */
      void handleRequest(const std::string &request, std::string &response);

    private:
      std::string                     m_name;             ///< The request handler name
      Server                         *m_pServer;          ///< The server in which the request handler is declared
      RequestSignal                   m_requestSignal;
      Rpc                            *m_pRpc;
    };

    //-------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------

    template <typename Controller>
    inline RequestHandler::RequestHandler(Server *pServer, const std::string &name, Controller *pController, void (Controller::*function)(const std::string &request, std::string &response)) :
      m_name(name),
      m_pServer(pServer),
      m_pRpc(nullptr)
    {
      m_requestSignal.connect(pController, function);
    }

    //-------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------

    class CommandHandler
    {
      friend class Server;
    public:
      typedef Signal<const std::string &> CommandSignal;

      /**
       * Get the request name
       */
      const std::string &name() const;

      /**
       * Get the server in which the request handler is declared
       */
      Server *server() const;

    private:
      /**
       * Constructor
       *
       * @param pServer the server managing the request handler
       * @param name the request handler name
       */
      template <typename Controller>
      CommandHandler(Server *pServer, const std::string &name, Controller *pController, void (Controller::*function)(const std::string &command));

      /**
       * Constructor
       *
       * @param pServer the server managing the request handler
       * @param name the request handler name
       */
      CommandHandler(Server *pServer, const std::string &name);

      /**
       * Destructor
       */
      ~CommandHandler();

      /**
       * Create the actual request handler connection
       */
      void startHandlingCommands();

      /**
       * Remove the actual request handler connection
       */
      void stopHandlingCommands();

      /**
       * Whether the request handler is connected
       */
      bool isHandlingCommands() const;

      /**
       * [onRequest description]
       * @return [description]
       */
      CommandSignal &onCommand();

    private:
     /** Command class.
     *
     *  The concrete dim command implementation
     */
     class Command : public DimCommand
     {
     public:
       /**
        * Contructor
        */
       Command(CommandHandler *pHandler);

       /**
        * The dim command handler
        */
       void commandHandler();

     private:
       CommandHandler        *m_pHandler;     ///< The request handler owner instance
     };

     friend class Command;

    private:
      /**
       * [handleCommand description]
       * @param request  [description]
       * @param response [description]
       */
      void handleCommand(const std::string &command);

    private:
      std::string                     m_name;             ///< The command handler name
      Server                         *m_pServer;          ///< The server in which the command handler is declared
      CommandSignal                   m_commandSignal;
      Command                         *m_pCommand;
    };

    //-------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------

    template <typename Controller>
    inline CommandHandler::CommandHandler(Server *pServer, const std::string &name, Controller *pController, void (Controller::*function)(const std::string &command)) :
      m_name(name),
      m_pServer(pServer),
      m_pCommand(nullptr)
    {
      m_commandSignal.connect(pController, function);
    }

  }

}

#endif  //  REQUESTHANDLER_H
