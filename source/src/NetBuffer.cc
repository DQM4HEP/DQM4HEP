/// \file DQMNet.cc
/*
 *
 * DQMNet.cc source template automatically generated by a class generator
 * Creation date : dim. d�c. 4 2016
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
#include "dqm4hep/DQMNet.h"

namespace dqm4hep {

  namespace net {

    const char NullBuffer::buffer[] = "\0";
    const size_t NullBuffer::size = 1;

    //-------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------

    RawBuffer::RawBuffer() {
      this->adopt(NullBuffer::buffer, NullBuffer::size);
    }

    //-------------------------------------------------------------------------------------------------

    const char *RawBuffer::begin() const {
      return m_pBuffer;
    }

    //-------------------------------------------------------------------------------------------------

    const char *RawBuffer::end() const {
      return m_pBuffer + m_size;
    }

    //-------------------------------------------------------------------------------------------------

    size_t RawBuffer::size() const {
      return m_size;
    }

    //-------------------------------------------------------------------------------------------------

    void RawBuffer::adopt(const char *buffer, size_t size) {
      m_pBuffer = buffer;
      m_size = size;
    }

    //-------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------

    const RawBuffer &BufferModel::raw() const {
      return m_rawBuffer;
    }

    //-------------------------------------------------------------------------------------------------

    void BufferModel::handle(const char *buffer, size_t size) {
      m_rawBuffer.adopt(buffer, size);
    }

    //-------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------

    Buffer::Buffer() {
      this->adopt(NullBuffer::buffer, NullBuffer::size);
    }

    //-------------------------------------------------------------------------------------------------

    Buffer::Buffer(Buffer &&buffer) {
      m_model = std::move(buffer.m_model);
    }

    //-------------------------------------------------------------------------------------------------

    std::shared_ptr<BufferModel> Buffer::createModel() const {
      return std::make_shared<BufferModel>();
    }

    //-------------------------------------------------------------------------------------------------

    void Buffer::setModel(std::shared_ptr<BufferModel> model) {
      if (!model)
        return;
      m_model = model;
    }

    //-------------------------------------------------------------------------------------------------

    const char *Buffer::begin() const {
      return m_model->raw().begin();
    }

    //-------------------------------------------------------------------------------------------------

    const char *Buffer::end() const {
      return m_model->raw().end();
    }

    //-------------------------------------------------------------------------------------------------

    size_t Buffer::size() const {
      return m_model->raw().size();
    }

    //-------------------------------------------------------------------------------------------------

    void Buffer::adopt(const char *buffer, size_t size) {
      auto model = this->createModel();
      model->handle(buffer, size);
      this->setModel(model);
    }

    //-------------------------------------------------------------------------------------------------

    BufferModelPtr Buffer::model() const {
      return m_model;
    }
  }
}
