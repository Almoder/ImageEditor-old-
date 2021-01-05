#include "MainForm.h"

using namespace System::Threading::Tasks;
using namespace ImageEditor;

#pragma region Operators

#pragma endregion
#pragma region Common

Engine::Engine(Action^ del, Action^ upd) {
	data = gcnew List<Bitmap^>();
	this->del = del;
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
	if (!dataEmpty()) return data[current];
	else return nullptr;
}

void Engine::addNode(Image^ img) {
	data->Add(gcnew Bitmap(img));
}

void Engine::clearData() {
	data->Clear();
}

#pragma endregion
#pragma region Transforms
#pragma region Do

void Engine::doNegative() {
	thread = gcnew Thread(gcnew ThreadStart(this, &Engine::negative));
	thread->Priority = ThreadPriority::Highest;
	thread->Start();
}

void Engine::doHalftone() {
	thread = gcnew Thread(gcnew ThreadStart(this, &Engine::halftone));
	thread->Priority = ThreadPriority::Highest;
	thread->Start();
}

void Engine::doBinar(int t, int b0, int b1) {
	this->t = t; this->b0 = b0; this->b1 = b1;
	thread = gcnew Thread(gcnew ThreadStart(this, &Engine::binar));
	thread->Priority = ThreadPriority::Highest;
	thread->Start();
}

void Engine::doBinarAdaptive() {
	thread = gcnew Thread(gcnew ThreadStart(this, &Engine::binarAdaptive));
	thread->Priority = ThreadPriority::Highest;
	thread->Start();
}

void Engine::doPower(double c, double g) {
	this->c = c; this->g = g;
	thread = gcnew Thread(gcnew ThreadStart(this, &Engine::power));
	thread->Priority = ThreadPriority::Highest;
	thread->Start();
}

void Engine::doLBrightness(int val) {
	t = val;
	thread = gcnew Thread(gcnew ThreadStart(this, &Engine::lBrightness));
	thread->Priority = ThreadPriority::Highest;
	thread->Start();
}

void Engine::doNBrightness(int val) {
	t = val;
	thread = gcnew Thread(gcnew ThreadStart(this, &Engine::nBrightness));
	thread->Priority = ThreadPriority::Highest;
	thread->Start();
}

void Engine::doLContrast(int val) {
	t = val;
	thread = gcnew Thread(gcnew ThreadStart(this, &Engine::lContrast));
	thread->Priority = ThreadPriority::Highest;
	thread->Start();
}

void Engine::doNContrast(int val) {
	t = val;
	thread = gcnew Thread(gcnew ThreadStart(this, &Engine::nContrast));
	thread->Priority = ThreadPriority::Highest;
	thread->Start();
}

void Engine::doAutolevels() {
	b1 = 441;
	thread = gcnew Thread(gcnew ThreadStart(this, &Engine::autolevels));
	thread->Priority = ThreadPriority::Highest;
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
	b0 = size + 1;
	b1 = mSize[size];
	thread->Priority = ThreadPriority::Highest;
	thread->Start();
}

void Engine::doFrequencyDomain(int radius, int order) {
	b0 = radius; b1 = order;
	thread = gcnew Thread(gcnew ThreadStart(this, &Engine::frequencyDomain));
	thread->Priority = ThreadPriority::Highest;
	thread->Start();
}

#pragma endregion
#pragma region Calc
#pragma region Transforms

void Engine::negative() {
	Bitmap^ orig = gcnew Bitmap(data[current]);
	Bitmap^ ret = gcnew Bitmap(orig->Width, orig->Height);
	for (int row = 0; row < orig->Width; row++) {
		for (int col = 0; col < orig->Height; col++) {
			Color c = orig->GetPixel(row, col);
			ret->SetPixel(row, col, Color::FromArgb(255 - c.R, 255 - c.G, 255 - c.B));
		}
		progressPtr->Invoke(del);
	}
	addNode(ret);
	picturePtr->Invoke(upd);
}

void Engine::halftone() {
	Bitmap^ orig = gcnew Bitmap(data[current]);
	Bitmap^ ret = gcnew Bitmap(orig->Width, orig->Height);
	for (int row = 0; row < orig->Width; row++) {
		for (int col = 0; col < orig->Height; col++) {
			Color temp = orig->GetPixel(row, col);
			int v = (int)(0.3 * temp.R + 0.59 * temp.G + 0.11 * temp.B);
			ret->SetPixel(row, col, Color::FromArgb(v, v, v));
		}
		progressPtr->Invoke(del);
	}
	addNode(ret);
	picturePtr->Invoke(upd);
}

void Engine::binar() {
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
		progressPtr->Invoke(del);
	}
	addNode(ret);
	picturePtr->Invoke(upd);
}

