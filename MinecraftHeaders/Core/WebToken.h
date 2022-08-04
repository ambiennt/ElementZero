#pragma once
#include "json.h"

class WebToken {
public:
	std::string mHeader;
	Json::Value mHeaderInfo;
	std::string mData;
	Json::Value mDataInfo;
	std::string mSignature;

	MCAPI std::string toString() const;
};

static_assert(offsetof(WebToken, mHeader) == 0x0);
static_assert(offsetof(WebToken, mHeaderInfo) == 0x20);
static_assert(offsetof(WebToken, mData) == 0x30);
static_assert(offsetof(WebToken, mDataInfo) == 0x50);
static_assert(offsetof(WebToken, mSignature) == 0x60);
static_assert(sizeof(WebToken) == 0x80);