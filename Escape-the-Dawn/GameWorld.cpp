#include "GameWorld.h"


void GameWorld::Initialize()
{
	World::Initialize();

	std::shared_ptr<Components::Transform> transform;
	std::shared_ptr<Components::Model> model;
	std::shared_ptr<Components::PointLight> pointLight;
	std::shared_ptr<Components::Camera> camera;
	std::shared_ptr<Components::Bounds> bounds;
	std::shared_ptr<Components::Collision> collision;
	std::shared_ptr<Components::SoundEmitter> soundEmitter;
	EntityID ent;

	// Fucking lights
	/*ent = CreateEntity();
	transform = AddComponent<Components::Transform>(ent, "Transform");
	transform->Position = glm::vec3(0.f, 7.f, 0.f);
	pointLight = AddComponent<Components::PointLight>(ent, "PointLight");
	pointLight->Specular = glm::vec3(1.0,  1.0,  1.0);
	pointLight->Diffuse = glm::vec3(0.0,  0.0,  5.0);
	pointLight->constantAttenuation = 0.f;
	pointLight->linearAttenuation = 1.f;
	pointLight->quadraticAttenuation = 0.f;
	pointLight->spotExponent = 0.0f;
	model = AddComponent<Components::Model>(ent, "Model");
	model->ModelFile = "Models/sphere.obj";
	ent = CreateEntity();
	transform = AddComponent<Components::Transform>(ent, "Transform");
	transform->Position = glm::vec3(10.f, 7.f, 0.f);
	pointLight = AddComponent<Components::PointLight>(ent, "PointLight");
	pointLight->Specular = glm::vec3(1.0,  1.0,  1.0);
	pointLight->Diffuse = glm::vec3(0.0,  5.0,  0.0);
	pointLight->constantAttenuation = 0.f;
	pointLight->linearAttenuation = 1.f;
	pointLight->quadraticAttenuation = 0.f;
	pointLight->spotExponent = 0.0f;
	model = AddComponent<Components::Model>(ent, "Model");
	model->ModelFile = "Models/sphere.obj";*/
	auto sun = CreateEntity();
	SetProperty(sun, "Name", std::string("Sun"));
	transform = AddComponent<Components::Transform>(sun, "Transform");
	transform->Position = glm::vec3(0.f, 100.f, 30.f);
	AddComponent<Components::Input>(sun, "Input");
	pointLight = AddComponent<Components::PointLight>(sun, "PointLight");
	pointLight->Specular = glm::vec3(1.0,  1.0,  1.0);
	pointLight->Diffuse = glm::vec3(1.0,  0.45,  0.0);
	pointLight->constantAttenuation = 0.009f;
	pointLight->linearAttenuation = -0.0177f;
	pointLight->quadraticAttenuation = 0.00043f;
	pointLight->spotExponent = 0.0f;
	model = AddComponent<Components::Model>(sun, "Model");
	model->ModelFile = "Models/sphere.obj";

	//ground
	auto ground = CreateEntity();
	transform = AddComponent<Components::Transform>(ground, "Transform");
	transform->Position = glm::vec3(0.f, 0.f, 0.f);
	model = AddComponent<Components::Model>(ground, "Model");
	model->ModelFile = "Models/plane.obj";

	// Camera
	entcamera = CreateEntity();
	SetProperty(entcamera, "Name", std::string("Camera"));
	transform = AddComponent<Components::Transform>(entcamera, "Transform");
	AddComponent<Components::Input>(entcamera, "Input");
	transform->Position = glm::vec3(0.f, 10.f, 14.f);
	camera = AddComponent<Components::Camera>(entcamera, "Camera");
	camera->FOV		= glm::radians(45.f);
	camera->FarClip	= 1000.f;
	camera->NearClip	= 0.01f;
	transform->Orientation = glm::angleAxis<float>(glm::radians(15.0f),glm::vec3(1,0,0));

	// Player
	m_Player = CreateEntity();
	SetProperty(m_Player, "Name", std::string("Player"));
	SetProperty(m_Player, "Camera", entcamera);
	SetProperty(m_Player, "Ground", ground);
	SetProperty(m_Player, "Sun", sun);
	transform = AddComponent<Components::Transform>(m_Player, "Transform");
	transform->Position = glm::vec3(0.f, 2.f, -5.f);
	transform->Velocity = glm::vec3(10.f, 0.f, 100.f);
	transform->Scale = glm::vec3(1.0f);
	model = AddComponent<Components::Model>(m_Player, "Model");
	model->ModelFile = "Models/ship.obj";
	model->ShadowCaster = false;
	AddComponent<Components::Input>(m_Player, "Input");
	collision = AddComponent<Components::Collision>(m_Player, "Collision");
	collision->Phantom = false;
	collision->Interested = true;
	bounds = AddComponent<Components::Bounds>(m_Player, "Bounds");
	bounds->Origin = glm::vec3(0, 0, 2.f);
	bounds->VolumeVector = glm::vec3(2.7f, 0.7f, 1);
	// Sound Emitter PowerUp
	auto soundPowerUp = CreateEntity(m_Player);
	{
		AddComponent<Components::Transform>(soundPowerUp, "Transform");
		soundEmitter = AddComponent<Components::SoundEmitter>(soundPowerUp, "SoundEmitter");
		soundEmitter->Gain = 2.5f;
		SetProperty(m_Player, "SoundEmitterPowerUp", soundEmitter.get());
	}
	// Sound Emitter PowerUp
	auto soundEngine = CreateEntity(m_Player);
	{
		AddComponent<Components::Transform>(soundEngine, "Transform");
		soundEmitter = AddComponent<Components::SoundEmitter>(soundEngine, "SoundEmitter");
		soundEmitter->Gain = 1.5f;
		soundEmitter->Path = "Sounds/engine.wav";
		soundEmitter->Loop = true;
		auto soundSystem = GetSystem<Systems::SoundSystem>("SoundSystem");
		soundSystem->PlaySound(soundEmitter.get(), "Sounds/engine.wav");
		SetProperty(m_Player, "SoundEmitterEngine", soundEmitter.get());
	}
	// Player light
	auto playerLight = CreateEntity(m_Player);
	SetProperty(m_Player, "LightLeft", playerLight);
	transform = AddComponent<Components::Transform>(playerLight, "Transform");
	transform->Position = glm::vec3(1.5f, 0.25f, 2.5f);
	pointLight = AddComponent<Components::PointLight>(playerLight, "PointLight");
	pointLight->Specular = glm::vec3(0.1f, 0.1f, 0.1f);
	pointLight->Diffuse = glm::vec3(0.05f, 0.36f, 1.f);
	pointLight->constantAttenuation = 0.f;
	pointLight->linearAttenuation = 0.9f;
	pointLight->quadraticAttenuation = 0.f;
	pointLight->spotExponent = 0.0f;
	bounds = AddComponent<Components::Bounds>(playerLight, "Bounds");
	bounds->VolumeVector = glm::vec3(0.5f);
	playerLight = CreateEntity(m_Player);
	SetProperty(m_Player, "LightRight", playerLight);
	transform = AddComponent<Components::Transform>(playerLight, "Transform");
	transform->Position = glm::vec3(-1.5f, 0.25f, 2.5f);
	pointLight = AddComponent<Components::PointLight>(playerLight, "PointLight");
	pointLight->Specular = glm::vec3(0.1f, 0.1f, 0.1f);
	pointLight->Diffuse = glm::vec3(0.05f, 0.36f, 1.f);
	pointLight->constantAttenuation = 0.f;
	pointLight->linearAttenuation = 0.9f;
	pointLight->quadraticAttenuation = 0.f;
	pointLight->spotExponent = 0.0f;
	bounds = AddComponent<Components::Bounds>(playerLight, "Bounds");
	bounds->VolumeVector = glm::vec3(0.5f);
	playerLight = CreateEntity(m_Player);
	transform = AddComponent<Components::Transform>(playerLight, "Transform");
	transform->Position = glm::vec3(0.0f, 2.0f, 2.5f);
	pointLight = AddComponent<Components::PointLight>(playerLight, "PointLight");
	pointLight->Specular = glm::vec3(0.1f, 0.1f, 0.1f);
	pointLight->Diffuse = glm::vec3(0.05f, 0.36f, 1.f);
	pointLight->constantAttenuation = 0.f;
	pointLight->linearAttenuation = 1.0f;
	pointLight->quadraticAttenuation = 0.f;
	pointLight->spotExponent = 0.0f;
	bounds = AddComponent<Components::Bounds>(playerLight, "Bounds");
	bounds->VolumeVector = glm::vec3(0.5f);
	// Player sound

	/*ent = CreateEntity();
	transform = AddComponent<Components::Transform>(ent, "Transform");
	transform->Position = glm::vec3(10.f, 4.f, 0.f);
	model = AddComponent<Components::Model>(ent, "Model");
	model->ModelFile = "Models/ship.obj";
	collision = AddComponent<Components::Collision>(player2, "Collision");
	collision->Phantom = false;
	bounds = AddComponent<Components::Bounds>(player2, "Bounds");
	bounds->Origin = transform->Position;
	bounds->VolumeVector = glm::vec3(2.f,2.f,2.f);*/
}

