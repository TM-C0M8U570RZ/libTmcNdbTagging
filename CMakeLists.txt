cmake_minimum_required(VERSION 3.16)

project(TmcNdbTagging LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(TmcNdbTagging SHARED
  TmcNdbTagging_global.h

  tmcndbtagging.h
  ndbtag.h ndbtag.cpp
  copywrongtag.h copywrongtag.cpp
  authortag.h authortag.cpp
  chartag.h chartag.cpp
  speciestag.h speciestag.cpp
  generaltag.h generaltag.cpp
  metatag.h metatag.cpp
  loretag.h loretag.cpp
  reservedndbtag.h reservedndbtag.cpp
  ndbtagweb.h ndbtagweb.cpp
)
target_include_directories(TmcNdbTagging PRIVATE $ENV{TMC_SDK_PATH}/current/helpers/include)

target_compile_definitions(TmcNdbTagging PRIVATE TMCNDBTAGGING_LIBRARY)
