#include "Dialog.h"
#include <math.h>

using namespace Lab1;

[STAThread]
void main() {
	MainForm ^form = gcnew MainForm();
	Application::Run(form);
	return;
}

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
		initData(type);
		data = String::Concat(data, L"[T = " + t + "| b0 = " + b0 + "| b1 = " + b1 + "]");
	}
}

Entry::Entry(int type, double c, double g) {
	if (type == 4) {
		initData(type);
		data = String::Concat(data, L"[C = " + c + "| G = " + g + "]");
	}
}

//MainForm
MainForm::MainForm(void) {
	InitializeComponent();
	size = logsize = 0;
	current = curBP = sFDindex = 0;
	t = b0 = b1 = 0;
	c = g = 1.0;
	images = nullptr;
	log = nullptr;
	fileName = nullptr;
	toolPanel->Visible = false;
	binaryFixButton->BackgroundImage = gcnew System::Drawing::Bitmap("fix.png");
	powerFixButton->BackgroundImage = gcnew System::Drawing::Bitmap("fix.png");
	Icon = gcnew System::Drawing::Icon("Icon.ico");
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
	openFileDialog->Filter = "BMP (*.bmp)|*.bmp|JPEG (*.jpeg)|*.jpeg|PNG (*.png)|*.png";
	openFileDialog->FilterIndex = 1;
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
			logsize = current = 0;
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
			if (openFileDialog->FileName->Contains(L".bmp")) sFDindex = 1;
			if (openFileDialog->FileName->Contains(L".jpeg")) sFDindex = 2;
			if (openFileDialog->FileName->Contains(L".png")) sFDindex = 3;
			pictureBox->Image = dynamic_cast<Image^>(images[0]);
			editorPanel->Size = Drawing::Size(editorPanel->Size.Width + toolPanel->Size.Width + 4, this->Size.Height - 100);
			temp->Close();
		}
	}
	delete openFileDialog;
	editorPanel->Size = Drawing::Size(toolPanel->Location.X - 4, this->Size.Height - 100);
}

Void MainForm::saveMIClick(Object^ sender, EventArgs^ e) {
	if (fileName != nullptr) {
		backUpFromPictureBox();
		SaveFileDialog^ saveFileDialog = gcnew SaveFileDialog;
		saveFileDialog->FileName = fileName;
		System::IO::FileStream^ fs = safe_cast<System::IO::FileStream^>(saveFileDialog->OpenFile());
		switch (sFDindex) {
		case 1:
			images[current]->Save(fs, System::Drawing::Imaging::ImageFormat::Bmp);
			break;
		case 2:
			images[current]->Save(fs, System::Drawing::Imaging::ImageFormat::Jpeg);
			break;
		case 3:
			images[current]->Save(fs, System::Drawing::Imaging::ImageFormat::Png);
			break;
		}
		fs->Close();
		delete saveFileDialog;
	}
	else saveAsMIClick(sender, e);
}

Void MainForm::saveAsMIClick(Object^ sender, EventArgs^ e) {
	if (images == nullptr) return;
	//backUpFromPictureBox();
	SaveFileDialog^ saveFileDialog = gcnew SaveFileDialog;
	saveFileDialog->Filter = "BMP (*.bmp)|*.bmp|JPEG (*.jpeg)|*.jpeg|PNG (*.png)|*.png";
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
	buttonsEnable(false);
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
}

Void MainForm::halftoneClick(Object^ sender, EventArgs^ e) {
	if (images == nullptr) return;
	buttonsEnable(false);
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
}

Void MainForm::binarClick(Object^  sender, EventArgs^ e) {
	for (int i = 0; i < Application::OpenForms->Count; i++) {
		if (Application::OpenForms[i]->Name == "Dialog") {
			Application::OpenForms[i]->Close();
		}
	}
	Dialog^ dialog = gcnew Dialog(this, 1);
	dialog->Show();
}

Void MainForm::powerClick(Object^ sender, EventArgs^ e) {
	for (int i = 0; i < Application::OpenForms->Count; i++) {
		if (Application::OpenForms[i]->Name == "Dialog") {
			Application::OpenForms[i]->Close();
		}
	}
	Dialog^ dialog = gcnew Dialog(this, 2);
	dialog->Show();
}

Void MainForm::brightСorrectClick(Object^ sender, EventArgs^ e) {

}

Void MainForm::undoClick(Object^ sender, EventArgs^ e) {
	if (current > 0) {
		current--;
		pictureBox->Image = images[current];
	}

}

Void MainForm::redoClick(Object^ sender, EventArgs^ e) {
	if (current < size - 1) {
		current++;
		pictureBox->Image = images[current];
	}
}

