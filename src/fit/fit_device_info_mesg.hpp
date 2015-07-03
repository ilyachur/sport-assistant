////////////////////////////////////////////////////////////////////////////////
// The following FIT Protocol software provided may be used with FIT protocol
// devices only and remains the copyrighted property of Dynastream Innovations Inc.
// The software is being provided on an "as-is" basis and as an accommodation,
// and therefore all warranties, representations, or guarantees of any kind
// (whether express, implied or statutory) including, without limitation,
// warranties of merchantability, non-infringement, or fitness for a particular
// purpose, are specifically disclaimed.
//
// Copyright 2015 Dynastream Innovations Inc.
////////////////////////////////////////////////////////////////////////////////
// ****WARNING****  This file is auto-generated!  Do NOT edit this file.
// Profile Version = 15.10Release
// Tag = development-akw-15.10.00-0-g92bb614
////////////////////////////////////////////////////////////////////////////////


#if !defined(FIT_DEVICE_INFO_MESG_HPP)
#define FIT_DEVICE_INFO_MESG_HPP

#include "fit_mesg.hpp"

namespace fit
{

class DeviceInfoMesg : public Mesg
{
   public:
      DeviceInfoMesg(void) : Mesg(Profile::MESG_DEVICE_INFO)
      {
      }

      DeviceInfoMesg(const Mesg &mesg) : Mesg(mesg)
      {
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns timestamp field
      // Units: s
      ///////////////////////////////////////////////////////////////////////
      FIT_DATE_TIME GetTimestamp(void) const
      {
         return GetFieldUINT32Value(253, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set timestamp field
      // Units: s
      ///////////////////////////////////////////////////////////////////////
      void SetTimestamp(FIT_DATE_TIME timestamp)
      {
         SetFieldUINT32Value(253, timestamp, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns device_index field
      ///////////////////////////////////////////////////////////////////////
      FIT_DEVICE_INDEX GetDeviceIndex(void) const
      {
         return GetFieldUINT8Value(0, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set device_index field
      ///////////////////////////////////////////////////////////////////////
      void SetDeviceIndex(FIT_DEVICE_INDEX deviceIndex)
      {
         SetFieldUINT8Value(0, deviceIndex, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns device_type field
      ///////////////////////////////////////////////////////////////////////
      FIT_UINT8 GetDeviceType(void) const
      {
         return GetFieldUINT8Value(1, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set device_type field
      ///////////////////////////////////////////////////////////////////////
      void SetDeviceType(FIT_UINT8 deviceType)
      {
         SetFieldUINT8Value(1, deviceType, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns antplus_device_type field
      ///////////////////////////////////////////////////////////////////////
      FIT_ANTPLUS_DEVICE_TYPE GetAntplusDeviceType(void) const
      {
         return GetFieldUINT8Value(1, 0, (FIT_UINT16) Profile::DEVICE_INFO_MESG_DEVICE_TYPE_FIELD_ANTPLUS_DEVICE_TYPE);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set antplus_device_type field
      ///////////////////////////////////////////////////////////////////////
      void SetAntplusDeviceType(FIT_ANTPLUS_DEVICE_TYPE antplusDeviceType)
      {
         SetFieldUINT8Value(1, antplusDeviceType, 0, (FIT_UINT16) Profile::DEVICE_INFO_MESG_DEVICE_TYPE_FIELD_ANTPLUS_DEVICE_TYPE);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns ant_device_type field
      ///////////////////////////////////////////////////////////////////////
      FIT_UINT8 GetAntDeviceType(void) const
      {
         return GetFieldUINT8Value(1, 0, (FIT_UINT16) Profile::DEVICE_INFO_MESG_DEVICE_TYPE_FIELD_ANT_DEVICE_TYPE);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set ant_device_type field
      ///////////////////////////////////////////////////////////////////////
      void SetAntDeviceType(FIT_UINT8 antDeviceType)
      {
         SetFieldUINT8Value(1, antDeviceType, 0, (FIT_UINT16) Profile::DEVICE_INFO_MESG_DEVICE_TYPE_FIELD_ANT_DEVICE_TYPE);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns manufacturer field
      ///////////////////////////////////////////////////////////////////////
      FIT_MANUFACTURER GetManufacturer(void) const
      {
         return GetFieldUINT16Value(2, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set manufacturer field
      ///////////////////////////////////////////////////////////////////////
      void SetManufacturer(FIT_MANUFACTURER manufacturer)
      {
         SetFieldUINT16Value(2, manufacturer, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns serial_number field
      ///////////////////////////////////////////////////////////////////////
      FIT_UINT32Z GetSerialNumber(void) const
      {
         return GetFieldUINT32ZValue(3, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set serial_number field
      ///////////////////////////////////////////////////////////////////////
      void SetSerialNumber(FIT_UINT32Z serialNumber)
      {
         SetFieldUINT32ZValue(3, serialNumber, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns product field
      ///////////////////////////////////////////////////////////////////////
      FIT_UINT16 GetProduct(void) const
      {
         return GetFieldUINT16Value(4, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set product field
      ///////////////////////////////////////////////////////////////////////
      void SetProduct(FIT_UINT16 product)
      {
         SetFieldUINT16Value(4, product, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns garmin_product field
      ///////////////////////////////////////////////////////////////////////
      FIT_GARMIN_PRODUCT GetGarminProduct(void) const
      {
         return GetFieldUINT16Value(4, 0, (FIT_UINT16) Profile::DEVICE_INFO_MESG_PRODUCT_FIELD_GARMIN_PRODUCT);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set garmin_product field
      ///////////////////////////////////////////////////////////////////////
      void SetGarminProduct(FIT_GARMIN_PRODUCT garminProduct)
      {
         SetFieldUINT16Value(4, garminProduct, 0, (FIT_UINT16) Profile::DEVICE_INFO_MESG_PRODUCT_FIELD_GARMIN_PRODUCT);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns software_version field
      ///////////////////////////////////////////////////////////////////////
      FIT_FLOAT32 GetSoftwareVersion(void) const
      {
         return GetFieldFLOAT32Value(5, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set software_version field
      ///////////////////////////////////////////////////////////////////////
      void SetSoftwareVersion(FIT_FLOAT32 softwareVersion)
      {
         SetFieldFLOAT32Value(5, softwareVersion, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns hardware_version field
      ///////////////////////////////////////////////////////////////////////
      FIT_UINT8 GetHardwareVersion(void) const
      {
         return GetFieldUINT8Value(6, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set hardware_version field
      ///////////////////////////////////////////////////////////////////////
      void SetHardwareVersion(FIT_UINT8 hardwareVersion)
      {
         SetFieldUINT8Value(6, hardwareVersion, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns cum_operating_time field
      // Units: s
      // Comment: Reset by new battery or charge.
      ///////////////////////////////////////////////////////////////////////
      FIT_UINT32 GetCumOperatingTime(void) const
      {
         return GetFieldUINT32Value(7, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set cum_operating_time field
      // Units: s
      // Comment: Reset by new battery or charge.
      ///////////////////////////////////////////////////////////////////////
      void SetCumOperatingTime(FIT_UINT32 cumOperatingTime)
      {
         SetFieldUINT32Value(7, cumOperatingTime, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns battery_voltage field
      // Units: V
      ///////////////////////////////////////////////////////////////////////
      FIT_FLOAT32 GetBatteryVoltage(void) const
      {
         return GetFieldFLOAT32Value(10, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set battery_voltage field
      // Units: V
      ///////////////////////////////////////////////////////////////////////
      void SetBatteryVoltage(FIT_FLOAT32 batteryVoltage)
      {
         SetFieldFLOAT32Value(10, batteryVoltage, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns battery_status field
      ///////////////////////////////////////////////////////////////////////
      FIT_BATTERY_STATUS GetBatteryStatus(void) const
      {
         return GetFieldUINT8Value(11, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set battery_status field
      ///////////////////////////////////////////////////////////////////////
      void SetBatteryStatus(FIT_BATTERY_STATUS batteryStatus)
      {
         SetFieldUINT8Value(11, batteryStatus, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns sensor_position field
      // Comment: Indicates the location of the sensor
      ///////////////////////////////////////////////////////////////////////
      FIT_BODY_LOCATION GetSensorPosition(void) const
      {
         return GetFieldENUMValue(18, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set sensor_position field
      // Comment: Indicates the location of the sensor
      ///////////////////////////////////////////////////////////////////////
      void SetSensorPosition(FIT_BODY_LOCATION sensorPosition)
      {
         SetFieldENUMValue(18, sensorPosition, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns descriptor field
      // Comment: Used to describe the sensor or location
      ///////////////////////////////////////////////////////////////////////
      FIT_WSTRING GetDescriptor(void) const
      {
         return GetFieldSTRINGValue(19, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set descriptor field
      // Comment: Used to describe the sensor or location
      ///////////////////////////////////////////////////////////////////////
      void SetDescriptor(FIT_WSTRING descriptor)
      {
         SetFieldSTRINGValue(19, descriptor, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns ant_transmission_type field
      ///////////////////////////////////////////////////////////////////////
      FIT_UINT8Z GetAntTransmissionType(void) const
      {
         return GetFieldUINT8ZValue(20, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set ant_transmission_type field
      ///////////////////////////////////////////////////////////////////////
      void SetAntTransmissionType(FIT_UINT8Z antTransmissionType)
      {
         SetFieldUINT8ZValue(20, antTransmissionType, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns ant_device_number field
      ///////////////////////////////////////////////////////////////////////
      FIT_UINT16Z GetAntDeviceNumber(void) const
      {
         return GetFieldUINT16ZValue(21, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set ant_device_number field
      ///////////////////////////////////////////////////////////////////////
      void SetAntDeviceNumber(FIT_UINT16Z antDeviceNumber)
      {
         SetFieldUINT16ZValue(21, antDeviceNumber, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns ant_network field
      ///////////////////////////////////////////////////////////////////////
      FIT_ANT_NETWORK GetAntNetwork(void) const
      {
         return GetFieldENUMValue(22, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set ant_network field
      ///////////////////////////////////////////////////////////////////////
      void SetAntNetwork(FIT_ANT_NETWORK antNetwork)
      {
         SetFieldENUMValue(22, antNetwork, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns source_type field
      ///////////////////////////////////////////////////////////////////////
      FIT_SOURCE_TYPE GetSourceType(void) const
      {
         return GetFieldENUMValue(25, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set source_type field
      ///////////////////////////////////////////////////////////////////////
      void SetSourceType(FIT_SOURCE_TYPE sourceType)
      {
         SetFieldENUMValue(25, sourceType, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

};

} // namespace fit

#endif // !defined(FIT_DEVICE_INFO_MESG_HPP)
