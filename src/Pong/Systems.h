#pragma once
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <print.h>
#include <FastNoise.h>
#include <random>
#include <ctime>
#include <sol/sol.hpp>
#include <Game/ScriptingManager.h>

#include "Components.h"

#include "ECS/Components.h"
#include "ECS/Entity.h"
#include "ECS/SystemTypes/SetupSystem.h"
#include "ECS/SystemTypes/SystemTypes.h"

#include "ECS/SystemTypes/UpdateSystem.h"
#include "Game/Graphics/TextureManager.h"


class HelloWorldSystem : public SetupSystem {
  public:
    HelloWorldSystem() {
      print("Hello World Constructor");
    }

    ~HelloWorldSystem() {
      print("Hello World Destructor");
    }

    void run() {
      print("Hello World run!");
    }
};

class MovementUpdateSystem : public UpdateSystem {
  public:
    void run(float dT) {
      const auto playerView = scene->r.view<TransformComponent, SpeedComponent>();

      for (const auto entity : playerView) {
        auto& t = playerView.get<TransformComponent>(entity);
        auto& s = playerView.get<SpeedComponent>(entity);
        if (s.x == 0 && s.y == 0) {
          continue;
        }
        t.x += s.x * dT;
        t.y += s.y * dT;
      }

      const auto bulletView = scene->r.view<TransformComponent,SpeedComponent,BulletComponent>();

      for (const auto entity : bulletView) {
        auto& t = bulletView.get<TransformComponent>(entity);
        auto& s = bulletView.get<SpeedComponent>(entity);
        auto& b = bulletView.get<BulletComponent>(entity);

        t.x += s.x * dT;
        t.y += s.y * dT;
        b.lifetime -= dT;
        if(b.lifetime <= 0){
          scene->r.destroy(entity);
        }
      }
  }
};


