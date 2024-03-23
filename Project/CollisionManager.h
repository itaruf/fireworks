#pragma once
#include <map>
#include <memory>
#include <functional>
#include <vector>
#include <unordered_set>

class ICollidable;

typedef std::function<void(std::shared_ptr<ICollidable>)> CollisionManagerCallback;

class CollisionManager
{
private:

	struct CollisionConfig
	{
		struct Collision
		{
			int collidableTag;
			CollisionManagerCallback callback;

			Collision(int collidableTag, CollisionManagerCallback callback) : collidableTag(collidableTag), callback(callback) {};
		};

		int collisionTags = 0;
		std::vector<Collision> collisions;

		void AddCollision(int collidableTag, CollisionManagerCallback callback)
		{
			collisions.push_back({ collidableTag, callback });
			collisionTags |= collidableTag;
		}
	};


	std::unordered_set<std::shared_ptr<ICollidable>> _allObjects;
	std::map<std::shared_ptr<ICollidable>,CollisionConfig> _allCollisions;

	std::unordered_set<std::shared_ptr<ICollidable>> _objectToRemove;

	bool AreColliding(const std::shared_ptr<ICollidable>& collider1, const std::shared_ptr<ICollidable>& collider2);
	void CheckCollisions();

public:
	CollisionManager() = default;
	CollisionManager(const CollisionManager& model) = delete;
	CollisionManager(CollisionManager&& moved) = delete;
	virtual ~CollisionManager() = default;
	CollisionManager& operator=(const CollisionManager&) = delete;

	void AddCollider(std::shared_ptr<ICollidable> collidable);
	void RemoveCollider(std::shared_ptr<ICollidable> collidable);
	void AddCollisionCallback(std::shared_ptr<ICollidable> collider, int collisionTag, CollisionManagerCallback callback);

	void Tick();

	void Release();
};
