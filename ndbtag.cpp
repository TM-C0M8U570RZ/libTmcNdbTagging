#include "ndbtag.h"

namespace tmc {

NdbTag::NdbTag(AxceModYum am, std::string tag, std::vector<NdbTag*> parents, std::vector<std::string> aliases)
{

}

std::string NdbTag::toTagFmt(std::string str)
{
    std::wstring ws(str.begin(), str.end());
    std::transform(ws.begin(), ws.end(), ws.begin(), [](uchr c){ return towlower(c); });
    std::size_t found = ws.find(L' ');
    while (found != std::wstring::npos)
    {
        ws.replace(found, 1, 1, L'_');
    }
    return std::string(ws.begin(), ws.end());
}

} // namespace tmc
