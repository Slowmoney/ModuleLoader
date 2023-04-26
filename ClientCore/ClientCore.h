#pragma once
#include "BaseCore.h"

using namespace alt;

class ClientCore : public BaseCore
{
	virtual IDiscordManager* GetDiscordManager() const {
		return NULL;
	};
	virtual IStatData* GetStatData(const std::string& statname) const {
		return NULL;
	};
	virtual std::shared_ptr<alt::IHandlingData> GetHandlingData(uint32_t modelHash) const {
		return NULL;
	};
	virtual std::shared_ptr<alt::IWeaponData> GetWeaponData(uint32_t weaponHash) const {
		return NULL;
	};

	virtual void TriggerServerEvent(const std::string& ev, MValueArgs args) {

	};
	virtual void TriggerServerEventUnreliable(const std::string& ev, MValueArgs args) {

	};

	virtual ILocalPlayer* GetLocalPlayer() const {
		return NULL;
	};

	virtual KeyState GetKeyState(uint32_t keyCode) const {
		return KeyState{ false, false };
	};
	virtual bool AreControlsEnabled() const {
		return NULL;
	};
	virtual Vector2f GetCursorPosition(bool normalized = false) const {
		return Vector2f{ 0.0,0.0 };
	};
	virtual void SetCursorPosition(Vector2f pos, bool normalized = false) {

	};

	virtual bool SetConfigFlag(const std::string& flag, bool state) {
		return NULL;
	};
	virtual bool GetConfigFlag(const std::string& flag) const {
		return NULL;
	};
	virtual bool DoesConfigFlagExist(const std::string& flag) const {
		return NULL;
	};

	virtual void SetVoiceInputMuted(bool state) {

	};
	virtual bool IsVoiceInputMuted() const {
		return NULL;
	};
	virtual bool IsVoiceActivationEnabled() const {
		return NULL;
	};
	virtual void ToggleVoiceControls(bool state) {

	};
	virtual bool AreVoiceControlsEnabled() const {
		return NULL;
	};
	virtual uint32_t GetVoiceActivationKey() {
		return NULL;
	};

	virtual std::string GetLicenseHash() const {
		return "NULL";
	};
	virtual std::string GetLocale() const {
		return "NULL";
	};
	virtual bool IsInStreamerMode() const {
		return NULL;
	};
	virtual bool IsMenuOpen() const {
		return NULL;
	};
	virtual bool IsConsoleOpen() const {
		return NULL;
	};

	virtual const Array<INative*> GetAllNatives() const {
		return Array<INative*>();
	};

	virtual INative* GetNativeByName(const std::string& name) const {
		return NULL;
	};
	virtual INative* GetNativeByHash(uint64_t hash) const {
		return NULL;
	};
	virtual IEntity* GetEntityByScriptGuid(int32_t scriptGuid) const {
		return NULL;
	};

	virtual void* GetTextureFromDrawable(uint32_t modelHash, const std::string& targetTextureName) const {
		return NULL;
	};

	virtual void RequestIPL(const std::string& ipl) {

	};
	virtual void RemoveIPL(const std::string& ipl) {

	};

	virtual bool BeginScaleformMovieMethodMinimap(const std::string& methodName) {
		return NULL;
	};

	virtual int32_t GetMsPerGameMinute() const {
		return NULL;
	};
	virtual void SetMsPerGameMinute(int32_t val) {

	};
	virtual void SetWeatherCycle(alt::Array<uint8_t> weathers, alt::Array<uint8_t> multipliers) {

	};
	virtual void SetWeatherSyncActive(bool active) {

	};

	virtual void SetCamFrozen(bool frozen) {

	};
	virtual bool IsCamFrozen() {
		return NULL;
	};

	virtual std::shared_ptr<alt::IMapData> GetMapData(uint8_t zoomDataId) {
		return NULL;
	}
	virtual std::shared_ptr<alt::IMapData> GetMapData(const std::string& alias) {
		return NULL;
	}
	virtual uint8_t GetMapDataIDFromAlias(const std::string& alias) {
		return NULL;
	};
	virtual void ResetMapData(uint8_t zoomDataId) {

	};
	virtual void ResetMapData(const std::string& alias) {

	};
	virtual void ResetAllMapData() {

	};