Void MainForm::binaryButtonClick(Object^ sender, EventArgs^ e) {
	if (images == nullptr) return;
	if (binaryBoxTextBox1->Text == String::Empty ||
		binaryBoxTextBox2->Text == String::Empty ||
		binaryBoxTextBox3->Text == String::Empty) return;
	t = binaryBoxTrackBar1->Value;
	b0 = binaryBoxTrackBar2->Value;
	b1 = binaryBoxTrackBar3->Value;
	buttonsEnable(false);
	progressBar->Maximum = images[current]->Size.Width;
	progressBar->Value = 0;
	progressBar->Visible = true;
	if (log != nullptr) {
		if(log[logsize - 1]->type != 3) curBP = current;
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
}

Void MainForm::powerButtonClick(Object^ sender, EventArgs^ e) {
	if (images == nullptr) return;
	if (powerBoxTextBox1->Text == String::Empty ||
		powerBoxTextBox2->Text == String::Empty) return;
	c = (double)(powerBoxTrackBar1->Value / 100.0);
	g = (double)(powerBoxTrackBar2->Value / 100.0);
	buttonsEnable(false);
	progressBar->Maximum = images[current]->Size.Width;
	progressBar->Value = 0;
	progressBar->Visible = true;
	if (log != nullptr) {
		if (log[logsize - 1]->type != 4) curBP = current;
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
}

Void MainForm::fixButtonClick(Object^ sender, EventArgs^ e) {
	curBP = current;
	Focus();
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
	pictureBox->BeginInvoke(gcnew PictureBoxChangeImage(this, &MainForm::pictureBoxChangeImage), ret);
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
	pictureBox->BeginInvoke(gcnew PictureBoxChangeImage(this, &MainForm::pictureBoxChangeImage), ret);
}

Void MainForm::binar() {
	Bitmap^ image = gcnew Bitmap(images[curBP]);
	Bitmap^ ret = gcnew Bitmap(image->Size.Width, image->Size.Height);
	int completePercentage = 0, t = this->t, b0 = this->b0, b1 = this->b1;
	for (int row = 0; row < image->Width; row++) {
		for (int col = 0; col < image->Height; col++) {
			Color b = image->GetPixel(row, col);
			ret->SetPixel(row, col, Color::FromArgb((b.R <= t ? b0 : b1), (b.G <= t ? b0 : b1), (b.B <= t ? b0 : b1)));
		}
		completePercentage++;
		progressBar->BeginInvoke(gcnew ProgressBarChangeValue(this, &MainForm::progressBarChangeValue), completePercentage);
	}
	pictureBox->BeginInvoke(gcnew PictureBoxChangeImage(this, &MainForm::pictureBoxChangeImage), ret);
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
	pictureBox->BeginInvoke(gcnew PictureBoxChangeImage(this, &MainForm::pictureBoxChangeImage), ret);
}

Void MainForm::brightCorrect() {

}

//UI
Void MainForm::toolPanelShowHide(Object^ sender, EventArgs^ e) {
	if (toolPanel->Visible == true){
		toolPanel->Visible = false;
		editorPanel->Size = Drawing::Size(editorPanel->Size.Width + toolPanel->Size.Width + 4, toolPanel->Size.Height);
	}
	else {
		toolPanel->Visible = true;
		editorPanel->Size = Drawing::Size(toolPanel->Location.X - 4, this->Size.Height - 100);
	}
}

Void MainForm::progressBar_SizeChanged(Object^ sender, EventArgs^ e) {
	this->progressBar->Size.Height = 10;
}

Void MainForm::buttonsEnable(bool state) {
	negativeButton->Enabled = state;
	halftoneButton->Enabled = state;
	binaryButton->Enabled = state;
	powerButton->Enabled = state;
}

//toolpanel textBoxes
Void MainForm::binaryBoxTextBox1KeyDown(Object^ sender, KeyEventArgs^ e) {
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
}

Void MainForm::binaryBoxTextBox2KeyDown(Object^ sender, KeyEventArgs^ e) {
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
}

Void MainForm::binaryBoxTextBox3KeyDown(Object^ sender, KeyEventArgs^ e) {
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
}

Void MainForm::powerBoxTextBox1KeyDown(Object^ sender, KeyEventArgs^ e) {
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
	default:
		e->Handled = true;
		break;
	}
}

Void MainForm::powerBoxTextBox2KeyDown(Object^ sender, KeyEventArgs^ e) {
	switch (e->KeyCode) {
	case Keys::Up:
		powerBoxTextBox1->Focus();
		break;
	case Keys::Down:
		powerBoxTextBox1->Focus();
		break;
	case Keys::Enter:
		e->Handled = true;
		break;
	}
}

Void MainForm::binaryBoxTextBox1TextChanged(Object^ sender, EventArgs^ e) {
	if (binaryBoxTextBox1->Text != String::Empty && Convert::ToInt32(binaryBoxTextBox1->Text) <= 255) {
		binaryBoxTrackBar1->Value = Convert::ToInt32(binaryBoxTextBox1->Text);
	}
}

Void MainForm::binaryBoxTextBox2TextChanged(Object^ sender, EventArgs^ e) {
	if (binaryBoxTextBox2->Text != String::Empty && Convert::ToInt32(binaryBoxTextBox2->Text) <= 255) {
		binaryBoxTrackBar2->Value = Convert::ToInt32(binaryBoxTextBox2->Text);
	}
}

Void MainForm::binaryBoxTextBox3TextChanged(Object^ sender, EventArgs^ e) {
	if (binaryBoxTextBox3->Text != String::Empty && Convert::ToInt32(binaryBoxTextBox3->Text) <= 255) {
		binaryBoxTrackBar3->Value = Convert::ToInt32(binaryBoxTextBox3->Text);
	}
}

Void MainForm::powerBoxTextBox1TextChanged(Object^ sender, EventArgs^ e) {
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
}

Void MainForm::powerBoxTextBox2TextChanged(Object^ sender, EventArgs^ e) {
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
}

Void MainForm::textBox_KeyPressInt(Object^ sender, KeyPressEventArgs^ e) {
	if (!Char::IsControl(e->KeyChar) && !Char::IsDigit(e->KeyChar)) {
		e->Handled = true;
	}
}

Void MainForm::textBox_KeyPressDouble(Object^ sender, KeyPressEventArgs^ e) {
	if (!Char::IsControl(e->KeyChar) && !Char::IsDigit(e->KeyChar) && (e->KeyChar != ',')) {
		e->Handled = true;
	}
}

//toolpanel trackbars
Void MainForm::binaryBoxTrackBar1ValueChanged(Object^ sender, EventArgs^ e) {
	binaryBoxTextBox1->Text = binaryBoxTrackBar1->Value.ToString();
	t = binaryBoxTrackBar1->Value;
}

Void MainForm::binaryBoxTrackBar2ValueChanged(Object^ sender, EventArgs^ e) {
	binaryBoxTextBox2->Text = binaryBoxTrackBar2->Value.ToString();
	b0 = binaryBoxTrackBar2->Value;
}

Void MainForm::binaryBoxTrackBar3ValueChanged(Object^ sender, EventArgs^ e) {
	binaryBoxTextBox3->Text = binaryBoxTrackBar3->Value.ToString();
	b1 = binaryBoxTrackBar3->Value;
}

Void MainForm::powerBoxTrackBar1ValueChanged(Object^ sender, EventArgs^ e) {
	powerBoxTextBox1->Text = Convert::ToString((double)powerBoxTrackBar1->Value / 100.0);
}

Void MainForm::powerBoxTrackBar2ValueChanged(Object^ sender, EventArgs^ e) {
	powerBoxTextBox2->Text = Convert::ToString((double)powerBoxTrackBar2->Value / 100.0);
}

//threading
Bitmap^ MainForm::getCurrentImage() {
	return images[current];
}

Void MainForm::pictureBoxChangeImage(Bitmap^ image) {
	pictureBox->Image = image;
	backUpFromPictureBox();
	progressBar->Visible = false;
	buttonsEnable(true);
}

Void MainForm::progressBarChangeValue(int value) {
	progressBar->Value = value;
}

//fromDialog
Void MainForm::dialogBinar(int t, int b0, int b1) {
	if (images == nullptr) return;
	Array::Resize(log, logsize + 1);
	log[logsize] = gcnew Entry(3, t, b0, b1);
	logBox->Items->Add(log[logsize]->data);
	if (logsize > 1) {
		if (log[logsize - 1]->type != 3) backUpFromPictureBox();
	}
	logsize++;
	this->t = t;
	this->b0 = b0;
	this->b1 = b1;
}

Void MainForm::dialogPower(double c, double g) {
	if (images == nullptr) return;
	Array::Resize(log, logsize + 1);
	log[logsize] = gcnew Entry(4, c, g);
	logBox->Items->Add(log[logsize]->data);
	if (logsize > 1) {
		if (log[logsize - 1]->type != 3) backUpFromPictureBox();
	}
	logsize++;
	this->c = c;
	this->g = g;
}

Void MainForm::backUpFromPictureBox() {
	if (images == nullptr) return;
	Array::Resize(images, size + 1);
	images[size] = gcnew Bitmap(pictureBox->Image);
	size++;
	current++;
}