void Engine::binarAdaptive() {
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
		progressPtr->Invoke(del);
	}
	int histSize = (int)(max - min + 1);
	int* hist = new int[histSize] {0};
	for (int row = 0; row < orig->Width; row++) {
		for (int col = 0; col < orig->Height; col++) {
			hist[(int)(orig->GetPixel(row, col).GetBrightness() * 255 - min)]++;
		}
		progressPtr->Invoke(del);
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
	thread = gcnew Thread(gcnew ThreadStart(this, &Engine::binar));
	thread->Priority = ThreadPriority::Highest;
	thread->Start();
}

void Engine::power() {
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
		progressPtr->Invoke(del);
	}
	addNode(ret);
	picturePtr->Invoke(upd);
}

void Engine::lBrightness() {
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
		progressPtr->Invoke(del);
	}
	addNode(ret);
	picturePtr->Invoke(upd);
}

void Engine::nBrightness() {
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
		progressPtr->Invoke(del);
	}
	addNode(ret);
	picturePtr->Invoke(upd);
}

void Engine::lContrast() {
	Bitmap^ orig = gcnew Bitmap(data[current]);
	Bitmap^ ret = gcnew Bitmap(orig->Width, orig->Height);
	int val = t, gray = 0;
	int r = 0, g = 0, b = 0;
	for (int row = 0; row < orig->Width; row++) {
		for (int col = 0; col < orig->Height; col++) {
			Color temp = orig->GetPixel(row, col);
			gray += (int)(0.3 * temp.R + 0.59 * temp.G + 0.11 * temp.B);
		}
		progressPtr->Invoke(del);
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
		progressPtr->Invoke(del);
	}
	addNode(ret);
	picturePtr->Invoke(upd);
}

void Engine::nContrast() {
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
		progressPtr->Invoke(del);
	}
	addNode(ret);
	picturePtr->Invoke(upd);
}

void Engine::autolevels() {
	Bitmap^ orig = gcnew Bitmap(data[current]);
	Bitmap^ temp = gcnew Bitmap(orig->Width, orig->Height);
	Bitmap^ ret = gcnew Bitmap(orig->Width, orig->Height);
	float rs = 0, gs = 0, bs = 0;
	int** mask = getMask(0);
	/*int rmin = 255, gmin = 255, bmin = 255;
	int rmax = 0, gmax = 0, bmax = 0;*/
	for (int row = 0; row < orig->Width; row++) {
		for (int col = 0; col < orig->Height; col++) {
			int r = 0, g = 0, b = 0, cdiv = 441;
			for (int i = row - 10; i <= row + 10; i++) {
				for (int j = col - 10; j <= col + 10; j++) {
					if (i < 0 || i >= orig->Width || j < 0 || j >= orig->Height) {
						cdiv--;
						continue;
					}
					Color t = orig->GetPixel(i, j);
					r += t.R; g += t.G; b += t.B;
				}
			}
			r /= cdiv; g /= cdiv; b /= cdiv;
			temp->SetPixel(row, col, Color::FromArgb(r, g, b));
			/*Color a = orig->GetPixel(row, col);
			a.R < rmin ? rmin = a.R : rmin = rmin;
			a.R > rmax ? rmax = a.R : rmax = rmax;
			a.G < gmin ? gmin = a.G : gmin = gmin;
			a.G > gmax ? gmax = a.G : gmax = gmax;
			a.B < bmin ? bmin = a.B : bmin = bmin;
			a.B > bmax ? bmax = a.B : bmax = bmax;*/
			
		}
		progressPtr->Invoke(del);
	}
	/*int ra = rmax - rmin, ga = gmax - gmin, ba = bmax - bmin;*/
	/*float rf = rmax == rmin ? 255.0f : 255.0f / float(rmax - rmin);
	float gf = gmax == gmin ? 255.0f : 255.0f / float(gmax - gmin);
	float bf = bmax == bmin ? 255.0f : 255.0f / float(bmax - bmin);*/
	for (int row = 0; row < orig->Width; row++) {
		for (int col = 0; col < orig->Height; col++) {
			Color a = orig->GetPixel(row, col);
			Color c = temp->GetPixel(row, col);
			double r = double(a.R) / double(c.R);
			double g = double(a.G) / double(c.G);
			double b = double(a.B) / double(c.B);
			r *= 170.0; g *= 170.0; b *= 170.0;
			ret->SetPixel(row, col, Color::FromArgb(
				int(r) > 255 ? 255 : int(r),
				int(g) > 255 ? 255 : int(g),
				int(b) > 255 ? 255 : int(b)));
			/*ret->SetPixel(row, col, Color::FromArgb(
				int(a.R * r) > 255 ? 255 : int(a.R * r),
				int(a.G * g) > 255 ? 255 : int(a.G * g),
				int(a.B * b) > 255 ? 255 : int(a.B * b)));*/
			/*ret->SetPixel(row, col, Color::FromArgb(
				int(a.R * rs) < 0 ? 0 : int(a.R * rs) > 255 ? 255 : int(a.R * rs),
				int(a.G * gs) < 0 ? 0 : int(a.G * gs) > 255 ? 255 : int(a.G * gs),
				int(a.B * bs) < 0 ? 0 : int(a.B * bs) > 255 ? 255 : int(a.B * bs)));*/
			/*int t1 = Math::Abs(a.R - rmin);
			int t2 = Math::Abs(a.G - gmin);
			int t3 = Math::Abs(a.B - bmin);
			ret->SetPixel(row, col, Color::FromArgb(
				int(t1 * rf) > 255 ? 255 : int(t1 * rf),
				int(t2 * gf) > 255 ? 255 : int(t2 * gf),
				int(t3 * bf) > 255 ? 255 : int(t3 * bf)));*/
		}
		progressPtr->Invoke(del);
	}
	addNode(ret);
	picturePtr->Invoke(upd);
}