class PlayerInputSystem : public EventSystem {
  void run(SDL_Event event) {
    auto& playerSpeed = scene->player->get<SpeedComponent>();
    auto& shadowSpeed = scene->shadow->get<SpeedComponent>();
    auto& heart1Speed = scene->heart1->get<SpeedComponent>();
    auto& heart2Speed  = scene->heart2->get<SpeedComponent>();
    auto& heart3Speed  = scene->heart3->get<SpeedComponent>();
    
    int speed = 350;

    if (event.type == SDL_KEYDOWN) {
      
      if(event.key.keysym.sym == SDLK_a){
        const auto playerTransformComponent = scene->player->get<TransformComponent>();
        scene->bullet = new Entity(scene->r.create(), scene);
          scene->bullet->addComponent<TransformComponent>(playerTransformComponent.x,playerTransformComponent.y);
          auto& bulletSprite = scene->bullet->addComponent<SpriteComponent>(
            "Sprites/Cat/final.png",
            0, 9,
            48,
            4,
            250
            );
            bulletSprite.lastUpdate = SDL_GetTicks();
            scene->bullet->addComponent<ColliderComponent>(19, 19, 10, 10, SDL_Color{200, 0, 200});
            scene->bullet->addComponent<BulletComponent>();
            scene->bullet->addComponent<SpeedComponent>(-375,0);
      }
      else if(event.key.keysym.sym == SDLK_w){
        const auto playerTransformComponent = scene->player->get<TransformComponent>();
        scene->bullet = new Entity(scene->r.create(), scene);
          scene->bullet->addComponent<TransformComponent>(playerTransformComponent.x,playerTransformComponent.y);
          auto& bulletSprite = scene->bullet->addComponent<SpriteComponent>(
            "Sprites/Cat/final.png",
            0, 9,
            48,
            4,
            250
            );
            bulletSprite.lastUpdate = SDL_GetTicks();
            scene->bullet->addComponent<ColliderComponent>(19, 19, 10, 10, SDL_Color{200, 0, 200});
            scene->bullet->addComponent<BulletComponent>();
            scene->bullet->addComponent<SpeedComponent>(0,-375);
      }
      else if(event.key.keysym.sym == SDLK_s){
        const auto playerTransformComponent = scene->player->get<TransformComponent>();
        scene->bullet = new Entity(scene->r.create(), scene);
          scene->bullet->addComponent<TransformComponent>(playerTransformComponent.x,playerTransformComponent.y);
          auto& bulletSprite = scene->bullet->addComponent<SpriteComponent>(
            "Sprites/Cat/final.png",
            0, 9,
            48,
            4,
            250
            );
            bulletSprite.lastUpdate = SDL_GetTicks();
            scene->bullet->addComponent<ColliderComponent>(19, 19, 10, 10, SDL_Color{200, 0, 200});
            scene->bullet->addComponent<BulletComponent>();
            scene->bullet->addComponent<SpeedComponent>(0,375);
      }
      else if(event.key.keysym.sym == SDLK_d){
        const auto playerTransformComponent = scene->player->get<TransformComponent>();
        scene->bullet = new Entity(scene->r.create(), scene);
          scene->bullet->addComponent<TransformComponent>(playerTransformComponent.x,playerTransformComponent.y);
          auto& bulletSprite = scene->bullet->addComponent<SpriteComponent>(
            "Sprites/Cat/final.png",
            0, 9,
            48,
            4,
            250
            );
            bulletSprite.lastUpdate = SDL_GetTicks();
            scene->bullet->addComponent<ColliderComponent>(19, 19, 10, 10, SDL_Color{200, 0, 200});
            scene->bullet->addComponent<BulletComponent>();
            scene->bullet->addComponent<SpeedComponent>(375,0);
      }
      else if(event.key.keysym.sym == SDLK_RIGHT){
          playerSpeed.x = speed;
          shadowSpeed.x = speed;
          heart1Speed.x = speed;
          heart2Speed.x = speed;
          heart3Speed.x = speed;
      }
      else if(event.key.keysym.sym == SDLK_LEFT){
          playerSpeed.x = -speed;
          shadowSpeed.x = -speed;
          heart1Speed.x = -speed;
          heart2Speed.x = -speed;
          heart3Speed.x = -speed;
      }
      else if(event.key.keysym.sym == SDLK_UP){
          playerSpeed.y = -speed;
          shadowSpeed.y = -speed;
          heart1Speed.y = -speed;
          heart2Speed.y = -speed;
          heart3Speed.y = -speed;
      }
      else if(event.key.keysym.sym == SDLK_DOWN){
          playerSpeed.y = speed;
          shadowSpeed.y = speed;
          heart1Speed.y = speed;
          heart2Speed.y = speed;
          heart3Speed.y = speed;
      }
      else if(event.key.keysym.sym == SDLK_h){
          auto view = scene->r.view<EnemyComponent, TransformComponent>();
          for(auto entity: view){
            auto& enemy = view.get<EnemyComponent>(entity);

            if(enemy.id == 1){
                          print("DESTRY:");
            print(enemy.id);
            
                scene->r.destroy(entity);
                ScriptingManager::lua["reset_enemy"](enemy.id);
            }
            }
      }
    }
    if (event.type == SDL_KEYUP) {
      switch(event.key.keysym.sym) {
        case SDLK_RIGHT:
          playerSpeed.x = 0;
          shadowSpeed.x = 0;
          heart1Speed.x = 0;
          heart2Speed.x = 0;
          heart3Speed.x = 0;
          break;
        case SDLK_LEFT:
          playerSpeed.x = 0;
          shadowSpeed.x = 0;
          heart1Speed.x = 0;
          heart2Speed.x = 0;
          heart3Speed.x = 0;
          break;
        case SDLK_UP:
          playerSpeed.y = 0;
          shadowSpeed.y = 0;
          heart1Speed.y = 0;
          heart2Speed.y = 0;
          heart3Speed.y = 0;
          break;
        case SDLK_DOWN:
          playerSpeed.y = 0;
          shadowSpeed.y = 0;
          heart1Speed.y = 0;
          heart2Speed.y = 0;
          heart3Speed.y = 0;
          break;
      }
    }
  }
};

class SpriteSetupSystem : public SetupSystem {
  public:
    SpriteSetupSystem(SDL_Renderer* renderer)
      : renderer(renderer) { }

    ~SpriteSetupSystem() {
      auto view = scene->r.view<SpriteComponent>();

      for(auto entity : view) {
        const auto spriteComponent = view.get<SpriteComponent>(entity);
  
        TextureManager::UnloadTexture(spriteComponent.name, spriteComponent.shader.name);
      }
    }

