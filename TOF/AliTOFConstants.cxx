 /**************************************************************************
 * Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 *                                                                        *
 * Author: The ALICE Off-line Project.                                    *
 * Contributors are mentioned in the code where appropriate.              *
 *                                                                        *
 * Permission to use, copy, modify and distribute this software and its   *
 * documentation strictly for non-commercial purposes is hereby granted   *
 * without fee, provided that the above copyright notice appears in all   *
 * copies and that both the copyright notice and this permission notice   *
 * appear in the supporting documentation. The authors make no claims     *
 * about the suitability of this software for any purpose. It is          *
 * provided "as is" without express or implied warranty.                  *
 **************************************************************************/

/*
$Log$
Revision 1.1  2001/11/22 11:22:51  hristov
Updated version of TOF digitization, N^2 problem solved (J.Chudoba)

*/

////////////////////////////////////////////////////////////////////////
//
// AliTOFConstants class
//
// This class serves to group constants needed by TOF detector in 1
// easily accessible place. All constants are public const static data 
// members. The class is never instatiated.
//
// Note: only a few constants are in the first version of this class,
//       more should be added by TOF developpers
//
// Author: Jiri Chudoba (CERN)
//
////////////////////////////////////////////////////////////////////////

#include "AliTOFConstants.h"

const Int_t AliTOFConstants::fgkNStripA;
const Int_t AliTOFConstants::fgkNStripB;
const Int_t AliTOFConstants::fgkNStripC;
const Int_t AliTOFConstants::fgkNpadX;
const Int_t AliTOFConstants::fgkNpadZ;
const Int_t AliTOFConstants::fgkPadXSector;
const Int_t AliTOFConstants::fgkNSectors;
const Int_t AliTOFConstants::fgkNPlates;

const Int_t AliTOFConstants::fgkTimeDiff;

ClassImp(AliTOFConstants)
