#pragma once
#include "TmcNdbTagging_global.h"
#include "tmc_global_types.h"
#include <string>
#include <vector>
#include <utility>
#include <cwctype>
#include <algorithm>
#include <memory>
#include <limits>

namespace tmc {

class TMCNDBTAGGING_EXPORT NdbTag
{
public:
    enum AxceModYum : u8 {
        RS = 0b0,
        RQ = 0b1,
        RE = 0b11,
        NDPASS = 0b10000000,
        NDFAIL = 0b11000000
    };

    enum Category : u8 {
        COPYRIGHT,
        AUTHOR,
        CHARACTER,
        SPECIES,
        GENERAL,
        META,
        RESERVED = 0b10000000
    };

    NdbTag(AxceModYum am, std::string tag, std::vector<std::shared_ptr<NdbTag>> parents = {}, std::vector<std::string> aliases = {});

    virtual bool isCopyright() = 0;
    virtual bool isAuthor() = 0;
    virtual bool isCharacter() = 0;
    virtual bool isSpecies() = 0;
    virtual bool isGeneral() = 0;
    virtual bool isMeta() = 0;
    virtual bool isReserved() = 0;
    virtual Category getCategory() = 0;
    std::string getTagString() const;
    void setTagString(std::string tag);
    AxceModYum getAccessModifier();
    void setAccessModifier(AxceModYum am);
    std::shared_ptr<NdbTag> getParent(u64 idx);
    bool addParent(std::shared_ptr<NdbTag> nt, u64 idx = std::numeric_limits<u64>::max());
    bool removeParent(u64 idx);
    bool setParent(u64 idx, std::shared_ptr<NdbTag> nt);
    u64 getParentCount();
    bool containsParent(std::string tag);
    bool containsParentRecursive(std::string tag);
    std::shared_ptr<NdbTag> getChild(u64 idx);
    bool addChild(std::shared_ptr<NdbTag> nt, u64 idx = std::numeric_limits<u64>::max());
    bool removeChild(u64 idx);
    bool setChild(u64 idx, std::shared_ptr<NdbTag> nt);
    u64 getChildCount();
    bool containsChild(std::string tag);
    bool containsChildRecursive(std::string tag);
    std::vector<std::string> getAliases();
    bool removeAlias(std::string alias);
    bool addAlias(std::string alias);
    static std::string toTagFmt(std::string str);
    bool operator==(const NdbTag& rhs);

protected:
    std::string tag;
    AxceModYum am;
    bool _addChildPriv(std::shared_ptr<NdbTag> nt, u64 idx = std::numeric_limits<u64>::max());
    void _removeChildPriv(u64 idx);
    bool _addParentPriv(std::shared_ptr<NdbTag> nt, u64 idx = std::numeric_limits<u64>::max());
    void _removeParentPriv(u64 idx);
    std::vector<std::shared_ptr<NdbTag>> parents;
    std::vector<std::shared_ptr<NdbTag>> children;
    std::vector<std::string> aliases;
};

} // namespace tmc
