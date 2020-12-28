#include "MainForm.h"

using namespace ImageEditor;

[STAThread]
void main() {
	Application::EnableVisualStyles();
	MainForm^ form = gcnew MainForm();
	Application::Run(form);
	return;
}

MainForm::MainForm() {
	InitializeComponent();
	splitContainer->Panel2Collapsed = true;
	engine = gcnew Engine();
	curPictureBox = pictureBox1;
	setColors();
}

MainForm::~MainForm()
{
	if (components)
	{
		delete components;
	}
}

#pragma region UI
Void MainForm::openItemClick(Object^ sender, EventArgs^ e) {
	if (engine->fileName != nullptr) {
		String^ text = L"Последние изменения не сохранены!\nПродолжить?", ^ caption = L"Внимание!";
		MessageBoxButtons mbb = MessageBoxButtons::YesNo;
		MessageBoxIcon mbi = MessageBoxIcon::Warning;
		if (MessageBox::Show(text, caption, mbb, mbi) == Windows::Forms::DialogResult::No) return;
	}
	System::IO::Stream^ temp;
	OpenFileDialog^ openFileDialog = gcnew OpenFileDialog;
	openFileDialog->Filter = engine->filter;
	openFileDialog->FilterIndex = engine->sFDindex;
	openFileDialog->RestoreDirectory = true;
	if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		if ((temp = openFileDialog->OpenFile()) != nullptr) {
			if (!engine->dataEmpty()) engine->clearData();
			engine->fileName = nullptr;
			engine->current = 0;
			try {
				engine->addNode(gcnew Bitmap(temp));
			}
			catch (System::ArgumentException^ exc) {
				engine->clearData();
				MessageBox::Show(exc->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				delete exc;
				return;
			}
			this->Text = openFileDialog->FileName;
			engine->sFDindex = openFileDialog->FilterIndex;
			pictureBox1->Image = engine->getCurrent();
			pictureBox2->Image = engine->getCurrent();
			countLabel->Text = gcnew String("Count: " + engine->count());
			cur1Label->Text = gcnew String("Cur1: " + engine->current);
			temp->Close();
		}
	}
	delete openFileDialog;
}

Void MainForm::saveItemClick(Object^ sender, EventArgs^ e) {
	if (engine->fileName != nullptr) {
		engine->getCurrent()->Save(engine->fileName);
	}
	else saveAsItemClick(sender, e);
}

Void MainForm::saveAsItemClick(Object^ sender, EventArgs^ e) {
	if (engine->dataEmpty()) return;
	SaveFileDialog^ saveFileDialog = gcnew SaveFileDialog;
	saveFileDialog->Filter = engine->filter;
	saveFileDialog->FilterIndex = engine->sFDindex;
	saveFileDialog->RestoreDirectory = true;
	if (saveFileDialog->ShowDialog() == Windows::Forms::DialogResult::Cancel) return;
	if (saveFileDialog->FileName != "") {
		Imaging::ImageFormat^ format;
		String^ formatString;
		switch (saveFileDialog->FilterIndex) {
		case 1:
			format = Imaging::ImageFormat::Bmp;
			formatString = ".bmp";
			break;
		case 2:
			format = Imaging::ImageFormat::Jpeg;
			formatString = ".jpeg";
			break;
		case 3:
			format = Imaging::ImageFormat::Png;
			formatString = ".png";
			break;
		}
		saveFileDialog->FileName->Concat(saveFileDialog->FileName, formatString);
		engine->getCurrent()->Save(saveFileDialog->OpenFile(), format);
		engine->fileName = saveFileDialog->FileName;
		engine->sFDindex = saveFileDialog->FilterIndex;
		delete saveFileDialog;
	}
}

Void MainForm::undoItemClick(Object^ sender, EventArgs^ e) {
	curPictureBox->Image = engine->undo();
}

Void MainForm::redoItemClick(Object^ sender, EventArgs^ e) {
	curPictureBox->Image = engine->redo();
}

Void MainForm::doubleItemClick(Object^ sender, EventArgs^ e) {
	splitContainer->Panel2Collapsed = !splitContainer->Panel2Collapsed;
}

Void MainForm::pictureBoxClick(Object^ sender, EventArgs^ e) {
	curPictureBox = safe_cast<PictureBox^>(sender);
}

Void MainForm::MainFormSizeChanged(Object^ sender, EventArgs^ e) {
	splitContainer->Size = Drawing::Size(tableLayout->Location.X - 3, splitContainer->Size.Height);
}

Void MainForm::setColors() {
	Color back = Color::FromArgb(40, 40, 40);
	Color fore = Color::White;
	this->BackColor = back;
	this->ForeColor = fore;
	for each (Control^ var in Controls)
	{
		var->BackColor = back;
		var->ForeColor = fore;
	}
	for each (ToolStripMenuItem^ var in menuStrip->Items)
	{
		var->BackColor = back;
		var->ForeColor = fore;
	}
	tabPage1->BackColor = SystemColors::Control;
	tabPage2->BackColor = back;
	splitContainer->BackColor = SystemColors::Control;
	splitContainer->Panel1->BackColor = back;
	splitContainer->Panel2->BackColor = back;

}

#pragma endregion
