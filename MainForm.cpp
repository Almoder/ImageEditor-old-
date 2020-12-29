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
	engine = gcnew Engine(
		gcnew Action(this, &MainForm::progressBarIncValue),
		gcnew Action(this, &MainForm::updatePictures));
	engine->progressPtr = progressBar;
	engine->picturePtr = pictureBox1;
	tableLayout->AutoScroll = false;
	tableLayout->HorizontalScroll->Maximum = 0;
	tableLayout->VerticalScroll->Maximum = 0;
	tableLayout->VerticalScroll->Enabled = true;
	tableLayout->AutoScroll = true;
	splitContainer->Panel2Collapsed = true;
	curPictureBox = pictureBox1;
	progressBar->Visible = false;
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
	System::Windows::Forms::DialogResult result;
	try {
		result = openFileDialog->ShowDialog();
	}
	catch (System::Exception^ exc) {
		MessageBox::Show(exc->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		delete exc;
	}
	if (result == System::Windows::Forms::DialogResult::OK) {
		try {
			temp = openFileDialog->OpenFile();
		}
		catch (System::Exception^ exc) {
			MessageBox::Show(exc->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			delete exc;
		}
		if (temp != nullptr) {
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
	if (curLabel == 1) cur1Label->Text = gcnew String("Cur1: " + engine->current);
	else cur2Label->Text = gcnew String("Cur2: " + engine->current);
}

Void MainForm::redoItemClick(Object^ sender, EventArgs^ e) {
	curPictureBox->Image = engine->redo();
	if (curLabel == 1) cur1Label->Text = gcnew String("Cur1: " + engine->current);
	else cur2Label->Text = gcnew String("Cur2: " + engine->current);
}

Void MainForm::doubleItemClick(Object^ sender, EventArgs^ e) {
	splitContainer->Panel2Collapsed = !splitContainer->Panel2Collapsed;
	cur2Label->Visible = !cur2Label->Visible;
}

Void MainForm::pictureBoxClick(Object^ sender, EventArgs^ e) {
	curPictureBox = safe_cast<PictureBox^>(sender);
	curLabel = curPictureBox->Name->Contains("1") ? 1 : 2;
}

Void MainForm::MainFormSizeChanged(Object^ sender, EventArgs^ e) {
	splitContainer->Size = Drawing::Size(tableLayout->Location.X - 3, splitContainer->Size.Height);
}

Void MainForm::setColors() {
	Color back = Color::FromArgb(40, 40, 40);
	Color fore = Color::White;
	Color over = Color::FromArgb(64, 64, 64);
	Color down = Color::Aqua;
	this->BackColor = back;
	this->ForeColor = fore;
	for each (Control^ var in Controls) {
		var->BackColor = back;
		var->ForeColor = fore;
	}
	for each (ToolStripMenuItem^ var in menuStrip->Items) {
		var->BackColor = back;
		var->ForeColor = fore;
	}
	for each (ToolStripMenuItem ^ var in fileItem->DropDownItems) {
		var->BackColor = back;
		var->ForeColor = fore;
	}
	for each (ToolStripMenuItem ^ var in viewItem->DropDownItems) {
		var->BackColor = back;
		var->ForeColor = fore;
	}
	for each (Control ^ var in tableLayout->Controls) {
		if (var->Name->Contains("button")) {
			safe_cast<Button^>(var)->FlatAppearance->BorderSize = 0;
			safe_cast<Button^>(var)->FlatAppearance->MouseDownBackColor = down;
			safe_cast<Button^>(var)->FlatAppearance->MouseOverBackColor = over;
		}
		if (var->Name->Contains("textBox")) var->BackColor = over;
		else var->BackColor = back;
		var->ForeColor = fore;
	}
	tabPage1->BackColor = SystemColors::Control;
	tabPage2->BackColor = back;
	splitContainer->BackColor = SystemColors::Control;
	splitContainer->Panel1->BackColor = back;
	splitContainer->Panel2->BackColor = back;
}

#pragma endregion
#pragma region Threading

Void MainForm::progressBarIncValue() {
	progressBar->Value++;
}

Void MainForm::updatePictures() {
	engine->current = engine->count() - 1;
	progressBar->Visible = false;
	pictureBox1->Image = engine->getCurrent();
	countLabel->Text = gcnew String("Count: " + engine->count());
	cur1Label->Text = gcnew String("Cur1: " + engine->current);
	disableControls();
}

Void MainForm::disableControls() {
	for each (Control^ var in tableLayout->Controls) {
		if (var->Name->Contains("button"))
			safe_cast<Button^>(var)->Enabled = !safe_cast<Button^>(var)->Enabled;
	}
	for each (ToolStripMenuItem ^ var in fileItem->DropDownItems) {
		var->Enabled = !var->Enabled;
	}
}

#pragma endregion
#pragma region TableLayout
#pragma region Buttons

Void MainForm::button1Click(Object^, EventArgs^) {
	if (engine->dataEmpty()) return;
	progressBar->Value = 0;
	progressBar->Maximum = engine->getCurrent()->Width;
	progressBar->Visible = true;
	engine->doNegative();
	disableControls();
}

Void MainForm::button2Click(Object^, EventArgs^) {
	if (engine->dataEmpty()) return;
	progressBar->Value = 0;
	progressBar->Maximum = engine->getCurrent()->Width;
	progressBar->Visible = true;
	engine->doHalftone();
	disableControls();
}

Void MainForm::button3Click(Object^, EventArgs^) {
	if (engine->dataEmpty()) return;
	if (textBox1->Text == String::Empty || 
		textBox2->Text == String::Empty || 
		textBox3->Text == String::Empty) return;
	progressBar->Value = 0;
	progressBar->Maximum = engine->getCurrent()->Width;
	progressBar->Visible = true;
	engine->doBinar(
		Convert::ToInt32(textBox1->Text),
		Convert::ToInt32(textBox2->Text),
		Convert::ToInt32(textBox3->Text));
	disableControls();
}

Void MainForm::button4Click(Object^, EventArgs^) {
	if (engine->dataEmpty()) return;
	progressBar->Value = 0;
	progressBar->Maximum = engine->getCurrent()->Width * 4;
	progressBar->Visible = true;
	engine->doBinarAdaptive();
	disableControls();
}

Void MainForm::button5Click(Object^, EventArgs^) {
	if (engine->dataEmpty()) return;
	if (textBox4->Text == String::Empty ||
		textBox5->Text == String::Empty) return;
	double c, g;
	try {
		c = Convert::ToDouble(textBox4->Text);
		g = Convert::ToDouble(textBox5->Text);
	}
	catch (System::FormatException^ exc) {
		delete exc;
		return;
	}
	progressBar->Value = 0;
	progressBar->Maximum = engine->getCurrent()->Width;
	progressBar->Visible = true;
	engine->doPower(c, g);
	disableControls();
}

Void MainForm::button6Click(Object^, EventArgs^) {
	if (engine->dataEmpty() || textBox6->Text == String::Empty) return;
	progressBar->Value = 0;
	progressBar->Maximum = engine->getCurrent()->Width;
	progressBar->Visible = true;
	engine->doLBrightness(Convert::ToInt32(textBox6->Text));
	disableControls();
}

Void MainForm::button7Click(Object^, EventArgs^) {
	if (engine->dataEmpty() || textBox7->Text == String::Empty) return;
	progressBar->Value = 0;
	progressBar->Maximum = engine->getCurrent()->Width * 2;
	progressBar->Visible = true;
	engine->doLContrast(Convert::ToInt32(textBox7->Text));
	disableControls();
}

Void MainForm::button8Click(Object^, EventArgs^) {
	if (engine->dataEmpty() || textBox8->Text == String::Empty) return;
	progressBar->Value = 0;
	progressBar->Maximum = engine->getCurrent()->Width;
	progressBar->Visible = true;
	engine->doNBrightness(Convert::ToInt32(textBox8->Text));
	disableControls();
}

Void MainForm::button9Click(Object^, EventArgs^) {
	if (engine->dataEmpty() || textBox9->Text == String::Empty) return;
	progressBar->Value = 0;
	progressBar->Maximum = engine->getCurrent()->Width;
	progressBar->Visible = true;
	engine->doNContrast(Convert::ToInt32(textBox9->Text));
	disableControls();
}

Void MainForm::button10Click(Object^, EventArgs^) {
	if (engine->dataEmpty()) return;
	progressBar->Value = 0;
	progressBar->Maximum = engine->getCurrent()->Width * 2;
	progressBar->Visible = true;
	engine->doAutolevels();
	disableControls();
}

Void ImageEditor::MainForm::button11Click(Object^, EventArgs^) {
	if (engine->dataEmpty()) return;
	progressBar->Value = 0;
	progressBar->Maximum = engine->getCurrent()->Width * 2;
	progressBar->Visible = true;
	engine->doPerfectReflect();
	disableControls();
}

Void ImageEditor::MainForm::button12Click(Object^, EventArgs^) {
	if (engine->dataEmpty() || comboBox1->Text == "Type" || comboBox2->Text == "Size") return;
	progressBar->Value = 0;
	progressBar->Maximum = engine->getCurrent()->Width * 2;
	progressBar->Visible = true;
	engine->doFiltration(
		comboBox1->SelectedIndex, comboBox2->SelectedIndex);
	disableControls();
}

#pragma endregion
#pragma region Events

Void MainForm::textBoxKeyDown(Object^ sender, KeyEventArgs^ e) {
	switch (safe_cast<TextBox^>(sender)->TabIndex) {
	case 7: switch (e->KeyCode) {
		case Keys::Up:	textBox3->Focus(); break;
		case Keys::Down:textBox2->Focus(); break;
		}
		break;
	case 8: switch (e->KeyCode) {
		case Keys::Up:	textBox1->Focus(); break;
		case Keys::Down:textBox3->Focus(); break;
		}
		break;
	case 9: switch (e->KeyCode) {
		case Keys::Up:	textBox2->Focus(); break;
		case Keys::Down:textBox1->Focus(); break;
		}
		break;
	}
	if (e->KeyCode == Keys::Enter) 
		e->SuppressKeyPress = true;
}

Void MainForm::textBoxKeyPress(Object^ sender, KeyPressEventArgs^ e) {
	TextBox^ temp = safe_cast<TextBox^>(sender);
	switch (temp->TabIndex) {
	case 7:	case 8:	case 9: case 29:
		if (!Char::IsControl(e->KeyChar) && 
			!Char::IsDigit(e->KeyChar)) 
			e->Handled = true;
			break;
	case 15: case 16:
		if (!Char::IsControl(e->KeyChar) && 
			!Char::IsDigit(e->KeyChar) && 
			(e->KeyChar != ',')) 
			e->Handled = true;
		if (temp->Text == String::Empty && e->KeyChar == ',')
			e->Handled = true;
		break;
	case 21: case 22: case 28: 
		if (!Char::IsControl(e->KeyChar) &&
			!Char::IsDigit(e->KeyChar) &&
			(e->KeyChar != '-'))
			e->Handled = true;
		if (temp->Text != String::Empty && e->KeyChar == '-')
			e->Handled = true;
		break;
	default:
		break;
	}
	if (!Char::IsControl(e->KeyChar) &&
		safe_cast<TextBox^>(sender)->Text->Length == safe_cast<TextBox^>(sender)->MaxLength)
		e->Handled = true;
}

Void MainForm::textBoxTextChanged(Object^ sender, EventArgs^ e) {
	TextBox^ temp = safe_cast<TextBox^>(sender);
	switch (temp->TabIndex) {
	case 21: case 22: case 28:
		if (temp->Text != String::Empty && temp->Text != "-" &&
			Convert::ToDouble(temp->Text) < -255) temp->Text = "-255";
		else if (temp->Text != String::Empty && temp->Text != "-" &&
			Convert::ToDouble(temp->Text) > 255) temp->Text = "255";
		break;
	case 7: case 8: case 9:
		if (temp->Text != String::Empty &&
			Convert::ToInt32(temp->Text) > 255) temp->Text = "255";
		break;
	case 29:
		if (temp->Text != String::Empty &&
			Convert::ToInt32(temp->Text) > 300) temp->Text = "300";
		break;
	}
}

Void MainForm::comboBox1SelectedValueChanged(Object^sender , EventArgs^ e) {
	if (comboBox1->SelectedIndex == 3) {
		comboBox2->Items[0] = "5x5";
		comboBox2->Items[1] = "7x7";
		comboBox2->Text = "Size";
	}
	else if (comboBox2->Items[0] == "5x5") {
		comboBox2->Items[0] = "3x3";
		comboBox2->Items[1] = "5x5";
		comboBox2->Text = "Size";
	}
}

#pragma endregion
#pragma endregion
