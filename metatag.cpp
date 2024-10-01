#include "metatag.h"

namespace tmc {
namespace Bidoof {

MetaTag::MetaTag(AxceModYum am, std::string tag, std::vector<std::shared_ptr<NdbTag>> parents, std::vector<std::string> aliases) : NdbTag(am, tag, parents, aliases)
{

}

bool MetaTag::isCopyright()
{
    return false;
}

bool MetaTag::isAuthor()
{
    return false;
}

bool MetaTag::isCharacter()
{
    return false;
}

bool MetaTag::isSpecies()
{
    return false;
}

bool MetaTag::isGeneral()
{
    return false;
}

bool MetaTag::isMeta()
{
    return true;
}

bool MetaTag::isLore()
{
    return false;
}

bool MetaTag::isReserved()
{
    return false;
}

MetaTag::Category MetaTag::getCategory()
{
    return MetaTag::META;
}

} // namespace Bidoof
} // namespace tmc
