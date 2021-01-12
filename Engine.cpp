#include "MainForm.h"

using namespace System::Threading::Tasks;
using namespace ImageEditor;

#pragma region Operators

#pragma endregion
#pragma region Common

Engine::Engine(PbarInc^ upd) {
	data = gcnew List<Bitmap^>();
	this->upd = upd;
};

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
	return data[current];
}

Image^ Engine::getLast() {
	return data[data->Count - 1];
}

void Engine::addNode(Image^ img) {
	data->Add(gcnew Bitmap(img));
	empty = false;
}

void Engine::preset(PbarInc^ del, ProgressBar^ ptr) {
	progressPtr = ptr;
	this->del = del;
}

void Engine::clearData() {
	data->Clear();
	empty = true;
}

bool Engine::dataEmpty() {
	return count() == 0;
}

int Engine::count() {
	try {
		if (data == nullptr) return 0;
		else return data->Count; 
	}
	catch (System::NullReferenceException^ e) {
		delete e;
		return 0;
	}
}

#pragma endregion
#pragma region Transforms
#pragma region Do

void Engine::doNegative() {
	thread = gcnew Thread(gcnew ThreadStart(this, &Engine::negative));
	thread->Start();
}

void Engine::doHalftone() {
	thread = gcnew Thread(gcnew ThreadStart(this, &Engine::halftone));
	thread->Start();
}

void Engine::doBinar(int t, int b0, int b1) {
	this->t = t; this->b0 = b0; this->b1 = b1;
	thread = gcnew Thread(gcnew ThreadStart(this, &Engine::binar));
	thread->Start();
}

void Engine::doBinarAdaptive() {
	thread = gcnew Thread(gcnew ThreadStart(this, &Engine::binarAdaptive));
	thread->Start();
}

void Engine::doPower(double c, double g) {
	this->c = c; this->g = g;
	thread = gcnew Thread(gcnew ThreadStart(this, &Engine::power));
	thread->Start();
}

void Engine::doLBrightness(int val) {
	t = val;
	thread = gcnew Thread(gcnew ThreadStart(this, &Engine::lBrightness));
	thread->Start();
}

void Engine::doNBrightness(int val) {
	t = val;
	thread = gcnew Thread(gcnew ThreadStart(this, &Engine::nBrightness));
	thread->Start();
}

void Engine::doLContrast(int val) {
	t = val;
	thread = gcnew Thread(gcnew ThreadStart(this, &Engine::lContrast));
	thread->Start();
}

void Engine::doNContrast(int val) {
	t = val;
	thread = gcnew Thread(gcnew ThreadStart(this, &Engine::nContrast));
	thread->Start();
}

void Engine::doAutolevels(int type, int size) {
	t = type;
	b0 = size + 1;
	b1 = mSize[size];
	thread = gcnew Thread(gcnew ThreadStart(this, &Engine::autolevels));
	thread->Start();
}

void Engine::doFiltration(int type, int size) {
	switch (type) {
	case 0: thread = gcnew Thread(
		gcnew ThreadStart(this, &Engine::filterLF));
		break;
	case 1: thread = gcnew Thread(
		gcnew ThreadStart(this, &Engine::filterRL));
		break;
	case 2: thread = gcnew Thread(
		gcnew ThreadStart(this, &Engine::filterCS));
		break;
	case 3: thread = gcnew Thread(
		gcnew ThreadStart(this, &Engine::filterRS));
		break;
	case 4: thread = gcnew Thread(
		gcnew ThreadStart(this, &Engine::filterHL));
		break;
	case 5: thread = gcnew Thread(
		gcnew ThreadStart(this, &Engine::filterVL));
		break;
	case 6:	thread = gcnew Thread(
		gcnew ThreadStart(this, &Engine::filterD1));
		break;
	case 7: thread = gcnew Thread(
		gcnew ThreadStart(this, &Engine::filterD2));
		break;
	default: picturePtr->Invoke(upd); return;
	}
	t = type;
	b0 = size + 1;
	b1 = mSize[size];
	thread->Start();
}

void Engine::doFrequencyDomain(int radius, int order) {
	b0 = radius; b1 = order;
	thread = gcnew Thread(gcnew ThreadStart(this, &Engine::frequencyDomain));
	thread->Start();
}

