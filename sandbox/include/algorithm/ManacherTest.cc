#include <io>
#include "Manacher.h"

int main() {
    std::string test("ababababbaba");
    auto algo = algorithm::Manacher();
    std::cout << algo.preProcess(test) << std::endl;
    algo.findPalindroms(test);
    std::cout << algo.getPalindroms() << std::endl;
    return 0;
}

