#pragma once
#include "TmcNdbTagging_global.h"
#include "ndbtag.h"
#include "copywrongtag.h"
#include "authortag.h"
#include "chartag.h"
#include "speciestag.h"
#include "generaltag.h"
#include "loretag.h"
#include "metatag.h"
#include "reservedndbtag.h"
#include "ndbtagweb.h"

namespace tmc::Bidoof
{
template <class ndb_tag_t>
std::shared_ptr<ndb_tag_t> ndb_tag_cast(std::shared_ptr<NdbTag> nt)
{
    std::shared_ptr<ndb_tag_t> result = std::make_shared<ndb_tag_t>(nt->getAccessModifier(), nt->getTagString(),
                                                   std::vector<std::shared_ptr<NdbTag>>(), nt->getAliases());
    for (u64 i = 0; i < nt->getParentCount(); i++)
    {
        result->addParent(nt->getParent(i));
    }
    for (u64 i = 0; i < nt->getChildCount(); i++)
    {
        result->addChild(nt->getChild(i));
    }
    return result;
}
}
