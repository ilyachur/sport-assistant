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


#if !defined(FIT_SPORT_MESG_HPP)
#define FIT_SPORT_MESG_HPP

#include "fit_mesg.hpp"

namespace fit
{

class SportMesg : public Mesg
{
   public:
      SportMesg(void) : Mesg(Profile::MESG_SPORT)
      {
      }

      explicit SportMesg(const Mesg &mesg) : Mesg(mesg)
      {
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns sport field
      ///////////////////////////////////////////////////////////////////////
      FIT_SPORT GetSport(void) const
      {
         return GetFieldENUMValue(0, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set sport field
      ///////////////////////////////////////////////////////////////////////
      void SetSport(FIT_SPORT sport)
      {
         SetFieldENUMValue(0, sport, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns sub_sport field
      ///////////////////////////////////////////////////////////////////////
      FIT_SUB_SPORT GetSubSport(void) const
      {
         return GetFieldENUMValue(1, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set sub_sport field
      ///////////////////////////////////////////////////////////////////////
      void SetSubSport(FIT_SUB_SPORT subSport)
      {
         SetFieldENUMValue(1, subSport, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns name field
      ///////////////////////////////////////////////////////////////////////
      FIT_WSTRING GetName(void) const
      {
         return GetFieldSTRINGValue(3, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set name field
      ///////////////////////////////////////////////////////////////////////
      void SetName(FIT_WSTRING name)
      {
         SetFieldSTRINGValue(3, name, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

};

} // namespace fit

#endif // !defined(FIT_SPORT_MESG_HPP)
