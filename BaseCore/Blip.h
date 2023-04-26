#pragma once
#include <SDK.h>
namespace alt {
	class Blip : public alt::IBlip
	{
		std::unordered_map<std::string, MValue>* metaData = new std::unordered_map<std::string, MValue>();
	public:
		virtual alt::IBaseObject::Type GetType() const override {
			return alt::IBaseObject::Type::COLSHAPE;
		};

		virtual bool HasMetaData(const std::string& key) const {
			return metaData->contains(key);
		};
		virtual MValueConst GetMetaData(const std::string& key) const {
			auto it = metaData->find(key);
			if (it == metaData->end()) return MValueConst(MValueNone());
			auto data = metaData->at(key);

			return data;
		};
		virtual void SetMetaData(const std::string& key, MValue val) {
			metaData->insert({ key, val });
		};
		virtual void DeleteMetaData(const std::string& key) {
			metaData->erase(key);
		};
		virtual std::vector<std::string> GetMetaDataKeys() const {
			std::vector<std::string> keys;
			for (auto& i : *metaData) keys.push_back(i.first);
			return keys;
		};

		virtual bool IsRemoved() const {
			return removed;
		};



		bool removed = false;
		alt::IBaseObject::Type type = alt::IBaseObject::Type::COLSHAPE;
		int id;

		Position GetPosition() const {
			return this->pos;
		};
		void SetPosition(Position pos) {
			this->pos = pos;
		};

		int32_t GetDimension() const {
			return this->dimension;
		};
		void SetDimension(int32_t dimension) {
			this->dimension = dimension;
		};
		Position pos;
		int32_t dimension = 0;

		Blip(int id, IPlayer* target, IBlip::BlipType type, Position pos): id(id), target(target) {}
		Blip(int id, IPlayer* target, IBlip::BlipType type, IEntity* attachTo): id(id), target(target), attachTo(attachTo) {}

		virtual uint32_t GetID() const {
			return id;
		}

		virtual uint32_t GetScriptID() const {
			return 0;
		}

		virtual bool IsRemote() const {
			return false;
		};

		virtual bool IsGlobal() const {
			return false;
		}
		virtual IPlayer* GetTarget() const {
			return this->target;
		}
		virtual bool IsAttached() const {
			return false;
		}
		virtual IEntity* AttachedTo() const {
			return attachTo;
		}
		virtual void AttachTo(IEntity* entity) {}
		virtual BlipType GetBlipType() const {
			return blipType;
		}
		virtual Vector2f GetScaleXY() const {
			return Vector2f{ 0.0,0.0 };
		}
		virtual void SetScaleXY(Vector2f scale) {}
		virtual int GetDisplay() const {
			return 0;
		}
		virtual void SetDisplay(int display) {}
		virtual int GetSprite() const {
			return 0;
		}
		virtual int GetColor() const {
			return 0;
		}
		virtual alt::RGBA GetSecondaryColor() const {
			return alt::RGBA{ 0,0,0,0 };
		}
		virtual int GetAlpha() const { return 0; }
		virtual int GetFlashTimer() const { return 0; }
		virtual int GetFlashInterval() const { return 0; }
		virtual bool GetAsFriendly() const { return false; }
		virtual bool GetRoute() const { return false; }
		virtual bool GetBright() const { return false; }
		virtual int GetNumber() const {
			return 0;
		}
		virtual bool GetShowCone() const { return false; }
		virtual bool GetFlashes() const { return false; }
		virtual bool GetFlashesAlternate() const { return false; }
		virtual bool GetAsShortRange() const { return false; }
		virtual int GetPriority() const { return 0; }
		virtual float GetRotation() const { return 0.0; }
		virtual std::string GetGxtName() const {
			return "";
		}
		virtual std::string GetName() const {
			return "";
		}
		virtual alt::RGBA GetRouteColor() const {
			return alt::RGBA{ 0,0,0,0 };
		};
		virtual bool GetPulse() const { return false; }
		virtual bool GetAsMissionCreator() const { return false; }
		virtual bool GetTickVisible() const { return false; }
		virtual bool GetHeadingIndicatorVisible() const { return false; }
		virtual bool GetOutlineIndicatorVisible() const { return false; }
		virtual bool GetFriendIndicatorVisible() const { return false; }
		virtual bool GetCrewIndicatorVisible() const { return false; }
		virtual int GetCategory() const { return 0; }
		virtual bool GetAsHighDetail() const { return false; }
		virtual bool GetShrinked() const { return false; }

		virtual void SetSprite(int sprite) {}
		virtual void SetColor(int color) {}
		virtual void SetRoute(bool state) {}
		virtual void SetRouteColor(alt::RGBA color) {}
		virtual void SetSecondaryColor(alt::RGBA color) {}
		virtual void SetAlpha(int alpha) {}
		virtual void SetFlashTimer(int timer) {}
		virtual void SetFlashInterval(int interval) {}
		virtual void SetAsFriendly(bool friendly) {}
		virtual void SetBright(bool bright) {};
		virtual void SetNumber(int number) {}
		virtual void SetShowCone(bool state) {}
		virtual void SetFlashes(bool state) {}
		virtual void SetFlashesAlternate(bool state) {};
		virtual void SetAsShortRange(bool state) {}
		virtual void SetPriority(int state) {}
		virtual void SetRotation(float rot) {}
		virtual void SetGxtName(const std::string& name) {}
		virtual void SetName(const std::string& name) {}
		virtual void SetPulse(bool val) {}
		virtual void SetAsMissionCreator(bool val) {}
		virtual void SetTickVisible(bool val) {}
		virtual void SetHeadingIndicatorVisible(bool val) {}
		virtual void SetOutlineIndicatorVisible(bool val) {}
		virtual void SetFriendIndicatorVisible(bool val) {}
		virtual void SetCrewIndicatorVisible(bool val) {}
		virtual void SetCategory(int val) {}
		virtual void SetAsHighDetail(bool val) {}
		virtual void SetShrinked(bool val) {}
		virtual void Fade(uint32_t opacity, uint32_t duration) {}

		IPlayer* target;
		IBlip::BlipType blipType;
		IEntity* attachTo;
	};
}

