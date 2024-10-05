#pragma once
#include "TmcNdbTagging_global.h"
#include "authortag.h"
#include "chartag.h"
#include "copywrongtag.h"
#include "generaltag.h"
#include "loretag.h"
#include "metatag.h"
#include "reservedndbtag.h"
#include "speciestag.h"
#include <fstream>
#include <utility>
#include <sstream>
#include <map>
#include <set>

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
    bool removeTopLevelTag(u64 idx);
    bool setTopLevelTag(std::shared_ptr<NdbTag> tlt, u64 idx);
    std::multimap<std::string, bool> globuleToSearchCriteria(std::string globule);
    std::string findFromAlias(std::string alias);
    std::set<std::string> findFromWildcard(std::string wildcard);
    void setFilename(std::string filename);
    void writeOut();

private:
    std::vector<std::shared_ptr<NdbTag>> topLevel;
    std::string filename;
    u64 byteVecToU64(std::vector<char> bVec);
    std::vector<std::shared_ptr<NdbTag>> connectHierarchy(std::vector<std::shared_ptr<NdbTag>> topLevel, std::vector<std::shared_ptr<NdbTag>> subTags, std::vector<std::pair<std::string, std::vector<std::string>>> lossChunks);
    std::vector<char> pushMagic(std::vector<char> buf, u8 vMaj, u8 vMin, u8 vPch);
    std::vector<char> pushU64(std::vector<char> buf, u64 qWord);
    std::vector<char> pushMeta(std::vector<char> buf, NdbTag::AxceModYum am, NdbTag::Category cat);
    std::vector<char> pushString(std::vector<char> buf, std::string str);
    std::vector<char> pushStringArray(std::vector<char> buf, std::vector<std::string> strArr);
    std::vector<char> pushHierarchy(std::vector<char> buf, std::vector<std::shared_ptr<NdbTag>> subTags);
    std::string _findFromAlias(std::string alias, std::vector<std::shared_ptr<NdbTag>> web);
    std::set<std::string> _findFromWildcard(std::string wildcard, std::vector<std::shared_ptr<NdbTag>> web);
    std::set<std::string> appendSet(std::set<std::string> s1, std::set<std::string> s2);
    bool alreadyFound;
    std::vector<std::string> alreadyPushed;

};

} // namespace Bidoof
} // namespace tmc
