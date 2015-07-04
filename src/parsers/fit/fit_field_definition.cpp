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


#include <ostream>
#include "fit_field_definition.hpp"

namespace fit
{

FieldDefinition::FieldDefinition()
: num(FIT_FIELD_NUM_INVALID), size(0), type(FIT_UINT8_INVALID)
{
}

FieldDefinition::FieldDefinition(const Field& field)
: num(field.GetNum()), size(field.GetSize()), type(field.GetType())
{
}

FieldDefinition::FieldDefinition(const Field* field)
{
   if (field != FIT_NULL)
   {
      num = field->GetNum();
      size = field->GetSize();
      type = field->GetType();
   }
   else
   {
      num = FIT_FIELD_NUM_INVALID;
      size = 0;
      type = FIT_UINT8_INVALID;
   }
}

FIT_UINT8 FieldDefinition::GetNum() const
{
   return num;
}

FIT_UINT8 FieldDefinition::GetSize() const
{
   return size;
}

FIT_UINT8 FieldDefinition::GetType() const
{
   return type;
}

void FieldDefinition::SetNum(const FIT_UINT8 newNum)
{
   num = newNum;
}

void FieldDefinition::SetSize(const FIT_UINT8 newSize)
{
   size = newSize;
}

void FieldDefinition::SetType(const FIT_UINT8 newType)
{
   type = newType;
}

FIT_BOOL FieldDefinition::operator==(const FieldDefinition& field) const
{
   if (num != field.num)
      return FIT_FALSE;

   if (size != field.size)
      return FIT_FALSE;

   if (type != field.type)
      return FIT_FALSE;

   return FIT_TRUE;
}      

FIT_BOOL FieldDefinition::operator!=(const FieldDefinition& field) const
{
   return !(*this==field);
}

FIT_UINT8 FieldDefinition::Write(std::ostream &file) const
{
   file.put(num);
   file.put(size);
   file.put(type);

   return 3;
}

} // namespace fit