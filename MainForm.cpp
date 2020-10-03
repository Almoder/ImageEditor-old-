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
	InitializeBackgoundWorker();
	size = logsize = 0;
	current = sFDindex = 0;
	t = b0 = b1 = 0;
	c = g = 1.0;
	images = nullptr;
	log = nullptr;
	fileName = nullptr;
	toolPanel->Visible = false;
}

MainForm::~MainForm() {
	if (components)	{
		delete components;
	}
	if (images != nullptr) delete[] images;
	if (log != nullptr) delete[] log;
	if (fileName != nullptr) delete fileName;
}

void MainForm::InitializeBackgoundWorker() {
	backgroundWorker->DoWork += gcnew DoWorkEventHandler(this, &MainForm::backgroundWorkerDoWork);
	backgroundWorker->RunWorkerCompleted += gcnew RunWorkerCompletedEventHandler(this, &MainForm::backgroundWorkerRunWorkerCompleted);
}

//File items
Void MainForm::openMIClick(Object^  sender, EventArgs^  e) {
	System::IO::Stream^ temp;
	OpenFileDialog^ openFileDialog = gcnew OpenFileDialog;
	openFileDialog->Filter = "BMP (*.bmp)|*.bmp|JPEG (*.jpeg)|*.jpeg|PNG (*.png)|*.png|All files (*.*)|*.*";
	openFileDialog->FilterIndex = 4;
	openFileDialog->RestoreDirectory = true;
	if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		if ((temp = openFileDialog->OpenFile()) != nullptr)
		{
			if (images != nullptr) delete[] images;
			size = 1;
			current = 0;
			images = gcnew array<Bitmap^>(size);
			images[0] = gcnew Bitmap(temp);
			pictureBox->Image = dynamic_cast<Image^>(images[0]);
			editorPanel->Size = Drawing::Size(editorPanel->Size.Width + toolPanel->Size.Width + 4, this->Size.Height - 100);
		}
	}
	temp->Close();
	delete openFileDialog;
	toolPanelShowHide(sender, e);
	toolPanelShowHide(sender, e);
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
	backUpFromPictureBox();
	SaveFileDialog^ saveFileDialog = gcnew SaveFileDialog;
	saveFileDialog->Filter = "BMP (*.bmp)|*.bmp|JPEG (*.jpeg)|*.jpeg|PNG (*.png)|*.png";
	saveFileDialog->FilterIndex = 2;
	saveFileDialog->RestoreDirectory = true;
	if (saveFileDialog->ShowDialog() == Windows::Forms::DialogResult::Cancel) return;
	if (saveFileDialog->FileName != "") {
		if (saveFileDialog->FileName->Contains(L".bmp")) saveFileDialog->FileName->Concat(saveFileDialog->FileName, ".bmp");
		if (saveFileDialog->FileName->Contains(L".jpeg")) saveFileDialog->FileName->Concat(saveFileDialog->FileName, ".jpeg");
		if (saveFileDialog->FileName->Contains(L".png")) saveFileDialog->FileName->Concat(saveFileDialog->FileName, ".png");
		System::IO::FileStream^ fs = safe_cast<System::IO::FileStream^>(saveFileDialog->OpenFile());
		switch (saveFileDialog->FilterIndex) {
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
		fileName = saveFileDialog->FileName;
		sFDindex = saveFileDialog->FilterIndex;
		fs->Close();
		delete saveFileDialog;
	}
}

Void MainForm::exitMIClick(Object^  sender, EventArgs^  e) {
	Application::Exit();
}

//lab functions
Void MainForm::negativeClick(Object^  sender, EventArgs^  e) {
	if (images == nullptr) return;
	buttonsEnable(false);
	backgroundWorker->RunWorkerAsync(1);
	Array::Resize(log, logsize + 1);
	log[logsize] = gcnew Entry(1);
	logBox->Items->Add(log[logsize]->data);
	logsize++;
}

Void MainForm::halftoneClick(Object^  sender, EventArgs^  e) {
	if (images == nullptr) return;
	buttonsEnable(false);
	backgroundWorker->RunWorkerAsync(2);
	Array::Resize(log, logsize + 1);
	log[logsize] = gcnew Entry(2);
	logBox->Items->Add(log[logsize]->data);
	logsize++;
}

Void MainForm::binarClick(Object^  sender, EventArgs^  e) {
	for (int i = 0; i < Application::OpenForms->Count; i++) {
		if (Application::OpenForms[i]->Name == "Dialog") {
			Application::OpenForms[i]->Close();
		}
	}
	Dialog^ dialog = gcnew Dialog(this, 1);
	dialog->Show();
}

