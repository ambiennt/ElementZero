#pragma once
#include "json.h"

class WebToken {
public:
	std::string header;
	Json::Value headerInfo;
	std::string data;
	Json::Value dataInfo;
	std::string signature;
};

static_assert(offsetof(WebToken, header) == 0x0);
static_assert(offsetof(WebToken, headerInfo) == 0x20);
static_assert(offsetof(WebToken, data) == 0x30);
static_assert(offsetof(WebToken, dataInfo) == 0x50);
static_assert(offsetof(WebToken, signature) == 0x60);
static_assert(sizeof(WebToken) == 0x80);