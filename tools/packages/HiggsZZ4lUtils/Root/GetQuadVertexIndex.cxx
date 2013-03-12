// $Id: GetQuadVertexIndex.cxx 501230 2012-05-17 19:27:07Z krasznaa $

// ROOT include(s):
#include <TError.h>

// STL include(s):
#include <algorithm>

// Local include(s):
#include "../HiggsZZ4lUtils/GetQuadVertexIndex.h"

/// Number of leptons in a quadruplet
static const size_t QUAD_SIZE = 4;

/// Helper macro for printing nice error messages
/**
 * This macro is used to print some pretty error messages that specify
 * the file name and line number. This can be very useful when debugging
 * problems.
 *
 * It can be placed into a ROOT print function like this:
 *
 * <code>
 *  ::Error( "ThisFunction", ERROR_MESSAGE( "My message with an int %i" ), myInt );
 * </code>
 *
 * @param MESSAGE The message to "make pretty"
 */
#define ERROR_MESSAGE( MESSAGE )                \
   "%s:%i " MESSAGE, __FILE__, __LINE__

namespace {

   /// Function checking if the indices in the two vectors are the same
   /**
    * This function is used internally to decide if two vectors contain the
    * same indices.
    *
    * @param sel_indices    Indices of the leptons selected by the analysis
    * @param ntuple_indices Indices of the leptons of the 4-lepton vertex
    * @return <code>kTRUE</code> if the two set of indices are the same,
    *         <code>kFALSE</code> if they're not
    */
   ::Bool_t ContainsLeptons( const std::vector< int >& sel_indices,
                             const std::vector< int >& ntuple_indices ) {

      std::vector< ::Int_t >::const_iterator itr = sel_indices.begin();
      std::vector< ::Int_t >::const_iterator end = sel_indices.end();
      for( ; itr != end; ++itr ) {
         if( std::find( ntuple_indices.begin(), ntuple_indices.end(),
                        *itr ) == ntuple_indices.end() ) {
            return kFALSE;
         }
      }

      return kTRUE;
   }

} // private namespace

/**
 *  @short Function returning the index of the 4-lepton vertex describing some leptons
 *
 *         This function should be used to figure out which 4-lepton vertex describes
 *         the lepton quadruplet selected by the H->ZZ*->llll analysis.
 *
 *  @param el_indices    Indices of the electrons in the quadruplet
 *  @param staco_indices Indices of the staco muons in the quadruplet
 *  @param muid_indices  Indices of the muid muons in the quadruplet
 *  @param calo_indices  Indices of the calo muon in the quadruplet
 *  @param cbpart_el_index       Pointer to the quad_cbpart_el_index variable
 *  @param cbpart_mu_staco_index Pointer to the quad_cbpart_mu_staco_index variable
 *  @param cbpart_mu_muid_index  Pointer to the quad_cbpart_mu_muid_index variable
 *  @param cbpart_mu_calo_index  Pointer to the quad_cbpart_mu_calo_index variable
 *  @param vtx_index             Pointer to the quad_vtx_index variable
 *  @return The index of the quadruplet/vertex in the quad_ and quad_vtx_ branches
 *          describing the specified leptons
 *
 * @author Attila Krasznahorkay <Attila.Krasznahorkay@cern.ch>
 * @author Kirill Prokofiev     <Kirill.Prokofiev@cern.ch>
 *
 * $Revision: 501230 $
 * $Date: 2012-05-17 21:27:07 +0200 (Thu, 17 May 2012) $
 */
int GetQuadVertexIndex( const std::vector< int >& el_indices,
                        const std::vector< int >& staco_indices,
                        const std::vector< int >& muid_indices,
                        const std::vector< int >& calo_indices,
                        const std::vector< std::vector< int > >* cbpart_el_index,
                        const std::vector< std::vector< int > >* cbpart_mu_staco_index,
                        const std::vector< std::vector< int > >* cbpart_mu_muid_index,
                        const std::vector< std::vector< int > >* cbpart_mu_calo_index,
                        const std::vector< int >* vtx_index ) {

   // Check that the inputs make sense:
   if( ( el_indices.size() + staco_indices.size() + muid_indices.size() +
         calo_indices.size() ) != QUAD_SIZE ) {
      ::Error( "GetQuadVertexIndex",
               ERROR_MESSAGE( "The function needs the index of exactly 4 leptons" ) );
      return -1;
   }

   // Check that the ntuple variables are okay:
   if( ( ! cbpart_el_index ) || ( ! cbpart_mu_staco_index ) ||
       ( ! cbpart_mu_muid_index ) || ( ! cbpart_mu_calo_index ) ||
       ( ! vtx_index ) ) {
      ::Error( "GetQuadVertexIndex",
               ERROR_MESSAGE( "Received a null pointer as input" ) );
      return -1;
   }
   if( ( cbpart_el_index->size() != cbpart_mu_staco_index->size() ) ||
       ( cbpart_el_index->size() != cbpart_mu_muid_index->size() ) ||
       ( cbpart_el_index->size() != cbpart_mu_calo_index->size() ) ||
       ( cbpart_el_index->size() != vtx_index->size() ) ||
       ( cbpart_mu_staco_index->size() != cbpart_mu_muid_index->size() ) ||
       ( cbpart_mu_staco_index->size() != cbpart_mu_calo_index->size() ) ||
       ( cbpart_mu_staco_index->size() != vtx_index->size() ) ||
       ( cbpart_mu_muid_index->size() != cbpart_mu_calo_index->size() ) ||
       ( cbpart_mu_muid_index->size() != vtx_index->size() ) ||
       ( cbpart_mu_calo_index->size() != vtx_index->size() ) ) {
      ::Error( "GetQuadVertexIndex",
               ERROR_MESSAGE( "Not all the ntuple variables are of the same size" ) );
      return -1;
   }

   // Loop over the "ntuple quadruplets" and check which one describes the specified
   // leptons:
   for( size_t i = 0; i < cbpart_el_index->size(); ++i ) {

      // Check if all the selected leptons are in this ntuple quaduplet:
      if( ! ContainsLeptons( el_indices, ( *cbpart_el_index )[ i ] ) ) {
         continue;
      }
      if( ! ContainsLeptons( staco_indices, ( *cbpart_mu_staco_index )[ i ] ) ) {
         continue;
      }
      if( ! ContainsLeptons( muid_indices, ( *cbpart_mu_muid_index )[ i ] ) ) {
         continue;
      }
      if( ! ContainsLeptons( calo_indices, ( *cbpart_mu_calo_index )[ i ] ) ) {
         continue;
      }

      // This is the quadruplet we've been looking for:
      return ( *vtx_index )[ i ];
   }

   // If we reached this point, we didn't find the quadruplet vertex...
   ::Warning( "GetQuadVertexIndex",
              "Didn't find the HSG2 lepton vertex describing the "
              "quadruplet" );
   return -1;
}
