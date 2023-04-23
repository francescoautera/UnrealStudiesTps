# UnrealStudies

# Introduction
An UE4 (version 4.27) project made for studying TPS mechanics. The project has only the player's rifle sound implemented. Here the list of what I faced during the development.

C++ with UE4: a focus on UE4 classes like Pawn, Actor, ActorComponent, Character, AIController
- Delegates and how to bind them in Blueprint
- Animator: work with blendspace, FSM animation, also work with timeline from C++ code
- Implementing TPS mechanics: walk, move camera, aim on the shoulder, cover system, reload, shooting, grenade arch prediction
- Implementing AI with Behaviour tree. In this project I made two kinds of Enemy:
    - The Enemy with red skin who chases the player character and attacks from close
    - The Enemy with blue skin attacks from long range and uses the covers on the battlefield
    - The Enmey with green skin is a boss with 3 phases, first and last phases chase player, mid phase shoot meteorites with arch trajectory
- Implementening room system, in which every room has varius enemies and logic for initizialize and end fight
- Implementing audio system that change music depends on enemy status.

# Input
- Walk: WASD || left stick
- Camera: mouse movement || right stick
- Aim: mouse right click || left trigger LT
- Aim Grenade: X key || left shoulder LB
- Shoot: mouse left click || right trigger RT
- Cover: C key || X button
- Reload: R key || right shoulder RB
- Restart Level: L key
- Quit Game: escape

# Classes
- ATP_ThirdPersonCharacter: this class implements the playable character. Based on the ATP_ThirdPersonCharacter class of the UE4 content pack

- AEnemy: this class handles the mechanics implementation of the enemies

- AAIController: this class implements the sight and hearing senses of the enemies. It runs automatically the given behaviour tree. Behaviour trees are made with the Blueprint tools of UE4.

- ACoverActor: this class implements the covers for the all the Characters in scene

- UHealthComponent: this component implements the health system both ATP_ThirdPersonCharacter and AEnemy are using this to manage health

- FWeaponSlot: this is a structure, used to represents weapons for ATP_ThirdPersonCharacter and AEnemy
