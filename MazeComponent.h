#ifndef MAZE_COMPONENT
#define MAZE_COMPONENT
#include<iostream>
#include<map>
using namespace std;

enum Direction{
	North,
	South,
	East,
	West
};

class MapSite{
public:
	virtual void Enter() = 0;
};

class Room : virtual public MapSite{
protected:
		MapSite* _sides[4];
		int _roomNumber;
public:
	Room(int room){
		_roomNumber = room;
		for(int i=0; i<4; i++)
			_sides[i] = 0;
	}
	MapSite* GetSide(Direction);
	void SetSide(Direction, MapSite*);
	virtual void Enter();
};
MapSite* Room::GetSide(Direction direction){
	return _sides[direction];
}
void Room::SetSide(Direction direction, MapSite* component){
	_sides[direction] = component;
}
void Room::Enter(){
	cout<<"Enter Room#"<<_roomNumber <<endl;
}

class Wall : public virtual MapSite{
public:
	virtual void Enter();
};
void Wall::Enter(){
	cout<<"It's a wall"<<endl;
}

class Door : public virtual MapSite{
protected:
	Room * _room1;
	Room * _room2;
	bool _isLocked;
public:
	Door(Room*, Room*);
	Room* OtherSideFrom(Room*);
	inline void Lock();
	inline void Unlock();
	inline bool IsLocked();
	virtual void Enter();
};
Door::Door(Room* r1, Room* r2){
	_room1 = r1;
	_room2 = r1!=r2? r2:0;
}
Room* Door::OtherSideFrom(Room* room){
	if(room == _room1)
		return _room2;
	if(room == _room2)
		return _room1;
	return 0;
}
void Door::Lock(){
	_isLocked = true;
}
void Door::Unlock(){
	_isLocked = false;
}
bool Door::isLocked(){
	return _isLocked;
}
void Door::Enter(){
	cout<<(_isLocked? "The door is opened":"The door is locked")<<endl;
}

class Maze{
protected:
	map<int, Room*> _maze;
	int _count;
public:
	Map(){count = 0;}
	inline int GetRoomCount(){return _count;}
	bool AddRoom(Room*);
	Room* RoomNo(int);
};
bool Maze::AddRoom(Room* room){
	if(!room)
		return false;
	if(!(_maze.insert(pair<int,Room*>(count++,room))).second){
		--count;
		return false;
	}
	return true;
}
Room* Maze::RoomNo(int number){
	map<int, Room*>::iterator it;
	it = _maze.find(number);
	return (it!=_maze.end())? it->second:0;
}
#endif
