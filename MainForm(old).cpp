/*
#include "MainForm(old).h"
#include <math.h>

using namespace ImageEditor;

//Entry
void Entry::initData(int type) {
	switch (type){
	case 0:
		data = L"Отмена предыдущего действия ";
		break;
	case 1:
		data = L"Преобразование изображения в негатив ";
		break;
	case 2:
		data = L"Преобразование изображения в полутоновое ";
		break;
	case 3:
		data = L"Бинарное преобразование изображения ";
		break;
	case 4:
		data = L"Степенное преобразование изображения ";
		break;
	case 5:
		data = L"Коррекция яркости ";
		break;
	case 6:
		data = L"Адаптивное бинарное преобразование изображения ";
		break;
	default:
		data = L"Unregistred type!";
		break;
	}
}

Entry::Entry(void) {
	Entry(0);
}

Entry::Entry(int type) {
	this->type = type;
	initData(type);
}

Entry::Entry(int type, int t, int b0, int b1) {
	if (type == 3) {
		this->type = type;
		initData(type);
		data = String::Concat(data, L"[T = " + t + "| b0 = " + b0 + "| b1 = " + b1 + "]");
	}
}

Entry::Entry(int type, float minB, float maxB) {
	if (type == 5) {
		this->type = type;
		initData(type);
		data = String::Concat(data, L"[minB = " + minB + "| maxB = " + maxB + "]");
	}
}

Entry::Entry(int type, double c, double g) {
	if (type == 4) {
		this->type = type;
		initData(type);
		data = String::Concat(data, L"[C = " + c + "| G = " + g + "]");
	}
}

//Obj
Obj::Obj() {
	width = 0;
	height = 0;
}

bool Obj::contain(Point^ dot) {
	if (dots = nullptr) return false;
	for (int i = 0; i < dots->Length; i++) {
		for (int j = 0; j < dots[i]->Length; j++) {
			if (dots[i][j]->Equals(dot)) return true;
		}
	}
	return false;
}

//MainForm
MainForm::MainForm(void) {
	InitializeComponent();
}

MainForm::~MainForm() {
	if (components)	{
		delete components;
	}
	if (images != nullptr) delete[] images;
	if (log != nullptr) delete[] log;
	if (fileName != nullptr) delete fileName;
}

//File items
Void MainForm::openMIClick(Object^ sender, EventArgs^ e) {
	if (fileName != nullptr || logsize != 0) {
		String^ text = L"Последние изменения не сохранены!\nПродолжить?", ^caption = L"Внимание!";
		MessageBoxButtons mbb = MessageBoxButtons::YesNo;
		MessageBoxIcon mbi = MessageBoxIcon::Warning;
		if (MessageBox::Show(text, caption, mbb, mbi) == Windows::Forms::DialogResult::No) return;
	}
	System::IO::Stream^ temp;
	OpenFileDialog^ openFileDialog = gcnew OpenFileDialog;
	openFileDialog->Filter = "BMP (*.bmp)|*.bmp|JPEG (*.jpeg), JPG (*.jpg)|*.jpeg; *.jpg|PNG (*.png)|*.png";
	openFileDialog->FilterIndex = sFDindex;
	openFileDialog->RestoreDirectory = true;
	if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		if ((temp = openFileDialog->OpenFile()) != nullptr)	{
			if (images != nullptr) delete[] images;
			if (log != nullptr) {
				delete[] log;
				logBox->Items->Clear();
			}
			fileName = nullptr;
			size = 1;
			statusSize->Text = gcnew String("Size: " + size);
			logsize = current = cur2 = 0;
			images = gcnew array<Bitmap^>(size);
			try {
				images[0] = gcnew Bitmap(temp);
			}
			catch (System::ArgumentException^ exc) {
				delete[] images;
				images = nullptr;
				size = 0;
				MessageBox::Show(exc->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				delete exc;
				return;
			}
			this->Text = openFileDialog->FileName;
			sFDindex = openFileDialog->FilterIndex;
			pictureBox1->Image = dynamic_cast<Image^>(images[0]);
			pictureBox2->Image = dynamic_cast<Image^>(images[0]);
			temp->Close();
		}
	}
	delete openFileDialog;
	//editorPanel1->Size = Drawing::Size(toolPanel->Location.X - 4, this->Size.Height - 114);
}

Void MainForm::saveMIClick(Object^ sender, EventArgs^ e) {
	if (fileName != nullptr) {
		backUpFrompictureBox1();
		images[current]->Save(fileName);
	}
	else saveAsMIClick(sender, e);
}

Void MainForm::saveAsMIClick(Object^ sender, EventArgs^ e) {
	if (images == nullptr) return;
	SaveFileDialog^ saveFileDialog = gcnew SaveFileDialog;
	saveFileDialog->Filter = "BMP (*.bmp)|*.bmp|JPEG (*.jpeg), JPG (*.jpg)|*.jpeg; *.jpg|PNG (*.png)|*.png";
	saveFileDialog->FilterIndex = sFDindex;
	saveFileDialog->RestoreDirectory = true;
	if (saveFileDialog->ShowDialog() == Windows::Forms::DialogResult::Cancel) return;
	if (saveFileDialog->FileName != "") {
		System::IO::FileStream^ fs;
		switch (saveFileDialog->FilterIndex) {
		case 1:
			saveFileDialog->FileName->Concat(saveFileDialog->FileName, ".bmp");
			fs = safe_cast<System::IO::FileStream^>(saveFileDialog->OpenFile());
			images[current]->Save(fs, System::Drawing::Imaging::ImageFormat::Bmp);
			break;
		case 2:
			saveFileDialog->FileName->Concat(saveFileDialog->FileName, ".jpeg");
			fs = safe_cast<System::IO::FileStream^>(saveFileDialog->OpenFile());
			images[current]->Save(fs, System::Drawing::Imaging::ImageFormat::Jpeg);
			break;
		case 3:
			saveFileDialog->FileName->Concat(saveFileDialog->FileName, ".png");
			fs = safe_cast<System::IO::FileStream^>(saveFileDialog->OpenFile());
			images[current]->Save(fs, System::Drawing::Imaging::ImageFormat::Png);
			break;
		}
		fileName = saveFileDialog->FileName;
		sFDindex = saveFileDialog->FilterIndex;
		fs->Close();
		delete saveFileDialog;
	}
}

Void MainForm::exitMIClick(Object^ sender, EventArgs^ e) {
	Application::Exit();
}

//lab functions
Void MainForm::negativeClick(Object^ sender, EventArgs^ e) {
	if (images == nullptr) return;
	controlsEnabled(false);
	progressBar->Maximum = images[current]->Size.Width;
	progressBar->Value = 0;
	progressBar->Visible = true;
	transformThread = gcnew Thread(gcnew ThreadStart(this, &MainForm::negative));
	transformThread->IsBackground = true;
	transformThread->Priority = ThreadPriority::Highest;
	transformThread->Start();
	Array::Resize(log, logsize + 1);
	log[logsize] = gcnew Entry(1);
	logBox->Items->Add(log[logsize]->data);
	logsize++;
	statusLogsize->Text = gcnew String("Logsize: " + logsize);
}

Void MainForm::halftoneClick(Object^ sender, EventArgs^ e) {
	if (images == nullptr) return;
	controlsEnabled(false);
	progressBar->Maximum = images[current]->Size.Width;
	progressBar->Value = 0;
	progressBar->Visible = true;
	transformThread = gcnew Thread(gcnew ThreadStart(this, &MainForm::halftone));
	transformThread->IsBackground = true;
	transformThread->Priority = ThreadPriority::Highest;
	transformThread->Start();
	Array::Resize(log, logsize + 1);
	log[logsize] = gcnew Entry(2);
	logBox->Items->Add(log[logsize]->data);
	logsize++;
	statusLogsize->Text = gcnew String("Logsize: " + logsize);
}

Void MainForm::adaptiveBinarClick(Object^ sender, EventArgs^ e) {
	if (images == nullptr) return;
	controlsEnabled(false);
	progressBar->Maximum = images[current]->Size.Width;
	progressBar->Value = 0;
	progressBar->Visible = true;
	b0 = 0;
	b1 = 255;
	transformThread = gcnew Thread(gcnew ThreadStart(this, &MainForm::adaptiveBinar));
	transformThread->IsBackground = true;
	transformThread->Priority = ThreadPriority::Highest;
	transformThread->Start();
	Array::Resize(log, logsize + 1);
	log[logsize] = gcnew Entry(6);
	logBox->Items->Add(log[logsize]->data);
	logsize++;
	statusLogsize->Text = gcnew String("Logsize: " + logsize);
}

Void MainForm::undoClick(Object^ sender, EventArgs^ e) {
	if (activePB == 0 && current > 0) {
		current--;
		statusCurrent->Text = gcnew String("Current: " + current);
		pictureBox1->Image = images[current];
	}
	else if (activePB == 1 && cur2 > 0) {
		cur2--;
		statusCurrent->Text = gcnew String("Cur2: " + current);
		pictureBox2->Image = images[cur2];
	}
}

Void MainForm::redoClick(Object^ sender, EventArgs^ e) {
	if (activePB == 0 && current < size - 1) {
		current++;
		statusCurrent->Text = gcnew String("Current: " + current);
		pictureBox1->Image = images[current];
	}
	else if (activePB == 1 && cur2 < size - 1) {
		cur2++;
		statusCurrent->Text = gcnew String("Cur2: " + cur2);
		pictureBox2->Image = images[cur2];
	}
}

Void MainForm::binaryButtonClick(Object^ sender, EventArgs^ e) {
	if (images == nullptr) return;
	if (sender != nullptr && e != nullptr) {
		if (binaryBoxTextBox1->Text == String::Empty &&
			binaryBoxTextBox2->Text == String::Empty &&
			binaryBoxTextBox3->Text == String::Empty) return;
		t = binaryBoxTrackBar1->Value;
		b0 = binaryBoxTrackBar2->Value;
		b1 = binaryBoxTrackBar3->Value;
	}
	controlsEnabled(false);
	progressBar->Maximum = images[current]->Size.Width;
	progressBar->Value = 0;
	progressBar->Visible = true;
	if (log != nullptr) {
		if (log[logsize - 1]->type != 3) {
			curBP = current;
			statusCurBP->Text = gcnew String("CurBP: " + curBP);
		}
	}
	else curBP = current;
	transformThread = gcnew Thread(gcnew ThreadStart(this, &MainForm::binar));
	transformThread->IsBackground = true;
	transformThread->Priority = ThreadPriority::Highest;
	transformThread->Start();
	Array::Resize(log, logsize + 1);
	log[logsize] = gcnew Entry(3, t, b0, b1);
	logBox->Items->Add(log[logsize]->data);
	logsize++;
	statusLogsize->Text = gcnew String("Logsize: " + logsize);
}

Void MainForm::powerButtonClick(Object^ sender, EventArgs^ e) {
	if (images == nullptr) return;
	if (sender != nullptr && e != nullptr) {
		if (powerBoxTextBox1->Text == String::Empty ||
			powerBoxTextBox2->Text == String::Empty) return;
		c = (double)(powerBoxTrackBar1->Value / 100.0);
		g = (double)(powerBoxTrackBar2->Value / 100.0);
	}
	controlsEnabled(false);
	progressBar->Maximum = images[current]->Size.Width;
	progressBar->Value = 0;
	progressBar->Visible = true;
	if (log != nullptr) {
		if (log[logsize - 1]->type != 4) {
			curBP = current;
			statusCurBP->Text = gcnew String("CurBP: " + curBP);
		}
	}
	else curBP = current;
	transformThread = gcnew Thread(gcnew ThreadStart(this, &MainForm::power));
	transformThread->IsBackground = true;
	transformThread->Priority = ThreadPriority::Highest;
	transformThread->Start();
	Array::Resize(log, logsize + 1);
	log[logsize] = gcnew Entry(4, c, g);
	logBox->Items->Add(log[logsize]->data);
	logsize++;
	statusLogsize->Text = gcnew String("Logsize: " + logsize);
}

Void MainForm::linearTensionClick(Object^ sender, EventArgs^ e) {
	if (images == nullptr) return;
	controlsEnabled(false);
	progressBar->Maximum = images[current]->Size.Width * 2;
	progressBar->Value = 0;
	progressBar->Visible = true;
	transformThread = gcnew Thread(gcnew ThreadStart(this, &MainForm::linearTension));
	transformThread->IsBackground = true;
	transformThread->Priority = ThreadPriority::Highest;
	transformThread->Start();
	Array::Resize(log, logsize + 1);
	log[logsize] = gcnew Entry(1);
	logBox->Items->Add(log[logsize]->data);
	logsize++;
	statusLogsize->Text = gcnew String("Logsize: " + logsize);
}

Void MainForm::stretchContrastClick(Object^ sender, EventArgs^ e) {

}

Void MainForm::fixButtonClick(Object^ sender, EventArgs^ e) {
	curBP = current;
	statusCurBP->Text = gcnew String("CurBP: " + curBP);
	Focus();
}

Void MainForm::findClassButtonClick(Object^ sender, EventArgs^ e) {
	if (images == nullptr) return;

}

//lab functions
Void MainForm::negative() {
	Bitmap^ image = gcnew Bitmap(images[current]);
	Bitmap^ ret = gcnew Bitmap(image->Size.Width, image->Size.Height);
	int completePercentage = 0;
	for (int row = 0; row < ret->Width; row++) {
		for (int col = 0; col < ret->Height; col++) {
			Color temp = image->GetPixel(row, col);
			ret->SetPixel(row, col, Color::FromArgb(255 - temp.R, 255 - temp.G, 255 - temp.B));
		}
		completePercentage++;
		progressBar->BeginInvoke(gcnew ProgressBarChangeValue(this, &MainForm::progressBarChangeValue), completePercentage);
	}
	pictureBox1->BeginInvoke(gcnew PictureBoxChangeImage(this, &MainForm::pictureBoxChangeImage), ret);
}

Void MainForm::halftone() {
	Bitmap^ image = gcnew Bitmap(images[current]);
	Bitmap^ ret = gcnew Bitmap(image->Size.Width, image->Size.Height);
	int completePercentage = 0;
	for (int row = 0; row < ret->Width; row++) {
		for (int col = 0; col < ret->Height; col++) {
			Color temp = image->GetPixel(row, col);
			int Y = (int)(0.3 * temp.R + 0.59 * temp.G + 0.11 * temp.B);
			ret->SetPixel(row, col, Color::FromArgb(Y, Y, Y));
		}
		completePercentage++;
		progressBar->BeginInvoke(gcnew ProgressBarChangeValue(this, &MainForm::progressBarChangeValue), completePercentage);
	}
	pictureBox1->BeginInvoke(gcnew PictureBoxChangeImage(this, &MainForm::pictureBoxChangeImage), ret);
}

Void MainForm::binar() {
	Bitmap^ image = gcnew Bitmap(images[curBP]);
	Bitmap^ ret = gcnew Bitmap(image->Size.Width, image->Size.Height);
	int completePercentage = 0, t = this->t, b0 = this->b0, b1 = this->b1;
	for (int row = 0; row < image->Width; row++) {
		for (int col = 0; col < image->Height; col++) {
			Color b = image->GetPixel(row, col);
			b.GetBrightness() * 255 <= t ? ret->SetPixel(row, col, Color::FromArgb(b0, b0, b0)) : ret->SetPixel(row, col, Color::FromArgb(b1, b1, b1));
		}
		completePercentage++;
		progressBar->BeginInvoke(gcnew ProgressBarChangeValue(this, &MainForm::progressBarChangeValue), completePercentage);
	}
	pictureBox1->BeginInvoke(gcnew PictureBoxChangeImage(this, &MainForm::pictureBoxChangeImage), ret);
}

Void MainForm::adaptiveBinar() {
	Bitmap^ image = gcnew Bitmap(images[curBP]);
	int completePercentage = 0;
	float min = 255.0, max = 0.0;
	for (int row = 0; row < image->Width; row++) {
		for (int col = 0; col < image->Height; col++) {
			Color^ temp = image->GetPixel(row, col);
			if (temp->GetBrightness() * 255 < min) {
				min = temp->GetBrightness() * 255;
			}
			if (temp->GetBrightness() * 255 > max) {
				max = temp->GetBrightness() * 255;
			}
		}
		completePercentage++;
		progressBar->BeginInvoke(gcnew ProgressBarChangeValue(this, &MainForm::progressBarChangeValue), completePercentage);
	}
	int histSize = (int)(max - min + 1);
	int* hist = new int[histSize];
	for (int t = 0; t < histSize; t++)
		hist[t] = 0;
	completePercentage = 0;
	for (int row = 0; row < image->Width; row++) {
		for (int col = 0; col < image->Height; col++) {
			hist[(int)(image->GetPixel(row, col).GetBrightness() * 255 - min)]++;
		}
		completePercentage++;
		progressBar->BeginInvoke(gcnew ProgressBarChangeValue(this, &MainForm::progressBarChangeValue), completePercentage);
	}
	int m = 0, n = 0, threshold = 0, alpha1 = 0, beta1 = 0;
	for (int t = 0; t <= max - min; t++) {
		m += t * hist[t];
		n += hist[t];
	}

	float maxSigma = -1;
	for (int t = 0; t < max - min; t++)	{
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
	t = threshold;
	transformThread = gcnew Thread(gcnew ThreadStart(this, &MainForm::binar));
	transformThread->IsBackground = true;
	transformThread->Priority = ThreadPriority::Highest;
	transformThread->Start();
}

Void MainForm::power() {
	Bitmap^ image = gcnew Bitmap(images[curBP]);
	Bitmap^ ret = gcnew Bitmap(image->Size.Width, image->Size.Height);
	int completePercentage = 0;
	double c = this->c, g = this->g;
	for (int row = 0; row < image->Width; row++) {
		for (int col = 0; col < image->Height; col++) {
			Color a = image->GetPixel(row, col);
			Color b = Color::FromArgb(
				(long long int)pow(a.R * c, g) >= 255 ? 255 : (int)pow(a.R * c, g),
				(long long int)pow(a.G * c, g) >= 255 ? 255 : (int)pow(a.G * c, g),
				(long long int)pow(a.B * c, g) >= 255 ? 255 : (int)pow(a.B * c, g));
			ret->SetPixel(row, col, b);
		}
		completePercentage++;
		progressBar->BeginInvoke(gcnew ProgressBarChangeValue(this, &MainForm::progressBarChangeValue), completePercentage);
	}
	pictureBox1->BeginInvoke(gcnew PictureBoxChangeImage(this, &MainForm::pictureBoxChangeImage), ret);
}

Void MainForm::linearTension() {
	Bitmap^ image = gcnew Bitmap(images[current]);
	Bitmap^ ret = gcnew Bitmap(image->Size.Width, image->Size.Height);
	int completePercentage = 0, R, G, B;
	float minB = 255.0, maxB = 0.0;
	Color^ min, ^max;
	for (int row = 0; row < image->Width; row++) {
		for (int col = 0; col < image->Height; col++) {
			Color^ temp = image->GetPixel(row, col);
			if (temp->GetBrightness() * 255 < minB) {
				minB = temp->GetBrightness() * 255;
				min = temp;
			}
			if (temp->GetBrightness() * 255 > maxB) {
				maxB = temp->GetBrightness() * 255;
				max = temp;
			}
		}
		completePercentage++;
		progressBar->BeginInvoke(gcnew ProgressBarChangeValue(this, &MainForm::progressBarChangeValue), completePercentage);
	}
	R = (int)(255.0 / (max->R - min->R)) > 255 ? 255 : (int)(255.0 / (max->R - min->R));
	G = (int)(255.0 / (max->G - min->G)) > 255 ? 255 : (int)(255.0 / (max->G - min->G));
	B = (int)(255.0 / (max->B - min->B)) > 255 ? 255 : (int)(255.0 / (max->B - min->B));
	for (int row = 0; row < image->Width; row++) {
		for (int col = 0; col < image->Height; col++) {
			Color^ temp = image->GetPixel(row, col);
			ret->SetPixel(row, col, Color::FromArgb(
				(long long int)((temp->R - min->R) * R) > 255 ? 255 : (long long int)((
				(temp->R - min->R) < 0 ? 0 : (temp->R - min->R)) * R),
				(long long int)((temp->G - min->G) * G) > 255 ? 255 : (long long int)((
				(temp->G - min->G) < 0 ? 0 : (temp->G - min->G)) * G),
				(long long int)((temp->B - min->B) * B) > 255 ? 255 : (long long int)((
				(temp->B - min->B) < 0 ? 0 : (temp->B - min->B)) * B)));
		}
		completePercentage++;
		progressBar->BeginInvoke(gcnew ProgressBarChangeValue(this, &MainForm::progressBarChangeValue), completePercentage);
	}
	pictureBox1->BeginInvoke(gcnew PictureBoxChangeImage(this, &MainForm::pictureBoxChangeImage), ret);
	BeginInvoke(gcnew LogBoxLinearTension(this, &MainForm::logBoxLinearTension), minB, maxB);
}

Void MainForm::stretchContrast() {

}

//UI
Void MainForm::toolPanelShowHide(Object^ sender, EventArgs^ e) {
	toolPanel->Visible = toolPanel->Visible ? false : true;
	mainFormSizeChanged(sender, e);
}

Void MainForm::secondPictureShowHide(Object^ sender, EventArgs^ e) {
	editorPanel2->Visible = editorPanel2->Visible ? false : true;
	if (images != nullptr) pictureBox2->Image = images[cur2];
	mainFormSizeChanged(sender, e);
}

Void MainForm::mainFormSizeChanged(Object^ sender, EventArgs^ e) {
	if (editorPanel2->Visible) {
		if (toolPanel->Visible) {
			editorPanel1->Size = Drawing::Size((editorPage->Width - toolPanel->Width - 12) / 2, editorPage->Height - 3);
		}
		else {
			editorPanel1->Size = Drawing::Size((editorPage->Width - 8) / 2, editorPage->Height - 3);
		}
		editorPanel1->Location = Point(3, 3);
		editorPanel2->Location = Point(editorPanel1->Width + 6, 3);
		editorPanel2->Size = Drawing::Size(editorPanel1->Width, editorPage->Height - 3);
	}
	else {
		if (toolPanel->Visible) {
			editorPanel1->Size = Drawing::Size(editorPage->Width - toolPanel->Width - 3, editorPage->Height - 3);
		}
		else {
			editorPanel1->Size = Drawing::Size(editorPage->Width - 3, editorPage->Height - 3);
		}
		editorPanel1->Location = Point(3, 3);
	}
}

Void MainForm::progressBarSizeChanged(Object^ sender, EventArgs^ e) {
	this->progressBar->Size.Height = 10;
}

Void MainForm::controlsEnabled(bool state) {
	negativeButton->Enabled = state;
	halftoneButton->Enabled = state;
	binaryButton->Enabled = state;
	powerButton->Enabled = state;
	binaryFixButton->Enabled = state;
	powerFixButton->Enabled = state;
	binaryBoxTrackBar1->Enabled = state;
	binaryBoxTrackBar2->Enabled = state;
	binaryBoxTrackBar3->Enabled = state;
	powerBoxTrackBar1->Enabled = state;
	powerBoxTrackBar2->Enabled = state;
	binaryBoxTextBox1->Enabled = state;
	binaryBoxTextBox2->Enabled = state;
	binaryBoxTextBox3->Enabled = state;
	powerBoxTextBox1->Enabled = state;
	powerBoxTextBox2->Enabled = state;
}

Void MainForm::pictureBoxClick(Object^ sender, EventArgs^ e) {
	if (safe_cast<PictureBox^>(sender)->TabIndex == 0) {
		activePB = 0;
		statusCurrent->Text = gcnew String("Current: " + current);
	}
	else {
		activePB = 1;
		statusCurrent->Text = gcnew String("Cur2: " + cur2);
	}
}

//toolpanel
Void MainForm::toolPanelTextBoxKeyDown(Object^ sender, KeyEventArgs^ e) {
	switch (safe_cast<TextBox^>(sender)->Parent->TabIndex * safe_cast<TextBox^>(sender)->TabIndex) {
	case 10:
		switch (e->KeyCode) {
		case Keys::Up:
			binaryBoxTextBox3->Focus();
			break;
		case Keys::Down:
			binaryBoxTextBox2->Focus();
			break;
		case Keys::Enter:
			e->SuppressKeyPress = true;
			break;
		}
		break;
	case 12:
		switch (e->KeyCode) {
		case Keys::Up:
			binaryBoxTextBox1->Focus();
			break;
		case Keys::Down:
			binaryBoxTextBox3->Focus();
			break;
		case Keys::Enter:
			e->SuppressKeyPress = true;
			break;
		}
		break;
	case 14:
		switch (e->KeyCode) {
		case Keys::Up:
			binaryBoxTextBox2->Focus();
			break;
		case Keys::Down:
			binaryBoxTextBox1->Focus();
			break;
		case Keys::Enter:
			e->SuppressKeyPress = true;
			break;
		}
		break;
	case 15:
		switch (e->KeyCode) {
		case Keys::Up:
			powerBoxTextBox2->Focus();
			break;
		case Keys::Down:
			powerBoxTextBox2->Focus();
			break;
		case Keys::Enter:
			e->SuppressKeyPress = true;
			break;
		}
		break;
	case 18:
		switch (e->KeyCode) {
		case Keys::Up:
			powerBoxTextBox1->Focus();
			break;
		case Keys::Down:
			powerBoxTextBox1->Focus();
			break;
		case Keys::Enter:
			e->SuppressKeyPress = true;
			break;
		}
		break;
	default:
		e->SuppressKeyPress = true;
		break;
	}
}

Void MainForm::toolPanelTextBoxTextChanged(Object^ sender, EventArgs^ e) {
	switch (safe_cast<TextBox^>(sender)->Parent->TabIndex * safe_cast<TextBox^>(sender)->TabIndex) {
	case 10:
		if (binaryBoxTextBox1->Text != String::Empty && 
			Convert::ToInt32(binaryBoxTextBox1->Text) <= 255) {
			binaryBoxTrackBar1->Value = Convert::ToInt32(binaryBoxTextBox1->Text);
		}
		else binaryBoxTrackBar1->Value = 255;
		break;
	case 12:
		if (binaryBoxTextBox2->Text != String::Empty && 
			Convert::ToInt32(binaryBoxTextBox2->Text) <= 255) {
			binaryBoxTrackBar2->Value = Convert::ToInt32(binaryBoxTextBox2->Text);
		}
		else binaryBoxTrackBar2->Value = 255;
		break;
	case 14:
		if (binaryBoxTextBox3->Text != String::Empty && 
			Convert::ToInt32(binaryBoxTextBox3->Text) <= 255) {
			binaryBoxTrackBar3->Value = Convert::ToInt32(binaryBoxTextBox3->Text);
		}
		else binaryBoxTrackBar3->Value = 255;
		break;
	case 15:
		if (powerBoxTextBox1->Text != String::Empty) {
			try {
				if (Convert::ToDouble(powerBoxTextBox1->Text) * 100.0 >= 400.0) powerBoxTrackBar1->Value = 400;
				else powerBoxTrackBar1->Value = (int)(Convert::ToDouble(powerBoxTextBox1->Text) * 100.0);
			}
			catch (System::FormatException^ exc) {
				delete exc;
				return;
			}
		}
		else powerBoxTrackBar1->Value = 0;
		break;
	case 18:
		if (powerBoxTextBox2->Text != String::Empty) {
			try {
				if (Convert::ToDouble(powerBoxTextBox2->Text) * 100.0 >= 400.0) powerBoxTrackBar2->Value = 400;
				else powerBoxTrackBar2->Value = (int)(Convert::ToDouble(powerBoxTextBox2->Text) * 100.0);
			}
			catch (System::FormatException^ exc) {
				delete exc;
				return;
			}
		}
		else powerBoxTrackBar2->Value = 0;
		break;
	default:
		break;
	}
}

Void MainForm::toolPanelTextBoxKeyPress(Object^ sender, KeyPressEventArgs^ e) {
	switch (safe_cast<TextBox^>(sender)->Parent->TabIndex) {
	case 2:
		if (!Char::IsControl(e->KeyChar) && !Char::IsDigit(e->KeyChar)) e->Handled = true;
		break;
	case 3:
		if (!Char::IsControl(e->KeyChar) && !Char::IsDigit(e->KeyChar) && (e->KeyChar != ',')) e->Handled = true;
		break;
	default:
		break;
	}
	
}

Void MainForm::toolPanelTrackBarValueChanged(Object^ sender, EventArgs^ e) {
	switch (safe_cast<TrackBar^>(sender)->Parent->TabIndex * safe_cast<TrackBar^>(sender)->TabIndex) {
	case 16:
		binaryBoxTextBox1->Text = binaryBoxTrackBar1->Value.ToString();
		break;
	case 18:
		binaryBoxTextBox2->Text = binaryBoxTrackBar2->Value.ToString();
		break;
	case 20:
		binaryBoxTextBox3->Text = binaryBoxTrackBar3->Value.ToString();
		break;
	case 24:
		powerBoxTextBox1->Text = Convert::ToString((double)powerBoxTrackBar1->Value / 100.0);
		break;
	case 27:
		powerBoxTextBox2->Text = Convert::ToString((double)powerBoxTrackBar2->Value / 100.0);
		break;
	default:
		break;
	}
}

//threading
Bitmap^ MainForm::getCurrentImage() {
	return images[current];
}

Void MainForm::pictureBoxChangeImage(Bitmap^ image) {
	pictureBox1->Image = image;
	backUpFrompictureBox1();
	progressBar->Visible = false;
	controlsEnabled(true);
}

Void MainForm::progressBarChangeValue(int value) {
	progressBar->Value = value;
}

Void MainForm::logBoxLinearTension(float minB, float maxB) {
	Array::Resize(log, logsize + 1);
	log[logsize] = gcnew Entry(5, minB, maxB);
	logBox->Items->Add(log[logsize]->data);
	logsize++;
	statusLogsize->Text = gcnew String("Logsize: " + logsize);
}

Void MainForm::binaryBeginInvoke() {
	//hahaha
}

//fromDialog_old
Void MainForm::dialogBinar(int t, int b0, int b1) {
	if (images == nullptr) return;
	this->t = t;
	this->b0 = b0;
	this->b1 = b1;
	binaryButtonClick(nullptr, nullptr);
}

Void MainForm::dialogPower(double c, double g) {
	if (images == nullptr) return;
	this->c = c;
	this->g = g;
	powerButtonClick(nullptr, nullptr);
}

Void MainForm::backUpFrompictureBox1() {
	if (images == nullptr) return;
	Array::Resize(images, size + 1);
	images[size] = gcnew Bitmap(pictureBox1->Image);
	size++;
	current = size - 1;
	statusSize->Text = gcnew String("Size: " + size);
	statusCurrent->Text = gcnew String("Current: " + current);
}
*/