#pragma endregion
#pragma region Calc
#pragma region Transforms

void Engine::negative() {
	ProgressBar^ pb = progressPtr; PbarInc^ _del = del;
	Bitmap^ orig = gcnew Bitmap(data[current2]);
	Bitmap^ ret = gcnew Bitmap(orig->Width, orig->Height);
	for (int row = 0; row < orig->Width; row++) {
		for (int col = 0; col < orig->Height; col++) {
			Color c = orig->GetPixel(row, col);
			ret->SetPixel(row, col, Color::FromArgb(255 - c.R, 255 - c.G, 255 - c.B));
		}
		pb->Invoke(_del, pb);
	}
	addNode(ret);
	picturePtr->Invoke(upd, pb);
}

void Engine::halftone() {
	ProgressBar^ pb = progressPtr; PbarInc^ _del = del;
	Bitmap^ orig = gcnew Bitmap(data[current2]);
	Bitmap^ ret = gcnew Bitmap(orig->Width, orig->Height);
	for (int row = 0; row < orig->Width; row++) {
		for (int col = 0; col < orig->Height; col++) {
			Color temp = orig->GetPixel(row, col);
			int v = (int)(0.3 * temp.R + 0.59 * temp.G + 0.11 * temp.B);
			ret->SetPixel(row, col, Color::FromArgb(v, v, v));
		}
		pb->Invoke(_del, pb);
	}
	addNode(ret);
	picturePtr->Invoke(upd, pb);
}

void Engine::binar() {
	ProgressBar^ pb = progressPtr; PbarInc^ _del = del;
	Bitmap^ orig = gcnew Bitmap(data[current]);
	Bitmap^ ret = gcnew Bitmap(orig->Width, orig->Height);
	int _t = t;
	Color _b0 = Color::FromArgb(b0, b0, b0);
	Color _b1 = Color::FromArgb(b1, b1, b1);
	for (int row = 0; row < orig->Width; row++) {
		for (int col = 0; col < orig->Height; col++) {
			Color b = orig->GetPixel(row, col);
			b.GetBrightness() * 255 <= _t ?
				ret->SetPixel(row, col, _b0) :
				ret->SetPixel(row, col, _b1);
		}
		pb->Invoke(_del, pb);
	}
	addNode(ret);
	picturePtr->Invoke(upd, pb);
}

void Engine::binarAdaptive() {
	ProgressBar^ pb = progressPtr; PbarInc^ _del = del;
	Bitmap^ dst = gcnew Bitmap(data[current]);
	Bitmap^ orig = gcnew Bitmap(dst->Width, dst->Height);
	float min = 255.0, max = 0.0, maxSigma = -1;
	int m = 0, n = 0, threshold = 0, alpha1 = 0, beta1 = 0;
	for (int row = 0; row < dst->Width; row++) {
		for (int col = 0; col < dst->Height; col++) {
			Color temp = dst->GetPixel(row, col);
			int v = (int)(0.3 * temp.R + 0.59 * temp.G + 0.11 * temp.B);
			orig->SetPixel(row, col, Color::FromArgb(v, v, v));
			Color t2 = orig->GetPixel(row, col);
			if (t2.GetBrightness() * 255 < min)
				min = t2.GetBrightness() * 255;
			if (t2.GetBrightness() * 255 > max)
				max = t2.GetBrightness() * 255;
		}
		pb->Invoke(_del, pb);
	}
	int histSize = (int)(max - min + 1);
	int* hist = new int[histSize] {0};
	for (int row = 0; row < orig->Width; row++) {
		for (int col = 0; col < orig->Height; col++) {
			hist[(int)(orig->GetPixel(row, col).GetBrightness() * 255 - min)]++;
		}
		pb->Invoke(_del, pb);
	}
	for (int t = 0; t <= max - min; t++) {
		m += t * hist[t];
		n += hist[t];
	}
	for (int t = 0; t < max - min; t++) {
		alpha1 += t * hist[t];
		beta1 += hist[t];
		float w1 = (float)beta1 / n;
		float a = (float)alpha1 / beta1 - (float)(m - alpha1) / (n - beta1);
		float sigma = w1 * (1 - w1) * a * a;
		if (sigma > maxSigma) {
			maxSigma = sigma;
			threshold = t;
		}
	}
	threshold += (int)min;
	t = threshold; b0 = 0; b1 = 255;
	progressPtr = pb;
	thread = gcnew Thread(gcnew ThreadStart(this, &Engine::binar));
	thread->Priority = ThreadPriority::Highest;
	thread->Start();
}

