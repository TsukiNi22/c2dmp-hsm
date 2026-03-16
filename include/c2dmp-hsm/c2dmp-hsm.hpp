/**************************************************************\

 ██╗  ██╗ █████╗ ██████╗ ████████╗ █████╗ ███╗   ██╗██╗ █████╗ 
 ╚██╗██╔╝██╔══██╗██╔══██╗╚══██╔══╝██╔══██╗████╗  ██║██║██╔══██╗
  ╚███╔╝ ███████║██████╔╝   ██║   ███████║██╔██╗ ██║██║███████║
  ██╔██╗ ██╔══██║██╔══██╗   ██║   ██╔══██║██║╚██╗██║██║██╔══██║
 ██╔╝ ██╗██║  ██║██║  ██║   ██║   ██║  ██║██║ ╚████║██║██║  ██║
 ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝

Edition:
##  @date 16/03/2026 by @author Tsukini

File Name:
##  @file c2dmp-hsm.hpp

File Description:
##  Header for include all the different algorithm
\**************************************************************/

#ifndef C2DMP-HSM_H
    #define C2DMP-HSM_H

    //----------------------------------------------------------------//
    /* INCLUDE */

    /* algorithm */
    #include "algorithm/optimized.hpp"  // c2dmp_optimized

namespace c2dmp { // namespace start

// rediretion
template<std::uint32_t prefixDepthSearch = 3, typename UINTN = std::uint32_t>
inline float c2dmp(const std::string_view a, const std::string_view b)
{
    return c2dmp::algorithm::c2dmp_optimized<prefixDepthSearch, UINTN>(a, b);
}

} // namespace end
#endif /* C2DMP-HSM_H */