    void run() {
      auto view = scene->r.view<SpriteComponent>();

      for(auto entity : view) {
        const auto spriteComponent = view.get<SpriteComponent>(entity);
  
        TextureManager::LoadTexture(spriteComponent.name, renderer, spriteComponent.shader);
      }
    }

  private:
    SDL_Renderer* renderer;
};

class SpriteRenderSystem : public RenderSystem {
  public:
    void run(SDL_Renderer* renderer) {
      auto view = scene->r.view<TransformComponent, SpriteComponent>();
      const auto c = scene->mainCamera->get<TransformComponent>();
      const auto z = scene->mainCamera->get<CameraComponent>().zoom;

      for(auto entity : view) {
        const auto spriteComponent = view.get<SpriteComponent>(entity);
        const auto transformComponent = view.get<TransformComponent>(entity);
  
        Texture* texture = TextureManager::GetTexture(spriteComponent.name, spriteComponent.shader.name);
  
        SDL_Rect clip = {
          spriteComponent.xIndex * spriteComponent.size,
          spriteComponent.yIndex * spriteComponent.size,
          spriteComponent.size,
          spriteComponent.size
        };

        texture->render(
          transformComponent.x - c.x,
          transformComponent.y - c.y,
          48 * z,
          48 * z,
          &clip
        );
      }
    }
};

class SpriteUpdateSystem : public UpdateSystem {
  public:
    void run(float dT) {
      auto view = scene->r.view<SpriteComponent>();

      Uint32 now = SDL_GetTicks();

      for(auto entity : view) {
        auto& spriteComponent = view.get<SpriteComponent>(entity);

        if (spriteComponent.animationFrames > 0) {
          float timeSinceLastUpdate = now - spriteComponent.lastUpdate;

          int framesToUpdate = static_cast<int>(
            timeSinceLastUpdate / 
            spriteComponent.animationDuration * spriteComponent.animationFrames
          );

          if (framesToUpdate > 0) {
            spriteComponent.xIndex += framesToUpdate;
            spriteComponent.xIndex %= spriteComponent.animationFrames;
            spriteComponent.lastUpdate = now;            
          }
        }
      }
    }
};


class TilemapSetupSystem : public SetupSystem {
  public:
    TilemapSetupSystem(SDL_Renderer* renderer)
      : renderer(renderer) { }

    ~TilemapSetupSystem() {
    }

    void run() {
      const auto playerPosition = scene->player->get<TransformComponent>();
      const auto z = scene->mainCamera->get<CameraComponent>().zoom;
      Texture* waterTexture = TextureManager::LoadTexture("Tilesets/Water.png", renderer);
      Texture* grassTexture = TextureManager::LoadTexture("Tilesets/Grass.png", renderer);

      auto& tilemap = scene->world->get<TilemapComponent>();
      tilemap.map.resize(tilemap.width * tilemap.height);
      tilemap.width = 25;
      tilemap.height = 25; 

      Terrain grass{grassTexture};
      Terrain water{waterTexture};

      int predeterminedMatrix[25][25] = {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1},
            {1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
        };

      int centerX = playerPosition.x / z / tilemap.tileSize;
      int centerY = playerPosition.y / z / tilemap.tileSize;

      for (int y = 0; y < tilemap.height; y++) {
        for (int x = 0; x < tilemap.width; x++) {

          float factor = predeterminedMatrix[y][x];        

          int index = y * tilemap.width + x;

          Tile& tile = tilemap.map[index];

          if (factor == 1) {
            tile.up = grass;
            tile.down = water;
            tile.needsAutoTiling = true;
          } else {
            tile.up = water;
            tile.needsAutoTiling = false;
            tile.isWalkable = false;
          }
        }
      }

   }

  private:
    SDL_Renderer* renderer;
};


