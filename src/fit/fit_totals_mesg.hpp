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


#if !defined(FIT_TOTALS_MESG_HPP)
#define FIT_TOTALS_MESG_HPP

#include "fit_mesg.hpp"

namespace fit
{

class TotalsMesg : public Mesg
{
   public:
      TotalsMesg(void) : Mesg(Profile::MESG_TOTALS)
      {
      }

      TotalsMesg(const Mesg &mesg) : Mesg(mesg)
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
      // Returns timer_time field
      // Units: s
      // Comment: Excludes pauses
      ///////////////////////////////////////////////////////////////////////
      FIT_UINT32 GetTimerTime(void) const
      {
         return GetFieldUINT32Value(0, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set timer_time field
      // Units: s
      // Comment: Excludes pauses
      ///////////////////////////////////////////////////////////////////////
      void SetTimerTime(FIT_UINT32 timerTime)
      {
         SetFieldUINT32Value(0, timerTime, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns distance field
      // Units: m
      ///////////////////////////////////////////////////////////////////////
      FIT_UINT32 GetDistance(void) const
      {
         return GetFieldUINT32Value(1, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set distance field
      // Units: m
      ///////////////////////////////////////////////////////////////////////
      void SetDistance(FIT_UINT32 distance)
      {
         SetFieldUINT32Value(1, distance, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns calories field
      // Units: kcal
      ///////////////////////////////////////////////////////////////////////
      FIT_UINT32 GetCalories(void) const
      {
         return GetFieldUINT32Value(2, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set calories field
      // Units: kcal
      ///////////////////////////////////////////////////////////////////////
      void SetCalories(FIT_UINT32 calories)
      {
         SetFieldUINT32Value(2, calories, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns sport field
      ///////////////////////////////////////////////////////////////////////
      FIT_SPORT GetSport(void) const
      {
         return GetFieldENUMValue(3, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set sport field
      ///////////////////////////////////////////////////////////////////////
      void SetSport(FIT_SPORT sport)
      {
         SetFieldENUMValue(3, sport, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns elapsed_time field
      // Units: s
      // Comment: Includes pauses
      ///////////////////////////////////////////////////////////////////////
      FIT_UINT32 GetElapsedTime(void) const
      {
         return GetFieldUINT32Value(4, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set elapsed_time field
      // Units: s
      // Comment: Includes pauses
      ///////////////////////////////////////////////////////////////////////
      void SetElapsedTime(FIT_UINT32 elapsedTime)
      {
         SetFieldUINT32Value(4, elapsedTime, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns sessions field
      ///////////////////////////////////////////////////////////////////////
      FIT_UINT16 GetSessions(void) const
      {
         return GetFieldUINT16Value(5, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set sessions field
      ///////////////////////////////////////////////////////////////////////
      void SetSessions(FIT_UINT16 sessions)
      {
         SetFieldUINT16Value(5, sessions, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns active_time field
      // Units: s
      ///////////////////////////////////////////////////////////////////////
      FIT_UINT32 GetActiveTime(void) const
      {
         return GetFieldUINT32Value(6, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set active_time field
      // Units: s
      ///////////////////////////////////////////////////////////////////////
      void SetActiveTime(FIT_UINT32 activeTime)
      {
         SetFieldUINT32Value(6, activeTime, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns sport_index field
      ///////////////////////////////////////////////////////////////////////
      FIT_UINT8 GetSportIndex(void) const
      {
         return GetFieldUINT8Value(9, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set sport_index field
      ///////////////////////////////////////////////////////////////////////
      void SetSportIndex(FIT_UINT8 sportIndex)
      {
         SetFieldUINT8Value(9, sportIndex, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

};

} // namespace fit

#endif // !defined(FIT_TOTALS_MESG_HPP)
