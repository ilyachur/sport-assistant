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


#if !defined(FIT_TRAINING_FILE_MESG_LISTENER_HPP)
#define FIT_TRAINING_FILE_MESG_LISTENER_HPP

#include "fit_training_file_mesg.hpp"

namespace fit
{

class TrainingFileMesgListener
{
   public:
      virtual ~TrainingFileMesgListener() {}
      virtual void OnMesg(TrainingFileMesg& mesg) = 0;
};

} // namespace fit

#endif // !defined(FIT_TRAINING_FILE_MESG_LISTENER_HPP)
