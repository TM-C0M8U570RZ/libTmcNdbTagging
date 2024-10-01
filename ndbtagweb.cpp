#include "ndbtagweb.h"

namespace tmc {
namespace Bidoof {

NdbTagWeb::NdbTagWeb(std::vector<std::shared_ptr<NdbTag>> topLevel) {
    this->topLevel = topLevel;
    this->filename = "";
}

NdbTagWeb::NdbTagWeb(std::string filename)
{
    this->topLevel = {};
    this->filename = filename;
}

} // namespace Bidoof
} // namespace tmc
