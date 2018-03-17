//
// @author raver119@gmail.com
//

#if defined(__ALL_OPS) || defined(__CLION_IDE__) || defined(__unstack_list)

#include <ops/declarable/headers/list.h>

namespace nd4j {
namespace ops {
    LIST_OP_IMPL(unstack_list, 1, 1, 0, 0) {
        auto input = INPUT_VARIABLE(0);

        auto list = new NDArrayList<T>(0, true);
        list->unstack(input, 0);

        OVERWRITE_RESULT(list);

        return ND4J_STATUS_OK;
    }
}
}

#endif