class TilemapRenderSystem : public RenderSystem {
  public:
    void run(SDL_Renderer* renderer) {
      auto& tilemap = scene->world->get<TilemapComponent>();
      const auto c = scene->mainCamera->get<TransformComponent>();
      const auto cameraComponent = scene->mainCamera->get<CameraComponent>();
      const int z = cameraComponent.zoom;
      int size = tilemap.tileSize;

      int startX = std::max(0, c.x / (size * z));
      int endX = std::min(tilemap.width, (c.x + cameraComponent.viewportWidth) / (size * z));
      int startY = std::max(0, c.y / (size * z));
      int endY = std::min(tilemap.height, (c.y + cameraComponent.viewportHeight) / (size * z));


      for (int y = startY; y <= endY; y++) {
        for (int x = startX; x <= endX; x++) {
          Tile tile = tilemap.map[y * tilemap.width + x];

          int renderSize = tilemap.tileSize * z;

          if (tile.down.texture) {
            SDL_Rect downClip = {
              tile.down.x,
              tile.down.y,
              size,
              size
            };

            tile.down.texture->render(
              x * renderSize - c.x,
              y * renderSize - c.y,
              renderSize,
              renderSize,
              &downClip
            );
          }
          SDL_Rect upClip = {
              tile.up.x,
              tile.up.y,
              size,
              size
          };
          tile.up.texture->render(
            x * renderSize - c.x,
            y * renderSize - c.y,
            renderSize,
            renderSize,
            &upClip
          );
        }
      }
    }
};

std::map<u_int8_t, std::vector<std::pair<int, int>>> m = {
    {  2, {{   0,  80 }} },
    {  8, {{  48,  96 }} },
    { 10, {{  80, 112 }} },
    { 11, {{  48,  80 }} },
    { 16, {{   0,  96 }} },
    { 18, {{  64, 112 }} },
    { 22, {{  16,  80 }} },
    { 24, {{  16,  96 }, {  32,  96 }} },
    { 26, {{ 144,  32 }} },
    { 27, {{ 144,  80 }} },
    { 30, {{  96,  80 }} },
    { 31, {{  32,  80 }} },
    { 64, {{   0,  32 }} },
    { 66, {{   0,  48 }, {   0,  64 }} },
    { 72, {{  80,  96 }} },
    { 74, {{ 128,  32 }} },
    { 75, {{ 112,  80 }} },
    { 80, {{  64,  96 }} },
    { 82, {{ 144,  48 }} },
    { 86, {{ 128,  80 }} },
    { 88, {{ 128,  48 }} },
    { 90, {{   0, 112 }, {  16, 112 }} },
    { 91, {{  32, 112 }} },
    { 94, {{  96,  48 }} },
    { 95, {{  96, 112 }} },
    {104, {{  48,  48 }} },
    {106, {{ 144,  64 }} },
    {107, {{  48,  64 }} },
    {120, {{ 112,  64 }} },
    {122, {{  48, 112 }} },
    {123, {{ 112, 112 }} },
    {126, {{  48, 112 }} },
    {127, {{  64,  64 }} },
    {208, {{  16,  48 }} },
    {210, {{  96,  64 }} },
    {214, {{  16,  64 }} },
    {216, {{ 128,  64 }} },
    {218, {{  96,  32 }} },
    {219, {{  32, 112 }} },
    {222, {{  96,  96 }} },
    {223, {{  80,  64 }} },
    {248, {{  32,  48 }} },
    {250, {{ 112,  96 }} },
    {251, {{  64,  80 }} },
    {254, {{  80,  80 }} },
    {255, {
            {   0,   0 }, {  16,   0 }, {  32,   0 }, {  48,   0 }, {  64,   0 }, {  80,   0 },
            {   0,  16 }, {  16,  16 }, {  32,  16 }, {  48,  16 }, {  64,  16 }, {  80,  16 },
            {  32,  64 }
          }
    },
    {  0, {
            { 16,  32 }, {  32,  32 }, {  48,  32 },
            { 64,  32 }, {  80,  32 }, {  64,  48 }, {  80,  48 }
          }
    }
};


const int dx[8] = { -1,  0,  1, -1, 1, -1, 0, 1 }; 
const int dy[8] = { -1, -1, -1,  0, 0,  1, 1, 1 };

std::map<u_int8_t, std::pair<int, int>> d_corner = {
  {0, {  1,  1 }},
  {2, { -1,  1 }},
  {5, {  1, -1 }},
  {7, { -1, -1 }},
};

