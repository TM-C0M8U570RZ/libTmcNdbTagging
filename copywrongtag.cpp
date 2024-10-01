#include "copywrongtag.h"

namespace tmc {
namespace Bidoof {

CopywrongTag::CopywrongTag(AxceModYum am, std::string tag, std::vector<std::shared_ptr<NdbTag>> parents, std::vector<std::string> aliases) : NdbTag(am, tag, parents, aliases)
{

}

bool CopywrongTag::isCopyright()
{
    return true;
}

bool CopywrongTag::isAuthor()
{
    return false;
}

bool CopywrongTag::isCharacter()
{
    return false;
}

bool CopywrongTag::isSpecies()
{
    return false;
}

bool CopywrongTag::isGeneral()
{
    return false;
}

bool CopywrongTag::isMeta()
{
    return false;
}

bool CopywrongTag::isLore()
{
    return false;
}

bool CopywrongTag::isReserved()
{
    return false;
}

CopywrongTag::Category CopywrongTag::getCategory()
{
    return CopywrongTag::COPYRIGHT;
}

} // namespace PokegomTomOrbz
} // namespace tmc
