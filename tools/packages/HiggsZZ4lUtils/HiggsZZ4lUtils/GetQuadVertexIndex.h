// Dear emacs, this is -*- c++ -*-
// $Id: GetQuadVertexIndex.h 501230 2012-05-17 19:27:07Z krasznaa $
#ifndef HIGGSZZ4LUTILS_GETQUADVERTEXINDEX_H
#define HIGGSZZ4LUTILS_GETQUADVERTEXINDEX_H

// STL include(s):
#include <vector>

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
                        const std::vector< int >* vtx_index );

/**
 *  @short Convenience interface to the GetQuadVertexIndex function
 *
 *         This is just a convenience interface to the previous function. Can
 *         be used with a class created by TTree::MakeClass(...) or
 *         TTree::MakeSelector(...).
 *
 *  @param el_indices    Indices of the electrons in the quadruplet
 *  @param staco_indices Indices of the staco muons in the quadruplet
 *  @param muid_indices  Indices of the muid muons in the quadruplet
 *  @param calo_indices  Indices of the calo muon in the quadruplet
 *  @param ntuple        Reference to the object describing the input ntuple
 *  @return The index of the quadruplet/vertex in the quad_ and quad_vtx_ branches
 *          describing the specified leptons
 *
 * @author Attila Krasznahorkay <Attila.Krasznahorkay@cern.ch>
 * @author Kirill Prokofiev     <Kirill.Prokofiev@cern.ch>
 *
 * $Revision: 501230 $
 * $Date: 2012-05-17 21:27:07 +0200 (Thu, 17 May 2012) $
 */
template< class NTUPLE >
int GetQuadVertexIndex( const std::vector< int >& el_indices,
                        const std::vector< int >& staco_indices,
                        const std::vector< int >& muid_indices,
                        const std::vector< int >& calo_indices,
                        const NTUPLE& ntuple ) {

   return GetQuadVertexIndex( el_indices, staco_indices, muid_indices,
                              calo_indices, ntuple.quad_cbpart_el_index,
                              ntuple.quad_cbpart_mu_staco_index,
                              ntuple.quad_cbpart_mu_muid_index,
                              ntuple.quad_cbpart_mu_calo_index,
                              ntuple.quad_vtx_index );
}

#endif // HIGGSZZ4LUTILS_GETQUADVERTEXINDEX_H
