#include "ndbtag.h"

namespace tmc {

NdbTag::NdbTag(AxceModYum am, std::string tag, std::vector<std::shared_ptr<NdbTag>> parents, std::vector<std::string> aliases)
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

std::shared_ptr<NdbTag> NdbTag::getParent(u64 idx)
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

bool NdbTag::addParent(std::shared_ptr<NdbTag> nt, u64 idx)
{
    if (containsParentRecursive(nt->getTagString()) || (idx > parents.size() && idx != std::numeric_limits<u64>::max())) return false;
    if (parents.size() == 0) nt->_addChildPriv(std::shared_ptr<NdbTag>(this));
    else
    {
        for (u64 i = 0; i < parents[0]->getChildCount(); i++)
        {
            if (*(parents[0]->getChild(i)) == *(this))
            {
                nt->_addChildPriv(parents[0]->getChild(i));
                break;
            }
        }
    }
    if (idx == std::numeric_limits<u64>::max()) parents.push_back(nt);
    else parents.insert(parents.begin() + idx, nt);
    return true;
}

bool NdbTag::removeParent(u64 idx)
{
    if (idx >= getParentCount()) return false;
    for (u64 i = 0; i < parents[idx]->getChildCount(); i++)
    {
        if (*(parents[idx]->getChild(i)) == *(this)) parents[idx]->_removeChildPriv(i);
    }
    parents.erase(parents.begin() + idx);
    return true;
}

bool NdbTag::setParent(u64 idx, std::shared_ptr<NdbTag> nt)
{
    if (!removeParent(idx) || containsParentRecursive(nt->getTagString())) return false;
    addParent(nt, idx);
    return true;
}

u64 NdbTag::getChildCount()
{
    return children.size();
}

std::shared_ptr<NdbTag> NdbTag::getChild(u64 idx)
{
    if (idx >= children.size()) return nullptr;
    return children[idx];
}

bool NdbTag::containsChild(std::string tag)
{
    if (children.size() == 0) return false;
    for (u64 i = 0; i < children.size(); i++)
    {
        if (children[i]->getTagString() == tag) return true;
    }
    return false;
}

bool NdbTag::containsChildRecursive(std::string tag)
{
    if (children.size() == 0) return false;
    bool result = false;
    for (u64 i = 0; i < children.size(); i++)
    {
        if (children[i]->getTagString() == tag) result = true;
        result = result || (children[i]->containsChildRecursive(tag));
    }
    return result;
}

bool NdbTag::_addChildPriv(std::shared_ptr<NdbTag> nt, u64 idx)
{
    if (idx > children.size() && idx != std::numeric_limits<u64>::max()) return false;
    if (idx == std::numeric_limits<u64>::max()) children.push_back(nt);
    else children.insert(children.begin() + idx, nt);
    return true;
}

void NdbTag::_removeChildPriv(u64 idx)
{
    children.erase(children.begin() + idx);
}

bool NdbTag::_addParentPriv(std::shared_ptr<NdbTag> nt, u64 idx)
{
    if (idx > parents.size() && idx != std::numeric_limits<u64>::max()) return false;
    if (idx == std::numeric_limits<u64>::max()) parents.push_back(nt);
    else parents.insert(parents.begin() + idx, nt);
    return true;
}

void NdbTag::_removeParentPriv(u64 idx)
{
    parents.erase(parents.begin() + idx);
}

bool NdbTag::operator==(const NdbTag& rhs)
{
    return (this->getTagString() == rhs.getTagString());
}

bool NdbTag::addChild(std::shared_ptr<NdbTag> nt, u64 idx)
{
    if (containsChildRecursive(nt->getTagString()) || (idx > children.size() && idx != std::numeric_limits<u64>::max())) return false;
    if (children.size() == 0) nt->_addParentPriv(std::shared_ptr<NdbTag>(this));
    else
    {
        for (u64 i = 0; i < children[0]->getParentCount(); i++)
        {
            if (*(children[0]->getParent(i)) == *(this))
            {
                nt->_addParentPriv(children[0]->getParent(i));
                break;
            }
        }
    }
    if (idx == std::numeric_limits<u64>::max()) children.push_back(nt);
    else children.insert(children.begin() + idx, nt);
    return true;
}

bool NdbTag::removeChild(u64 idx)
{
    if (idx >= getChildCount()) return false;
    for (u64 i = 0; i < children[idx]->getParentCount(); i++)
    {
        if (*(children[idx]->getParent(i)) == *(this)) children[idx]->_removeParentPriv(i);
    }
    children.erase(children.begin() + idx);
    return true;
}

bool NdbTag::setChild(u64 idx, std::shared_ptr<NdbTag> nt)
{
    if (!removeChild(idx) || containsChildRecursive(nt->getTagString())) return false;
    addChild(nt, idx);
    return true;
}

} // namespace tmc
