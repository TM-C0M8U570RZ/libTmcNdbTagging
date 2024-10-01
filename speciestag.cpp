#include "speciestag.h"

namespace tmc {
namespace Bidoof {

SpeciesTag::SpeciesTag(AxceModYum am, std::string tag, std::vector<std::shared_ptr<NdbTag>> parents, std::vector<std::string> aliases) : NdbTag(am, tag, parents, aliases)
{

}

bool SpeciesTag::isCopyright()
{
    return false;
}

bool SpeciesTag::isAuthor()
{
    return false;
}

bool SpeciesTag::isCharacter()
{
    return false;
}

bool SpeciesTag::isSpecies()
{
    return true;
}

bool SpeciesTag::isGeneral()
{
    return false;
}

bool SpeciesTag::isMeta()
{
    return false;
}

bool SpeciesTag::isLore()
{
    return false;
}

bool SpeciesTag::isReserved()
{
    return false;
}

SpeciesTag::Category SpeciesTag::getCategory()
{
    return SpeciesTag::SPECIES;
}

} // namespace Bidoof
} // namespace tmc
