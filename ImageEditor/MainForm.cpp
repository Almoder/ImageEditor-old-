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
		this->data = L"Отмена предыдущего действия ";
		break;
	case 1:
		this->data = L"Преобразование изображения в негатив ";
		break;
	case 2:
		this->data = L"Преобразование изображения в полутоновое ";
		break;
	case 3:
		this->data = L"Бинарное преобразование изображения ";
		break;
	case 4:
		this->data = L"Степенное преобразование изображения ";
		break;
	default:
		this->data = L"Unregistred type!";
		break;
	}
}

Entry::Entry(void) {
	Entry(0);
}

Entry::Entry(int type) {
	this->type = type;
	this->initData(type);
}

Entry::Entry(int type, int t, int b0, int b1) {
	if (type == 3) {
		this->initData(type);
		this->data = String::Concat(this->data, L"[T = " + t + "| b0 = " + b0 + "| b1 = " + b1 + "]");
	}
}

Entry::Entry(int type, double c, double g) {
	if (type == 4) {
		this->initData(type);
		this->data = String::Concat(this->data, L"[C = " + c + "| G = " + g + "]");
	}
}


//File items
Void MainForm::openClick(Object^  sender, EventArgs^  e) {
	System::IO::Stream^ temp;
	OpenFileDialog^ openFileDialog = gcnew OpenFileDialog;
	openFileDialog->Filter = "BMP (*.bmp)|*.bmp|JPEG (*.jpeg)|*.jpeg|PNG (*.png)|*.png|All files (*.*)|*.*";
	openFileDialog->FilterIndex = 4;
	openFileDialog->RestoreDirectory = true;
	if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		if ((temp = openFileDialog->OpenFile()) != nullptr)
		{
			if (images != nullptr) delete[] images;
			size = 1;
			current = 0;
			images = gcnew array<Bitmap^>(size);
			images[0] = gcnew Bitmap(temp);
			temp->Close();
			this->pictureBox->Image = dynamic_cast<Image^>(images[0]);
		}
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

Void MainForm::chngBrightClick(Object^  sender, EventArgs^  e) {

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

Void MainForm::bkpPictureBox() {
	if (images == nullptr) return;
	Array::Resize(images, size + 1);
	images[size] = gcnew Bitmap(pictureBox->Image);
	size++;
	current++;
}

Void MainForm::toolPanelShowHide(Object^ sender, EventArgs^ e) {
	if (toolPanel->Visible == true) {
		toolPanel->Visible = false;
		editorPanel->Dock = DockStyle::Fill;
	}
	else {
		toolPanel->Visible = true;
		editorPanel->Dock = DockStyle::None;

	}
}

Void MainForm::textBox_KeyPress(Object^  sender, KeyPressEventArgs^  e) {
	if (!Char::IsControl(e->KeyChar) && !Char::IsDigit(e->KeyChar) && (e->KeyChar != '.')) {
		e->Handled = true;
	}
}

Void MainForm::MainForm_SizeChanged(Object^ sender, EventArgs^ e) {

}