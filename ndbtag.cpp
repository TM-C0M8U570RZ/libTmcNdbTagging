#include "ndbtag.h"

namespace tmc {

NdbTag::NdbTag(AxceModYum am, std::string tag, std::vector<NdbTag*> parents, std::vector<std::string> aliases)
{
    this->am = am;
    this->tag = tag;
    this->parents = parents;
    this->aliases = aliases;
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

bool NdbTag::addAlias(std::string alias)
{
    u64 index = aliases.size();
    for (u64 i = 0; i < aliases.size(); i++)
    {
        if (alias == aliases[i])
        {
            index = i;
            break;
        }
    }
    if (index != aliases.size()) return false;
    aliases.push_back(alias);
    return true;
}

bool NdbTag::removeAlias(std::string alias)
{
    u64 index = aliases.size();
    for (u64 i = 0; i < aliases.size(); i++)
    {
        if (alias == aliases[i])
        {
            index = i;
            break;
        }
    }
    if (index == aliases.size()) return false;
    aliases.erase(aliases.begin() + index);
    return true;
}

std::vector<std::string> NdbTag::getAliases()
{
    return aliases;
}

std::string NdbTag::getTagString()
{
    return tag;
}

void NdbTag::setTagString(std::string tag)
{
    this->tag = tag;
}

NdbTag::AxceModYum NdbTag::getAccessModifier()
{
    return am;
}

void NdbTag::setAccessModifier(AxceModYum am)
{
    this->am = am;
}

NdbTag* NdbTag::getParent(u64 idx)
{
    if (idx >= parents.size()) return nullptr;
    return parents[idx];
}

u64 NdbTag::getParentCount()
{
    return parents.size();
}

bool NdbTag::containsParent(std::string tag)
{
    if (getParentCount() == 0) return false;
    for (u64 i = 0; i < parents.size(); i++)
    {
        if (parents[i]->getTagString() == tag) return true;
    }
    return false;
}

bool NdbTag::containsParentRecursive(std::string tag)
{
    if (getParentCount() == 0) return false;
    bool result = false;
    for (u64 i = 0; i < parents.size(); i++)
    {
        if (parents[i]->getTagString() == tag) result = true;
        result = result || (parents[i]->containsParentRecursive(tag));
    }
    return result;
}

bool NdbTag::addParent(NdbTag* nt)
{
    if (containsParentRecursive(nt->getTagString())) return false;
    parents.push_back(std::move(nt));
    return true;
}

bool NdbTag::removeParent(u64 idx)
{
    if (idx >= getParentCount()) return false;
    parents.erase(parents.begin() + idx);
    parents.shrink_to_fit();
    return true;
}

bool NdbTag::setParent(u64 idx, NdbTag* nt)
{
    if (idx >= parents.size() || containsParent(nt->getTagString())) return false;
    parents.erase(parents.begin() + idx);
    parents.shrink_to_fit();
    parents.insert(parents.begin() + idx, std::move(nt));
    return true;
}

u64 NdbTag::getChildCount()
{
    return children.size();
}

NdbTag* NdbTag::getChild(u64 idx)
{
    if (idx >= children.size()) return nullptr;
    return children[idx];
}

} // namespace tmc
