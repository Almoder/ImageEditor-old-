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
	public:
		delegate void Pidor(Bitmap^, Bitmap^);
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
		void doPerfectReflect();
		void doFiltration(int, int);
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
		void perfectReflect();
		void filter1();
		void filter2();
		void filter3();
		void filter4();
		void filter5();
		void filter6();
		void filter7();
		void filter8();
	};
}