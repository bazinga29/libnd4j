# automatically generated by the FlatBuffers compiler, do not modify

# namespace: graph

import flatbuffers

class FlatResult(object):
    __slots__ = ['_tab']

    @classmethod
    def GetRootAsFlatResult(cls, buf, offset):
        n = flatbuffers.encode.Get(flatbuffers.packer.uoffset, buf, offset)
        x = FlatResult()
        x.Init(buf, n + offset)
        return x

    # FlatResult
    def Init(self, buf, pos):
        self._tab = flatbuffers.table.Table(buf, pos)

    # FlatResult
    def Id(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(4))
        if o != 0:
            return self._tab.Get(flatbuffers.number_types.Int64Flags, o + self._tab.Pos)
        return 0

    # FlatResult
    def Variables(self, j):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(6))
        if o != 0:
            x = self._tab.Vector(o)
            x += flatbuffers.number_types.UOffsetTFlags.py_type(j) * 4
            x = self._tab.Indirect(x)
            from .FlatVariable import FlatVariable
            obj = FlatVariable()
            obj.Init(self._tab.Bytes, x)
            return obj
        return None

    # FlatResult
    def VariablesLength(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(6))
        if o != 0:
            return self._tab.VectorLen(o)
        return 0

    # FlatResult
    def Timing(self, j):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(8))
        if o != 0:
            x = self._tab.Vector(o)
            x += flatbuffers.number_types.UOffsetTFlags.py_type(j) * 4
            x = self._tab.Indirect(x)
            from .FlatTiming import FlatTiming
            obj = FlatTiming()
            obj.Init(self._tab.Bytes, x)
            return obj
        return None

    # FlatResult
    def TimingLength(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(8))
        if o != 0:
            return self._tab.VectorLen(o)
        return 0

    # FlatResult
    def FootprintForward(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(10))
        if o != 0:
            return self._tab.Get(flatbuffers.number_types.Int64Flags, o + self._tab.Pos)
        return 0

    # FlatResult
    def FootprintBackward(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(12))
        if o != 0:
            return self._tab.Get(flatbuffers.number_types.Int64Flags, o + self._tab.Pos)
        return 0

def FlatResultStart(builder): builder.StartObject(5)
def FlatResultAddId(builder, id): builder.PrependInt64Slot(0, id, 0)
def FlatResultAddVariables(builder, variables): builder.PrependUOffsetTRelativeSlot(1, flatbuffers.number_types.UOffsetTFlags.py_type(variables), 0)
def FlatResultStartVariablesVector(builder, numElems): return builder.StartVector(4, numElems, 4)
def FlatResultAddTiming(builder, timing): builder.PrependUOffsetTRelativeSlot(2, flatbuffers.number_types.UOffsetTFlags.py_type(timing), 0)
def FlatResultStartTimingVector(builder, numElems): return builder.StartVector(4, numElems, 4)
def FlatResultAddFootprintForward(builder, footprintForward): builder.PrependInt64Slot(3, footprintForward, 0)
def FlatResultAddFootprintBackward(builder, footprintBackward): builder.PrependInt64Slot(4, footprintBackward, 0)
def FlatResultEnd(builder): return builder.EndObject()
