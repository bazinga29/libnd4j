//
// Created by george@skymind.io on 26.01.2018.
//

#if defined(__ALL_OPS) || defined(__CLION_IDE__) || defined(__normalize_moments)

#include <ops/declarable/CustomOperations.h>

namespace nd4j {
    namespace ops {
        CUSTOM_OP_IMPL(normalize_moments, 3, 2, false, 1, 0) {
            NDArray<T>* counts = INPUT_VARIABLE(0);
            NDArray<T>* means = INPUT_VARIABLE(1);
            NDArray<T>* variances = INPUT_VARIABLE(2);

            NDArray<T>* resMeans = OUTPUT_VARIABLE(0);
            NDArray<T>* resVariances = OUTPUT_VARIABLE(1);
/*
    divisor = math_ops.reciprocal(counts, name="divisor")
    if shift is not None:
      shifted_mean = math_ops.multiply(mean_ss, divisor, name="shifted_mean")
      mean = math_ops.add(shifted_mean, shift, name="mean")
    else:  # no shift.
      shifted_mean = math_ops.multiply(mean_ss, divisor, name="mean")
      mean = shifted_mean
    variance = math_ops.subtract(
        math_ops.multiply(variance_ss, divisor),
        math_ops.square(shifted_mean),
        name="variance")
  return (mean, variance)

*/

            T shift(0);
            
            if (block.getTArguments()->size() > 0) {
                shift = T_ARG(0);
            }

            means->template applyScalar<simdOps::Divide<T>>((*counts)(0), resMeans, nullptr);
            std::unique_ptr<NDArray<T>> squareMeans(resMeans->dup('c'));
            std::unique_ptr<NDArray<T>> tempVariances(resVariances->dup('c'));

            resMeans->template applyTransform<simdOps::Sqr<T>>(squareMeans.get(), nullptr);
            variances->template applyScalar<simdOps::Divide<T>>((*counts)(0), tempVariances.get(), nullptr);
            tempVariances->template applyPairwiseTransform<simdOps::Subtract<T>>(squareMeans.get(), resVariances, nullptr);
          
            if (shift != T(0)) {
                resMeans->template applyScalar<simdOps::Add<T>>(shift, resMeans, nullptr);
            }

            return ND4J_STATUS_OK;
        }

        DECLARE_SHAPE_FN(normalize_moments) {
    
            int* in = inputShape->at(1);

            int* meanShape = nullptr;
            int* varianceShape = nullptr;

            COPY_SHAPE_EX(in, meanShape, block.getWorkspace());
            COPY_SHAPE_EX(in, varianceShape, block.getWorkspace());

            auto shapeList = SHAPELIST(); 
            shapeList->push_back(meanShape);
            shapeList->push_back(varianceShape);

            return shapeList;
        }
    }

}

#endif