void Engine::power() {
	ProgressBar^ pb = progressPtr; PbarInc^ _del = del;
	Bitmap^ orig = gcnew Bitmap(data[current]);
	Bitmap^ ret = gcnew Bitmap(orig->Width, orig->Height);
	int c = int(this->c), r, g, b;
	double p = this->g;
	for (int row = 0; row < orig->Width; row++) {
		for (int col = 0; col < orig->Height; col++) {
			Color t = orig->GetPixel(row, col);
			r = Math::Pow(t.R, p) > 255 ? 255 : int(Math::Pow(t.R, p));
			g = Math::Pow(t.G, p) > 255 ? 255 : int(Math::Pow(t.G, p));
			b = Math::Pow(t.B, p) > 255 ? 255 : int(Math::Pow(t.B, p));
			r = r == 255 ? r : r * c > 255 ? 255 : r * c;
			g = g == 255 ? g : g * c > 255 ? 255 : g * c;
			b = b == 255 ? b : b * b > 255 ? 255 : b * c;
			ret->SetPixel(row, col, Color::FromArgb(r, g, b));
		}
		pb->Invoke(_del, pb);
	}
	addNode(ret);
	picturePtr->Invoke(upd, pb);
}

void Engine::lBrightness() {
	ProgressBar^ pb = progressPtr; PbarInc^ _del = del;
	Bitmap^ orig = gcnew Bitmap(data[current]);
	Bitmap^ ret = gcnew Bitmap(orig->Width, orig->Height);
	int val = t;
	for (int row = 0; row < orig->Width; row++) {
		for (int col = 0; col < orig->Height; col++) {
			Color t = orig->GetPixel(row, col);
			ret->SetPixel(row, col, Color::FromArgb(
				t.R + val < 0 ? 0 : t.R + val > 255 ? 255 : t.R + val,
				t.G + val < 0 ? 0 : t.G + val > 255 ? 255 : t.G + val,
				t.B + val < 0 ? 0 : t.B + val > 255 ? 255 : t.B + val));
		}
		pb->Invoke(_del, pb);
	}
	addNode(ret);
	picturePtr->Invoke(upd, pb);
}

void Engine::nBrightness() {
	ProgressBar^ pb = progressPtr; PbarInc^ _del = del;
	Bitmap^ orig = gcnew Bitmap(data[current]);
	Bitmap^ ret = gcnew Bitmap(orig->Width, orig->Height);
	int val = t;
	for (int row = 0; row < orig->Width; row++) {
		for (int col = 0; col < orig->Height; col++) {
			Color temp = orig->GetPixel(row, col);
			int r = int(temp.R + (Math::Log(1 + (265 - temp.R)) * val));
			int g = int(temp.G + (Math::Log(1 + (265 - temp.G)) * val));
			int b = int(temp.B + (Math::Log(1 + (265 - temp.B)) * val));
			ret->SetPixel(row, col, Color::FromArgb(
				r < 0 ? 0 : r > 255 ? 255 : r,
				g < 0 ? 0 : g > 255 ? 255 : g,
				b < 0 ? 0 : b > 255 ? 255 : b));
		}
		pb->Invoke(_del, pb);
	}
	addNode(ret);
	picturePtr->Invoke(upd, pb);
}

void Engine::lContrast() {
	ProgressBar^ pb = progressPtr; PbarInc^ _del = del;
	Bitmap^ orig = gcnew Bitmap(data[current]);
	Bitmap^ ret = gcnew Bitmap(orig->Width, orig->Height);
	int val = t, gray = 0;
	int r = 0, g = 0, b = 0;
	for (int row = 0; row < orig->Width; row++) {
		for (int col = 0; col < orig->Height; col++) {
			Color temp = orig->GetPixel(row, col);
			gray += (int)(0.3 * temp.R + 0.59 * temp.G + 0.11 * temp.B);
		}
		pb->Invoke(_del, pb);
	}
	gray /= (orig->Width * orig->Height);
	for (int row = 0; row < orig->Width; row++) {
		for (int col = 0; col < orig->Height; col++) {
			Color temp = orig->GetPixel(row, col);
			r = temp.R + (temp.R - gray) * val / 255;
			g = temp.G + (temp.G - gray) * val / 255;
			b = temp.B + (temp.B - gray) * val / 255;
			ret->SetPixel(row, col, Color::FromArgb(
				r < 0 ? 0 : r > 255 ? 255 : r,
				g < 0 ? 0 : g > 255 ? 255 : g,
				b < 0 ? 0 : b > 255 ? 255 : b));
		}
		pb->Invoke(_del, pb);
	}
	addNode(ret);
	picturePtr->Invoke(upd, pb);
}