Void MainForm::powerClick(Object^, EventArgs^) {
	for (int i = 0; i < Application::OpenForms->Count; i++) {
		if (Application::OpenForms[i]->Name == "Dialog") {
			Application::OpenForms[i]->Close();
		}
	}
	Dialog^ dialog = gcnew Dialog(this, 2);
	dialog->Show();
}

//lab functions
Bitmap^ MainForm::negative(Bitmap^ image, BackgroundWorker^ worker) {
	Bitmap^ ret = gcnew Bitmap(image->Width, image->Height);
	int completePercentage = 0;
	for (int row = 0; row < image->Width; row++) {
		for (int col = 0; col < image->Height; col++) {
			ret->SetPixel(row, col, Color::FromArgb(
				255 - Convert::ToInt32(image->GetPixel(row, col).R),
				255 - Convert::ToInt32(image->GetPixel(row, col).G),
				255 - Convert::ToInt32(image->GetPixel(row, col).B)));
		}
	}
	return ret;
}

Bitmap^ MainForm::halftone(Bitmap^ image, BackgroundWorker^ worker) {
	Bitmap^ ret = gcnew Bitmap(image->Width, image->Height);
	for (int row = 0; row < image->Width; row++) {
		for (int col = 0; col < image->Height; col++) {
			int Y = (int)(0.3 * image->GetPixel(row, col).R)
				+ (int)(0.59 * image->GetPixel(row, col).G)
				+ (int)(0.11 * image->GetPixel(row, col).B);
			ret->SetPixel(row, col, Color::FromArgb(Y, Y, Y));
		}
	}
	return ret;
}

Bitmap^ MainForm::binar(Bitmap^ image, int t, int b0, int b1) {
	Bitmap^ ret = gcnew Bitmap(image->Width, image->Height);
	for (int row = 0; row < image->Width; row++) {
		for (int col = 0; col < image->Height; col++) {
			Color b = image->GetPixel(row, col);
			ret->SetPixel(row, col, Color::FromArgb((b.R <= t ? b0 : b1), (b.G <= t ? b0 : b1), (b.B <= t ? b0 : b1)));
		}
	}
	return ret;
}

