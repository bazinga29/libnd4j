//
// @author raver119@gmail.com
//

#ifndef LIBND4J_BLOCK_H
#define LIBND4J_BLOCK_H

#include <vector>
#include "Variable.h"
#include "VariableSpace.h"


// CUDA-specific includes
#ifdef __CUDACC__

#include <cuda.h>
#include <cuda_runtime_api.h>
#include <cuda_runtime.h>
#include <cuda_device_runtime_api.h>

#endif

namespace nd4j {
    namespace graph {
        /**
         * This class defines input desired for any given node/operation within graph
         */
        template <typename T>
        class Block {
        protected:
            // int ids of the input nodes
            std::vector<int> _inputs;
            std::vector<nd4j::graph::Variable<T> *> _variables;
            nd4j::graph::VariableSpace<T>* _variableSpace;
            nd4j::random::RandomBuffer* _rng;
            int _nodeId;

            std::vector<T> _tArgs;
            std::vector<int> _iArgs;            
			
			bool _isInplace;

        public:

            // CUDA-specific fields
#ifdef __CUDACC__
            cudaStream_t* _stream;
#endif

            Block(int nodeId, VariableSpace<T> *variableSpace) {
                _nodeId = nodeId;
                _variableSpace = variableSpace;
				_isInplace = false;
            }

            Block(int nodeId, VariableSpace<T> *variableSpace, bool isInplace) : Block(nodeId, variableSpace) {
                _isInplace = isInplace;
            }

            ~Block() {
                //
            }


            nd4j::random::RandomBuffer* getRNG() {
                return _rng;
            }

            void setRNG(nd4j::random::RandomBuffer* rng) {
                _rng = rng;
            }

            int getNodeId() {
                return _nodeId;
            }

            /**
             * This method returns number of inputs available in this block
             * @return
             */
            unsigned long width() {
                return _inputs.size();
            };

            /**
             * This method returns variableSpace used in this block
             * @return
             */
            VariableSpace<T> *getVariableSpace() {
                return _variableSpace;
            }

            bool isInplace() {
                return _isInplace;
            }

            std::vector<T>* getTArguments() {
                return &_tArgs;
            }

            std::vector<int>* getIArguments() {
                return &_iArgs;
            }


            void pickInput(int input) {
                _inputs.push_back(input);

                if (!_variableSpace->hasVariable(input))
                    throw "Unknown variable was referenced";

                _variables.push_back(_variableSpace->getVariable(input));
            }

            void fillInputs(std::initializer_list<int> inputs) {
                for (auto v: inputs) {
                    pickInput(v);
                }
            }

            void fillInputs(std::vector<int> *inputs) {
                for (int e = 0; e < inputs->size(); e++) {
                    auto v = inputs->at(e);
                    pickInput(v);
                }
            }

            std::vector<nd4j::graph::Variable<T> *>& getVariables();
        };
    }
}


/**
* This method returns variables in this block
* @return
*/
template <typename T>
std::vector<nd4j::graph::Variable<T> *>& nd4j::graph::Block<T>::getVariables() {
    return _variables;
}

#endif //LIBND4J_BLOCK_H