	virtual PermissionState GetPermissionState(Permission permission) const {
		return PermissionState::Allowed;
	};

	using TakeScreenshotCallback = std::function<void(const std::string& base64)>;
	/**
	 * This is an async operation.
	 * @param callback will be called when the screenshot has been taken.
	 * The screenshot is taken exactly after the webviews has rendered.
	 */
	virtual PermissionState TakeScreenshot(TakeScreenshotCallback callback) const {
		return PermissionState::Allowed;
	};

	/**
	 * This is an async operation.
	 * @param callback will be called when the screenshot has been taken.
	 * The screenshot is taken exactly after GTA:V has rendered it's stuff and before alt:V renders anything custom.
	 */
	virtual PermissionState TakeScreenshotGameOnly(TakeScreenshotCallback callback) const {
		return PermissionState::Allowed;
	};


	virtual IWebView* CreateWebView(const std::string& url, uint32_t drawableHash, const std::string& targetTexture, IResource* res = nullptr) {
		return NULL;
	};
	virtual IWebView* CreateWebView(const std::string& url, Vector2i position, Vector2i size, bool isVisible, bool isOverlay, IResource* res = nullptr) {
		return NULL;
	};
	virtual IWebSocketClient* CreateWebSocketClient(const std::string& url, IResource* res = nullptr) {
		return NULL;
	};
	virtual IHttpClient* CreateHttpClient(IResource* res = nullptr) {
		return NULL;
	};
	virtual IBlip* CreateBlip(IBlip::BlipType type, Vector3f position, IResource* res = nullptr) {
		return NULL;
	};
	virtual IBlip* CreateBlip(IBlip::BlipType type, uint32_t entityID, IResource* res = nullptr) {
		return NULL;
	};
	virtual IBlip* CreateBlip(Vector3f position, float radius, IResource* res = nullptr) {
		return NULL;
	};
	virtual IBlip* CreateBlip(Vector3f position, float width, float height, IResource* res = nullptr) {
		return NULL;
	};
	virtual ICheckpoint* CreateCheckpoint(uint8_t type, Vector3f pos, Vector3f next, float radius, float height, alt::RGBA color, IResource* res = nullptr) {
		return NULL;
	};
	virtual IAudio* CreateAudio(const std::string& source, float volume, uint32_t category, bool frontend, IResource* res = nullptr) {
		return NULL;
	};
	//virtual IAudioFilter* CreateAudioFilter(uint32_t hash, IResource* res = nullptr) = 0;
	virtual IRmlDocument* CreateDocument(const std::string& url, const std::string& currentPath, IResource* res = nullptr) {
		return NULL;
	};
	//virtual IMarker* CreateMarker(IMarker::MarkerType type, Vector3f position, alt::RGBA color, IResource* res = nullptr) = 0;
	//virtual ITextLabel* CreateTextLabel(const std::string& text, const std::string& fontName, float fontSize, float scale, Vector3f position, Vector3f rot, alt::RGBA color, float outlineWidth, alt::RGBA outlineColor, IResource* res = nullptr) = 0;

	virtual void SetAngularVelocity(uint32_t entityId, alt::Vector4f velocity) {

	};

	virtual bool IsGameFocused() const {
		return NULL;
	};

	virtual void LoadModel(uint32_t hash) {

	};
	virtual void LoadModelAsync(uint32_t hash) {

	};

	virtual bool LoadYtyp(const std::string& path) {
		return NULL;
	};
	virtual bool UnloadYtyp(const std::string& path) {
		return NULL;
	};

	virtual std::string HeadshotToBase64(uint8_t id) {
		return "NULL";
	};

	virtual void SetDlcClothes(int32_t scriptID, uint8_t component, uint16_t drawable, uint8_t texture, uint8_t palette, uint32_t dlc) {

	};
	virtual void SetDlcProps(int32_t scriptID, uint8_t component, uint8_t drawable, uint8_t texture, uint32_t dlc) {

	};
	virtual void ClearProps(int32_t scriptID, uint8_t component) {

	};

	virtual void SetWatermarkPosition(uint8_t pos) {

	};

