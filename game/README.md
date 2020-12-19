# Game
Game stuff

Has the engine, compiles to the playable game

## Why so many singletons
This is so I can have self registering clients of a manager, this will be
better for extensible code because then you will not have to manually register
a ton of classes in the manager, it can also hide the implementation of the
manager but I'm not too worried about that

I am not here to support or attack singletons, I am just using them because
it makes registering things easier for me

Since many people don't like singletons, here is a list of all being used
(to make sure the amount of them don't go out of hand)

- Game::Core (kinda)
- Game::ECS::ComponentManager
- Game::ECS::SystemManager
- Game::SceneManager

Another note I would like to add is if I make this a full fledged 2D game engine later,
these are the managers of which the user can (and should be) creating clients for

## To-do
- Components, Systems, Scenes, etc. should not be initializable except for the respective manager class
