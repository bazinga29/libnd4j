//
// @author raver119@gmail.com
//

#ifndef LIBND4J_GNODE_H
#define LIBND4J_GNODE_H

#include <atomic>
#include <pointercast.h>
#include <string>
#include <NDArray.h>
#include "Context.h"
#include <ops/declarable/DeclarableOp.h>
#include <graph/generated/node_generated.h>


namespace nd4j {
    namespace graph {

        template <typename T>
        class Graph;

        template <typename T>
        class Node {
        protected:
            DataType _dataType;
            OpType _opType;
            ContextPrototype<T>* _protoContext = nullptr;
            Nd4jIndex _opNum;
            int _id;
            std::vector<std::pair<int, int>> _input;
            std::vector<std::pair<int, int>> _output;
            std::vector<int> _dimensions;

            int * _dim = nullptr;
            std::string _name;


            // this variable points to onion layer within graph
            int _layer = -1;

            // many ops require extra parameters to run
            T *_extraParams = nullptr;


            // optional scalar. used in scalar ops and in summary stats
            float _scalar;

            bool _hasExternalOutputs;
            bool _hasExternalInputs;
            bool _hasInternalOutputs;
            bool _hasInternalInputs;

            // this field is used to check, if op should be used in-place (so it can/will modify its inputs)
            bool _isInplace = false;

            // this field is used to delete attached customOp
            bool _isDeductable = false;

            OpClass _opClass;

            // these fields are used to store embedded CustomOps and Graph in case of Graph-in-Graph scenario
            nd4j::graph::Graph<T> * _graph= nullptr;
            nd4j::ops::DeclarableOp<T> *_customOp = nullptr;

            // each node can be active or inactive, if used with divergents, like IF statements
            bool _active = true;

            // these fields contain information about Scope these ops are related to
            int _scope_id = 0;
            std::string _scope_name;

            int _rewindNode = -1;
            std::pair<int, int> _rewindLayer = {-1, -1};

            Nd4jIndex _frameId = -1;

        public:
            Node(OpType opType = OpType_TRANSFORM, int opNum = 0, int id = 0, std::initializer_list<int> input = {}, std::initializer_list<int> output = {},  std::initializer_list<int> dimensions = {}, float scalar = 0.0f, std::initializer_list<T> tArgs = {}, std::initializer_list<int> iArgs = {});
            Node(const nd4j::graph::FlatNode *node);
            ~Node();

            bool equals(Node *other);

            DataType dataType();
            ContextPrototype<T>* protoContext();
            OpType opType();
            Nd4jIndex opNum();
            int id();
            std::vector<std::pair<int,int>> *input();
            std::vector<std::pair<int, int>> *output();

            Nd4jIndex getFrameId();
            void setFrameId(Nd4jIndex frameId);

            int getRewindNode();
            void setRewindNode(int nodeId);

            std::pair<int, int>& getRewindLayer();
            void setRewindLayer(int layerId, int stepId = 0);

            void setId(int id);

            T *extraParams();

            bool isMultiInput();
            bool isMultiOutput();

            int getLayer();
            void setLayer(int layer);

            bool isDivergencePoint();
            void setActive(bool reallyActive);
            bool isActive();

            bool hasExternalOutputs();
            bool hasExternalInputs();
            bool hasInternalOutputs();
            bool hasInternalInputs();

            T scalar();

            std::vector<int> * getDimensions();
            int * getDimensionsPtr();


            void pickOutputOnce(int outputId);
            void pickOutput(int outputId);
            void pickOutput(int nodeId, int outputId);
            void pickExternalOutput(int outputId);
            void pickInput(int inputId);
            void pickInput(int nodeId, int outputId);
            void pickInput(std::pair<int,int>& id);

            bool isDeductable();
            void setDeductable(bool reallyDeductable);

            void setName(std::string *name);
            void setName(const std::string& name);
            std::string * getName();
            std::string * name();


            void setContextPrototype(ContextPrototype<T> *block);
            ContextPrototype<T>* getContextPrototype();
            bool hasBlockAttached();

            void setCustomOp(nd4j::ops::DeclarableOp<T> *customOp = nullptr);
            nd4j::ops::DeclarableOp<T>* getCustomOp();
            bool hasCustomOp();

            void setGraph(nd4j::graph::Graph<T>* graph = nullptr);
            nd4j::graph::Graph<T>* getGraph();
            bool hasGraphEmbedded();

            bool isInplace();
            void markInplace(bool reallyInplace);


            OpClass getOpClass();

            // these methods are used for internal profiling
            void setOuterTime(Nd4jIndex time);
            void setInnerTime(Nd4jIndex time);

            // methods related to scopes
            bool isScoped();
            void setScopeInfo(int id, const char* name = nullptr);
            int scopeId();
            std::string* scopeName();

            // clone Node
            Node<T>* clone();

            // change Node data type
            template <typename N>
            Node<N>* asT();

            template <typename N>
            FORCEINLINE void pullValues(Node<N> *other) {

                if (this->_protoContext != nullptr)
                    delete _protoContext;

                this->_dataType = other->dataType();
                this->_protoContext = other->protoContext()->template asT<T>();
                this->_scalar = (T) other->scalar();
                this->_hasExternalInputs = other->hasExternalInputs();
                this->_hasExternalOutputs = other->hasExternalOutputs();
                this->_hasInternalInputs = other->hasInternalInputs();
                this->_hasInternalOutputs = other->hasInternalOutputs();

                this->markInplace(other->isInplace());
                this->setActive(other->isActive());
                this->setScopeInfo(other->scopeId(), other->scopeName()->c_str());
                this->setLayer(other->getLayer());
                this->setDeductable(other->isDeductable());


                if (this->_customOp != nullptr && _isDeductable)
                    delete this->_customOp;

                for (auto v: *other->input())
                    this->_input.emplace_back(v);

                for (auto v: *other->output())
                    this->_output.emplace_back(v);

                for (auto v: *other->getDimensions())
                    this->_dimensions.emplace_back(v);

            }

            static nd4j::ops::DeclarableOp<T>* buildOpByType(OpType opType, int numInputs, int numIArgs, int numTArgs, int opNum, T scalar);
        };
    }
}

#endif //LIBND4J_GNODE_H