	virtual uint16_t GetFps() const {
		return NULL;
	};
	virtual uint16_t GetPing() const {
		return NULL;
	};
	virtual uint64_t GetTotalPacketsSent() const {
		return NULL;
	};
	virtual uint32_t GetTotalPacketsLost() const {
		return NULL;
	};
	virtual std::string GetServerIp() const {
		return "0.0.0.0";
	};
	virtual uint16_t GetServerPort() const {
		return NULL;
	};
	virtual std::string GetClientPath() const {
		return "./client";
	};

	virtual bool HasLocalMetaData(const std::string& key) const {
		return NULL;
	};
	virtual MValue GetLocalMetaData(const std::string& key) const {
		return MValueNone();
	};

	virtual PermissionState CopyToClipboard(const std::string& value) {
		return PermissionState::Allowed;
	}

	virtual void ToggleRmlDebugger(bool state) {

	};
	virtual bool LoadRmlFontFace(IResource* resource, const std::string& path, const std::string& currentPath, const std::string& name, bool italic = false, bool bold = false) const {
		return NULL;
	};
	virtual void ToggleRmlControls(bool state) {

	};
	virtual bool AreRmlControlsEnabled() const {
		return NULL;
	};

	virtual Vector3f WorldToScreen(Vector3f pos) {
		return Vector3f{ 0.0,0.0,0.0 };
	}
	virtual Vector3f ScreenToWorld(Vector2f pos) {
		return Vector3f{ 0.0,0.0,0.0 };
	}
	virtual Vector3f GetCamPos() {
		return Vector3f{ 0.0,0.0,0.0 };
	}
	virtual Vector2i GetScreenResolution() const {
		return Vector2i{ 0, 0 };
	}

	virtual void SetMinimapComponentPosition(const std::string& name, char alignX, char alignY, Vector2f pos, Vector2f size) {

	};
	virtual void SetMinimapIsRectangle(bool state) {

	};

	virtual Config::Value::ValuePtr GetClientConfig() const {
		return "";
	}

	using RequestOAuth2TokenCallback = std::function<void(bool success, const std::string& token)>;
	virtual bool DiscordRequestOAuth2Token(const std::string& appid, RequestOAuth2TokenCallback callback) {
		return NULL;
	};

	virtual bool IsFocusOverriden() const {
		return NULL;
	};
	virtual Vector3f GetFocusOverridePos() const {
		return Vector3f{ 0.0,0.0,0.0 };
	}
	virtual Vector3f GetFocusOverrideOffset() const {
		return Vector3f{ 0.0,0.0,0.0 };
	}
	virtual IEntity* GetFocusOverrideEntity() const {
		return NULL;
	};
	virtual void OverrideFocusPosition(Vector3f pos, Vector3f offset = Vector3f{ 0, 0, 0 }) {

	};
	virtual void OverrideFocusEntity(IEntity* entity) {

	};
	virtual void ClearFocusOverride() {

	};
	virtual void LoadDefaultIpls() {

	};

	virtual bool IsPointOnScreen(Vector3f point) const {
		return NULL;
	};

	virtual IObject* CreateObject(uint32_t modelHash, Vector3f position, Vector3f rot, bool noOffset = false, bool dynamic = false, IResource* res = nullptr) {
		return NULL;
	}
	virtual const std::vector<IObject*> GetObjects() const {
		return std::vector<IObject*>();
	}
	virtual const std::vector<IObject*> GetWorldObjects() const {
		return std::vector<IObject*>();
	}
	//virtual std::vector<IWebView*> GetWebViews() const = 0;
	//virtual std::vector<IAudio*> GetAudios() const = 0;

	virtual Vector3f GetPedBonePos(int32_t scriptId, uint16_t boneId) const {
		return Vector3f{ 0.0,0.0,0.0 };
	}

	virtual IBaseObject* GetBaseObjectByRemoteID(alt::IBaseObject::Type type, uint32_t id) const {
		return NULL;
	};

	//virtual std::vector<IVirtualEntity*> GetVirtualEntitiesStreamedIn() const = 0;

	virtual const char* GetGxtEntry(uint32_t hash) const {
		return NULL;
	};

	virtual void InternalAddCefBootstrap(const std::string& bootstrap) {};
};


#undef ALT_CLIENT_API