void GameWorld::Update(double dt)
{
	World::Update(dt);
}

void GameWorld::RegisterComponents()
{
	m_ComponentFactory.Register("Bounds", []() { return new Components::Bounds(); });
	m_ComponentFactory.Register("Camera", []() { return new Components::Camera(); });
	m_ComponentFactory.Register("Collision", []() { return new Components::Collision(); });
	m_ComponentFactory.Register("DirectionalLight", []() { return new Components::DirectionalLight(); });
	m_ComponentFactory.Register("Input", []() { return new Components::Input(); });
	m_ComponentFactory.Register("Model", []() { return new Components::Model(); });
	m_ComponentFactory.Register("ParticleEmitter", []() { return new Components::ParticleEmitter(); });
	m_ComponentFactory.Register("PointLight", []() { return new Components::PointLight(); });
	m_ComponentFactory.Register("PowerUp", []() { return new Components::PowerUp(); });
	m_ComponentFactory.Register("SoundEmitter", []() { return new Components::SoundEmitter(); });
	m_ComponentFactory.Register("Sprite", []() { return new Components::Sprite(); });
	m_ComponentFactory.Register("Stat", []() { return new Components::Stat(); });
	m_ComponentFactory.Register("Template", []() { return new Components::Template(); });
	m_ComponentFactory.Register("Transform", []() { return new Components::Transform(); });
}