void Engine::nContrast() {
	ProgressBar^ pb = progressPtr; PbarInc^ _del = del;
	Bitmap^ orig = gcnew Bitmap(data[current]);
	Bitmap^ ret = gcnew Bitmap(orig->Width, orig->Height);
	int val = t;
	for (int row = 0; row < orig->Width; row++) {
		for (int col = 0; col < orig->Height; col++) {
			Color temp2 = orig->GetPixel(row, col);
			int r = int(val * Math::Log(1 + temp2.R));
			int g = int(val * Math::Log(1 + temp2.G));
			int b = int(val * Math::Log(1 + temp2.B));
			ret->SetPixel(row, col, Color::FromArgb(
				r < 0 ? 0 : r > 255 ? 255 : r,
				g < 0 ? 0 : g > 255 ? 255 : g,
				b < 0 ? 0 : b > 255 ? 255 : b));
		}
		pb->Invoke(_del, pb);
	}
	addNode(ret);
	picturePtr->Invoke(upd, pb);
}

void Engine::autolevels() {
	ProgressBar^ pb = progressPtr; PbarInc^ _del = del;
	Bitmap^ orig = gcnew Bitmap(data[current]);
	Bitmap^ temp = gcnew Bitmap(orig->Width, orig->Height);
	Bitmap^ ret = gcnew Bitmap(orig->Width, orig->Height);
	Comparison<Color>^ cmp = gcnew Comparison<Color>(this, &Engine::compar);
	int type = t, sub = b0, div = b1;
	int** mask = getMask();
	for (int row = 0; row < orig->Width; row++) {
		for (int col = 0; col < orig->Height; col++) {
			int r = 0, g = 0, b = 0, cdiv = div;
			float br = 0;
			List<Color>^ l = gcnew List<Color>();
			switch (type) {
			case 0://lf
				for (int i = row - sub; i <= row + sub; i++) {
					for (int j = col - sub; j <= col + sub; j++) {
						if (i < 0 || i >= orig->Width || j < 0 || j >= orig->Height) {
							cdiv--;
							continue;
						}
						Color t = orig->GetPixel(i, j);
						br += t.GetBrightness() * 255.0f;
						//r += t.R; g += t.G; b += t.B;
					}
				}
				br /= cdiv;
				temp->SetPixel(row, col,
					Color::FromArgb(int(br), int(br), int(br)));
				/*r /= cdiv; g /= cdiv; b /= cdiv;
				temp->SetPixel(row, col, Color::FromArgb(
					r == 0 ? 1 : r,
					g == 0 ? 1 : g,
					b == 0 ? 1 : b));*/
				break;
			case 1://rl
				for (int i = row - sub; i <= row + sub; i++) {
					for (int j = col - sub; j <= col + sub; j++) {
						if (i < 0 || i >= orig->Width || j < 0 || j >= orig->Height) continue;
						l->Add(orig->GetPixel(i, j));
					}
				}
				l->Sort(cmp);
				temp->SetPixel(row, col, l[l->Count / 2]);
				break;
			case 2://cs
				for (int i1 = row - sub, i2 = col - sub; i1 < row + sub; i1++, i2++) {
					if (i1 < 0 || i1 >= orig->Width || i2 < 0 || i2 >= orig->Height) continue;
					l->Add(orig->GetPixel(i1, col));
					if (i2 != row) l->Add(orig->GetPixel(row, i2));
				}
				l->Sort(cmp);
				temp->SetPixel(row, col, l[l->Count / 2]);
				break;
			case 3://rs
				for (int i = row - sub, s = 0; i < row + sub; i++, s < sub ? s++ : s--)
					for (int j = col - s; j < col + s; j++) {
						if (i < 0 || i >= orig->Width || j < 0 || j >= orig->Height) continue;
						l->Add(orig->GetPixel(i, j));
					}
				l->Sort(cmp);
				temp->SetPixel(row, col, l[l->Count / 2]);
				break;
			case 4://hl
				for (int i = row - sub, im = 0; i <= row + sub; i++, im++) {
					for (int j = col - sub, jm = 0; j <= col + sub; j++, jm++) {
						if (i < 0 || i >= orig->Width || j < 0 || j >= orig->Height) {
							cdiv--;
							continue;
						}
						Color t = orig->GetPixel(i, j);
						int m = mask[im][jm];
						r += t.R * m; g += t.G * m; b += t.B * m;
					}
				}
				r /= cdiv; g /= cdiv; b /= cdiv;
				temp->SetPixel(row, col, Color::FromArgb(
					r < 0 ? 0 : r > 255 ? 255 : r,
					g < 0 ? 0 : g > 255 ? 255 : g,
					b < 0 ? 0 : b > 255 ? 255 : b));
				break;
			case 5://vl
				for (int i = row - sub, im = 0; i <= row + sub; i++, im++) {
					for (int j = col - sub, jm = 0; j <= col + sub; j++, jm++) {
						if (i < 0 || i >= orig->Width || j < 0 || j >= orig->Height) {
							cdiv--;
							continue;
						}
						Color t = orig->GetPixel(i, j);
						int m = mask[im][jm];
						r += t.R * m; g += t.G * m; b += t.B * m;
					}
				}
				r /= cdiv; g /= cdiv; b /= cdiv;
				temp->SetPixel(row, col, Color::FromArgb(
					r < 0 ? 0 : r > 255 ? 255 : r,
					g < 0 ? 0 : g > 255 ? 255 : g,
					b < 0 ? 0 : b > 255 ? 255 : b));
				break;
			case 6://d1
				for (int i = row - sub, im = 0; i <= row + sub; i++, im++) {
					for (int j = col - sub, jm = 0; j <= col + sub; j++, jm++) {
						if (i < 0 || i >= orig->Width || j < 0 || j >= orig->Height) {
							cdiv--;
							continue;
						}
						Color t = orig->GetPixel(i, j);
						int m = mask[im][jm];
						r += t.R * m; g += t.G * m; b += t.B * m;
					}
				}
				r /= cdiv; g /= cdiv; b /= cdiv;
				temp->SetPixel(row, col, Color::FromArgb(
					r < 0 ? 0 : r > 255 ? 255 : r,
					g < 0 ? 0 : g > 255 ? 255 : g,
					b < 0 ? 0 : b > 255 ? 255 : b));
				break;
			case 7://d2
				for (int i = row - sub, im = 0; i <= row + sub; i++, im++) {
					for (int j = col - sub, jm = 0; j <= col + sub; j++, jm++) {
						if (i < 0 || i >= orig->Width || j < 0 || j >= orig->Height) {
							cdiv--;
							continue;
						}
						Color t = orig->GetPixel(i, j);
						int m = mask[im][jm];
						r += t.R * m; g += t.G * m; b += t.B * m;
					}
				}
				r /= cdiv; g /= cdiv; b /= cdiv;
				temp->SetPixel(row, col, Color::FromArgb(
					r < 0 ? 0 : r > 255 ? 255 : r,
					g < 0 ? 0 : g > 255 ? 255 : g,
					b < 0 ? 0 : b > 255 ? 255 : b));
				break;
			}
		}
		pb->Invoke(_del, pb);
	}
	for (int row = 0; row < orig->Width; row++) {
		for (int col = 0; col < orig->Height; col++) {
			Color a = orig->GetPixel(row, col);
			c = temp->GetPixel(row, col).GetBrightness() * 255.0f;
			//Color c = temp->GetPixel(row, col);
			double br = a.GetBrightness() * 255.0;
			double r = (Math::Log(
				double(a.R) / double(c)) * 127.5) + 127.5;
			double g = (Math::Log(
				double(a.G) / double(c)) * 127.5) + 127.5;
			double b = (Math::Log(
				double(a.B) / double(c)) * 127.5) + 127.5;
			ret->SetPixel(row, col, Color::FromArgb(
				int(r) < 0 ? 0 : int(r) > 255 ? 255 : int(r),
				int(g) < 0 ? 0 : int(g) > 255 ? 255 : int(g),
				int(b) < 0 ? 0 : int(b) > 255 ? 255 : int(b)));
		}
		pb->Invoke(_del, pb);
	}
	addNode(ret);
	picturePtr->Invoke(upd, pb);
}

