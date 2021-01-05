namespace ImageEditor {

	using namespace System;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;
	using namespace System::Threading;
	using namespace System::Windows::Forms;

	public ref class Engine {
	private:
		List<Bitmap^>^ data = nullptr;
		int t, b0, b1;
		double c, g;
		int* mSize = new int[7]{
			9, 25, 49, 81, 121, 169, 255};
		

	public:
		ProgressBar^ progressPtr = nullptr;
		PictureBox^ picturePtr = nullptr;

		String^ fileName;
		String^ filter = "BMP (*.bmp)|*.bmp|JPEG (*.jpeg), JPG (*.jpg)|*.jpeg; *.jpg|PNG (*.png)|*.png";
		int current = 0, current2 = 0, sFDindex = 0;
	private:
		Action^ del = nullptr, ^upd = nullptr;
		Thread^ thread = nullptr;

	public:
		Engine(Action^, Action^);
		~Engine();

		Image^ undo();
		Image^ redo();
		Image^ getCurrent();
		void addNode(Image^);
		void clearData();
		bool dataEmpty() { return data->Count == 0; };
		int count() { return data->Count; };
		void doNegative();
		void doHalftone();
		void doBinar(int, int, int);
		void doBinarAdaptive();
		void doPower(double, double);
		void doLBrightness(int);
		void doNBrightness(int);
		void doLContrast(int);
		void doNContrast(int);
		void doAutolevels();
		void doFiltration(int, int);
		void doFrequencyDomain(int, int);
	private:
		void negative();
		void halftone();
		void binar();
		void binarAdaptive();
		void power();
		void lBrightness();
		void nBrightness();
		void lContrast();
		void nContrast();
		void autolevels();
		void filterLF();
		void filterRL();
		void filterCS();
		void filterRS();
		void filterHL();
		void filterVL();
		void filterD1();
		void filterD2();
		void frequencyDomain();
		int** getMask(int);
		int compar(Color, Color);
	};
}