class AutoTilingSetupSystem : public SetupSystem {
public:
  void run() {
    auto& tilemapComponent = scene->world->get<TilemapComponent>();
    int width = tilemapComponent.width;
    int height = tilemapComponent.height;
    int size = tilemapComponent.tileSize;
    // Loop through each tile in the tilemap
    for (int y = 0; y < tilemapComponent.height; y++) {
      for (int x = 0; x < tilemapComponent.width; x++) {
        int index = y * width + x;
        auto& tilemap = tilemapComponent.map;
        Tile& tile = tilemap[index];

        if (!tile.needsAutoTiling)
          continue;


        uint8_t surrounding = 0;
        // Loop through each of the eight directions
        for (int i = 0; i < 8; i++) {
          // Calculate the coordinates of the neighboring tile
          int nx = x + dx[i];
          int ny = y + dy[i];

          // Check if the coordinates are out of bounds
          if (nx < 0 || nx >= width || ny < 0 || ny >= height) {
            continue;  // If out of bounds, skip this iteration
          }

          // For corner tiles, check the two adjacent cardinal directions
          if (i == 0 || i == 2 || i == 5 || i == 7) {  // i is 0, 2, 5, 7 for corner tiles
            int nx1 = nx + d_corner[i].first; 
            int ny1 = ny + 0;  // This is for legibility
            int nx2 = nx + 0;
            int ny2 = ny + d_corner[i].second;

            // If either of the cardinal tiles are missing, skip this iteration
            if (nx1 < 0 || nx1 >= width || ny1 < 0 || ny1 >= height || 
              nx2 < 0 || nx2 >= width || ny2 < 0 || ny2 >= height) {
              continue;
            }

            if (tilemap[ny1 * width + nx1].up.texture != tilemap[ny * width + nx].up.texture || 
              tilemap[ny2 * width + nx2].up.texture != tilemap[ny * width + nx].up.texture)
            {
              continue;
            }
          }

          int neighborIndex = ny * width + nx;
          // Get the Tile of the neighboring tile
          const Tile& neighborTile = tilemap[neighborIndex];
          if (tile.up.texture == neighborTile.up.texture) {
            surrounding |= 1 << i;          
          } 
        }
        auto iter = m.find(surrounding);

        if (iter == m.end()) {
          tile.up.x = 0;
          tile.up.y = 0;
          print("Tile not found", static_cast<int>(surrounding));
          exit(1);
        } else {
          auto& pairs = iter->second;

          if (pairs.size() == 1) {
            tile.up.x = pairs[0].first;
            tile.up.y = pairs[0].second;
          } else {
            int index = rand() % pairs.size();
            tile.up.x = pairs[index].first;
            tile.up.y = pairs[index].second;
          }
        }
      }
    }
  } 
};

class WorldSetupSystem : public SetupSystem {
  public:
    void run() {
      int tilemapWidth = 50;
      int tilemapHeight = 38;
      int tilemapTileSize = 16;

      scene->world = new Entity(scene->r.create(), scene);
      scene->world->addComponent<TilemapComponent>(tilemapWidth, tilemapHeight, tilemapTileSize);
      scene->world->addComponent<WorldComponent>(tilemapWidth * tilemapTileSize, tilemapHeight*tilemapTileSize);
    }
};

class CameraSetupSystem : public SetupSystem {
  public:
    void run() {
      const auto worldComponent = scene->world->get<WorldComponent>();
      
      int cameraWidth = 800;
      int cameraHeight = 600;
      int x = worldComponent.width / 2 - cameraWidth / 2;
      int y = worldComponent.height / 2 - cameraHeight / 2;
      float zoom = 4;

      scene->mainCamera = new Entity(scene->r.create(), scene);
      scene->mainCamera->addComponent<TransformComponent>(x, y);
      scene->mainCamera->addComponent<CameraComponent>(cameraWidth, cameraHeight, zoom);
    }
};

