//
// Created by yurii@skymind.io on 01.11.2017.
//

#include <ops/declarable/CustomOperations.h>
#include<ops/declarable/helpers/stack.h>

namespace nd4j {
namespace ops {

CUSTOM_OP_IMPL(stack, -1, 1, false, 0, 0) {
	NDArray<T>* input = INPUT_VARIABLE(0);
	NDArray<T>* output = OUTPUT_VARIABLE(0);
	int dim  = block.getIArguments()->size() > 0 ? INT_ARG(0) : 0;	 
	if(dim < 0)
 		dim += input->rankOf() + 1;
	
	// input validation
	// check whether shapes of all input array are the same				
	for (int i = 0; i < (int) block.width() - 1; ++i)
		REQUIRE_TRUE(shape::equalsSoft((INPUT_VARIABLE(i))->getShapeInfo(), (INPUT_VARIABLE(i+1))->getShapeInfo()), 0, "CUSTOM_OP stack: the shapes of input arrays are different !");
 	
 	if(input->rankOf() > 1)
 		REQUIRE_TRUE(dim <= input->rankOf(), 0, "CUSTOM_OP stack: the input dimension is greater/equal than rank of input arrays shapes !");
 	
 	std::vector<NDArray<T>*> inArrs(block.width());
 	for(int i = 0; i < block.width(); ++i)
		inArrs[i] = INPUT_VARIABLE(i);
	
	helpers::stack(inArrs, *output, dim);
	
	// remove unity from output shape if input arrays are vectors 
	// if(input->isVector())	{
	// 	std::vector<int> outShape(output->shapeOf(), output->shapeOf() + output->rankOf());		
	// 	outShape.erase(find(outShape.begin(), outShape.end(), 1));
	// 	output->reshapei(output->ordering(), outShape);
	// 	if(dim != 0 && (int)block.width() == 1)			// such is implemented by tensorFlow
	// 		output->permutei({1, 0});
	// 	output->getShapeInfo()[output->rankOf()*2 + 2] = 1;		
	// }
  	
  	return Status::OK();
}
DECLARE_SYN(pack, stack);
DECLARE_SYN(Pack, stack);


DECLARE_SHAPE_FN(stack) {
	
	// check whether input dimension is within rank range
	int* inShapeInfo = inputShape->at(0);
	int rank = inShapeInfo[0];
	int dim = INT_ARG(0);
	if(dim < 0 ) dim += rank + 1;
	
	if(rank == 0) {
		int* outShapeInfo = nullptr;
 		ALLOCATE(outShapeInfo, block.getWorkspace(), shape::shapeInfoLength(1), int);
  		outShapeInfo[0] = 1;
  		outShapeInfo[1] = block.width();
  		outShapeInfo[2] = 1;
  		outShapeInfo[3] = 1;
  		outShapeInfo[4] = 0;
  		outShapeInfo[5] = (int)shape::order(inShapeInfo);
  		return SHAPELIST(outShapeInfo);
	}
	
	//the rank of output ShapeInfo is larger by one compared to input ShapeInfo
	std::vector<int> outShape(inShapeInfo + 1, inShapeInfo + 1 + rank);
	
	// insert (int) block.width() at dim position of input shape to get output shape	
	outShape.insert(outShape.begin() + dim, (int) block.width());						
	
	// evaluate output ShapeInfo
	int newRank = outShape.size();
	int* outShapeInfo = nullptr;
  	ALLOCATE(outShapeInfo, block.getWorkspace(), shape::shapeInfoLength(newRank), int);
  	outShapeInfo[0] = newRank;
  	
  	for(int i=1; i <= newRank; ++i)
  		outShapeInfo[i] = outShape[i-1];
  	
  	shape::updateStrides(outShapeInfo, shape::order(inShapeInfo));    
  	
  	return SHAPELIST(outShapeInfo);
}

// 1) 1х4 + 1х4 = 2х1х4 (along dim=0) = 2x4 
// 2) 1х4 + 1х4 = 1х2х4 (along dim=1) = 2x4 
// 3) 4х1 + 4х1 = 2х4x1 (along dim=0) = 2x4 
// 4) 4х1 + 4х1 = 4х2x1 (along dim=1) = 4x2 

}
}