void GameWorld::RegisterSystems()
{
	m_SystemFactory.Register("LevelGenerationSystem", [this]() { return new Systems::LevelGenerationSystem(this); });
	m_SystemFactory.Register("InputSystem", [this]() { return new Systems::InputSystem(this, m_Renderer); });
	m_SystemFactory.Register("CollisionSystem", [this]() { return new Systems::CollisionSystem(this); });
	//m_SystemFactory.Register("ParticleSystem", [this]() { return new Systems::ParticleSystem(this); });
	m_SystemFactory.Register("PlayerSystem", [this]() { return new Systems::PlayerSystem(this); });
	m_SystemFactory.Register("SoundSystem", [this]() { return new Systems::SoundSystem(this); });
	m_SystemFactory.Register("TransformSystem", [this]() { return new Systems::TransformSystem(this); });
	m_SystemFactory.Register("RenderSystem", [this]() { return new Systems::RenderSystem(this, m_Renderer); });
}

void GameWorld::AddSystems()
{
	AddSystem("TransformSystem");
	AddSystem("LevelGenerationSystem");
	AddSystem("InputSystem");
	AddSystem("CollisionSystem");
	//AddSystem("ParticleSystem");
	AddSystem("PlayerSystem");
	AddSystem("SoundSystem");
	AddSystem("RenderSystem");
}