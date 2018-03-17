//
//  @author raver119@gmail.com
//

#if defined(__ALL_OPS) || defined(__CLION_IDE__) || defined(__to_uint64)

#include <ops/declarable/CustomOperations.h>

namespace nd4j {
    namespace ops {
        OP_IMPL(to_uint64, 1, 1, true) {
            auto input = INPUT_VARIABLE(0);
            auto output = OUTPUT_VARIABLE(0);

            if (!block.isInplace())
                output->assign(input);

            STORE_RESULT(output);

            return ND4J_STATUS_OK;
        }
    }
}

#endif