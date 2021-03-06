//
//  @author raver119@gmail.com
//

#ifndef ND4J_GRAPH_PROFILE_H
#define ND4J_GRAPH_PROFILE_H

#include "NodeProfile.h"
#include <pointercast.h>
#include <dll.h>
#include <vector>
#include <string>
#include <map>
#include <chrono>

namespace nd4j {
    namespace graph {
        class ND4J_EXPORT GraphProfile {
        private:
            // this variable
            Nd4jIndex _merges = 1L;

            /**
             * This is global memory values
             */
            Nd4jIndex _memoryTotal = 0L;
            Nd4jIndex _memoryActivations = 0L;
            Nd4jIndex _memoryTemporary = 0L;
            Nd4jIndex _memoryObjects = 0L;

            // time spent for graph construction
            Nd4jIndex _buildTime = 0L;

            // time spent for graph execution
            Nd4jIndex _executionTime = 0L;

            // collection of pointers to profile results 
            std::vector<NodeProfile *> _profiles;
            std::map<int, NodeProfile *> _profilesById;

            // collection of various timing reports
            std::map<std::string, Nd4jIndex> _timings;
            std::chrono::time_point<std::chrono::system_clock> _last;

            std::map<std::string, std::chrono::time_point<std::chrono::system_clock>> _timers;

            void updateLast();
        public:
            GraphProfile();
            ~GraphProfile();

            /**
             * These methods just adding amount of bytes to various counters
             */
            void addToTotal(Nd4jIndex bytes);
            void addToActivations(Nd4jIndex bytes);
            void addToTemporary(Nd4jIndex bytes);
            void addToObjects(Nd4jIndex bytes);

            /**
             * This method allows to set graph construction (i.e. deserialization) time in nanoseconds
             */
            void setBuildTime(Nd4jIndex nanos);

            /**
             * This method sets graph execution time in nanoseconds.
             */
            void setExecutionTime(Nd4jIndex nanos);

            void startEvent(const char *name);
            void recordEvent(const char *name);
            void deleteEvent(const char *name);

            /**
             * This method saves time as delta from last saved time
             */
            void spotEvent(const char *name);

            /**
             * This method returns pointer to NodeProfile by ID
             * PLEASE NOTE: this method will create new NodeProfile if there's none
             */
            NodeProfile* nodeById(int id, const char *name = nullptr);
            bool nodeExists(int id);

            /**
             * This method merges values from other profile report
             * @param other
             */
            void merge(GraphProfile *other);
            void assign(GraphProfile *other);

            /**
             * These methods are just utility methods for time
             */
            static Nd4jIndex currentTime();
            static Nd4jIndex relativeTime(Nd4jIndex time);

            void printOut();
        };
    }
}

#endif