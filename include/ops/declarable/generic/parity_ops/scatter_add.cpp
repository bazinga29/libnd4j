//
// Created by raver119 on 24.11.17.
//

#if defined(__ALL_OPS) || defined(__CLION_IDE__) || defined(__scatter_add)

#include <ops/declarable/CustomOperations.h>
#include <ops/declarable/generic/helpers/ScatterHelper.h>

namespace nd4j {
    namespace ops {
        OP_IMPL(scatter_add, 3, 1, true) {
            auto input = INPUT_VARIABLE(0);
            auto indices = INPUT_VARIABLE(1);
            auto updates = INPUT_VARIABLE(2);

            auto output = OUTPUT_VARIABLE(0);

            if (!block.isInplace())
                output->assign(input);

            ScatterHelper<T>::template scatter_apply<simdOps::Add<T>>(output, indices, updates);        

            return ND4J_STATUS_OK;
        }
        DECLARE_SYN(ScatterAdd, scatter_add);
    }
}

#endif