//
// Created by raver119 on 01.11.2017.
//

#if defined(__ALL_OPS) || defined(__CLION_IDE__) || defined(__ones_as)

#include <ops/declarable/CustomOperations.h>

namespace nd4j {
    namespace ops {
        OP_IMPL(ones_as, 1, 1, false) {
            auto output = OUTPUT_VARIABLE(0);

            output->assign((T) 1.0f);

            return ND4J_STATUS_OK;
        }
    }
}

#endif