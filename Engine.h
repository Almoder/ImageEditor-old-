#include "Entry.h"

namespace ImageEditor {

	using namespace System;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;
	using namespace System::Threading;
	using namespace System::Windows::Forms;

	public delegate Void PbarInc(ProgressBar^);

	public ref class Engine {
	private:
		List<Bitmap^>^ data = nullptr;
		List<Entry^>^ log = nullptr;
		ProgressBar^ progressPtr = nullptr;
		int t, b0, b1;
		double c, g;
		int* mSize = new int[9]{
			9, 25, 49, 81, 121, 169, 255, 289, 361};
		bool empty = true;
	public:
		PictureBox^ picturePtr = nullptr;
		String^ fileName, ^file;
		String^ filter = "BMP (*.bmp)|*.bmp|JPEG (*.jpeg), JPG (*.jpg)|*.jpeg; *.jpg|PNG (*.png)|*.png";
		int current = 0, current2 = 0, sFDindex = 0;
		bool permanent = false, works = false;
	private:
		PbarInc^ del = nullptr, ^upd = nullptr;
		Thread^ thread = nullptr;

	public:
		Engine(PbarInc^ del);
		~Engine();
		Image^ undo();
		Image^ redo();
		Image^ getCurrent();
		Image^ getLast();
		Entry^ getLog();
		void addNode(Image^);
		void preset(PbarInc^, ProgressBar^);
		void clearData();
		bool dataEmpty();
		int count();
		void doNegative();
		void doHalftone();
		void doBinar(int, int, int);
		void doBinarAdaptive();
		void doPower(double, double);
		void doLBrightness(int);
		void doNBrightness(int);
		void doLContrast(int);
		void doNContrast(int);
		void doAutolevels(int, int);
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
		int** getMask();
		int compar(Color, Color);
	};
}