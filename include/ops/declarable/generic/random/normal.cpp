//
//  @author raver119@gmail.com
//

#include <ops/declarable/headers/random.h>

namespace nd4j {
    namespace ops {
        CUSTOM_OP_IMPL(random_normal, 1, 1, true, 2, 0) {
            // normal distribution
            auto rng = block.getRNG();

            if (rng == nullptr)
                return Status::THROW("RNG is null, aborting...");

            auto x = INPUT_VARIABLE(0);
            auto z = OUTPUT_VARIABLE(0);

            functions::random::RandomFunction<T>::template execTransform<randomOps::GaussianDistribution<T>>(block.getRNG(), z->getBuffer(), z->getShapeInfo(), z->getBuffer(), z->getShapeInfo(), z->getBuffer(), z->getShapeInfo(), block.getTArguments()->data());

            return Status::OK();
        }

        DECLARE_SHAPE_FN(random_normal) {
            auto in = INPUT_VARIABLE(0);
            auto shape = in->template asVectorT<int>();

            int *newShape;
            ALLOCATE(newShape, block.getWorkspace(), shape::shapeInfoLength(shape.size()), int);
            shape::shapeBuffer(shape.size(), shape.data(), newShape);

            return SHAPELIST(newShape);
        }
    }
}