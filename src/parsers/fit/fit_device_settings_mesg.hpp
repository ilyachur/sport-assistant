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


#if !defined(FIT_DEVICE_SETTINGS_MESG_HPP)
#define FIT_DEVICE_SETTINGS_MESG_HPP

#include "fit_mesg.hpp"

namespace fit
{

class DeviceSettingsMesg : public Mesg
{
   public:
      DeviceSettingsMesg(void) : Mesg(Profile::MESG_DEVICE_SETTINGS)
      {
      }

      explicit DeviceSettingsMesg(const Mesg &mesg) : Mesg(mesg)
      {
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns active_time_zone field
      // Comment: Index into time zone arrays.
      ///////////////////////////////////////////////////////////////////////
      FIT_UINT8 GetActiveTimeZone(void) const
      {
         return GetFieldUINT8Value(0, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set active_time_zone field
      // Comment: Index into time zone arrays.
      ///////////////////////////////////////////////////////////////////////
      void SetActiveTimeZone(FIT_UINT8 activeTimeZone)
      {
         SetFieldUINT8Value(0, activeTimeZone, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns utc_offset field
      // Comment: Offset from system time. Required to convert timestamp from system time to UTC.
      ///////////////////////////////////////////////////////////////////////
      FIT_UINT32 GetUtcOffset(void) const
      {
         return GetFieldUINT32Value(1, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set utc_offset field
      // Comment: Offset from system time. Required to convert timestamp from system time to UTC.
      ///////////////////////////////////////////////////////////////////////
      void SetUtcOffset(FIT_UINT32 utcOffset)
      {
         SetFieldUINT32Value(1, utcOffset, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns number of time_zone_offset
      ///////////////////////////////////////////////////////////////////////
      FIT_UINT8 GetNumTimeZoneOffset(void) const
      {
         return GetFieldNumValues(5, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns time_zone_offset field
      // Units: hr
      // Comment: timezone offset in 1/4 hour increments
      ///////////////////////////////////////////////////////////////////////
      FIT_FLOAT32 GetTimeZoneOffset(FIT_UINT8 index) const
      {
         return GetFieldFLOAT32Value(5, index, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set time_zone_offset field
      // Units: hr
      // Comment: timezone offset in 1/4 hour increments
      ///////////////////////////////////////////////////////////////////////
      void SetTimeZoneOffset(FIT_UINT8 index, FIT_FLOAT32 timeZoneOffset)
      {
         SetFieldFLOAT32Value(5, timeZoneOffset, index, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

};

} // namespace fit

#endif // !defined(FIT_DEVICE_SETTINGS_MESG_HPP)
