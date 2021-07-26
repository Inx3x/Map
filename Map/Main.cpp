//ver_1.0

#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <string>

using namespace std;

struct Vector3
{
	float x, y, z;

	Vector3() : x(0), y(0), z(0) {}
	Vector3(float _x, float _y) : x(_x), y(_y), z(0) {}
};
struct Transform
{
	Vector3 Position;
};

class Object {
protected:
	Transform TransPos;
	string strKey;
public:
	Object() {}
	virtual ~Object() {}

	virtual void Initialize() = 0;
	virtual void Output() { cout << strKey << endl; };
	virtual string GetKey() { return strKey; }
};

class Player : public Object {
public:
	Player() {}
	virtual ~Player() {}

	virtual void Initialize()override { strKey = "Player"; }
};
class Enemy : public Object {
public:
	Enemy() {}
	virtual ~Enemy() {}

	virtual void Initialize()override { strKey = "Enemy"; }
};

class Bullet : public Object {
public:
	Bullet() {}
	virtual ~Bullet() {}

	virtual void Initialize()override { strKey = "Bullet"; }
};

template <typename T>
Object* CreateObject();

void AddObject(Object*);

map<string, list<Object*>> ObjectList;

int main() {
	AddObject(CreateObject<Player>());

	AddObject(CreateObject<Bullet>());
	AddObject(CreateObject<Bullet>());
	AddObject(CreateObject<Bullet>());

	AddObject(CreateObject<Enemy>());
	AddObject(CreateObject<Enemy>());
	AddObject(CreateObject<Enemy>());	

	for (map<string, list<Object*>>::iterator iter = ObjectList.begin(); iter != ObjectList.end(); iter++)
	{
		for (list<Object*>::iterator iter2 = (*iter).second.begin(); iter2 != (*iter).second.end(); iter2++) {
			(*iter2)->Output();
		}
	}

	return 0;
}

template <typename T>
Object* CreateObject() {
	Object* pObj = new T;
	pObj->Initialize();

	return pObj;
}

void AddObject(Object* _pObj) {
	map<string, list<Object*>>::iterator iter = ObjectList.find(_pObj->GetKey());

	if (iter == ObjectList.end()) {
		list<Object*> TempList;
		TempList.push_back(_pObj);

		ObjectList.insert(make_pair(_pObj->GetKey(), TempList));
	}
	else {
		iter->second.push_back(_pObj);
	}
}