/// \file MonitorElement.h
/*
 *
 * MonitorElement.h header template automatically generated by a class generator
 * Creation date : jeu. sept. 4 2014
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
 * @author Ete Remi
 * @copyright CNRS , IPNL
 */

#ifndef DQM4HEP_MONITORELEMENT_H
#define DQM4HEP_MONITORELEMENT_H

// -- dqm4hep headers
#include <dqm4hep/Internal.h>
#include <dqm4hep/PtrHandler.h>
#include <dqm4hep/StatusCodes.h>
#include <dqm4hep/json.h>

// -- root headers
#include <Rtypes.h>
#include <TGraph.h>
#include <TObject.h>
#include <TText.h>
#include <TBrowser.h>
#include <TPad.h>

namespace xdrstream {
  class IODevice;
}

namespace dqm4hep {

  namespace core {

    class MonitorElementManager;

    /**
     *  @brief  MonitorElement class.
     *
     *  @author Remi Ete, DESY
     */
    class MonitorElement {
      friend class MonitorElementManager;

    public:
      /** 
       *  @brief  Make a shared pointer of MonitorElement
       */
      static MonitorElementPtr make_shared();

      /** 
       *  @brief  Make a shared pointer of MonitorElement
       *
       *  @param  pMonitorObject a root object as main monitor object
       */
      static MonitorElementPtr make_shared(TObject *pMonitorObject);

      /** 
       *  @brief  Make a shared pointer of MonitorElement
       *
       *  @param  pMonitorObject a root object as main monitor object
       *  @param  pReferenceObject a root object as reference object
       */
      static MonitorElementPtr make_shared(TObject *pMonitorObject, TObject *pReferenceObject);

      /** 
       *  @brief  Make a shared pointer of MonitorElement
       *
       *  @param  monitorObject a root object pointer as main monitor object
       */
      static MonitorElementPtr make_shared(const PtrHandler<TObject> &monitorObject);

      /** 
       *  @brief  Make a shared pointer of MonitorElement
       *
       *  @param  monitorObject a root object pointer as main monitor object
       *  @param  referenceObject a root object pointer as reference object
       */
      static MonitorElementPtr make_shared(const PtrHandler<TObject> &monitorObject,
                                           const PtrHandler<TObject> &referenceObject);
      
      /**
       *  @brief  Default destructor
       */
      virtual ~MonitorElement() = default;

      /** 
       *  @brief  Get the monitor element type (class name)
       */
      std::string type() const;

      /** 
       *  @brief  Get the object name
       */
      std::string name() const;
      
      /** 
       *  @brief  Get the object title
       */
      std::string title() const;
      
      /**
       *  @brief  Set the object title.
       *
       *  Throw if the object does not inherit the TNamed class
       * 
       *  @param  title the object title
       */
      void setTitle(const std::string &title);

      /** 
       *  @brief  Get the object path (in directory structure)
       */
      std::string path() const;

      /** 
       *  @brief  Whether the monitor element has a valid object ptr
       */
      bool hasObject() const;

      /** 
       *  @brief  Whether the monitor element has a valid reference ptr
       */
      bool hasReference() const;

      /**
       *  @brief  Get the monitor object
       */
      TObject *object();

      /** Get the monitor object
       */
      const TObject *object() const;

      /** 
       *  @brief  Get the reference object
       */
      TObject *reference();

      /** 
       *  @brief  Get the reference object
       */
      const TObject *reference() const;

      /** 
       *  @brief  Get a casted version of the monitor object
       */
      template <typename T>
      T *objectTo();

      /** 
       *  @brief  Get a casted version of the reference object
       */
      template <typename T>
      T *referenceTo();

      /** 
       *  @brief  Set the monitor object
       *
       *  @param  pMonitorObject a root object as main monitor object
       */
      void setMonitorObject(TObject *pMonitorObject);

      /** 
       *  @brief  Set the wrapped object (ptr handle)
       *
       *  @param  monitorObject a root object pointer as main monitor object
       */
      void setMonitorObject(const PtrHandler<TObject> &monitorObject);

      /** 
       *  @brief  Set the wrapped reference object
       *
       *  @param  pReferenceObject a root object as reference object
       */
      void setReferenceObject(TObject *pReferenceObject);

      /** 
       *  @brief  Set the wrapped reference object (ptr handle)
       *
       *  @param  referenceObject a root object pointer as reference object
       */
      void setReferenceObject(const PtrHandler<TObject> &referenceObject);

      /** 
       *  @brief  Set the wrapped object and reference object
       *
       *  @param  pMonitorObject a root object as main monitor object
       *  @param  pReferenceObject a root object as reference object
       */
      void set(TObject *pMonitorObject, TObject *pReferenceObject);

      /** 
       *  @brief  Set the wrapped object and reference object (ptr handle)
       *
       *  @param  monitorObject a root object pointer as main monitor object
       *  @param  referenceObject a root object pointer as reference object
       */
      void set(const PtrHandler<TObject> &monitorObject, const PtrHandler<TObject> &referenceObject);
      