Bitmap^ MainForm::power(Bitmap^ image, double c, double g) {
	Bitmap^ ret = gcnew Bitmap(image->Width, image->Height);
	for (int row = 0; row < image->Width; row++) {
		for (int col = 0; col < image->Height; col++) {
			Color a = image->GetPixel(row, col);
			Color b = Color::FromArgb(
				(int)pow(a.R * c, g) >= 255 ? 255 : (int)pow(a.R * c, g),
				(int)pow(a.G * c, g) >= 255 ? 255 : (int)pow(a.G * c, g),
				(int)pow(a.B * c, g) >= 255 ? 255 : (int)pow(a.B * c, g));
			ret->SetPixel(row, col, b);
		}
	}
	return ret;
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

Void MainForm::textBox_KeyPressInt(Object^  sender, KeyPressEventArgs^  e) {
	if (!Char::IsControl(e->KeyChar) && !Char::IsDigit(e->KeyChar)) {
		e->Handled = true;
	}
}

Void MainForm::textBox_KeyPressDouble(Object^  sender, KeyPressEventArgs^  e) {
	if (!Char::IsControl(e->KeyChar) && !Char::IsDigit(e->KeyChar) && (e->KeyChar != '.')) {
		e->Handled = true;
	}
}

Void MainForm::progressBar_SizeChanged(Object^ sender, EventArgs^ e) {
	this->progressBar->Size.Height = 10;
}

Void MainForm::buttonsEnable(bool state) {
	negativeButton->Enabled = state;
	halftoneButton->Enabled = state;
}

//toolpanel textBoxes
Void MainForm::binaryBoxTextBox1KeyDown(Object^  sender, KeyEventArgs^  e) {
	if (binaryBoxTextBox1->Text != String::Empty && Convert::ToInt32(binaryBoxTextBox1->Text) <= 255) {
		binaryBoxTrackBar1->Value = Convert::ToInt32(binaryBoxTextBox1->Text);
		t = Convert::ToInt32(binaryBoxTextBox1->Text);
	}
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

Void MainForm::binaryBoxTextBox2KeyDown(Object^  sender, KeyEventArgs^  e) {
	if (binaryBoxTextBox2->Text != String::Empty && Convert::ToInt32(binaryBoxTextBox1->Text) <= 255) {
		binaryBoxTrackBar2->Value = Convert::ToInt32(binaryBoxTextBox2->Text);
		b0 = Convert::ToInt32(binaryBoxTextBox2->Text);
	}
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

Void MainForm::binaryBoxTextBox3KeyDown(Object^  sender, KeyEventArgs^  e) {
	if (binaryBoxTextBox3->Text != String::Empty && Convert::ToInt32(binaryBoxTextBox1->Text) <= 255) {
		binaryBoxTrackBar3->Value = Convert::ToInt32(binaryBoxTextBox3->Text);
		b1 = Convert::ToInt32(binaryBoxTextBox1->Text);
	}
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

Void MainForm::powerBoxTextBox1KeyDown(Object^  sender, KeyEventArgs^  e) {
	if (powerBoxTextBox1->Text != String::Empty) {
		if (Convert::ToDouble(powerBoxTextBox1->Text) * 25.0 >= 100.0) powerBoxTrackBar1->Value = 50;
		else powerBoxTrackBar1->Value = (int)(Convert::ToDouble(powerBoxTextBox1->Text) * 25);
		c = (double)powerBoxTrackBar1->Value / 25.0;
	}
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
}

Void MainForm::powerBoxTextBox2KeyDown(Object^  sender, KeyEventArgs^  e) {
	if (powerBoxTextBox2->Text != String::Empty) {
		if (Convert::ToDouble(powerBoxTextBox2->Text) * 25.0 >= 100.0) powerBoxTrackBar2->Value = 50;
		else powerBoxTrackBar2->Value = (int)(Convert::ToDouble(powerBoxTextBox2->Text) * 25);
		g = (double)powerBoxTrackBar2->Value / 25.0;
	}
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
}

//toolpanel trackbars
Void MainForm::binaryBoxTrackBar1ValueChanged(Object^  sender, EventArgs^  e) {
	binaryBoxTextBox1->Text = binaryBoxTrackBar1->Value.ToString();
	t = binaryBoxTrackBar1->Value;
}

Void MainForm::binaryBoxTrackBar2ValueChanged(Object^  sender, EventArgs^  e) {
	binaryBoxTextBox2->Text = binaryBoxTrackBar2->Value.ToString();
	b0 = binaryBoxTrackBar2->Value;
}

Void MainForm::binaryBoxTrackBar3ValueChanged(Object^  sender, EventArgs^  e) {
	binaryBoxTextBox3->Text = binaryBoxTrackBar3->Value.ToString();
	b1 = binaryBoxTrackBar3->Value;
}

Void MainForm::powerBoxTrackBar1ValueChanged(Object^  sender, EventArgs^  e) {
	powerBoxTextBox1->Text = Convert::ToString((double)powerBoxTrackBar1->Value / 25.0);
	c = (double)powerBoxTrackBar1->Value / 25.0;
}

Void MainForm::powerBoxTrackBar2ValueChanged(Object^  sender, EventArgs^  e) {
	powerBoxTextBox2->Text = Convert::ToString((double)powerBoxTrackBar2->Value / 25.0);
	g = (double)powerBoxTrackBar2->Value / 25.0;
}

//backgroundWorker
Void MainForm::backgroundWorkerDoWork(Object^ sender, DoWorkEventArgs^ e) {
	BackgroundWorker^ worker = dynamic_cast<BackgroundWorker^>(sender);
	switch (Convert::ToInt32(e->Argument)) {
	case 1:
		e->Result = negative(images[current], worker);
		break;
	case 2:
		e->Result = halftone(images[current], worker);
		break;
	case 3:
		e->Result = binar(images[current], t, b0, b1);
		break;
	case 4:
		e->Result = power(images[current], c, g);
		break;
	default:
		e->Result = nullptr;
		break;
	}
}

Void MainForm::backgroundWorkerRunWorkerCompleted(Object^ sender, RunWorkerCompletedEventArgs^ e) {
	if (e->Error != nullptr) {
		MessageBox::Show(e->Error->Message, L"Error!");
	}
	else
	if (e->Cancelled) {
		MessageBox::Show(L"Thread is canceled!", L"Attention!", MessageBoxButtons::OK, MessageBoxIcon::Asterisk);
	}
	else {
	pictureBox->Image = dynamic_cast<Bitmap^>(e->Result);
	backUpFromPictureBox();
	}
	buttonsEnable(true);
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
	backgroundWorker->RunWorkerAsync(3);
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
	backgroundWorker->RunWorkerAsync(4);
}

Void MainForm::backUpFromPictureBox() {
	if (images == nullptr) return;
	Array::Resize(images, size + 1);
	images[size] = gcnew Bitmap(pictureBox->Image);
	size++;
	current++;
}