#pragma endregion
#pragma region Filters

void Engine::filterLF() {
	ProgressBar^ pb = progressPtr; PbarInc^ _del = del;
	Bitmap^ orig = gcnew Bitmap(data[current]);
	Bitmap^ ret = gcnew Bitmap(orig->Width, orig->Height);
	int sub = b0, div = b1;
	for (int row = 0; row < orig->Width; row++) {
		for (int col = 0; col < orig->Height; col++) {
			int r = 0, g = 0, b = 0, cdiv = div;
			for (int i = row - sub; i <= row + sub; i++) {
				for (int j = col - sub; j <= col + sub; j++) {
					if (i < 0 || i >= orig->Width || j < 0 || j >= orig->Height) {
						cdiv--;
						continue;
					}
					Color t = orig->GetPixel(i, j);
					r += t.R; g += t.G; b += t.B;
				}
			}
			r /= cdiv; g /= cdiv; b /= cdiv;
			ret->SetPixel(row, col, Color::FromArgb(r, g, b));
		}
		pb->Invoke(_del, pb);
	}
	addNode(ret);
	picturePtr->Invoke(upd, pb);
}

void Engine::filterRL() {
	ProgressBar^ pb = progressPtr; PbarInc^ _del = del;
	Bitmap^ orig = gcnew Bitmap(data[current]);
	Bitmap^ ret = gcnew Bitmap(orig->Width, orig->Height);
	Comparison<Color>^ cmp = gcnew Comparison<Color>(this, &Engine::compar);
	int sub = b0;
	for (int row = 0; row < orig->Width; row++) {
		for (int col = 0; col < orig->Height; col++) {
			List<Color>^ l = gcnew List<Color>();
			for (int i = row - sub; i <= row + sub; i++) {
				for (int j = col - sub; j <= col + sub; j++) {
					if (i < 0 || i >= orig->Width || j < 0 || j >= orig->Height) continue;
					l->Add(orig->GetPixel(i, j));
				}
			}
			l->Sort(cmp);
			ret->SetPixel(row, col, l[sub]);
		}
		pb->Invoke(_del, pb);
	}
	addNode(ret);
	picturePtr->Invoke(upd, pb);
}