class EnemySetupSystem : public SetupSystem{
  public:
  void run(){
    ScriptingManager::init();
    ScriptingManager::runScriptFile("script.lua");

    sol::table enemies = ScriptingManager::lua["enemies"];
    enemies.for_each([&](sol::object const& key, sol::object const& value){
      sol::table enemy = value.as<sol::table>();
      int x = enemy["x"];
      int y = enemy["y"];
      int id = key.as<int>();
      int hp = key.as<int>();

      scene->enemyEntity = new Entity(scene->r.create(),scene);
      scene->enemyEntity->addComponent<TransformComponent>(x,y);
      auto& enemySprite = scene->enemyEntity->addComponent<SpriteComponent>(
        "Sprites/Cat/final.png",
            0, 11,
            48,
            4,
            500
      );
      enemySprite.lastUpdate = SDL_GetTicks();
      scene->enemyEntity->addComponent<EnemyComponent>(id,hp);
    });
      ScriptingManager::runScriptFile("enemyMove.lua");
  }
};

class EnemyUpdateSystem : public UpdateSystem{
  public:
  void run(float dT){
  int speed = 250 * dT;
  const auto playerPosition = scene->player->get<TransformComponent>();

  ScriptingManager::lua["update_enemies"](speed, playerPosition.x, playerPosition.y);
  //print(speed);
  sol::table enemies = ScriptingManager::lua["enemies"];
  auto view = scene->r.view<EnemyComponent, TransformComponent>();

  int size = 0;

  for(auto entity: view){

    auto& transformComponent = view.get<TransformComponent>(entity);
    const auto enemyComponent = view.get<EnemyComponent>(entity);
    
    sol::table enemy = enemies[enemyComponent.id];
    float x = enemy["x"];
    float y = enemy["y"];
    
    //print(x,y);

    transformComponent.x = (int) x;
    transformComponent.y = (int)y;
    size++;
    }

    int asd = 1;//rand() % 4 + 1;

  if(size < 4 && dT != 0){

    //ScriptingManager::init();
    //ScriptingManager::runScriptFile("script.lua");
      print(asd);
        scene->enemyEntity = new Entity(scene->r.create(),scene);
      scene->enemyEntity->addComponent<TransformComponent>(1500,1500);
      auto& enemySprite = scene->enemyEntity->addComponent<SpriteComponent>(
        "Sprites/Cat/final.png",
            0, 11,
            48,
            4,
            500
      );
      enemySprite.lastUpdate = SDL_GetTicks();
      scene->enemyEntity->addComponent<EnemyComponent>(1,3);
      

  }
  
  }
};

class PlayerSetupSystem : public SetupSystem {
  public:
    void run() {
      const auto worldComponent = scene->world->get<WorldComponent>();
      const auto cameraComponent = scene->mainCamera->get<CameraComponent>();
      int spriteSize = 48;
      int x = worldComponent.width / 2 - (spriteSize * cameraComponent.zoom) / 2;
      int y = worldComponent.height / 2 - (spriteSize * cameraComponent.zoom) / 2;
 
      scene->player = new Entity(scene->r.create(), scene);
      scene->player->addComponent<TransformComponent>(x, y);
      scene->player->addComponent<HPComponent>(3);
      scene->player->addComponent<ScoreComponent>(0);
      auto& s1 = scene->player->addComponent<SpriteComponent>(
        "Sprites/Cat/final.png",
        0, 0,
        spriteSize,
        4,
        500
      );
      s1.lastUpdate = SDL_GetTicks();
      scene->player->addComponent<ColliderComponent>(19, 18, 10, 14, SDL_Color{200, 0, 200});

      scene->shadow = new Entity(scene->r.create(), scene);
      scene->shadow->addComponent<TransformComponent>(x-5, y);
      auto& s2 = scene->shadow->addComponent<SpriteComponent>(
        "Sprites/Cat/final.png",
        0, 0,
        spriteSize,
        4,
        500,PixelShader{
          [](Uint32 color) -> Uint32 {return (color == 0xEEC39AFF || color == 0x663931FF || color == 0x9BADB7FF || color == 0xFFFFFFFF) ? 0x000000FF: color;},
          "shadow"
        }
      );
      s2.lastUpdate = SDL_GetTicks();

      scene->heart1 = new Entity(scene->r.create(), scene);
    scene->heart1->addComponent<TransformComponent>(x-10, y+70);
    scene->heart1->addComponent<SpeedComponent>();
    scene->heart1->addComponent<SpriteComponent>(
        "Sprites/Cat/final.png",
        0, 10,
        48,
        0,
        0
      );

    scene->heart2 = new Entity(scene->r.create(), scene);
    scene->heart2->addComponent<TransformComponent>(x+20, y+70);
    scene->heart2->addComponent<SpeedComponent>();
    scene->heart2->addComponent<SpriteComponent>(
        "Sprites/Cat/final.png",
        0, 10,
        48,
        0,
        0
      );

    scene->heart3 = new Entity(scene->r.create(), scene);
    scene->heart3->addComponent<TransformComponent>(x+50, y+70);
    scene->heart3->addComponent<SpeedComponent>();
    scene->heart3->addComponent<SpriteComponent>(
        "Sprites/Cat/final.png",
        0, 10,
        48,
        0,
        0
      );

    }
};