      /**
       *  @brief  Reset the monitor element
       *
       *  @param  resetQtests whether to also reset the quality tests 
       */
      virtual void reset(bool resetQtests = true);
      
      /**
       *  @brief  Convert the monitor element to json
       *  
       *  @param  object the json object to receive
       */
      virtual void toJson(json &object) const;
      
#if ROOT_VERSION_CODE >= ROOT_VERSION(6, 14, 0)
      /**
       *  @brief  Parse the json object and set monitor element properties
       *  
       *  @param  object the json object to parse
       */
      virtual void fromJson(const json &value);
#endif
      /**
       *  @brief  Write monitor element to device
       *  
       *  @param  device the device to write to
       */
      virtual StatusCode toDevice(xdrstream::IODevice *device) const;
      
      /**
       *  @brief  Read the monitor element from device
       * 
       *  @param  device the device to read from
       */
      virtual StatusCode fromDevice(xdrstream::IODevice *device);

    protected:
      /** 
       *  @brief  Constructor
       */
      MonitorElement();

      /** 
       *  @brief  Constructor with ROOT object
       *
       *  @param  pMonitorObject a root object as main monitor object
       */
      MonitorElement(TObject *pMonitorObject);

      /** 
       *  @brief  Constructor with ROOT object and reference
       *
       *  @param  pMonitorObject a root object as main monitor object
       *  @param  pReferenceObject a root object as reference object
       */
      MonitorElement(TObject *pMonitorObject, TObject *pReferenceObject);

      /** 
       *  @brief  Constructor with ROOT object ptr
       *
       *  @param  monitorObject a root object pointer as main monitor object
       */
      MonitorElement(const PtrHandler<TObject> &monitorObject);

      /** 
       *  @brief  Constructor with ROOT object and reference ptr
       *
       *  @param  monitorObject a root object pointer as main monitor object
       *  @param  referenceObject a root object pointer as reference object
       */
      MonitorElement(const PtrHandler<TObject> &monitorObject, const PtrHandler<TObject> &referenceObject);
      
      /** 
       *  @brief  Set the monitor element object name
       *
       *  @param  name the monitor element name
       */
      void setName(const std::string &name);

      /** 
       *  @brief  Set the monitor element object path
       *
       *  @param  path the monitor element path
       */
      void setPath(const std::string &path);

      /** 
       *  @brief  Add a quality test
       *
       *  @param  qualityTest a quality test pointer
       */
      StatusCode addQualityTest(QTestPtr qualityTest);

      /** 
       *  @brief  Remove a quality test
       *
       *  @param  name the quality test name
       */
      StatusCode removeQualityTest(const std::string &name);

      /** 
       *  @brief  Run all quality tests
       *
       *  @param  reports the list of quality test reports to receive
       */
      virtual StatusCode runQualityTests(QReportMap &reports);

      /** 
       *  @brief  Run a specific quality test
       *
       *  @param  name the quality test name to run
       *  @param  report the quality test report to receive
       */
      virtual StatusCode runQualityTest(const std::string &name, QReport &report);

    private:
      /// The monitor element path
      std::string m_path = {""};
      /// The monitored object
      PtrHandler<TObject> m_monitorObject = {};
      /// The reference object
      PtrHandler<TObject> m_referenceObject = {};
      /// The list of assigned quality tests
      QTestMap m_qualityTests = {};
    };

    //-------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------

    template <typename T>
    inline T *MonitorElement::objectTo() {
      return dynamic_cast<T*>(object());
    }

    //-------------------------------------------------------------------------------------------------

    template <typename T>
    inline T *MonitorElement::referenceTo() {
      return dynamic_cast<T*>(reference());
    }

    //-------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------

    /** TScalarObject class.
     *  Extension of a TText for scalar values like int,
     *  float, double or string.
     */
    template <typename T>
    class TScalarObject : public TText {
    public:
      /** Default constructor
       */
      TScalarObject();
      TScalarObject& operator=(const TScalarObject&) = delete;
      TScalarObject(const TScalarObject&) = delete;

      /** Constructor with scalar value
       */
      TScalarObject(const T &scalar);

      /** Destructor
       */
      ~TScalarObject() override;

      /** Clear the scalar object
       */
      void Clear(Option_t *option = "") override;

      /** Draw the scalar object
       */
      void Draw(Option_t *option = "") override;

      /** The scalar value
       */
      void Set(const T &value);

      /** Get the scalar value
       */
      const T &Get() const;

      /** Convert the scalar value to std::string
       */
      std::string ToString() const;
      
      /**
       *  @brief  Whether the scalar is equal to an other one.
       *          Compare only the value itself
       *          
       *  @param  other the other scalar object
       */
      Bool_t IsEqual(const TObject *other) const override;
      
      /**
       *  @brief  Browse the TScalarObject
       * 
       *  @param  b the ROOT browser
       */
      void Browse(TBrowser *b) override;

