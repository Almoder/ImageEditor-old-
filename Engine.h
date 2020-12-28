namespace ImageEditor {

	using namespace System;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	public ref class Engine {
	private:
		List<Image^>^ data = nullptr;

	public:
		String^ fileName;
		String^ filter = "BMP (*.bmp)|*.bmp|JPEG (*.jpeg), JPG (*.jpg)|*.jpeg; *.jpg|PNG (*.png)|*.png";
		int current = 0, sFDindex = 0;

		Engine();
		~Engine();

		Image^ undo();
		Image^ redo();
		Image^ getCurrent();
		void addNode(Image^);
		void clearData();
		bool dataEmpty() { return data->Count == 0; };
		int count() { return data->Count; };
	};
}