class PlayerSpriteUpdateSystem : public UpdateSystem {
public:
  void run(float dT) {
    const auto playerSpeed = scene->player->get<SpeedComponent>();
    auto& playerSprite = scene->player->get<SpriteComponent>();
    auto& playerShadow = scene->shadow->get<SpriteComponent>();

    if (playerSpeed.x < 0) {
      playerSprite.yIndex = 7;
      playerShadow.yIndex = 7;
    }
    else if (playerSpeed.x > 0) {
      playerSprite.yIndex = 6;
      playerShadow.yIndex = 6;
    }
    else if (playerSpeed.y < 0) {
      playerSprite.yIndex = 5;
      playerShadow.yIndex = 5;
    }
    else if (playerSpeed.y > 0) {
      playerSprite.yIndex = 4;
      playerShadow.yIndex = 4;
    } else {
      if (playerSprite.yIndex == 7) {
        playerSprite.yIndex = 2;
        playerShadow.yIndex = 2;
      } else if (playerSprite.yIndex == 6) {
        playerSprite.yIndex = 3;
        playerShadow.yIndex = 3;
      } else if (playerSprite.yIndex == 5) {
        playerSprite.yIndex = 1;
        playerShadow.yIndex = 1;
      } else if (playerSprite.yIndex == 4) {
        playerSprite.yIndex = 0;
        playerShadow.yIndex = 0;
      }
    }

  }
};

class CameraFollowUpdateSystem : public UpdateSystem {
public:
  void run(float dT) {
    auto& cameraPosition = scene->mainCamera->get<TransformComponent>();
    const auto cameraComponent = scene->mainCamera->get<CameraComponent>();
    const auto playerPosition = scene->player->get<TransformComponent>();
    const auto worldComponent = scene->world->get<WorldComponent>();
    const int spriteSize = scene->player->get<SpriteComponent>().size * cameraComponent.zoom;

    int px = playerPosition.x - cameraComponent.viewportWidth/2 + spriteSize/2;
    int py = playerPosition.y - cameraComponent.viewportHeight/2 + spriteSize/2;

    if (px > 0 && px < worldComponent.width) {
      cameraPosition.x = px;
    }
    if (py > 0 && py < worldComponent.height) {
      cameraPosition.y = py;
    }
  }
};

class ColliderRenderSystem : public RenderSystem {
public:
  void run(SDL_Renderer* r) {
    auto view = scene->r.view<TransformComponent, ColliderComponent>();
    const auto c = scene->mainCamera->get<TransformComponent>();
    const auto z = scene->mainCamera->get<CameraComponent>().zoom;

    for(auto entity : view) {
      const auto colliderComponent = view.get<ColliderComponent>(entity);
      const auto transformComponent = view.get<TransformComponent>(entity);

      SDL_Rect col {
        static_cast<int>(transformComponent.x + colliderComponent.xo * z - c.x),
        static_cast<int>(transformComponent.y + colliderComponent.yo * z - c.y),
        static_cast<int>(colliderComponent.w * z),
        static_cast<int>(colliderComponent.h * z)
      };
      SDL_SetRenderDrawColor(r, colliderComponent.color.r, colliderComponent.color.g, colliderComponent.color.b, 200);
      SDL_RenderDrawRect(r, &col);
    }
  }
};

