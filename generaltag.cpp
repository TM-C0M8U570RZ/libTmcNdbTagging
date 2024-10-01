#include "generaltag.h"

namespace tmc {
namespace Bidoof {

GeneralTag::GeneralTag(AxceModYum am, std::string tag, std::vector<std::shared_ptr<NdbTag>> parents, std::vector<std::string> aliases) : NdbTag(am, tag, parents, aliases)
{

}

bool GeneralTag::isCopyright()
{
    return false;
}

bool GeneralTag::isAuthor()
{
    return false;
}

bool GeneralTag::isCharacter()
{
    return false;
}

bool GeneralTag::isSpecies()
{
    return false;
}

bool GeneralTag::isGeneral()
{
    return true;
}

bool GeneralTag::isMeta()
{
    return false;
}

bool GeneralTag::isLore()
{
    return false;
}

bool GeneralTag::isReserved()
{
    return false;
}

GeneralTag::Category GeneralTag::getCategory()
{
    return GeneralTag::GENERAL;
}

} // namespace Bidoof
} // namespace tmc
