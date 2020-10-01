#include "Dialog.h"
#include <math.h>

using namespace Lab1;

[STAThreadAttribute]
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
	size = 0; logsize = 0;
	current = 0; sFDindex = 0;
	t = 0; b0 = 0; b1 = 0;
	c = 1.0; g = 1.0;
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

//File items
Void MainForm::openClick(Object^  sender, EventArgs^  e) {
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
}

Void MainForm::saveMI_Click(Object^ sender, EventArgs^ e) {
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
	else saveAsMI_Click(sender, e);
}

Void MainForm::saveAsMI_Click(Object^ sender, EventArgs^ e) {
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
	Array::Resize(images, size + 1);
	Array::Resize(log, logsize + 1);
	images[size] = negative(images[current]);
	log[logsize] = gcnew Entry(1);
	logBox->Items->Add(log[logsize]->data);
	size++; logsize++;
	current++;
	pictureBox->Image = images[current];
}

Void MainForm::halftoneClick(Object^  sender, EventArgs^  e) {
	if (images == nullptr) return;
	Array::Resize(images, size + 1);
	Array::Resize(log, logsize + 1);
	images[size] = halftone(images[current]);
	log[logsize] = gcnew Entry(2);
	logBox->Items->Add(log[logsize]->data);
	size++; logsize++;
	current++;
	pictureBox->Image = images[current];
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

Bitmap^ MainForm::negative(Bitmap^ image) {
	Bitmap^ ret = gcnew Bitmap(image->Width, image->Height);
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

Bitmap^ MainForm::halftone(Bitmap^ image) {
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

Void MainForm::textBox_KeyPress(Object^  sender, KeyPressEventArgs^  e) {
	if (!Char::IsControl(e->KeyChar) && !Char::IsDigit(e->KeyChar) && (e->KeyChar != '.')) {
		e->Handled = true;
	}
}

//toolpanel textBoxes
Void MainForm::binaryBoxTextBox1KeyDown(Object^  sender, KeyEventArgs^  e) {
	t = Convert::ToInt32(binaryBoxTextBox1->Text);
	switch (e->KeyCode) {
	case Keys::Up:
		binaryBoxTextBox3->Focus();
		break;
	case Keys::Down:
		binaryBoxTextBox2->Focus();
		break;
	case Keys::Enter:
		dialogBinar(t, b0, b1);
		e->SuppressKeyPress = true;
		break;
	}
}

Void MainForm::binaryBoxTextBox2KeyDown(Object^  sender, KeyEventArgs^  e) {
	b0 = Convert::ToInt32(binaryBoxTextBox2->Text);
	switch (e->KeyCode) {
	case Keys::Up:
		binaryBoxTextBox1->Focus();
		break;
	case Keys::Down:
		binaryBoxTextBox3->Focus();
		break;
	case Keys::Enter:
		dialogBinar(t, b0, b1);
		e->SuppressKeyPress = true;
		break;
	}
}

Void MainForm::binaryBoxTextBox3KeyDown(Object^  sender, KeyEventArgs^  e) {
	b1 = Convert::ToInt32(binaryBoxTextBox1->Text);
	switch (e->KeyCode) {
	case Keys::Up:
		binaryBoxTextBox2->Focus();
		break;
	case Keys::Down:
		binaryBoxTextBox1->Focus();
		break;
	case Keys::Enter:
		dialogBinar(t, b0, b1);
		e->SuppressKeyPress = true;
		break;
	}
}

Void MainForm::powerBoxTextBox1KeyDown(Object^  sender, KeyEventArgs^  e) {
	c = Convert::ToInt32(powerBoxTextBox1->Text);
	switch (e->KeyCode) {
	case Keys::Up:
		powerBoxTextBox2->Focus();
		break;
		powerBoxTextBox2->Focus();
		break;
	case Keys::Enter:
		if (Convert::ToDouble(powerBoxTextBox1->Text) * 25.0 >= 100.0) powerBoxTrackBar1->Value = 50;
		else powerBoxTrackBar1->Value = (int)(Convert::ToDouble(powerBoxTextBox1->Text) * 25);
		dialogPower(c, g);
		e->SuppressKeyPress = true;
		break;
	}
}

Void MainForm::powerBoxTextBox2KeyDown(Object^  sender, KeyEventArgs^  e) {
	g = Convert::ToInt32(powerBoxTextBox2->Text);
	switch (e->KeyCode) {
	case Keys::Up:
		powerBoxTextBox1->Focus();
		break;
	case Keys::Down:
		powerBoxTextBox1->Focus();
		break;
	case Keys::Enter:
		if (Convert::ToDouble(powerBoxTextBox2->Text) * 25.0 >= 100.0) powerBoxTrackBar2->Value = 50;
		else powerBoxTrackBar2->Value = (int)(Convert::ToDouble(powerBoxTextBox2->Text) * 25);
		dialogPower(c, g);
		e->SuppressKeyPress = true;
		break;
	}
}

//toolpanel trackbars
Void MainForm::binaryBoxTrackBar1ValueChanged(Object^  sender, EventArgs^  e) {
	binaryBoxTextBox1->Text = binaryBoxTrackBar1->Value.ToString();
	t = binaryBoxTrackBar1->Value;
	dialogBinar(t, b0, b1);
}

Void MainForm::binaryBoxTrackBar2ValueChanged(Object^  sender, EventArgs^  e) {
	binaryBoxTextBox2->Text = binaryBoxTrackBar2->Value.ToString();
	b0 = binaryBoxTrackBar2->Value;
	dialogBinar(t, b0, b1);
}

Void MainForm::binaryBoxTrackBar3ValueChanged(Object^  sender, EventArgs^  e) {
	binaryBoxTextBox3->Text = binaryBoxTrackBar3->Value.ToString();
	b1 = binaryBoxTrackBar3->Value;
	dialogBinar(t, b0, b1);
}

Void MainForm::powerBoxTrackBar1ValueChanged(Object^  sender, EventArgs^  e) {
	powerBoxTextBox1->Text = Convert::ToString((double)powerBoxTrackBar1->Value / 25.0);
	c = (double)powerBoxTrackBar1->Value / 25.0;
	dialogPower(c, g);
}

Void MainForm::powerBoxTrackBar2ValueChanged(Object^  sender, EventArgs^  e) {
	powerBoxTextBox2->Text = Convert::ToString((double)powerBoxTrackBar2->Value / 25.0);
	g = (double)powerBoxTrackBar2->Value / 25.0;
	dialogPower(c, g);
}

Void MainForm::dialogBinar(int t, int b0, int b1) {
	if (images == nullptr) return;
	pictureBox->Image = binar(images[current], t, b0, b1);
	Array::Resize(log, logsize + 1);
	log[logsize] = gcnew Entry(3, t, b0, b1);
	logBox->Items->Add(log[logsize]->data);
	logsize++;
}

Void MainForm::dialogPower(double c, double g) {
	if (images == nullptr) return;
	pictureBox->Image = power(images[current], c, g);
	Array::Resize(log, logsize + 1);
	log[logsize] = gcnew Entry(4, c, g);
	logBox->Items->Add(log[logsize]->data);
	logsize++;
}

Void MainForm::backUpFromPictureBox() {
	if (images == nullptr) return;
	Array::Resize(images, size + 1);
	images[size] = gcnew Bitmap(pictureBox->Image);
	size++;
	current++;
}