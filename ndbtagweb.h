#pragma once
#include "TmcNdbTagging_global.h"
#include "ndbtag.h"

namespace tmc {
namespace Bidoof {

class TMCNDBTAGGING_EXPORT NdbTagWeb
{
public:
    NdbTagWeb(std::vector<std::shared_ptr<NdbTag>> topLevel = {});
    NdbTagWeb(std::string filename);
    std::string getFilename();
    std::shared_ptr<NdbTag>& operator[](u64 idx);
    u64 getTopLevelTagCount();
    bool addTopLevelTag(std::shared_ptr<NdbTag> tlt, u64 idx = std::numeric_limits<u64>::max());
    bool containsTopLevelTag(std::string tlts);
    bool containsTagHierarchy(std::string ts);
    bool removeTag(u64 idx);
    bool setTag(std::shared_ptr<NdbTag> tlt, u64 idx);
    void setFilename(std::string filename);
    void writeOut();

private:
    std::vector<std::shared_ptr<NdbTag>> topLevel;
    std::string filename;
};

} // namespace Bidoof
} // namespace tmc
