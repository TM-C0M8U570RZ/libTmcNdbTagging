#include "loretag.h"

namespace tmc {
namespace Bidoof {

LoreTag::LoreTag(AxceModYum am, std::string tag, std::vector<std::shared_ptr<NdbTag>> parents, std::vector<std::string> aliases) : NdbTag(am, tag, parents, aliases)
{

}

bool LoreTag::isCopyright()
{
    return false;
}

bool LoreTag::isAuthor()
{
    return false;
}

bool LoreTag::isCharacter()
{
    return false;
}

bool LoreTag::isSpecies()
{
    return false;
}

bool LoreTag::isGeneral()
{
    return false;
}

bool LoreTag::isMeta()
{
    return false;
}

bool LoreTag::isLore()
{
    return true;
}

bool LoreTag::isReserved()
{
    return false;
}

LoreTag::Category LoreTag::getCategory()
{
    return LoreTag::LORE;
}

} // namespace Bidoof
} // namespace tmc
