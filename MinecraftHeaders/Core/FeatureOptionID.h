#pragma once

 enum class FeatureOptionID {
	None                             = 0,
	NetworkLogAllPackets             = 1, // Enable Packet Profiling
	Scoreboards                      = 2, // Scoreboards
	Functions                        = 3, // Functions
	UIAsyncLoadingAndAnimations      = 4, // UI Async Loading and Screen Animations
	Allow3rdPartyServerSplitscreen   = 5, // Allow 3rd Party Server Splitscreen
	ExperimentalGameplayInAllWorlds  = 6, // Default new worlds to be experimental on
	Hummingbird                      = 7, // New Scripting and UI Infrastructure (requires restart)
	HummingbirdDebugging             = 8, // Enable Hummingbird Debugging (requires restart and the infrastructure)
	UIRefresh                        = 9, // Experimental UI (requires the infrastructure)
	Scripting                        = 10, // Experimental Scripting (requires restart and the infrastructure)
	Realms                           = 11, // Realms Enabled
	RealmsContent                    = 12, // Realms Content
	EnableLoadTimer                  = 13, // Enable Load Timers
	ExternalWorldTemplatePackSources = 14, // External World Template Pack Sources
	Win10Subscriptions               = 15, // Enable Win10 subscriptions
	PlayerRenaming                   = 16, // Enable Player Renaming After Sign-in (requires restart)
	PersonaBackend                   = 17, // ***DOES NOT EXIST***
	PersonaSkin                      = 18, // ***DOES NOT EXIST***
	PlayFabInsightsTelemetry         = 19, // Enable PlayFab Insights (requires restart)
	PersonaEnabled                   = 20, // Enable Persona
	PersonaServiceEnabled            = 21, // Enable Persona Service
	PersonaTestCatalog               = 22, // Enable Persona Testing Resource Pack
	PersonaCape                      = 23, // ***DOES NOT EXIST***
	PersonaFeatures                  = 24, // Enable Persona Features
	PersonaChallengeFeature          = 25, // Enable Persona Challenge Feature
	StorefrontTestLayouts            = 26, // Enable Store Test Layouts
	UseDevOffersIfAvailable          = 27, // Enable Dev Offers
	RenderDragonRenderPath           = 28, // Experimental Render Path
	BaseGameVersioniningTestPacks    = 29, // Enables the use of test packs for base game versioning
	LevelStoragePerfLog              = 30, // ***DOES NOT EXIST***
	TrueTypeFontLoading              = 31, // Load true type fonts specified in font_metadata.json when booting the application
	EnableItemStackNetManager        = 32, // Enable ItemStackNetManager (requires server restart)
	PauseMenuOnFocusLost             = 33 // Show the pause menu screen upon the app losing focus
};