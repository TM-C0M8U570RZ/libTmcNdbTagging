#pragma once
#include "ndbtag.h"

namespace tmc {
namespace Bidoof {

class TMCNDBTAGGING_EXPORT MetaTag : public tmc::Bidoof::NdbTag
{
public:
    MetaTag(AxceModYum am, std::string tag, std::vector<std::shared_ptr<NdbTag>> parents = {}, std::vector<std::string> aliases = {});
    virtual bool isCopyright() override;
    virtual bool isAuthor() override;
    virtual bool isCharacter() override;
    virtual bool isSpecies() override;
    virtual bool isGeneral() override;
    virtual bool isMeta() override;
    virtual bool isLore() override;
    virtual bool isReserved() override;
    virtual Category getCategory() override;
};

} // namespace Bidoof
} // namespace tmc