void Engine::filterCS() {
	ProgressBar^ pb = progressPtr; PbarInc^ _del = del;
	Bitmap^ orig = gcnew Bitmap(data[current]);
	Bitmap^ ret = gcnew Bitmap(orig->Width, orig->Height);
	Comparison<Color>^ cmp = gcnew Comparison<Color>(this, &Engine::compar);
	int sub = b0;
	for (int row = 0; row < orig->Width; row++) {
		for (int col = 0; col < orig->Height; col++) {
			List<Color>^ l = gcnew List<Color>();
			for (int i1 = row - sub, i2 = col - sub; i1 < row + sub; i1++, i2++) {
				if (i1 < 0 || i1 >= orig->Width || i2 < 0 || i2 >= orig->Height) continue;
				l->Add(orig->GetPixel(i1, col));
				if (i2 != row) l->Add(orig->GetPixel(row, i2));
			}
			l->Sort(cmp);
			ret->SetPixel(row, col, l[sub]);
		}
		pb->Invoke(_del, pb);
	}
	addNode(ret);
	picturePtr->Invoke(upd, pb);
}

void Engine::filterRS() {
	ProgressBar^ pb = progressPtr; PbarInc^ _del = del;
	Bitmap^ orig = gcnew Bitmap(data[current]);
	Bitmap^ ret = gcnew Bitmap(orig->Width, orig->Height);
	Comparison<Color>^ cmp = gcnew Comparison<Color>(this, &Engine::compar);
	int sub = b0;
	for (int row = 0; row < orig->Width; row++) {
		for (int col = 0; col < orig->Height; col++) {
			List<Color>^ l = gcnew List<Color>();
			for (int i = row - sub, s = 0; i < row + sub; i++, s < sub ? s++ : s--)
				for (int j = col - s; j < col + s; j++) {
					if (i < 0 || i >= orig->Width || j < 0 || j >= orig->Height) continue;
					l->Add(orig->GetPixel(i, j));
				}
			l->Sort(cmp);
			ret->SetPixel(row, col, l[sub]);
		}
		pb->Invoke(_del, pb);
	}
	addNode(ret);
	picturePtr->Invoke(upd, pb);
}

