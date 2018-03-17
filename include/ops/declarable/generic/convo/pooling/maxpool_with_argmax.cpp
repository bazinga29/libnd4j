//
// Created by GS <sgazeos@gmail.com> at 2/20/18
//

#if defined(__ALL_OPS) || defined(__CLION_IDE__) || defined(__max_pool_with_argmax)

#include <ops/declarable/CustomOperations.h>
#include <ops/declarable/generic/helpers/convolutions.h>
#include <ops/declarable/helpers/max_pooling.h>

namespace nd4j {
    namespace ops {
        CUSTOM_OP_IMPL(max_pool_with_argmax, 1, 2, false, 0, 9) {

            NDArray<T>* x = INPUT_VARIABLE(0);
            NDArray<T>* z = OUTPUT_VARIABLE(0);
            NDArray<T>* indeces = OUTPUT_VARIABLE(1);

            REQUIRE_TRUE(x->rankOf() == 4, 0, "max_pool_with_argmax: Input should have rank of 4, but got %i instead", x->rankOf());

            std::vector<int> argI = *(block.getIArguments());

            helpers::maxPoolingFunctor(x, z, argI, indeces);

            return ND4J_STATUS_OK;
        }
        
        DECLARE_SHAPE_FN(max_pool_with_argmax) {
            int* in = inputShape->at(0);
            int* valuesShape = nullptr;
            int* indicesShape = nullptr;
            COPY_SHAPE(in, valuesShape);
            COPY_SHAPE(in, indicesShape);
            auto shapes = SHAPELIST(valuesShape, indicesShape);

            return shapes;
        }
    }
}

#endif

