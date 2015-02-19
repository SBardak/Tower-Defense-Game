#include "BaseModel.h"


BaseModel::BaseModel()
{
	this->observers = new std::list <IObserver*> ;
}


BaseModel::~BaseModel()
{
	delete this->observers;
}

void BaseModel::Attach(IObserver* o){
	this->observers->push_back(o);
}

void BaseModel::Detach(IObserver* o){
	this->observers->remove(o);
}

void BaseModel::Notify(){
	//Update every view attached to the model
	for (std::list<IObserver*>::iterator i = this->observers->begin(); i != this->observers->end(); ++i){
		(*i)->Update();
	}
}

std::list<IObserver*>* BaseModel::GetObservers(){
	return observers;
}
