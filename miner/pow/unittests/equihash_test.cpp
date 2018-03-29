#include "../equihash.h"

int main()
{
    equi::Input input{1, 2, 3, 4, 56};

    equi::uint256_t nonce{1, 2, 4};
    auto proof = equi::get_solution(input, nonce);
    std::cout << proof.solution.size() << std::endl;

    if (equi::is_valid_proof(input, proof))
    {
        std::cout << "Solution is correct\n";
        return 0;
    }
    return -1;
}