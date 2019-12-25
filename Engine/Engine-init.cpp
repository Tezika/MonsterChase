#include "stdafx.h"
#include "Engine-init.h"
#include "ConsolePrint.h"
#include "HeapManager.h"
#include "SubSystemHeaders.h"
#include "MemorySystem.h"
#include "MessageSystem.h"
#include <Audio/Audio.h>

namespace Engine
{
	bool Engine::Initialize( HINSTANCE i_hInstance, int i_nCmdShow, int i_wWidth, int i_wHeight, const char* i_pWindowName )
	{
#ifdef USE_CUSTOM_MEMORYMANAGEMENT
		// Initial the memory system
		// For ~100M memory
		const size_t 	 sizeHeap = 100 * 1000 * 1000;
		const unsigned int 	numDescriptors = 2048;
		// Allocate memory for my test heap.
		void* pHeapMemory = HeapAlloc( GetProcessHeap(), 0, sizeHeap );
		_ASSERT_EXPR( pHeapMemory, L"Allocate the memory failed." );

		// Create your HeapManager and FixedSizeAllocators.
		bool successd = InitializeMemorySystem( pHeapMemory, sizeHeap, numDescriptors );
		_ASSERT_EXPR( successd, L"Failed to initialize the memory system." );
#endif
		// Initialize the sub systems
		bool bSuccess = false;

		// For Message System
		bSuccess = Messaging::MessageSystem::GetInstance().Initialize();
		_ASSERT_EXPR( bSuccess, L"Failed to initialize the message system." );

		// For Physics
		bSuccess = Physics::PhysicsManager::GetInstance().Initialize();
		_ASSERT_EXPR( bSuccess, L"Failed to initialize the physics system." );

		// For Rendering
		bSuccess = Render::RenderManager::GetInstance().Initialize( i_hInstance, i_nCmdShow, i_wWidth, i_wHeight, i_pWindowName );
		_ASSERT_EXPR( bSuccess, L"Failed to initialize the renderring system." );

		// For Controller Manager
		bSuccess = Controller::ControllerManager::GetInstance().Initialize();
		_ASSERT_EXPR( bSuccess, L"Failed to initialize the controller system." );

		// For Audio system
		Audio::sAudioInitializationParameters audioInitializationParamters;
		bSuccess = Audio::Initialize( audioInitializationParamters );
		_ASSERT_EXPR( bSuccess, L"Faild to initialize the audio system." );
		return true;
	}

	void Engine::Destroy()
	{
		// Destroy the sub systems firstly
		bool bSuccess = false;
		// For Physics
		bSuccess = Physics::PhysicsManager::GetInstance().Destroy();
		_ASSERT_EXPR( bSuccess, L"Failed to uninitialize the physics system." );

		// For Controller Manager
		bSuccess = Controller::ControllerManager::GetInstance().Destroy();
		_ASSERT_EXPR( bSuccess, L"Failed to uninitialize the controller system." );

		// For Rendering
		bSuccess = Render::RenderManager::GetInstance().Destroy();
		_ASSERT_EXPR( bSuccess, L"Failed to uninitialize the rendering system." );

		// For Messaging
		bSuccess = Messaging::MessageSystem::GetInstance().Destroy();
		_ASSERT_EXPR( bSuccess, L"Failed to uninitialize the messaging system." );

		// For Audio system
		bSuccess = Audio::CleanUp();
		_ASSERT_EXPR( bSuccess, L"Failed to unintialize the audio system." );

#ifdef USE_CUSTOM_MEMORYMANAGEMENT
		// Destroy the memory management system
		DestroyMemorySystem();
#endif // USE_FIXED_ALLOCATORS
	}
}