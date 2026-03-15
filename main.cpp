#include "c2dmp-hsm/c2dmp-hsm_optimized.cpp"
#include "c2dmp-hsm/c2dmp-hsm_simplified.cpp"
#include <iostream>

int main()
{
    std::cout << c2dmp_optimized("test", "test") << std::endl;
    std::cout << c2dmp_simplified("test", "test") << std::endl;
    return 0;
}
