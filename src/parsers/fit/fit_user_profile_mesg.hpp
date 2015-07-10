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


#if !defined(FIT_USER_PROFILE_MESG_HPP)
#define FIT_USER_PROFILE_MESG_HPP

#include "fit_mesg.hpp"

namespace fit
{

class UserProfileMesg : public Mesg
{
   public:
      UserProfileMesg(void) : Mesg(Profile::MESG_USER_PROFILE)
      {
      }

      explicit UserProfileMesg(const Mesg &mesg) : Mesg(mesg)
      {
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns message_index field
      ///////////////////////////////////////////////////////////////////////
      FIT_MESSAGE_INDEX GetMessageIndex(void) const
      {
         return GetFieldUINT16Value(254, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set message_index field
      ///////////////////////////////////////////////////////////////////////
      void SetMessageIndex(FIT_MESSAGE_INDEX messageIndex)
      {
         SetFieldUINT16Value(254, messageIndex, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns friendly_name field
      ///////////////////////////////////////////////////////////////////////
      FIT_WSTRING GetFriendlyName(void) const
      {
         return GetFieldSTRINGValue(0, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set friendly_name field
      ///////////////////////////////////////////////////////////////////////
      void SetFriendlyName(FIT_WSTRING friendlyName)
      {
         SetFieldSTRINGValue(0, friendlyName, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns gender field
      ///////////////////////////////////////////////////////////////////////
      FIT_GENDER GetGender(void) const
      {
         return GetFieldENUMValue(1, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set gender field
      ///////////////////////////////////////////////////////////////////////
      void SetGender(FIT_GENDER gender)
      {
         SetFieldENUMValue(1, gender, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns age field
      // Units: years
      ///////////////////////////////////////////////////////////////////////
      FIT_UINT8 GetAge(void) const
      {
         return GetFieldUINT8Value(2, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set age field
      // Units: years
      ///////////////////////////////////////////////////////////////////////
      void SetAge(FIT_UINT8 age)
      {
         SetFieldUINT8Value(2, age, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns height field
      // Units: m
      ///////////////////////////////////////////////////////////////////////
      FIT_FLOAT32 GetHeight(void) const
      {
         return GetFieldFLOAT32Value(3, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set height field
      // Units: m
      ///////////////////////////////////////////////////////////////////////
      void SetHeight(FIT_FLOAT32 height)
      {
         SetFieldFLOAT32Value(3, height, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns weight field
      // Units: kg
      ///////////////////////////////////////////////////////////////////////
      FIT_FLOAT32 GetWeight(void) const
      {
         return GetFieldFLOAT32Value(4, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set weight field
      // Units: kg
      ///////////////////////////////////////////////////////////////////////
      void SetWeight(FIT_FLOAT32 weight)
      {
         SetFieldFLOAT32Value(4, weight, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns language field
      ///////////////////////////////////////////////////////////////////////
      FIT_LANGUAGE GetLanguage(void) const
      {
         return GetFieldENUMValue(5, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set language field
      ///////////////////////////////////////////////////////////////////////
      void SetLanguage(FIT_LANGUAGE language)
      {
         SetFieldENUMValue(5, language, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns elev_setting field
      ///////////////////////////////////////////////////////////////////////
      FIT_DISPLAY_MEASURE GetElevSetting(void) const
      {
         return GetFieldENUMValue(6, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set elev_setting field
      ///////////////////////////////////////////////////////////////////////
      void SetElevSetting(FIT_DISPLAY_MEASURE elevSetting)
      {
         SetFieldENUMValue(6, elevSetting, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns weight_setting field
      ///////////////////////////////////////////////////////////////////////
      FIT_DISPLAY_MEASURE GetWeightSetting(void) const
      {
         return GetFieldENUMValue(7, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set weight_setting field
      ///////////////////////////////////////////////////////////////////////
      void SetWeightSetting(FIT_DISPLAY_MEASURE weightSetting)
      {
         SetFieldENUMValue(7, weightSetting, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns resting_heart_rate field
      // Units: bpm
      ///////////////////////////////////////////////////////////////////////
      FIT_UINT8 GetRestingHeartRate(void) const
      {
         return GetFieldUINT8Value(8, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set resting_heart_rate field
      // Units: bpm
      ///////////////////////////////////////////////////////////////////////
      void SetRestingHeartRate(FIT_UINT8 restingHeartRate)
      {
         SetFieldUINT8Value(8, restingHeartRate, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns default_max_running_heart_rate field
      // Units: bpm
      ///////////////////////////////////////////////////////////////////////
      FIT_UINT8 GetDefaultMaxRunningHeartRate(void) const
      {
         return GetFieldUINT8Value(9, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set default_max_running_heart_rate field
      // Units: bpm
      ///////////////////////////////////////////////////////////////////////
      void SetDefaultMaxRunningHeartRate(FIT_UINT8 defaultMaxRunningHeartRate)
      {
         SetFieldUINT8Value(9, defaultMaxRunningHeartRate, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns default_max_biking_heart_rate field
      // Units: bpm
      ///////////////////////////////////////////////////////////////////////
      FIT_UINT8 GetDefaultMaxBikingHeartRate(void) const
      {
         return GetFieldUINT8Value(10, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set default_max_biking_heart_rate field
      // Units: bpm
      ///////////////////////////////////////////////////////////////////////
      void SetDefaultMaxBikingHeartRate(FIT_UINT8 defaultMaxBikingHeartRate)
      {
         SetFieldUINT8Value(10, defaultMaxBikingHeartRate, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns default_max_heart_rate field
      // Units: bpm
      ///////////////////////////////////////////////////////////////////////
      FIT_UINT8 GetDefaultMaxHeartRate(void) const
      {
         return GetFieldUINT8Value(11, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set default_max_heart_rate field
      // Units: bpm
      ///////////////////////////////////////////////////////////////////////
      void SetDefaultMaxHeartRate(FIT_UINT8 defaultMaxHeartRate)
      {
         SetFieldUINT8Value(11, defaultMaxHeartRate, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns hr_setting field
      ///////////////////////////////////////////////////////////////////////
      FIT_DISPLAY_HEART GetHrSetting(void) const
      {
         return GetFieldENUMValue(12, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set hr_setting field
      ///////////////////////////////////////////////////////////////////////
      void SetHrSetting(FIT_DISPLAY_HEART hrSetting)
      {
         SetFieldENUMValue(12, hrSetting, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns speed_setting field
      ///////////////////////////////////////////////////////////////////////
      FIT_DISPLAY_MEASURE GetSpeedSetting(void) const
      {
         return GetFieldENUMValue(13, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set speed_setting field
      ///////////////////////////////////////////////////////////////////////
      void SetSpeedSetting(FIT_DISPLAY_MEASURE speedSetting)
      {
         SetFieldENUMValue(13, speedSetting, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns dist_setting field
      ///////////////////////////////////////////////////////////////////////
      FIT_DISPLAY_MEASURE GetDistSetting(void) const
      {
         return GetFieldENUMValue(14, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set dist_setting field
      ///////////////////////////////////////////////////////////////////////
      void SetDistSetting(FIT_DISPLAY_MEASURE distSetting)
      {
         SetFieldENUMValue(14, distSetting, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns power_setting field
      ///////////////////////////////////////////////////////////////////////
      FIT_DISPLAY_POWER GetPowerSetting(void) const
      {
         return GetFieldENUMValue(16, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set power_setting field
      ///////////////////////////////////////////////////////////////////////
      void SetPowerSetting(FIT_DISPLAY_POWER powerSetting)
      {
         SetFieldENUMValue(16, powerSetting, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns activity_class field
      ///////////////////////////////////////////////////////////////////////
      FIT_ACTIVITY_CLASS GetActivityClass(void) const
      {
         return GetFieldENUMValue(17, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set activity_class field
      ///////////////////////////////////////////////////////////////////////
      void SetActivityClass(FIT_ACTIVITY_CLASS activityClass)
      {
         SetFieldENUMValue(17, activityClass, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns position_setting field
      ///////////////////////////////////////////////////////////////////////
      FIT_DISPLAY_POSITION GetPositionSetting(void) const
      {
         return GetFieldENUMValue(18, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set position_setting field
      ///////////////////////////////////////////////////////////////////////
      void SetPositionSetting(FIT_DISPLAY_POSITION positionSetting)
      {
         SetFieldENUMValue(18, positionSetting, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns temperature_setting field
      ///////////////////////////////////////////////////////////////////////
      FIT_DISPLAY_MEASURE GetTemperatureSetting(void) const
      {
         return GetFieldENUMValue(21, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set temperature_setting field
      ///////////////////////////////////////////////////////////////////////
      void SetTemperatureSetting(FIT_DISPLAY_MEASURE temperatureSetting)
      {
         SetFieldENUMValue(21, temperatureSetting, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns local_id field
      ///////////////////////////////////////////////////////////////////////
      FIT_USER_LOCAL_ID GetLocalId(void) const
      {
         return GetFieldUINT16Value(22, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set local_id field
      ///////////////////////////////////////////////////////////////////////
      void SetLocalId(FIT_USER_LOCAL_ID localId)
      {
         SetFieldUINT16Value(22, localId, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns number of global_id
      ///////////////////////////////////////////////////////////////////////
      FIT_UINT8 GetNumGlobalId(void) const
      {
         return GetFieldNumValues(23, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns global_id field
      ///////////////////////////////////////////////////////////////////////
      FIT_BYTE GetGlobalId(FIT_UINT8 index) const
      {
         return GetFieldBYTEValue(23, index, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set global_id field
      ///////////////////////////////////////////////////////////////////////
      void SetGlobalId(FIT_UINT8 index, FIT_BYTE globalId)
      {
         SetFieldBYTEValue(23, globalId, index, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns height_setting field
      ///////////////////////////////////////////////////////////////////////
      FIT_DISPLAY_MEASURE GetHeightSetting(void) const
      {
         return GetFieldENUMValue(30, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set height_setting field
      ///////////////////////////////////////////////////////////////////////
      void SetHeightSetting(FIT_DISPLAY_MEASURE heightSetting)
      {
         SetFieldENUMValue(30, heightSetting, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

};

} // namespace fit

#endif // !defined(FIT_USER_PROFILE_MESG_HPP)
