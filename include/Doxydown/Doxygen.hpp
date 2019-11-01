#pragma once
#include <unordered_map>
#include <string>
#include "Node.hpp"

namespace Doxydown {
    class TextPrinter;

    class Doxygen {
    public:
        Doxygen();

        void load(const std::string& inputDir);
        void finalize(const Config& config, const TextPrinter& plainPrinter, const TextPrinter& markdownPrinter);

        const Node& getIndex() const {
            return *index;
        }

        NodePtr find(const std::string& refid) const;

        const NodeCacheMap& getCache() const {
            return cache;
        }
    private:
        typedef std::unordered_multimap<std::string, std::string> KindRefidMap;

        KindRefidMap getIndexKinds(const std::string& inputDir) const;
        void getIndexCache(NodeCacheMap& cache, const NodePtr& node) const;
        void finalizeRecursively(const Config& config,
                                 const TextPrinter& plainPrinter,
                                 const TextPrinter& markdownPrinter,
                                 const NodePtr& node);
        void updateGroupPointers(const NodePtr& node);

        // The root object that holds everything (index.xml)
        NodePtr index;
        NodeCacheMap cache;
    };
}