void Engine::filterHL() {
	ProgressBar^ pb = progressPtr; PbarInc^ _del = del;
	Bitmap^ orig = gcnew Bitmap(data[current]);
	Bitmap^ ret = gcnew Bitmap(orig->Width, orig->Height);
	int sub = b0, div = b1;
	int** mask = getMask();
	for (int row = 0; row < orig->Width; row++) {
		for (int col = 0; col < orig->Height; col++) {
			int r = 0, g = 0, b = 0, cdiv = div;
			for (int i = row - sub, im = 0; i <= row + sub; i++, im++) {
				for (int j = col - sub, jm = 0; j <= col + sub; j++, jm++) {
					if (i < 0 || i >= orig->Width || j < 0 || j >= orig->Height) {
						cdiv--;
						continue;
					}
					Color t = orig->GetPixel(i, j);
					int m = mask[im][jm];
					r += t.R * m; g += t.G * m; b += t.B * m;
				}
			}
			r /= cdiv; g /= cdiv; b /= cdiv;
			ret->SetPixel(row, col, Color::FromArgb(
				r < 0 ? 0 : r > 255 ? 255 : r,
				g < 0 ? 0 : g > 255 ? 255 : g,
				b < 0 ? 0 : b > 255 ? 255 : b));
		}
		pb->Invoke(_del, pb);
	}
	addNode(ret);
	picturePtr->Invoke(upd, pb);
}

void Engine::filterVL() {
	ProgressBar^ pb = progressPtr; PbarInc^ _del = del;
	Bitmap^ orig = gcnew Bitmap(data[current]);
	Bitmap^ ret = gcnew Bitmap(orig->Width, orig->Height);
	int sub = b0, div = b1;
	int** mask = getMask();
	for (int row = 0; row < orig->Width; row++) {
		for (int col = 0; col < orig->Height; col++) {
			int r = 0, g = 0, b = 0, cdiv = div;
			for (int i = row - sub, im = 0; i <= row + sub; i++, im++) {
				for (int j = col - sub, jm = 0; j <= col + sub; j++, jm++) {
					if (i < 0 || i >= orig->Width || j < 0 || j >= orig->Height) {
						cdiv--;
						continue;
					}
					Color t = orig->GetPixel(i, j);
					int m = mask[im][jm];
					r += t.R * m; g += t.G * m; b += t.B * m;
				}
			}
			r /= cdiv; g /= cdiv; b /= cdiv;
			ret->SetPixel(row, col, Color::FromArgb(
				r < 0 ? 0 : r > 255 ? 255 : r,
				g < 0 ? 0 : g > 255 ? 255 : g,
				b < 0 ? 0 : b > 255 ? 255 : b));
		}
		pb->Invoke(_del, pb);
	}
	addNode(ret);
	picturePtr->Invoke(upd, pb);
}

void Engine::filterD1() {
	ProgressBar^ pb = progressPtr; PbarInc^ _del = del;
	Bitmap^ orig = gcnew Bitmap(data[current]);
	Bitmap^ ret = gcnew Bitmap(orig->Width, orig->Height);
	int sub = b0, div = b1;
	int** mask = getMask();
	for (int row = 0; row < orig->Width; row++) {
		for (int col = 0; col < orig->Height; col++) {
			int r = 0, g = 0, b = 0, cdiv = div;
			for (int i = row - sub, im = 0; i <= row + sub; i++, im++) {
				for (int j = col - sub, jm = 0; j <= col + sub; j++, jm++) {
					if (i < 0 || i >= orig->Width || j < 0 || j >= orig->Height) {
						cdiv--;
						continue;
					}
					Color t = orig->GetPixel(i, j);
					int m = mask[im][jm];
					r += t.R * m; g += t.G * m; b += t.B * m;
				}
			}
			r /= cdiv; g /= cdiv; b /= cdiv;
			ret->SetPixel(row, col, Color::FromArgb(
				r < 0 ? 0 : r > 255 ? 255 : r,
				g < 0 ? 0 : g > 255 ? 255 : g,
				b < 0 ? 0 : b > 255 ? 255 : b));
		}
		pb->Invoke(_del, pb);
	}
	addNode(ret);
	picturePtr->Invoke(upd, pb);
}

