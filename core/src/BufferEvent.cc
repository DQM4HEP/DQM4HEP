/// \file BufferEvent.cc
/*
 *
 * BufferEvent.cc source template automatically generated by a class generator
 * Creation date : lun. mars 7 2016
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
#include "dqm4hep/BufferEvent.h"
#include "dqm4hep/PluginManager.h"
#include "dqm4hep/StreamingHelper.h"

namespace dqm4hep {

  namespace core {
    
    BufferEvent::~BufferEvent() {
      clear();
    }
    
    //-------------------------------------------------------------------------------------------------

    EventPtr BufferEvent::make_shared() {
      auto ptr = std::shared_ptr<Event>(new EventBase<BufferEvent>(new BufferEvent()));
      ptr->setStreamerName("BufferEventStreamer");
      return ptr;
    }

    //-------------------------------------------------------------------------------------------------

    void BufferEvent::copyBuffer(const char *const b, std::size_t len) {
      if(nullptr == b) {
        return;
      }
      clear();
      m_buffer.m_size = len;
      m_buffer.m_buffer = new char[len];
      m_buffer.m_isOwner = true;
      memcpy(m_buffer.m_buffer, b, len);
    }
    
    //-------------------------------------------------------------------------------------------------

    void BufferEvent::moveBuffer(char *b, std::size_t len) {
      if(nullptr == b) {
        return;
      }
      clear();
      m_buffer.m_size = len;
      m_buffer.m_buffer = b;
      m_buffer.m_isOwner = true;
    }
    
    //-------------------------------------------------------------------------------------------------

    void BufferEvent::handleBuffer(char *b, std::size_t len) {
      if(nullptr == b) {
        return;
      }
      clear();
      m_buffer.m_size = len;
      m_buffer.m_buffer = b;
      m_buffer.m_isOwner = false;
    }
    
    //-------------------------------------------------------------------------------------------------

    const char* BufferEvent::buffer() const {
      return m_buffer.m_buffer;
    }
    
    //-------------------------------------------------------------------------------------------------

    std::size_t BufferEvent::bufferSize() const {
      return m_buffer.m_size;
    }
    
    //-------------------------------------------------------------------------------------------------
    
    void BufferEvent::clear() {
      if( nullptr != m_buffer.m_buffer && m_buffer.m_isOwner ) {
        delete [] m_buffer.m_buffer;
      }
      m_buffer.m_buffer = nullptr;
      m_buffer.m_size = 0;
    }

  }
  
}