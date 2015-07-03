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


#if !defined(FIT_FILE_ID_MESG_HPP)
#define FIT_FILE_ID_MESG_HPP

#include "fit_mesg.hpp"

namespace fit
{

class FileIdMesg : public Mesg
{
   public:
      FileIdMesg(void) : Mesg(Profile::MESG_FILE_ID)
      {
      }

      FileIdMesg(const Mesg &mesg) : Mesg(mesg)
      {
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns type field
      ///////////////////////////////////////////////////////////////////////
      FIT_FILE GetType(void) const
      {
         return GetFieldENUMValue(0, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set type field
      ///////////////////////////////////////////////////////////////////////
      void SetType(FIT_FILE type)
      {
         SetFieldENUMValue(0, type, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns manufacturer field
      ///////////////////////////////////////////////////////////////////////
      FIT_MANUFACTURER GetManufacturer(void) const
      {
         return GetFieldUINT16Value(1, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set manufacturer field
      ///////////////////////////////////////////////////////////////////////
      void SetManufacturer(FIT_MANUFACTURER manufacturer)
      {
         SetFieldUINT16Value(1, manufacturer, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns product field
      ///////////////////////////////////////////////////////////////////////
      FIT_UINT16 GetProduct(void) const
      {
         return GetFieldUINT16Value(2, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set product field
      ///////////////////////////////////////////////////////////////////////
      void SetProduct(FIT_UINT16 product)
      {
         SetFieldUINT16Value(2, product, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns garmin_product field
      ///////////////////////////////////////////////////////////////////////
      FIT_GARMIN_PRODUCT GetGarminProduct(void) const
      {
         return GetFieldUINT16Value(2, 0, (FIT_UINT16) Profile::FILE_ID_MESG_PRODUCT_FIELD_GARMIN_PRODUCT);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set garmin_product field
      ///////////////////////////////////////////////////////////////////////
      void SetGarminProduct(FIT_GARMIN_PRODUCT garminProduct)
      {
         SetFieldUINT16Value(2, garminProduct, 0, (FIT_UINT16) Profile::FILE_ID_MESG_PRODUCT_FIELD_GARMIN_PRODUCT);
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
      // Returns time_created field
      // Comment: Only set for files that are can be created/erased.
      ///////////////////////////////////////////////////////////////////////
      FIT_DATE_TIME GetTimeCreated(void) const
      {
         return GetFieldUINT32Value(4, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set time_created field
      // Comment: Only set for files that are can be created/erased.
      ///////////////////////////////////////////////////////////////////////
      void SetTimeCreated(FIT_DATE_TIME timeCreated)
      {
         SetFieldUINT32Value(4, timeCreated, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns number field
      // Comment: Only set for files that are not created/erased.
      ///////////////////////////////////////////////////////////////////////
      FIT_UINT16 GetNumber(void) const
      {
         return GetFieldUINT16Value(5, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set number field
      // Comment: Only set for files that are not created/erased.
      ///////////////////////////////////////////////////////////////////////
      void SetNumber(FIT_UINT16 number)
      {
         SetFieldUINT16Value(5, number, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

};

} // namespace fit

#endif // !defined(FIT_FILE_ID_MESG_HPP)
