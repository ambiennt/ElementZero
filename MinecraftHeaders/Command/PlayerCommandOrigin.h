#pragma once

#include "../dll.h"
#include "CommandOrigin.h"
#include "../Math/Vec3.h"
#include "../Actor/ActorUniqueID.h"

class CommandOrigin;
class Level;

class PlayerCommandOrigin : public CommandOrigin {
public:
	ActorUniqueID mPlayerId;
	Level *mLevel;

	MCAPI PlayerCommandOrigin(Player &);

	inline virtual ~PlayerCommandOrigin() override {}
	MCAPI virtual std::string const &getRequestId() const override;
	MCAPI virtual std::string getName() const override;
	MCAPI virtual BlockPos getBlockPosition() const override;
	MCAPI virtual Vec3 getWorldPosition() const override;
	MCAPI virtual Level *getLevel() const override;
	MCAPI virtual Dimension *getDimension() const override;
	MCAPI virtual Actor *getEntity() const override;
	MCAPI virtual CommandPermissionLevel getPermissionsLevel() const override;
	MCAPI virtual std::unique_ptr<CommandOrigin> clone() const override;
	MCAPI virtual std::optional<BlockPos> getCursorHitBlockPos() const override;
	MCAPI virtual std::optional<Vec3> getCursorHitPos() const override;
	MCAPI virtual bool canUseAbility(AbilitiesIndex) const override;
	MCAPI virtual bool isSelectorExpansionAllowed() const override; 
	MCAPI virtual NetworkIdentifier const &getSourceId() const override;
	MCAPI virtual unsigned char getSourceSubId() const override;
	MCAPI virtual CommandOriginType getOriginType() const override;
};

static_assert(sizeof(PlayerCommandOrigin) == 0x28);