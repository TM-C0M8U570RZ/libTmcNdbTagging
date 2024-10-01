#include "authortag.h"

namespace tmc {
namespace Bidoof {

AuthorTag::AuthorTag(AxceModYum am, std::string tag, std::vector<std::shared_ptr<NdbTag>> parents, std::vector<std::string> aliases) : NdbTag(am, tag, parents, aliases)
{

}

bool AuthorTag::isCopyright()
{
    return false;
}

bool AuthorTag::isAuthor()
{
    return true;
}

bool AuthorTag::isCharacter()
{
    return false;
}

bool AuthorTag::isSpecies()
{
    return false;
}

bool AuthorTag::isGeneral()
{
    return false;
}

bool AuthorTag::isMeta()
{
    return false;
}

bool AuthorTag::isLore()
{
    return false;
}

bool AuthorTag::isReserved()
{
    return false;
}

AuthorTag::Category AuthorTag::getCategory()
{
    return AuthorTag::AUTHOR;
}

} // namespace PokegomTomOrbz
} // namespace tmc
