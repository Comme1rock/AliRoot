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

//_________________________________________________________________________
// Algorithm class to identify the type of particle from the PHOS TrackSegment alone 
//*-- Author : Y. Schutz SUBATECH
//////////////////////////////////////////////////////////////////////////////

// --- ROOT system ---

// --- Standard library ---

#include <iostream>

// --- AliRoot header files ---

#include "AliPHOSPIDv1.h"
#include "AliPHOSTrackSegment.h"
#include "AliPHOSRecParticle.h"

ClassImp( AliPHOSPIDv1) 


//____________________________________________________________________________
 AliPHOSPIDv1::AliPHOSPIDv1(): fCutOnDispersion(1.5) 

{
  // ctor

}

//____________________________________________________________________________
 AliPHOSPIDv1::~AliPHOSPIDv1()
{ 
  // dtor
}


//____________________________________________________________________________
void  AliPHOSPIDv1::MakeParticles(TrackSegmentsList * trsl, RecParticlesList * rpl)
{
  // main function, does the job

  TIter next(trsl) ; 
  AliPHOSTrackSegment * tracksegment ; 
  Int_t index = 0 ; 
  AliPHOSRecParticle * rp ; 
  Int_t type ; 

  while ( (tracksegment = (AliPHOSTrackSegment *)next()) ) {
    new( (*rpl)[index] ) AliPHOSRecParticle(tracksegment) ;
    rp = (AliPHOSRecParticle *)(*rpl)[index] ; 

    // try to figure out the type of particle:
    //    1. just looking at the PPSD information 
    if( tracksegment->GetPpsdUp() == 0 ) {     // Neutral
      
      if( tracksegment->GetPpsdLow() == 0 )    // Neutral  
	type = kNEUTRAL ;   
      else                           // Gamma
	type = kGAMMA ;               
    }
    else                            // Charged           
      type = kCHARGED ;   

    //   2. from the shower profile analysis
    if ( type == kNEUTRAL ) { 
      AliPHOSEmcRecPoint * recp = tracksegment->GetEmcRecPoint() ; 
      Float_t * lambda = new Float_t[2]; 
      recp->GetElipsAxis(lambda) ; 
      if ( ( lambda[0] > fLambda1m && lambda[0] < fLambda1M ) && // shower profile cut
	   ( lambda[1] > fLambda2m && lambda[1] < fLambda2M ) )
	type = kNEUTRALEM ; 
      else 
	type = kNEUTRALHADRON ; 
      delete lambda ; 
   }

    //   3. from the shower dispersion 
    if (type == kCHARGED) { 
      if( tracksegment->GetEmcRecPoint()->GetDispersion() > fCutOnDispersion)  // shower dispersion cut
	type = kCHARGEDHADRON ;
      else  
	type = kELECTRON ; 
    } 
    rp->SetType(type) ; 
    index++ ; 
  }
    
}

//____________________________________________________________________________
void  AliPHOSPIDv1:: Print() 
{
  cout << "AliPHOSPIDv1 : cuts for the particle idendification based on the shower profile " << endl 
       << fLambda1m << " < value1 < " << fLambda1M << endl 
       << fLambda2m << " < value2 < " << fLambda2M << endl ;  

}

//____________________________________________________________________________
void  AliPHOSPIDv1::SetShowerProfileCuts(Float_t l1m, Float_t l1M, Float_t l2m, Float_t l2M)
{
  fLambda1m = l1m ; 
  fLambda1M = l1M ; 
  fLambda2m = l2m ; 
  fLambda2M = l2M ; 
}
