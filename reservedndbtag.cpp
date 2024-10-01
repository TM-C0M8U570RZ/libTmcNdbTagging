#include "reservedndbtag.h"

namespace tmc {
namespace Bidoof {

ReservedNdbTag::ReservedNdbTag(AxceModYum am, std::string tag, std::vector<std::shared_ptr<NdbTag>> parents, std::vector<std::string> aliases) : NdbTag(am, tag, parents, aliases)
{

}

bool ReservedNdbTag::isCopyright()
{
    return false;
}

bool ReservedNdbTag::isAuthor()
{
    return false;
}

bool ReservedNdbTag::isCharacter()
{
    return false;
}

bool ReservedNdbTag::isSpecies()
{
    return false;
}

bool ReservedNdbTag::isGeneral()
{
    return false;
}

bool ReservedNdbTag::isMeta()
{
    return true;
}

bool ReservedNdbTag::isLore()
{
    return false;
}

bool ReservedNdbTag::isReserved()
{
    return true;
}

ReservedNdbTag::Category ReservedNdbTag::getCategory()
{
    return static_cast<Category>(ReservedNdbTag::META | ReservedNdbTag::RESERVED);
}

} // namespace Bidoof
} // namespace tmc
