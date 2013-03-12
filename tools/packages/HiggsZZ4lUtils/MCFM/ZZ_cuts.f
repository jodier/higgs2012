
      subroutine ZZ_cuts(p,failed_cuts,cutsi,cutPairs) 
      implicit none
      include 'constants.f'
      double precision p(mxpart,4)
      logical failed_cuts 
      integer cutsi,cutPairs
      double precision ptl1,ptl2,ptl3,ptl4
      double precision pt,R,m34,m56,etarap,m45,m36
      double precision pt_hard,pt_soft
      double precision eta_max,mll34_s,mll34_h,mll56_s,mll56_h,m3456_s 
      integer pt_gt_h,pt_gt_s,j
      failed_cuts=.false.
!---- intialise variables 
      pt_hard=5d0
      pt_soft=5d0
      eta_max=10d0
      mll34_s=4d0
      mll34_h=1d8
      mll56_s=4d0
      mll56_h=1d8
! High and low mass cuts       
      if(cutsi .eq. 1) then 
         !PRINT *, 'Cut choice 1 gg->ZZ'
         pt_hard=5d0
         pt_soft=5d0
         eta_max=3d0
         mll34_s=12d0
         mll34_h=1d8
         mll56_s=12d0
         mll56_h=1d8
      else if(cutsi .eq. 2) then 
         !PRINT *, 'Cut choice 2 powheg dilepton'
         pt_hard=5d0
         pt_soft=5d0
         eta_max=10d0
         mll34_s=4d0
         mll34_h=1d8
         mll56_s=4d0
         mll56_h=1d8
      else if(cutsi .eq. 3) then 
         !PRINT *, 'Cut choice 3 powheg trilepton'
         pt_hard=5d0
         pt_soft=5d0
         eta_max=10d0
         mll34_s=4d0
         mll34_h=1d8
         mll56_s=4d0
         mll56_h=1d8
      else
         !PRINT *, 'Cut choice 0'
      endif
      
!--Counter for Pt cut
      pt_gt_h=0
      pt_gt_s=0
      
!-- count how many pt > low/high PT cuts and check rapidity 
      do j=3,6 
         if(pt(j,p).gt.pt_soft) then 
            pt_gt_s=pt_gt_s+1
         endif
         if(pt(j,p).gt.pt_hard) then 
            pt_gt_h=pt_gt_h+1
         endif
         if(dabs(etarap(j,p)).gt.eta_max) then 
             failed_cuts=.true. 
             return 
          endif
      enddo


!---Apply the 2 leptons with Pt above 5 GeV Selection
      if(cutsi .eq. 2) then
         if(pt_gt_s.lt.2) then 
            failed_cuts=.true.
            return
         endif
      endif

!---Apply the 3 leptons with Pt above 5 GeV Selection
      if(cutsi .eq. 3) then
         if(pt_gt_s.lt.3) then 
            failed_cuts=.true.
            return
         endif
      endif

!---Apply the 4 leptons with Pt above 5 GeV Selection
      if((cutsi .eq. 1)) then
         if(pt_gt_s.lt.4) then 
            failed_cuts=.true.
            return
         endif
      endif

!--- Mass 
      m34=0d0
      m56=0d0  
      m36=0d0
      m45=0d0
 !---+ metric     
      do j=1,4
         if(j.ne.4) then 
            m34=m34-(p(3,j)+p(4,j))**2
            m56=m56-(p(5,j)+p(6,j))**2            
            m36=m36-(p(3,j)+p(6,j))**2
            m45=m45-(p(4,j)+p(5,j))**2
         else
            m34=m34+(p(3,j)+p(4,j))**2
            m56=m56+(p(5,j)+p(6,j))**2
            m36=m36+(p(3,j)+p(6,j))**2
            m45=m45+(p(4,j)+p(5,j))**2
         endif
      enddo

      m34=dsqrt(max(m34,0d0)) 
      m56=dsqrt(max(m56,0d0))
      m36=dsqrt(max(m36,0d0)) 
      m45=dsqrt(max(m45,0d0))

!--- mass cuts
      if((m34.lt.mll34_s).or.(m34.gt.mll34_h)) then 
         failed_cuts=.true. 
         return 
      elseif((m56.lt.mll56_s).or.(m56.gt.mll56_h)) then 
         failed_cuts=.true. 
         return
      endif
      
!-- Cut set 3 corresponds to 4mu / 4e e.g where one can change the charge pairing of same flavor
!-- MCFM produces ee-mumu by default
      if(cutPairs .eq. 1) then
         if((m36.lt.mll56_s).or.(m36.gt.mll56_h)) then 
            failed_cuts=.true. 
            return 
         elseif((m45.lt.mll56_s).or.(m45.gt.mll56_h)) then 
            failed_cuts=.true. 
            return 
         endif
      endif
  


      
      return 
      end subroutine 





      
         