#pragma endregion
#pragma region Filters

void Engine::filterLF() {
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
		progressPtr->Invoke(del);
	}
	addNode(ret);
	picturePtr->Invoke(upd);
}

void Engine::filterRL() {
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
		progressPtr->Invoke(del);
	}
	addNode(ret);
	picturePtr->Invoke(upd);
}

void Engine::filterCS() {
	Bitmap^ orig = gcnew Bitmap(data[current]);
	Bitmap^ ret = gcnew Bitmap(orig->Width, orig->Height);
	Comparison<Color>^ cmp = gcnew Comparison<Color>(this, &Engine::compar);
	int sub = b0;
	for (int row = sub; row < orig->Width - sub; row++) {
		for (int col = sub; col < orig->Height - sub; col++) {
			List<Color>^ l = gcnew List<Color>();
			for (int i1 = row - sub, i2 = col - sub; i1 < row + sub; i1++, i2++) {
				l->Add(orig->GetPixel(i1, col));
				if (i2 != row) l->Add(orig->GetPixel(row, i2));
			}
			l->Sort(cmp);
			ret->SetPixel(row, col, l[sub]);
		}
		progressPtr->Invoke(del);
	}
	addNode(ret);
	picturePtr->Invoke(upd);
}

void Engine::filterRS() {
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
		progressPtr->Invoke(del);
	}
	addNode(ret);
	picturePtr->Invoke(upd);
}

void Engine::filterHL() {
	Bitmap^ orig = gcnew Bitmap(data[current]);
	Bitmap^ ret = gcnew Bitmap(orig->Width, orig->Height);
	int sub = b0, div = b1;
	int** mask = getMask(0);
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
		progressPtr->Invoke(del);
	}
	addNode(ret);
	picturePtr->Invoke(upd);
}

void Engine::filterVL() {
	Bitmap^ orig = gcnew Bitmap(data[current]);
	Bitmap^ ret = gcnew Bitmap(orig->Width, orig->Height);
	int sub = b0, div = b1;
	int** mask = getMask(1);
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
		progressPtr->Invoke(del);
	}
	addNode(ret);
	picturePtr->Invoke(upd);
}

void Engine::filterD1() {
	Bitmap^ orig = gcnew Bitmap(data[current]);
	Bitmap^ ret = gcnew Bitmap(orig->Width, orig->Height);
	int sub = b0, div = b1;
	int** mask = getMask(2);
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
		progressPtr->Invoke(del);
	}
	addNode(ret);
	picturePtr->Invoke(upd);
}

void Engine::filterD2() {
	Bitmap^ orig = gcnew Bitmap(data[current]);
	Bitmap^ ret = gcnew Bitmap(orig->Width, orig->Height);
	int sub = b0, div = b1;
	int** mask = getMask(3);
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
		progressPtr->Invoke(del);
	}
	addNode(ret);
	picturePtr->Invoke(upd);
}

void Engine::frequencyDomain() {
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
		progressPtr->Invoke(del);
	}
	addNode(ret);
	picturePtr->Invoke(upd);
}

int Engine::compar(Color x, Color y) {
	return x.GetBrightness() < y.GetBrightness() ? -1 :
		x.GetBrightness() == y.GetBrightness() ? 0 : 1;
}

int** Engine::getMask(int type) {
	int len = int(Math::Sqrt(b1));
	int** ret = new int* [len];
	for (int i = 0; i < len; i++) {
		ret[i] = new int[len];
		for (int j = 0; j < len; j++) {
			switch (type) {
			case 0: //horizontal
				if (j == len / 2) ret[i][j] = len - 1;
				else ret[i][j] = -1; break;
			case 1: //vertical
				if (i == len / 2) ret[i][j] = len - 1;
				else ret[i][j] = -1; break;
			case 2: //diagonal1
				if (j == len - i) ret[i][j] = len - 1;
				else ret[i][j] = -1; break;
			case 3: //diagonal2
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