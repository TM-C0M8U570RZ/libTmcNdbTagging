#include "ndbtagweb.h"
#include <iostream>

namespace tmc {
namespace Bidoof {

NdbTagWeb::NdbTagWeb(std::vector<std::shared_ptr<NdbTag>> topLevel) {
    found = nullptr;
    this->topLevel = topLevel;
    this->filename = "";
    alreadyFound = false;
}

NdbTagWeb::NdbTagWeb(std::string filename)
{
    found = nullptr;
    this->filename = filename;
    alreadyFound = false;
    std::ifstream in(filename, std::ios::binary);
    if (in.is_open())
    {
        in.seekg(8);
        std::vector<char> temp(8);
        in.read(temp.data(), 8);
        u64 topLevelCount = byteVecToU64(temp);
        std::vector<std::pair<std::string, std::vector<std::string>>> lossChunks;
        for (u64 i = 0; i < topLevelCount; i++)
        {
            in.read(temp.data(), 8);
            std::string tagStr = "";
            u64 counter = 0;
            while(in.peek() != 0) tagStr += in.get();
            in.seekg(1 + in.tellg());
            std::pair<std::string, std::vector<std::string>> knuts;
            knuts.first = tagStr;
            knuts.second = std::vector<std::string>();
            counter += tagStr.size() + 1;
            while (counter % 8 != 0)
            {
                counter++;
                in.seekg(1 + in.tellg());
            }
            NdbTag::AxceModYum am = static_cast<NdbTag::AxceModYum>(in.get());
            NdbTag::Category cat = static_cast<NdbTag::Category>(in.get());
            counter += 8;
            in.seekg(6 + in.tellg());
            in.read(temp.data(), temp.size());
            counter += 8;
            u64 aliasCount = byteVecToU64(temp);
            std::vector<std::string> aliases;
            for (u64 j = 0; j < aliasCount; j++)
            {
                aliases.push_back("");
                while (in.peek() != 0)
                {
                    aliases[j] += in.get();
                    counter++;
                }
                in.seekg(1 + in.tellg());
                counter++;
            }
            while (counter % 8 != 0)
            {
                counter++;
                in.seekg(1 + in.tellg());
            }
            in.read(temp.data(), temp.size());
            counter += 8;
            u64 childCount = byteVecToU64(temp);
            std::vector<std::string> children;
            for (u64 j = 0; j < childCount; j++)
            {
                children.push_back("");
                while (in.peek() != 0)
                {
                    children[j] += in.get();
                    counter++;
                }
                knuts.second.push_back(children[j]);
                in.seekg(1 + in.tellg());
                counter++;
            }
            lossChunks.push_back(knuts);
            while (counter % 8 != 0)
            {
                counter++;
                in.seekg(1 + in.tellg());
            }
            if (cat == NdbTag::COPYRIGHT) topLevel.push_back(std::make_shared<CopywrongTag>(am, tagStr, std::vector<std::shared_ptr<NdbTag>>(), aliases));
            else if (cat == NdbTag::AUTHOR) topLevel.push_back(std::make_shared<AuthorTag>(am, tagStr, std::vector<std::shared_ptr<NdbTag>>(), aliases));
            else if (cat == NdbTag::CHARACTER) topLevel.push_back(std::make_shared<CharTag>(am, tagStr, std::vector<std::shared_ptr<NdbTag>>(), aliases));
            else if (cat == NdbTag::SPECIES) topLevel.push_back(std::make_shared<SpeciesTag>(am, tagStr, std::vector<std::shared_ptr<NdbTag>>(), aliases));
            else if (cat == NdbTag::GENERAL) topLevel.push_back(std::make_shared<GeneralTag>(am, tagStr, std::vector<std::shared_ptr<NdbTag>>(), aliases));
            else if (cat == NdbTag::META) topLevel.push_back(std::make_shared<MetaTag>(am, tagStr, std::vector<std::shared_ptr<NdbTag>>(), aliases));
            else if (cat == NdbTag::LORE) topLevel.push_back(std::make_shared<LoreTag>(am, tagStr, std::vector<std::shared_ptr<NdbTag>>(), aliases));
            else if (cat == static_cast<NdbTag::Category>(NdbTag::META | NdbTag::RESERVED)) topLevel.push_back(std::make_shared<ReservedNdbTag>(am, tagStr, std::vector<std::shared_ptr<NdbTag>>(), aliases));
        }
        std::vector<std::shared_ptr<NdbTag>> subTags;
        while (in.peek() != std::ifstream::traits_type::eof())
        {
            in.read(temp.data(), 8);
            std::string tagStr = "";
            u64 counter = 0;
            while(in.peek() != 0) tagStr += in.get();
            in.seekg(1 + in.tellg());
            counter += tagStr.size() + 1;
            std::pair<std::string, std::vector<std::string>> knuts;
            knuts.first = tagStr;
            knuts.second = std::vector<std::string>();
            while (counter % 8 != 0)
            {
                counter++;
                in.seekg(1 + in.tellg());
            }
            NdbTag::AxceModYum am = static_cast<NdbTag::AxceModYum>(in.get());
            NdbTag::Category cat = static_cast<NdbTag::Category>(in.get());
            counter += 8;
            in.seekg(6 + in.tellg());
            in.read(temp.data(), temp.size());
            counter += 8;
            u64 parentCount = byteVecToU64(temp);
            std::vector<std::string> parents;
            for (u64 i = 0; i < parentCount; i++)
            {
                parents.push_back("");
                while (in.peek() != 0)
                {
                    parents[i] += in.get();
                    counter++;
                }
                in.seekg(1 + in.tellg());
                counter++;
            }
            while (counter % 8 != 0)
            {
                counter++;
                in.seekg(1 + in.tellg());
            }
            in.read(temp.data(), temp.size());
            counter += 8;
            u64 aliasCount = byteVecToU64(temp);
            std::vector<std::string> aliases;
            for (u64 i = 0; i < aliasCount; i++)
            {
                aliases.push_back("");
                while (in.peek() != 0)
                {
                    aliases[i] += in.get();
                    counter++;
                }
                in.seekg(1 + in.tellg());
                counter++;
            }
            while (counter % 8 != 0)
            {
                counter++;
                in.seekg(1 + in.tellg());
            }
            in.read(temp.data(), temp.size());
            counter += 8;
            u64 childCount = byteVecToU64(temp);
            std::vector<std::string> children;
            for (u64 i = 0; i < childCount; i++)
            {
                children.push_back("");
                while (in.peek() != 0)
                {
                    children[i] += in.get();
                    counter++;
                }
                knuts.second.push_back(children[i]);
                in.seekg(1 + in.tellg());
                counter++;
            }
            lossChunks.push_back(knuts);
            while (counter % 8 != 0)
            {
                counter++;
                in.seekg(1 + in.tellg());
            }
            if (cat == NdbTag::COPYRIGHT) topLevel.push_back(std::make_shared<CopywrongTag>(am, tagStr, std::vector<std::shared_ptr<NdbTag>>(), aliases));
            else if (cat == NdbTag::AUTHOR) topLevel.push_back(std::make_shared<AuthorTag>(am, tagStr, std::vector<std::shared_ptr<NdbTag>>(), aliases));
            else if (cat == NdbTag::CHARACTER) topLevel.push_back(std::make_shared<CharTag>(am, tagStr, std::vector<std::shared_ptr<NdbTag>>(), aliases));
            else if (cat == NdbTag::SPECIES) topLevel.push_back(std::make_shared<SpeciesTag>(am, tagStr, std::vector<std::shared_ptr<NdbTag>>(), aliases));
            else if (cat == NdbTag::GENERAL) topLevel.push_back(std::make_shared<GeneralTag>(am, tagStr, std::vector<std::shared_ptr<NdbTag>>(), aliases));
            else if (cat == NdbTag::META) topLevel.push_back(std::make_shared<MetaTag>(am, tagStr, std::vector<std::shared_ptr<NdbTag>>(), aliases));
            else if (cat == NdbTag::LORE) topLevel.push_back(std::make_shared<LoreTag>(am, tagStr, std::vector<std::shared_ptr<NdbTag>>(), aliases));
            else if (cat == static_cast<NdbTag::Category>(NdbTag::META | NdbTag::RESERVED)) topLevel.push_back(std::make_shared<ReservedNdbTag>(am, tagStr, std::vector<std::shared_ptr<NdbTag>>(), aliases));
        }
        in.close();
        for (u64 i = 0; i < lossChunks.size(); i++)
        {
            for (u64 j = 0; j < lossChunks[i].second.size(); j++)
            {
                operator[](lossChunks[i].first)->addChild(operator[](lossChunks[i].second[j]));
            }
        }
//        topLevel = connectHierarchy(topLevel, subTags, lossChunks);
    }
}

NdbTagWeb::NdbTagWeb(std::vector<char> buf)
{
    found = nullptr;
    this->filename = "";
    alreadyFound = false;
    std::vector<char> temp;
    for (u8 i = 8; i < 16; i++)
    {
        temp.push_back(buf[i]);
    }
    u64 topLevelCount = byteVecToU64(temp);
    u64 offset = 24;
    std::vector<std::pair<std::string, std::vector<std::string>>> lossChunks;
    while (topLevel.size() < topLevelCount)
    {
        std::string tagStr;
        while (buf[offset] != '\0')
        {
            tagStr += buf[offset];
            offset++;
        }
        offset++;
        std::pair<std::string, std::vector<std::string>> knuts;
        knuts.first = tagStr;
        knuts.second = std::vector<std::string>();
        while (offset % 8 != 0)
        {
            offset++;
        }
        NdbTag::AxceModYum am = static_cast<NdbTag::AxceModYum>(buf[offset]);
        offset++;
        NdbTag::Category cat = static_cast<NdbTag::Category>(buf[offset]);
        offset+= 7;
        u64 oofset = offset + 8;
        for (u64 i = offset; i < oofset; i++)
        {
            temp[i - offset] = buf[i];
        }
        offset += 8;
        u64 aliasCount = byteVecToU64(temp);
        std::vector<std::string> aliases;
        while (aliases.size() < aliasCount)
        {
            std::string alias;
            while (buf[offset] != '\0')
            {
                alias += buf[offset];
                offset++;
            }
            offset++;
            aliases.push_back(alias);
        }
        while (offset % 8 != 0)
        {
            offset++;
        }
        oofset = offset + 8;
        for (u64 i = offset; i < oofset; i++)
        {
            temp[i - offset] = buf[i];
        }
        u64 childCount = byteVecToU64(temp);
        offset += 8;
        while (knuts.second.size() < childCount)
        {
            std::string child;
            while (buf[offset] != '\0')
            {
                child += buf[offset];
                offset++;
            }
            offset++;
            knuts.second.push_back(child);
        }
        lossChunks.push_back(knuts);
        while (offset % 8 != 0)
        {
            offset++;
        }
        offset += 8;
        if (cat == NdbTag::COPYRIGHT) topLevel.push_back(std::make_shared<CopywrongTag>(am, tagStr, std::vector<std::shared_ptr<NdbTag>>(), aliases));
        else if (cat == NdbTag::AUTHOR) topLevel.push_back(std::make_shared<AuthorTag>(am, tagStr, std::vector<std::shared_ptr<NdbTag>>(), aliases));
        else if (cat == NdbTag::CHARACTER) topLevel.push_back(std::make_shared<CharTag>(am, tagStr, std::vector<std::shared_ptr<NdbTag>>(), aliases));
        else if (cat == NdbTag::SPECIES) topLevel.push_back(std::make_shared<SpeciesTag>(am, tagStr, std::vector<std::shared_ptr<NdbTag>>(), aliases));
        else if (cat == NdbTag::GENERAL) topLevel.push_back(std::make_shared<GeneralTag>(am, tagStr, std::vector<std::shared_ptr<NdbTag>>(), aliases));
        else if (cat == NdbTag::META) topLevel.push_back(std::make_shared<MetaTag>(am, tagStr, std::vector<std::shared_ptr<NdbTag>>(), aliases));
        else if (cat == NdbTag::LORE) topLevel.push_back(std::make_shared<LoreTag>(am, tagStr, std::vector<std::shared_ptr<NdbTag>>(), aliases));
        else if (cat == static_cast<NdbTag::Category>(NdbTag::META | NdbTag::RESERVED)) topLevel.push_back(std::make_shared<ReservedNdbTag>(am, tagStr, std::vector<std::shared_ptr<NdbTag>>(), aliases));
    }
    std::vector<std::shared_ptr<NdbTag>> subTags;
    while(offset < buf.size())
    {
        std::string tagStr;
        while (buf[offset] != '\0')
        {
            tagStr += buf[offset];
            offset++;
        }
        offset++;
        std::pair<std::string, std::vector<std::string>> knuts;
        knuts.first = tagStr;
        knuts.second = std::vector<std::string>();
        while (offset % 8 != 0)
        {
            offset++;
        }
        NdbTag::AxceModYum am = static_cast<NdbTag::AxceModYum>(buf[offset]);
        offset++;
        NdbTag::Category cat = static_cast<NdbTag::Category>(buf[offset]);
        offset+= 7;
        u64 oofset = offset + 8;
        for (u64 i = offset; i < oofset; i++)
        {
            temp[i - offset] = buf[i];
        }
        offset += 8;
        u64 parentCount = byteVecToU64(temp);
        std::vector<std::string> parents;
        while (parents.size() < parentCount)
        {
            std::string parent;
            while (buf[offset] != '\0')
            {
                parent += buf[offset];
                offset++;
            }
            offset++;
            parents.push_back(parent);
        }
        while (offset % 8 != 0)
        {
            offset++;
        }
        oofset = offset + 8;
        for (u64 i = offset; i < oofset; i++)
        {
            temp[i - offset] = buf[i];
        }
        offset += 8;
        u64 aliasCount = byteVecToU64(temp);
        std::vector<std::string> aliases;
        while (aliases.size() < aliasCount)
        {
            std::string alias;
            while (buf[offset] != '\0')
            {
                alias += buf[offset];
                offset++;
            }
            offset++;
            aliases.push_back(alias);
        }
        while (offset % 8 != 0)
        {
            offset++;
        }
        oofset = offset + 8;
        for (u64 i = offset; i < oofset; i++)
        {
            temp[i - offset] = buf[i];
        }
        offset += 8;
        u64 childCount = byteVecToU64(temp);
        while (knuts.second.size() < childCount)
        {
            std::string child;
            while (buf[offset] != '\0')
            {
                child += buf[offset];
                offset++;
            }
            offset++;
            knuts.second.push_back(child);
        }
        lossChunks.push_back(knuts);
        while (offset % 8 != 0)
        {
            offset++;
        }
        offset += 8;
        if (cat == NdbTag::COPYRIGHT) topLevel.push_back(std::make_shared<CopywrongTag>(am, tagStr, std::vector<std::shared_ptr<NdbTag>>(), aliases));
        else if (cat == NdbTag::AUTHOR) topLevel.push_back(std::make_shared<AuthorTag>(am, tagStr, std::vector<std::shared_ptr<NdbTag>>(), aliases));
        else if (cat == NdbTag::CHARACTER) topLevel.push_back(std::make_shared<CharTag>(am, tagStr, std::vector<std::shared_ptr<NdbTag>>(), aliases));
        else if (cat == NdbTag::SPECIES) topLevel.push_back(std::make_shared<SpeciesTag>(am, tagStr, std::vector<std::shared_ptr<NdbTag>>(), aliases));
        else if (cat == NdbTag::GENERAL) topLevel.push_back(std::make_shared<GeneralTag>(am, tagStr, std::vector<std::shared_ptr<NdbTag>>(), aliases));
        else if (cat == NdbTag::META) topLevel.push_back(std::make_shared<MetaTag>(am, tagStr, std::vector<std::shared_ptr<NdbTag>>(), aliases));
        else if (cat == NdbTag::LORE) topLevel.push_back(std::make_shared<LoreTag>(am, tagStr, std::vector<std::shared_ptr<NdbTag>>(), aliases));
        else if (cat == static_cast<NdbTag::Category>(NdbTag::META | NdbTag::RESERVED)) topLevel.push_back(std::make_shared<ReservedNdbTag>(am, tagStr, std::vector<std::shared_ptr<NdbTag>>(), aliases));
    }
    for (u64 i = 0; i < lossChunks.size(); i++)
    {
        for (u64 j = 0; j < lossChunks[i].second.size(); j++)
        {
            operator[](lossChunks[i].first)->addChild(operator[](lossChunks[i].second[j]));
        }
    }
    //        topLevel = connectHierarchy(topLevel, subTags, lossChunks);
}

std::vector<std::shared_ptr<NdbTag>> NdbTagWeb::connectHierarchy(std::vector<std::shared_ptr<NdbTag>> topLevel, std::vector<std::shared_ptr<NdbTag>> subTags, std::vector<std::pair<std::string, std::vector<std::string>>> lossChunks)
{
    for (u64 i = 0; i < subTags.size(); i++)
    {
        for (u64 j = 0; j < lossChunks.size(); j++)
        {
            if (subTags[i]->getTagString() == lossChunks[j].first)
            {
                for (u64 k = 0; k < lossChunks[j].second.size(); k++)
                {
                    for (u64 l = 0; l < subTags.size(); l++)
                    {
                        if (subTags[l]->getTagString() == lossChunks[j].second[k])
                        {
                            subTags[i]->addChild(subTags[l]);
                        }
                    }
                }
                break;
            }
        }
    }
    for (u64 i = 0; i < topLevel.size(); i++)
    {
        for (u64 j = 0; j < lossChunks.size(); j++)
        {
            if (topLevel[i]->getTagString() == lossChunks[j].first)
            {
                for (u64 k = 0; k < lossChunks[j].second.size(); k++)
                {
                    for (u64 l = 0; l < subTags.size(); l++)
                    {
                        if (subTags[l]->getTagString() == lossChunks[j].second[k])
                        {
                            topLevel[i]->addChild(subTags[l]);
                        }
                    }
                }
                break;
            }
        }
    }
    return topLevel;
}

u64 NdbTagWeb::byteVecToU64(std::vector<char> bVec)
{
    u64 ret = static_cast<u8>(bVec[0]);
    for (u8 i = 1; i < 8; i++)
    {
        ret <<= 8;
        ret |= static_cast<u8>(bVec[i]);
    }
    return ret;
}

std::string NdbTagWeb::getFilename()
{
    return filename;
}

void NdbTagWeb::setFilename(std::string filename)
{
    this->filename = filename;
}

std::shared_ptr<NdbTag>& NdbTagWeb::operator[](u64 idx)
{
    cleanTopLevel();
    return topLevel[idx];
}

u64 NdbTagWeb::getTopLevelTagCount()
{
    cleanTopLevel();
    return topLevel.size();
}

bool NdbTagWeb::containsTopLevelTag(std::string tlts)
{
    cleanTopLevel();
    for (u64 i = 0; i < topLevel.size(); i++)
    {
        if (topLevel[i]->getTagString() == tlts) return true;
    }
    return false;
}

bool NdbTagWeb::containsTagHierarchy(std::string ts)
{
    cleanTopLevel();
    if (containsTopLevelTag(ts)) return true;
    for (u64 i = 0; i < topLevel.size(); i++)
    {
        if (topLevel[i]->containsChildRecursive(ts)) return true;
    }
    return false;
}

bool NdbTagWeb::addTopLevelTag(std::shared_ptr<NdbTag> tlt, u64 idx)
{
    cleanTopLevel();
    if (containsTagHierarchy(tlt->getTagString())) return false;
    if (idx == std::numeric_limits<u64>::max())
    {
        topLevel.push_back(tlt);
        return true;
    }
    if (idx < topLevel.size())
    {
        topLevel.insert(topLevel.begin() + idx, tlt);
    }
    return false;
}

bool NdbTagWeb::removeTopLevelTag(u64 idx)
{
    cleanTopLevel();
    if (idx >= topLevel.size()) return false;
    topLevel.erase(topLevel.begin() + idx);
    return true;
}

bool NdbTagWeb::setTopLevelTag(std::shared_ptr<NdbTag> tlt, u64 idx)
{
    cleanTopLevel();
    if (idx >= topLevel.size() || containsTopLevelTag(tlt->getTagString())) return false;
    removeTopLevelTag(idx);
    if (idx == topLevel.size()) idx = std::numeric_limits<u64>::max();
    addTopLevelTag(tlt, idx);
    return true;
}

void NdbTagWeb::writeOut()
{
    cleanTopLevel();
    std::vector<char> buf;
    buf = pushMagic(buf, 1, 0, 0);
    buf = pushU64(buf, static_cast<u64>(topLevel.size()));
    std::vector<std::shared_ptr<NdbTag>> subTags;
    for (u64 i = 0; i < topLevel.size(); i++)
    {
        std::vector<char> temp;
        temp = pushString(temp, topLevel[i]->getTagString());
        temp = pushMeta(temp, topLevel[i]->getAccessModifier(), topLevel[i]->getCategory());
        temp = pushU64(temp, static_cast<u64>(topLevel[i]->getAliases().size()));
        temp = pushStringArray(temp, topLevel[i]->getAliases());
        temp = pushU64(temp, topLevel[i]->getChildCount());
        std::vector<std::string> children;
        for (u64 j = 0; j < topLevel[i]->getChildCount(); j++)
        {
            children.push_back(topLevel[i]->getChild(j)->getTagString());
            subTags.push_back(topLevel[i]->getChild(j));
        }
        temp = pushStringArray(temp, children);
        buf = pushU64(buf, static_cast<u64>(temp.size()));
        for (u64 j = 0; j < temp.size(); j++)
        {
            buf.push_back(temp[j]);
        }
    }
    buf = pushHierarchy(buf, subTags);
    alreadyPushed.erase(alreadyPushed.begin(), alreadyPushed.end());
    std::ofstream out(filename, std::ios::binary);
    out.write(buf.data(), buf.size());
    out.close();
}

std::vector<char> NdbTagWeb::getBuf()
{
    cleanTopLevel();
    std::vector<char> buf;
    buf = pushMagic(buf, 1, 0, 0);
    buf = pushU64(buf, static_cast<u64>(topLevel.size()));
    std::vector<std::shared_ptr<NdbTag>> subTags;
    for (u64 i = 0; i < topLevel.size(); i++)
    {
        std::vector<char> temp;
        temp = pushString(temp, topLevel[i]->getTagString());
        temp = pushMeta(temp, topLevel[i]->getAccessModifier(), topLevel[i]->getCategory());
        temp = pushU64(temp, static_cast<u64>(topLevel[i]->getAliases().size()));
        temp = pushStringArray(temp, topLevel[i]->getAliases());
        temp = pushU64(temp, topLevel[i]->getChildCount());
        std::vector<std::string> children;
        for (u64 j = 0; j < topLevel[i]->getChildCount(); j++)
        {
            children.push_back(topLevel[i]->getChild(j)->getTagString());
            subTags.push_back(topLevel[i]->getChild(j));
        }
        temp = pushStringArray(temp, children);
        buf = pushU64(buf, static_cast<u64>(temp.size()));
        for (u64 j = 0; j < temp.size(); j++)
        {
            buf.push_back(temp[j]);
        }
    }
    buf = pushHierarchy(buf, subTags);
    alreadyPushed.erase(alreadyPushed.begin(), alreadyPushed.end());
    return buf;
}

std::multimap<std::string, bool> NdbTagWeb::globuleToSearchCriteria(std::string globule)
{
    std::multimap<std::string, bool> criteria;
    std::stringstream sstr(globule);
    while(!sstr.eof())
    {
        std::string temp;
        std::getline(sstr, temp, ' ');
        if (temp[0] == '-')
        {
            if (containsTagHierarchy(temp.substr(1, temp.size() - 1)))
            {
                criteria.insert(criteria.end(), {temp.substr(1, temp.size() - 1), false});
            }
            else if (findFromAlias(temp.substr(1, temp.size() - 1)) != "")
            {
                criteria.insert(criteria.end(), {findFromAlias(temp.substr(1, temp.size() - 1)), false});
            }
            else
            {
                criteria.erase(criteria.begin(), criteria.end());
                criteria.insert(criteria.end(), {"Nobody here but Torchic and the cold of the night", false});
                return criteria;
            }
        }
        else if (temp.find('*') != std::string::npos)
        {
            std::set<std::string> matches = findFromWildcard(temp);
            for (auto& s: matches)
            {
                if (s == "Nobody here but Torchic and the cold of the night")
                {
                    criteria.erase(criteria.begin(), criteria.end());
                    criteria.insert(criteria.end(), {"Nobody here but Torchic and the cold of the night", false});
                    return criteria;
                }
                criteria.insert(criteria.end(), {s, true});
            }
        }
        else if (temp[0] == '~')
        {
            u64 pos = sstr.tellg();
            std::string toAdd;
            while(temp[0] == '~')
            {
                if (toAdd.size() != 0) toAdd += '|';
                if (containsTagHierarchy(temp.substr(1, temp.size() - 1)))
                {
                    toAdd += temp.substr(1, temp.size() - 1);
                }
                else if (findFromAlias(temp.substr(1, temp.size() - 1)) != "")
                {
                    toAdd += findFromAlias(temp.substr(1, temp.size() - 1));
                }
                else
                {
                    criteria.erase(criteria.begin(), criteria.end());
                    criteria.insert(criteria.end(), {"Nobody here but Torchic and the cold of the night", false});
                    return criteria;
                }
                pos = sstr.tellg();
                std::getline(sstr, temp, ' ');
            }
            sstr.seekg(pos);
            criteria.insert(criteria.end(), {toAdd, true});
        }
        else if (temp.find(' ') == std::string::npos && temp.find('|') == std::string::npos && temp.find('~') == std::string::npos && temp.find('-') == std::string::npos && temp.find('*') == std::string::npos)
        {
            if (containsTagHierarchy(temp))
            {
                criteria.insert(criteria.end(), {temp, true});
            }
            else if (findFromAlias(temp) != "")
            {
                criteria.insert(criteria.end(), {findFromAlias(temp), true});
            }
            else
            {
                criteria.erase(criteria.begin(), criteria.end());
                criteria.insert(criteria.end(), {"Nobody here but Torchic and the cold of the night", false});
                return criteria;
            }
        }
        else
        {
            criteria.erase(criteria.begin(), criteria.end());
            criteria.insert(criteria.end(), {"Nobody here but Torchic and the cold of the night", false});
            return criteria;
        }
        return criteria;
    }
    return {{"Nobody here but Torchic and the cold of the night", false}};
}

std::set<std::string> NdbTagWeb::findFromWildcard(std::string wildcard)
{
    return _findFromWildcard(wildcard, topLevel);
}

std::set<std::string> NdbTagWeb::_findFromWildcard(std::string wildcard, std::vector<std::shared_ptr<NdbTag>> web)
{
    cleanTopLevel();
    if (web.size() == 0) return std::set<std::string>();
    std::set<std::string> matches;
    std::vector<std::shared_ptr<NdbTag>> sublevel;
    bool readFromEnd = false;
    if (wildcard[0] == '*') readFromEnd = true;
    else if (wildcard[wildcard.size() - 1] != '*') return {"Nobody here but Torchic and the cold of the night"};
    for (u64 i = 0; i < web.size(); i++)
    {
        if (readFromEnd)
        {
            std::string searchPattern = wildcard.substr(1, wildcard.size() - 1);
            std::size_t found = web[i]->getTagString().rfind(searchPattern);
            if (found == web[i]->getTagString().size() - searchPattern.size()) matches.insert(matches.end(), web[i]->getTagString());
        }
        else
        {
            std::string searchPattern = wildcard.substr(0, wildcard.size() - 1);
            std::size_t found = web[i]->getTagString().find(searchPattern);
            if (found == 0) matches.insert(matches.end(), web[i]->getTagString());
        }
        for (u64 j = 0; j < web[i]->getChildCount(); j++)
        {
            sublevel.push_back(web[i]->getChild(j));
        }
    }
    return appendSet(matches, _findFromWildcard(wildcard, sublevel));
}

std::set<std::string> NdbTagWeb::appendSet(std::set<std::string> s1, std::set<std::string> s2)
{
    for (auto& s: s2)
    {
        s1.insert(s1.end(), s);
    }
    return s1;
}

std::string NdbTagWeb::findFromAlias(std::string alias)
{
    std::string ret = _findFromAlias(alias, topLevel);
    alreadyFound = false;
    return ret;
}

std::string NdbTagWeb::_findFromAlias(std::string alias, std::vector<std::shared_ptr<NdbTag>> web)
{
    cleanTopLevel();
    if (web.size() == 0 || alreadyFound) return "";
    std::vector<std::shared_ptr<NdbTag>> sublevel;
    std::string str;
    for (u64 i = 0; i < web.size(); i++)
    {
        for (u64 j = 0; j < web[i]->getAliases().size(); j++)
        {
            if (alias == web[i]->getAliases()[j] || alias == web[i]->getTagString())
            {
                alreadyFound = true;
                return web[i]->getTagString();
            }
            for (u64 j = 0; j < web[i]->getChildCount(); j++)
            {
                sublevel.push_back(web[i]->getChild(j));
            }
        }
    }
    return str + _findFromAlias(alias, sublevel);
}

std::shared_ptr<NdbTag> NdbTagWeb::operator[](std::string str)
{
    alreadyFound = false;
    std::shared_ptr<NdbTag> nt = _getFromString(str, topLevel);
    alreadyFound = false;
    found = nullptr;
    return nt;
}

std::shared_ptr<NdbTag> NdbTagWeb::_getFromString(std::string str, std::vector<std::shared_ptr<NdbTag>> web)
{
    cleanTopLevel();
    if (web.size() == 0 || alreadyFound) return found;
    std::vector<std::shared_ptr<NdbTag>> sublevel;
    for (u64 i = 0; i < web.size(); i++)
    {
        if (str == web[i]->getTagString())
        {
            alreadyFound = true;
            found = web[i];
            return found;
        }
        for (u64 j = 0; j < web[i]->getAliases().size(); j++)
        {
            if (str == web[i]->getAliases()[j])
            {
                alreadyFound = true;
                found = web[i];
                return found;
            }
        }
        for (u64 j = 0; j < web[i]->getChildCount(); j++)
        {
            sublevel.push_back(web[i]->getChild(j));
        }
    }
    return _getFromString(str, sublevel);
}

std::vector<char> NdbTagWeb::pushHierarchy(std::vector<char> buf, std::vector<std::shared_ptr<NdbTag>> subTags)
{
    cleanTopLevel();
    if (subTags.size() == 0) return buf;
    std::vector<std::shared_ptr<NdbTag>> childTags;
    for (u64 i = 0; i < subTags.size(); i++)
    {
        std::vector<char> temp;
        temp = pushString(temp, subTags[i]->getTagString());
        temp = pushMeta(temp, subTags[i]->getAccessModifier(), subTags[i]->getCategory());
        temp = pushU64(temp, subTags[i]->getParentCount());
        std::vector<std::string> parents;
        for (u64 j = 0; j < subTags[i]->getParentCount(); j++)
        {
            parents.push_back(subTags[i]->getParent(j)->getTagString());
        }
        temp = pushStringArray(temp, parents);
        temp = pushU64(temp, static_cast<u64>(subTags[i]->getAliases().size()));
        temp = pushStringArray(temp, subTags[i]->getAliases());
        temp = pushU64(temp, subTags[i]->getChildCount());
        std::vector<std::string> children;
        for (u64 j = 0; j < subTags[i]->getChildCount(); j++)
        {
            children.push_back(subTags[i]->getChild(j)->getTagString());
            childTags.push_back(subTags[i]->getChild(j));
        }
        temp = pushStringArray(temp, children);
        bool shouldAdd = true;
        for (u64 j = 0; j < alreadyPushed.size(); j++)
        {
            if (alreadyPushed[j] == subTags[i]->getTagString())
            {
                shouldAdd = false;
                break;
            }
        }
        if (shouldAdd)
        {
            buf = pushU64(buf, static_cast<u64>(temp.size()));
            for (u64 j = 0; j < temp.size(); j++)
            {
                buf.push_back(temp[j]);
            }
            alreadyPushed.push_back(subTags[i]->getTagString());
        }
    }
    return pushHierarchy(buf, childTags);
}

std::vector<char> NdbTagWeb::pushMagic(std::vector<char> buf, u8 vMaj, u8 vMin, u8 vPch)
{
    buf.push_back('N');
    buf.push_back('D');
    buf.push_back('T');
    buf.push_back('S');
    buf.push_back(0);
    buf.push_back(static_cast<char>(vMaj));
    buf.push_back(static_cast<char>(vMin));
    buf.push_back(static_cast<char>(vPch));
    return buf;
}

std::vector<char> NdbTagWeb::pushU64(std::vector<char> buf, u64 qWord)
{
    buf.push_back(qWord >> 56);
    buf.push_back((qWord >> 48) & 0xFF);
    buf.push_back((qWord >> 40) & 0xFF);
    buf.push_back((qWord >> 32) & 0xFF);
    buf.push_back((qWord >> 24) & 0xFF);
    buf.push_back((qWord >> 16) & 0xFF);
    buf.push_back((qWord >> 8) & 0xFF);
    buf.push_back(qWord & 0xFF);
    return buf;
}

std::vector<char> NdbTagWeb::pushMeta(std::vector<char> buf, NdbTag::AxceModYum am, NdbTag::Category cat)
{
    buf.push_back(static_cast<char>(am));
    buf.push_back(static_cast<char>(cat));
    buf.push_back(0);
    buf.push_back(0);
    buf.push_back(0);
    buf.push_back(0);
    buf.push_back(0);
    buf.push_back(0);
    return buf;
}

std::vector<char> NdbTagWeb::pushString(std::vector<char> buf, std::string str)
{
    for (u64 i = 0; i < str.size(); i++)
    {
        buf.push_back(str[i]);
    }
    buf.push_back(0);
    while(buf.size() % 8 != 0)
    {
        buf.push_back(0);
    }
    return buf;
}

std::vector<char> NdbTagWeb::pushStringArray(std::vector<char> buf, std::vector<std::string> strArr)
{
    for (u64 i = 0; i < strArr.size(); i++)
    {
        for (int j = 0; j < strArr[i].size(); j++)
        {
            buf.push_back(strArr[i][j]);
        }
        buf.push_back(0);
    }
    while(buf.size() % 8 != 0)
    {
        buf.push_back(0);
    }
    return buf;
}

void NdbTagWeb::cleanTopLevel()
{
    for (u64 i = 0; i < topLevel.size(); i++)
    {
        if (topLevel[i]->getParentCount() != 0)
        {
            topLevel.erase(topLevel.begin() + i);
            i--;
        }
    }
}

} // namespace Bidoof
} // namespace tmc