/*class TileColliderRenderSystem : public RenderSystem {
public:
  void run(SDL_Renderer* r) {
    const auto tilemap = scene->world->get<TilemapComponent>();
    const int width = tilemap.width;
    const int height = tilemap.height;
    const int size = tilemap.tileSize;
    const auto c = scene->mainCamera->get<TransformComponent>();
    const auto cameraComponent = scene->mainCamera->get<CameraComponent>();
    const int z = cameraComponent.zoom;
    
    int startX = std::max(0, c.x / (size * z));
    int endX = std::min(width, (c.x + cameraComponent.viewportWidth) / (size * z));
    int startY = std::max(0, c.y / (size * z));
    int endY = std::min(height, (c.y + cameraComponent.viewportHeight) / (size * z));

    //SDL_SetRenderDrawColor(r, 0, 0, 255, 255); 

    for (int y = startY; y <= endY; y++) {
      for (int x = startX; x <= endX; x++) {
        Tile tile = tilemap.map[y * tilemap.width + x];
        SDL_Rect col {
          static_cast<int>(x * size * z - c.x),
          static_cast<int>(y * size * z - c.y),
          static_cast<int>(size * z),
          static_cast<int>(size * z)
        };
        if (!tile.isWalkable) {
          SDL_RenderFillRect(r, &col);
        
      }
    }
  }
};*/

class TileCollisionUpdateSystem : public UpdateSystem {
  public:
    void run(float dT) {
      const auto playerPosition = scene->player->get<TransformComponent>();
      const auto playerCollider = scene->player->get<ColliderComponent>();
      const auto world = scene->world->get<WorldComponent>();
      const auto cameraZoom = scene->mainCamera->get<CameraComponent>().zoom;
      auto& playerMovement = scene->player->get<SpeedComponent>();
      auto& shadowMovement = scene->shadow->get<SpeedComponent>();
      auto& heartMovement1 = scene->heart1->get<SpeedComponent>();
      auto& heartMovement2 = scene->heart2->get<SpeedComponent>();
      auto& heartMovement3 = scene->heart3->get<SpeedComponent>();

      const auto bulletView = scene->r.view<TransformComponent, SpeedComponent, BulletComponent>();
      const auto tilemapComponent = scene->world->get<TilemapComponent>();
      const int tileSize = tilemapComponent.tileSize * cameraZoom;

      if (playerMovement.x == 0 && playerMovement.y == 0) {
        return;
      }

      const int colliderPositionX = playerPosition.x + playerCollider.xo * cameraZoom;
      const int colliderPositionY = playerPosition.y + playerCollider.yo * cameraZoom;
      const int colliderSize = playerCollider.w * cameraZoom;

      const int futureX = colliderPositionX + playerMovement.x * dT;
      const int futureY = colliderPositionY + playerMovement.y * dT;
      const int futureRightX = futureX + colliderSize;
      const int futureBottomY = futureY + colliderSize;

      if (futureX <= 0 || futureY <= 0 || futureRightX >= world.width * cameraZoom || futureBottomY >= world.height * cameraZoom) {
        playerMovement.x = 0;
        playerMovement.y = 0;
        shadowMovement.x = 0;
        shadowMovement.y = 0;
        heartMovement1.x = 0;
        heartMovement1.y = 0;
        heartMovement2.x = 0;
        heartMovement2.y = 0;
        heartMovement3.x = 0;
        heartMovement3.y = 0;
      }

      

    // Convert the future positions from pixels to tile coordinates.
    std::vector<std::pair<int, int>> futureTiles = {
        {futureX / tileSize, futureY / tileSize}, // top left corner
        {futureRightX / tileSize, futureY / tileSize}, // top right corner
        {futureX / tileSize, futureBottomY / tileSize}, // bottom left corner
        {futureRightX / tileSize, futureBottomY / tileSize}  // bottom right corner
    };

    for (const auto& [tileX, tileY] : futureTiles) {
        // Get the tile at the future position.
        const Tile& tile = tilemapComponent.map[tileY * tilemapComponent.width + tileX];

        // If the tile is not walkable, set the speed to 0.
        if (!tile.isWalkable) {
            playerMovement.x = 0;
            playerMovement.y = 0;
            shadowMovement.x = 0;
            shadowMovement.y = 0;
            heartMovement1.x = 0;
            heartMovement1.y = 0;
            heartMovement2.x = 0;
            heartMovement2.y = 0;
            heartMovement3.x = 0;
            heartMovement3.y = 0;
            return;
        }
    }
  }
};



