#include "Engine.h"

using namespace ImageEditor;

Engine::Engine() {
	data = gcnew List<Image^>();
}

Engine::~Engine() {
	delete[] data;
}

Image^ Engine::undo() {
	if (current > 0) current--;
	return getCurrent();
}

Image^ Engine::redo() {
	if (current < data->Count - 1) current++;
	return getCurrent();
}

Image^ Engine::getCurrent() {
	if (!dataEmpty()) return data[current];
	else return nullptr;
}

void Engine::addNode(Image^ img) {
	data->Add(img);
}

void Engine::clearData() {
	data->Clear();
}
