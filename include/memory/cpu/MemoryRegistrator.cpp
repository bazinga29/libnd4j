//
// Created by raver119 on 07.10.2017.
//

#include <memory/MemoryRegistrator.h>

namespace nd4j {
    namespace memory {

        MemoryRegistrator::MemoryRegistrator() {
            _workspace = nullptr;
        };

        MemoryRegistrator* MemoryRegistrator::getInstance() {
            if (_INSTANCE == 0)
                _INSTANCE = new MemoryRegistrator();

            return _INSTANCE;
        }

        bool MemoryRegistrator::hasWorkspaceAttached() {
            return _workspace != nullptr;
        }

        Workspace* MemoryRegistrator::getWorkspace() {
            return _workspace;
        }

        void MemoryRegistrator::attachWorkspace(Workspace* workspace) {
            _workspace = workspace;
        }

        void MemoryRegistrator::forgetWorkspace() {
            _workspace = nullptr;
        }

        void MemoryRegistrator::setGraphMemoryFootprint(Nd4jIndex hash, Nd4jIndex bytes) {
            _lock.lock();
    
            _footprint[hash] = bytes;

            _lock.unlock();
        }

        void MemoryRegistrator::setGraphMemoryFootprintIfGreater(Nd4jIndex hash, Nd4jIndex bytes) {
            _lock.lock();

            if (_footprint.count(hash) == 0)
                _footprint[hash] = bytes;
            else {
                Nd4jIndex cv = _footprint[hash];
                if (bytes > cv)
                    _footprint[hash] = bytes;
            }

            _lock.unlock();
        }

        Nd4jIndex MemoryRegistrator::getGraphMemoryFootprint(Nd4jIndex hash) {
            _lock.lock();
            
            Nd4jIndex result = 0L;
            if (_footprint.count(hash) > 0)
                result = _footprint[hash];
        
            _lock.unlock();

            return result;
        }

        MemoryRegistrator* MemoryRegistrator::_INSTANCE = 0;

    }
}