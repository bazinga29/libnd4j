//
// @author raver119@gmail.com
//

#ifndef LIBND4J_VARIABLETESTS_H
#define LIBND4J_VARIABLETESTS_H

#include "testlayers.h"
#include <NDArray.h>
#include <graph/Variable.h>
#include <flatbuffers/flatbuffers.h>
#include <NDArrayFactory.h>

using namespace nd4j;
using namespace nd4j::graph;

class VariableTests : public testing::Test {
public:

};

TEST_F(VariableTests, TestClone_1) {
    auto array1 = new NDArray<float>('c', {5, 5});
    array1->assign(1.0);

    auto var1 = new Variable<float>(array1, "alpha");
    var1->setId(119);


    auto var2 = var1->clone();

    ASSERT_FALSE(var1->getNDArray() == var2->getNDArray());
    auto array2 = var2->getNDArray();

    ASSERT_TRUE(array1->equalsTo(array2));
    ASSERT_EQ(var1->id(), var2->id());
    ASSERT_EQ(*var1->getName(), *var2->getName());

    delete var1;

    std::string str("alpha");
    ASSERT_EQ(*var2->getName(), str);
    array2->assign(2.0);

    ASSERT_NEAR(2.0, array2->meanNumber(), 1e-5);

    delete var2;
}

TEST_F(VariableTests, Test_FlatVariableDataType_1) {
    flatbuffers::FlatBufferBuilder builder(1024);
    NDArray<float> original('c', {5, 10});
    NDArrayFactory<float>::linspace(1, original);

    auto vec = original.asByteVector();

    auto fShape = builder.CreateVector(original.getShapeInfoAsVector());
    auto fBuffer = builder.CreateVector(vec);
    auto fVid = CreateIntPair(builder, 1, 12);

    auto fArray = CreateFlatArray(builder, fShape, fBuffer, nd4j::graph::DataType::DataType_FLOAT);

    auto flatVar = CreateFlatVariable(builder, fVid, 0, 0, fArray);

    builder.Finish(flatVar);

    auto ptr = builder.GetBufferPointer();

    auto restoredVar = GetFlatVariable(ptr);

    auto rv = new Variable<float>(restoredVar);

    ASSERT_EQ(1, rv->id());
    ASSERT_EQ(12, rv->index());

    auto restoredArray = rv->getNDArray();

    ASSERT_TRUE(original.isSameShape(restoredArray));
    ASSERT_TRUE(original.equalsTo(restoredArray));

    delete rv;
}

TEST_F(VariableTests, Test_FlatVariableDataType_2) {
    flatbuffers::FlatBufferBuilder builder(1024);
    NDArray<double> original('c', {5, 10});
    NDArrayFactory<double>::linspace(1, original);

    auto vec = original.asByteVector();

    auto fShape = builder.CreateVector(original.getShapeInfoAsVector());
    auto fBuffer = builder.CreateVector(vec);
    auto fVid = CreateIntPair(builder, 1, 12);

    auto fArray = CreateFlatArray(builder, fShape, fBuffer, nd4j::graph::DataType::DataType_DOUBLE);

    auto flatVar = CreateFlatVariable(builder, fVid, 0, 0, fArray);

    builder.Finish(flatVar);

    auto ptr = builder.GetBufferPointer();

    auto restoredVar = GetFlatVariable(ptr);

    auto rv = new Variable<double>(restoredVar);

    ASSERT_EQ(1, rv->id());
    ASSERT_EQ(12, rv->index());

    auto restoredArray = rv->getNDArray();

    ASSERT_TRUE(original.isSameShape(restoredArray));
    ASSERT_TRUE(original.equalsTo(restoredArray));

    delete rv;
}


TEST_F(VariableTests, Test_FlatVariableDataType_3) {
    flatbuffers::FlatBufferBuilder builder(1024);
    NDArray<double> original('c', {5, 10});
    NDArray<float> floating('c', {5, 10});
    NDArrayFactory<double>::linspace(1, original);
    NDArrayFactory<float>::linspace(1, floating);

    auto vec = original.asByteVector();

    auto fShape = builder.CreateVector(original.getShapeInfoAsVector());
    auto fBuffer = builder.CreateVector(vec);
    auto fVid = CreateIntPair(builder, 1, 12);

    auto fArray = CreateFlatArray(builder, fShape, fBuffer, nd4j::graph::DataType::DataType_DOUBLE);

    auto flatVar = CreateFlatVariable(builder, fVid, 0, 0, fArray);

    builder.Finish(flatVar);

    auto ptr = builder.GetBufferPointer();

    auto restoredVar = GetFlatVariable(ptr);

    auto rv = new Variable<float>(restoredVar);

    ASSERT_EQ(1, rv->id());
    ASSERT_EQ(12, rv->index());

    auto restoredArray = rv->getNDArray();

    ASSERT_TRUE(floating.isSameShape(restoredArray));
    ASSERT_TRUE(floating.equalsTo(restoredArray));

    delete rv;
}


TEST_F(VariableTests, Test_FlatVariableDataType_4) {
    flatbuffers::FlatBufferBuilder builder(1024);
    NDArray<float> original('c', {5, 10});


    auto vec = original.asByteVector();

    auto fShape = builder.CreateVector(original.getShapeInfoAsVector());
    auto fVid = CreateIntPair(builder, 37, 12);

    auto flatVar = CreateFlatVariable(builder, fVid, 0, fShape, 0);

    builder.Finish(flatVar);

    auto ptr = builder.GetBufferPointer();

    auto restoredVar = GetFlatVariable(ptr);

    auto rv = new Variable<float>(restoredVar);

    ASSERT_EQ(37, rv->id());
    ASSERT_EQ(12, rv->index());

    auto restoredArray = rv->getNDArray();

    ASSERT_TRUE(original.isSameShape(restoredArray));
    ASSERT_TRUE(original.equalsTo(restoredArray));

    delete rv;
}

TEST_F(VariableTests, Test_Dtype_Conversion_1) {
    auto x = new NDArray<float>('c', {2, 3}, {1, 2, 3, 4, 5, 6});
    Variable<float> v(x, "alpha", 12, 3);

    auto vd = v.template asT<double>();
    auto vf = vd->template asT<float>();

    ASSERT_EQ(*v.getName(), *vf->getName());
    ASSERT_EQ(v.id(), vf->id());
    ASSERT_EQ(v.index(), vf->index());

    auto xf = vf->getNDArray();

    ASSERT_TRUE(x->isSameShape(xf));
    ASSERT_TRUE(x->equalsTo(xf));

    delete vd;
    delete vf;
}

#endif //LIBND4J_VARIABLETESTS_H
