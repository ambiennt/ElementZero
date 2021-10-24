#pragma once

#include <vector>
#include <string>
#include <unordered_map>

#include "AnimatedImageData.h"
#include "SerializedPersonaPieceHandle.h"
#include "persona.h"
#include "TintMapColor.h"
#include "../../Core/Color.h"
#include "../../Core/mce.h"
#include "../../Core/json.h"
#include "../../dll.h"

class ConnectionRequest;
class SubClientConnectionRequest;
class ReadOnlyBinaryStream;
class BinaryStream;

class SerializedSkin {
public:
  enum struct TrustedFlag : char { UNSET, NO, YES };

  std::string skin_id, name, skin_resource_patch, geometry_name;
  mce::Image texture, cape_texture;
  std::vector<AnimatedImageData> animated_image_data;
  Json::Value geometry_data, geometry_data_mutable;
  std::string animation_data, cape_id;
  bool premium_skin, persona_skin, cape_on_classic_skin;
  std::vector<SerializedPersonaPieceHandle> persona_pieces;
  std::string arm_size;
  std::unordered_map<PieceType, TintMapColor> piece_tint_colors;
  Color skin_color;
  TrustedFlag trusted_flag;

#pragma region methods
  MCAPI SerializedSkin();
  MCAPI SerializedSkin(SerializedSkin const &);
  MCAPI SerializedSkin(ConnectionRequest const &);
  MCAPI SerializedSkin(SubClientConnectionRequest const &);

  MCAPI SerializedSkin &operator=(SerializedSkin const &);

  MCAPI void read(ReadOnlyBinaryStream &);
  MCAPI void write(BinaryStream &);
  MCAPI void updateGeometryName();

  inline std::string const &getName() const { return name; }
  inline bool getIsPersona() const { return persona_skin; }
  inline Json::Value const &getGeometryData() const { return geometry_data; }
  inline Json::Value const &getGeometryDataMutable() const { return geometry_data_mutable; }
  inline mce::Image const &getCapeImageData() const { return cape_texture; }
  inline bool isTrustedSkin() const { return trusted_flag == TrustedFlag::YES; }
  inline Color const &getSkinColor() { return skin_color; }

  inline void setCapeId(std::string const &str) {
    cape_id = str;
    name    = skin_id + str;
  }

  inline void setCapeImageData(mce::Image const *ptr) {
    if (ptr)
      cape_texture = ptr->clone();
    else
      cape_texture = {};
  }

  inline void setImageData(mce::Image const *ptr) {
    if (ptr)
      texture = ptr->clone();
    else
      texture = {};
  }

  inline bool setIsPersonaCapeOnClassicSkin(bool value) { return cape_on_classic_skin = value; }

  inline float getAnimationFrames(AnimatedTextureType type) const {
    for (auto &item : animated_image_data) {
      if (item.type == type) return item.frame;
    }
    return 1.0f;
  }
#pragma endregion
};

static_assert(offsetof(SerializedSkin, premium_skin) == 0x138);
static_assert(offsetof(SerializedSkin, persona_skin) == 0x139);
static_assert(offsetof(SerializedSkin, cape_on_classic_skin) == 0x13A);
static_assert(offsetof(SerializedSkin, persona_pieces) == 0x140);
static_assert(offsetof(SerializedSkin, arm_size) == 0x158);
static_assert(offsetof(SerializedSkin, piece_tint_colors) == 0x178);
static_assert(offsetof(SerializedSkin, skin_color) == 0x1B8);
static_assert(offsetof(SerializedSkin, trusted_flag) == 0x1C8);
static_assert(sizeof(SerializedSkin) == 0x1D0);