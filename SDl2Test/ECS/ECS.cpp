
#include "ECS.h"


//This is a very basic ECS I build to learn how to build an ECS, but I am going to switch this 
//out with EnTT eventually. 

void Entity::addGroup(Group mGroup) {
	groupBitset[mGroup] = true;
	manager.AddToGroup(this, mGroup);
}