    private:
      /** Initialize the scalar object (called only in C'tor)
       */
      void Init();

    private:
      ///< The scalar value
      T           fScalar = {};   

      ClassDefOverride(TScalarObject, 1);
    };

    typedef TScalarObject<int> TScalarInt;
    typedef TScalarObject<float> TScalarReal;
    typedef TScalarObject<float> TScalarFloat;
    typedef TScalarObject<double> TScalarDouble;
    typedef TScalarObject<short> TScalarShort;
    typedef TScalarObject<long> TScalarLong;
    typedef TScalarObject<Long64_t> TScalarLong64_t;
    typedef TScalarObject<std::string> TScalarString;

    //-------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------

    /** TDynamicGraph class
     *
     *  A TGraph with a dynamic x range axis
     */
    class TDynamicGraph : public TGraph {
    public:
      enum { kDynamicRange = BIT(14), kShrinkToRange = BIT(15) };

      /** Constructor
       */
      TDynamicGraph();
      TDynamicGraph& operator=(const TDynamicGraph&) = delete;
      TDynamicGraph(const TDynamicGraph&) = delete;

      /** Destructor
       */
      ~TDynamicGraph() override;

      /** Set the range length.
       *  If kDynamicRange and kShrinkToRange bit are set
       *  then all points that do not fit the x range are removed
       */
      void SetRangeLength(Double_t rangeLength);

      /** Add a point at end of array.
       *  Remove points that do not fit the dynamic range
       *  if kDynamicRange and kShrinkToRange bit are set
       */
      void AddPoint(Double_t x, Double_t y);

      // from ROOT base class
      void Draw(Option_t *option = "") override;

    private:
      /**
       */
      void ShrinkToRange();

    private:
      Double_t m_rangeLength = {0.};

      ClassDefOverride(TDynamicGraph, 1);
    };

    //-------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------

    template <typename T>
    inline TScalarObject<T>::TScalarObject() : 
      TText(0.5, 0.5, "") {
      Init();
      SetNDC(true);
      SetTextAlign(22);
    }

    //-------------------------------------------------------------------------------------------------

    template <typename T>
    inline TScalarObject<T>::TScalarObject(const T &scalar) : 
      TText(0.5, 0.5, ""),
      fScalar(scalar) {
      SetNDC(true);
      SetTextAlign(22);
    }

    //-------------------------------------------------------------------------------------------------

    template <typename T>
    inline TScalarObject<T>::~TScalarObject() {
    }

    //-------------------------------------------------------------------------------------------------

    template <typename T>
    inline void TScalarObject<T>::Clear(Option_t *option) {
      TText::Clear(option);
      fScalar = 0;
    }

    // //-------------------------------------------------------------------------------------------------
    // 
    template <typename T>
    inline void TScalarObject<T>::Draw(Option_t *option) {
      if(gPad) gPad->Clear();
      SetTitle(ToString().c_str());
      AppendPad(option);
    }

    //-------------------------------------------------------------------------------------------------

    template <typename T>
    inline void TScalarObject<T>::Set(const T &value) {
      Clear();
      fScalar = value;
      SetTitle(ToString().c_str());
    }

    //-------------------------------------------------------------------------------------------------

    template <typename T>
    inline const T &TScalarObject<T>::Get() const {
      return fScalar;
    }

    //-------------------------------------------------------------------------------------------------

    template <typename T>
    inline std::string TScalarObject<T>::ToString() const {
      std::stringstream ss;
      ss << fScalar;
      return ss.str();
    }

    //-------------------------------------------------------------------------------------------------

    template <typename T>
    inline void TScalarObject<T>::Init() {
      fScalar = 0;
    }
    
    //-------------------------------------------------------------------------------------------------
    
    template <typename T>
    inline Bool_t TScalarObject<T>::IsEqual(const TObject *other) const {
      const auto *otherScalar = (TScalarObject<T>*)other;
      if(nullptr == otherScalar)
        return false;
      const T &value = otherScalar->Get();
      return (value == fScalar);
    }
    
    // //-------------------------------------------------------------------------------------------------
    // 
    template <typename T>
    inline void TScalarObject<T>::Browse(TBrowser *b) {
      Draw(b->GetDrawOption() ? b->GetDrawOption() : "");
      gPad->Update();
    }
 
    //-------------------------------------------------------------------------------------------------
    // template specialization for std::string
    //-------------------------------------------------------------------------------------------------

    template <>
    inline void TScalarObject<std::string>::Clear(Option_t *option) {
      TText::Clear(option);
      fScalar.clear();
    }

    //-------------------------------------------------------------------------------------------------

    template <>
    inline std::string TScalarObject<std::string>::ToString() const {
      return fScalar;
    }

    //-------------------------------------------------------------------------------------------------

    template <>
    inline void TScalarObject<std::string>::Init() {
      fScalar = "";
    }
    
  }
  
}

#endif //  DQM4HEP_MONITORELEMENT_H