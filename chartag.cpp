#include "chartag.h"

namespace tmc {
namespace Bidoof {

CharTag::CharTag(AxceModYum am, std::string tag, std::vector<std::shared_ptr<NdbTag>> parents, std::vector<std::string> aliases) : NdbTag(am, tag, parents, aliases)
{

}

bool CharTag::isCopyright()
{
    return false;
}

bool CharTag::isAuthor()
{
    return false;
}

bool CharTag::isCharacter()
{
    return true;
}

bool CharTag::isSpecies()
{
    return false;
}

bool CharTag::isGeneral()
{
    return false;
}

bool CharTag::isMeta()
{
    return false;
}

bool CharTag::isLore()
{
    return false;
}

bool CharTag::isReserved()
{
    return false;
}

CharTag::Category CharTag::getCategory()
{
    return CharTag::CHARACTER;
}

} // namespace Bidoof
} // namespace tmc
