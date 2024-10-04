#include "ndbtagweb.h"

namespace tmc {
namespace Bidoof {

NdbTagWeb::NdbTagWeb(std::vector<std::shared_ptr<NdbTag>> topLevel) {
    this->topLevel = topLevel;
    this->filename = "";
}

NdbTagWeb::NdbTagWeb(std::string filename)
{
    this->filename = filename;
    std::ifstream in(filename, std::ios::binary);
    if (in.is_open())
    {
        in.seekg(8);
        std::vector<char> temp(8);
        u64 topLevelCount = byteVecToU64(temp);
        for (u64 i = 0; i < topLevelCount; i++)
        {
            in.read(temp.data(), 8);
            u64 entryLength = byteVecToU64(temp);
            std::string tagStr = "";
            u64 counter = 0;
            while(in.peek() != 0) tagStr += in.get();
            in.seekg(1 + in.tellg());
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
        }
        in.read(temp.data(), 8);
    }
}

u64 NdbTagWeb::byteVecToU64(std::vector<char> bVec)
{
    u64 ret = bVec[0];
    ret <<= 8;
    ret |= bVec[1];
    ret <<= 8;
    ret |= bVec[2];
    ret <<= 8;
    ret |= bVec[3];
    ret <<= 8;
    ret |= bVec[4];
    ret <<= 8;
    ret |= bVec[5];
    ret <<= 8;
    ret |= bVec[6];
    ret <<= 8;
    ret |= bVec[7];
    return ret;
}

} // namespace Bidoof
} // namespace tmc
