#pragma once
#include "TmcNdbTagging_global.h"
#include "tmc_global_types.h"
#include <string>
#include <vector>
#include <utility>
#include <cwctype>
#include <algorithm>

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

    NdbTag(AxceModYum am, std::string tag, std::vector<NdbTag*> parents = {}, std::vector<std::string> aliases = {});

    virtual bool isCopyright() = 0;
    virtual bool isAuthor() = 0;
    virtual bool isCharacter() = 0;
    virtual bool isSpecies() = 0;
    virtual bool isGeneral() = 0;
    virtual bool isMeta() = 0;
    virtual bool isReserved() = 0;
    virtual Category getCategory() = 0;
    std::string getTagString();
    void setTagString(std::string tag);
    AxceModYum getAccessModifier();
    void setAccessModifier(AxceModYum am);
    NdbTag* getParent(u64 idx);
    // add/set functions for parents/children call std::move
    bool addParent(NdbTag* nt);
    bool removeParent(u64 idx);
    bool setParent(u64 idx, NdbTag* nt);
    u64 getParentCount();
    bool containsParent(std::string tag);
    bool containsParentRecursive(std::string tag);
    NdbTag* getChild(u64 idx);
    bool addChild(NdbTag* nt);
    bool removeChild(u64 idx);
    bool setChild(u64 idx, NdbTag* nt);
    u64 getChildCount();
    bool containsChild(std::string tag);
    bool containsChildRecursive(std::string tag);
    std::vector<std::string> getAliases();
    bool removeAlias(std::string alias);
    bool addAlias(std::string alias);
    static std::string toTagFmt(std::string str);

protected:
    std::string tag;
    AxceModYum am;
    std::vector<NdbTag*> parents;
    std::vector<NdbTag*> children;
    std::vector<std::string> aliases;
};

} // namespace tmc
