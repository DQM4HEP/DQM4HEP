/// \file BufferEventStreamer.cc
/*
 *
 * BufferEventStreamer.cc source template automatically generated by a class generator
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
#include <dqm4hep/Event.h>
#include <dqm4hep/EventStreamer.h>
#include <dqm4hep/StatusCodes.h>
#include <dqm4hep/BufferEvent.h>
#include <dqm4hep/PluginManager.h>
#include <dqm4hep/StreamingHelper.h>

namespace dqm4hep {

  namespace core {

    /**
     * @brief BufferEventStreamer class
     */
    class BufferEventStreamer : public EventStreamerPlugin {
    public:
      BufferEventStreamer() = default;
      ~BufferEventStreamer() override = default;

      /** Factory method to create the corresponding event to this streamer.
       *  The event is expected to contains an allocated wrapped event
       */
      EventPtr createEvent() const override;

      /** Serialize the event and store it into a data stream.
       */
      StatusCode write(EventPtr event, xdrstream::IODevice *device) override;

      /** De-serialize the event.
       */
      StatusCode read(EventPtr event, xdrstream::IODevice *device) override;
    };
    
    //-------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------

    EventPtr BufferEventStreamer::createEvent() const {
      return Event::create<BufferEvent>();
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode BufferEventStreamer::write(EventPtr event, xdrstream::IODevice *device) {
      const BufferEvent *bufferEvent = event->getEvent<BufferEvent>();

      if (nullptr == bufferEvent) {
        return STATUS_CODE_INVALID_PARAMETER;
      }
      
      if (!XDR_TESTBIT( device->writeArray(bufferEvent->buffer(), bufferEvent->bufferSize()), xdrstream::XDR_SUCCESS )) {
        return STATUS_CODE_FAILURE;
      }

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode BufferEventStreamer::read(EventPtr event, xdrstream::IODevice *device) {
      BufferEvent *bufferEvent = event->getEvent<BufferEvent>();
      
      char *buffer = nullptr;
      std::size_t size = 0;
      if (!XDR_TESTBIT( device->readDynamicArray(buffer, size), xdrstream::XDR_SUCCESS )) {
        return STATUS_CODE_FAILURE;
      }
      bufferEvent->moveBuffer(buffer, size);
      
      return STATUS_CODE_SUCCESS;
    }
    
    //-------------------------------------------------------------------------------------------------
    
    DQM_PLUGIN_DECL(BufferEventStreamer, "BufferEventStreamer");
  }
}
