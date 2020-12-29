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
#pragma region Masks

		int** hl3x3 = new int* [3]{
			new int[3] {-1,	2, -1},
			new int[3] {-1, 2, -1},
			new int[3] {-1, 2, -1} };
		int** hl5x5 = new int* [5]{
			new int[5] {-1, -1, 4, -1, -1},
			new int[5] {-1, -1, 4, -1, -1},
			new int[5] {-1, -1, 4, -1, -1},
			new int[5] {-1, -1, 4, -1, -1},
			new int[5] {-1, -1, 4, -1, -1} };
		int** vl3x3 = new int*[3] {
			new int[3] {-1,	-1,	-1},
			new int[3] {2, 2, 2},
			new int[3] {-1, -1, -1} };
		int** vl5x5 = new int* [5]{
			new int[5] {-1, -1, -1, -1, -1},
			new int[5] {-1, -1, -1, -1, -1},
			new int[5] {4, 4, 4, 4, 4},
			new int[5] {-1, -1, -1, -1, -1},
			new int[5] {-1, -1, -1, -1, -1} };
		int** d13x3 = new int* [3]{
			new int[3] {2, -1, -1},
			new int[3] {-1, 2, -1},
			new int[3] {-1, -1, 2} };
		int** d15x5 = new int* [5]{
			new int[5] {4, -1, -1, -1, -1},
			new int[5] {-1, 4, -1, -1, -1},
			new int[5] {-1, -1, 4, -1, -1},
			new int[5] {-1, -1, -1, 4, -1},
			new int[5] {-1, -1, -1, -1, 4} };
		int** d23x3 = new int* [3]{
			new int[3] {-1,	-1,	2},
			new int[3] {-1, 2, -1},
			new int[3] {2, -1, -1} };
		int** d25x5 = new int* [5]{
			new int[5] {-1, -1, -1, -1, 4},
			new int[5] {-1, -1, -1, 4, -1},
			new int[5] {-1, -1, 4, -1, -1},
			new int[5] {-1, 4, -1, -1, -1},
			new int[5] {4, -1, -1, -1, -1} };

#pragma endregion

	public:
		//delegate void Pidor(Bitmap^, Bitmap^);
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
		int compar(Color, Color);
	};
}