void Engine::filterD2() {
	ProgressBar^ pb = progressPtr; PbarInc^ _del = del;
	Bitmap^ orig = gcnew Bitmap(data[current]);
	Bitmap^ ret = gcnew Bitmap(orig->Width, orig->Height);
	int sub = b0, div = b1;
	int** mask = getMask();
	for (int row = 0; row < orig->Width; row++) {
		for (int col = 0; col < orig->Height; col++) {
			int r = 0, g = 0, b = 0, cdiv = div;
			for (int i = row - sub, im = 0; i <= row + sub; i++, im++) {
				for (int j = col - sub, jm = 0; j <= col + sub; j++, jm++) {
					if (i < 0 || i >= orig->Width || j < 0 || j >= orig->Height) {
						cdiv--;
						continue;
					}
					Color t = orig->GetPixel(i, j);
					int m = mask[im][jm];
					r += t.R * m; g += t.G * m; b += t.B * m;
				}
			}
			r /= cdiv; g /= cdiv; b /= cdiv;
			ret->SetPixel(row, col, Color::FromArgb(
				r < 0 ? 0 : r > 255 ? 255 : r,
				g < 0 ? 0 : g > 255 ? 255 : g,
				b < 0 ? 0 : b > 255 ? 255 : b));
		}
		pb->Invoke(_del, pb);
	}
	addNode(ret);
	picturePtr->Invoke(upd, pb);
}

void Engine::frequencyDomain() {
	ProgressBar^ pb = progressPtr; PbarInc^ _del = del;
	Bitmap^ orig = gcnew Bitmap(data[current]);
	Bitmap^ ret = gcnew Bitmap(orig->Width, orig->Height);
	int d = b0, n = b1, r, g, b;
	Point c = Point(orig->Width / 2, orig->Height / 2);
	double radius;
	for (int row = 0; row < orig->Width; row++) {
		for (int col = 0; col < orig->Height; col++) {
			Color temp = orig->GetPixel(row, col);
			radius = Math::Sqrt(
				Math::Pow(row - c.X, 2.0) + Math::Pow(col - c.Y, 2.0));
			double v = 1.0 / (1.0 + Math::Pow(radius / d, 2.0 * n));
			r = int(temp.R * v);
			g = int(temp.R * v);
			b = int(temp.B * v);
			ret->SetPixel(row, col, Color::FromArgb(
				r < 0 ? 0 : r > 255 ? 255 : r,
				g < 0 ? 0 : g > 255 ? 255 : g,
				b < 0 ? 0 : b > 255 ? 255 : b));
		}
		pb->Invoke(_del, pb);
	}
	addNode(ret);
	picturePtr->Invoke(upd, pb);
}

int Engine::compar(Color x, Color y) {
	return x.GetBrightness() < y.GetBrightness() ? -1 :
		x.GetBrightness() == y.GetBrightness() ? 0 : 1;
}

int** Engine::getMask() {
	int len = int(Math::Sqrt(b1));
	int** ret = new int* [len];
	for (int i = 0; i < len; i++) {
		ret[i] = new int[len];
		for (int j = 0; j < len; j++) {
			switch (t) {
			case 4: //horizontal
				if (j == len / 2) ret[i][j] = len - 1;
				else ret[i][j] = -1; break;
			case 5: //vertical
				if (i == len / 2) ret[i][j] = len - 1;
				else ret[i][j] = -1; break;
			case 6: //diagonal1
				if (j == len - i) ret[i][j] = len - 1;
				else ret[i][j] = -1; break;
			case 7: //diagonal2
				if (j == i) ret[i][j] = len - 1;
				else ret[i][j] = -1; break;
			}
		}
	}
	return ret;
}

#pragma endregion
#pragma endregion
#pragma endregion