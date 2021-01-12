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
		gcnew PbarInc(this, &MainForm::updatePictures));
	engine->picturePtr = pictureBox1;
	pbars = gcnew List<ProgressBar^>();
	tableLayout->AutoScroll = false;
	tableLayout->HorizontalScroll->Maximum = 0;
	tableLayout->VerticalScroll->Maximum = 0;
	tableLayout->VerticalScroll->Enabled = true;
	tableLayout->AutoScroll = true;
	splitContainer->Panel2Collapsed = true;
	curPictureBox = pictureBox1;
	domainUpDown1->SelectedIndex = 0;
	domainUpDown2->SelectedIndex = 0;
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
			addLogEntry();
			countLabel->Text = gcnew String("Count: " + engine->count());
			cur1Label->Text = gcnew String("Cur1: " + engine->current);
			textBox10->Text = String::Empty;
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
	curPictureBox = pictureBox1;
	cur2Label->Visible = !cur2Label->Visible;
	curLabel = 0;
}

Void MainForm::autoConfigItemClick(Object^ sender, EventArgs^ e) {
	domainUpDown1->Visible = !domainUpDown1->Visible;
	domainUpDown2->Visible = !domainUpDown2->Visible;
}

Void MainForm::permanentClick(Object^ sender, EventArgs^ e) {
	engine->permanent = !engine->permanent;
	disableControls(engine->permanent || !engine->works);
	if (engine->permanent) 
		engine->current2 = engine->current;
}

Void MainForm::pictureBoxClick(Object^ sender, EventArgs^ e) {
	curPictureBox = safe_cast<PictureBox^>(sender);
	if (curPictureBox->Name->Contains("1")) {
		curLabel = 1;
		cur1Label->ForeColor = Color::Aqua;
		cur2Label->ForeColor = Color::White;
	}
	else {
		curLabel = 2;
		cur1Label->ForeColor = Color::White;
		cur2Label->ForeColor = Color::Aqua;
	}
}

Void MainForm::MainFormSizeChanged(Object^ sender, EventArgs^ e) {
	splitContainer->Size = Drawing::Size(
		tableLayout->Location.X - 3, splitContainer->Size.Height);
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
	for each (Control^ var in tableLayout->Controls) {
		if (var->Name->Contains("button")) {
			safe_cast<Button^>(var)->FlatAppearance->BorderSize = 0;
			safe_cast<Button^>(var)->FlatAppearance->MouseDownBackColor = down;
			safe_cast<Button^>(var)->FlatAppearance->MouseOverBackColor = over;
		}
		if (var->Name->Contains("textBox")) {
			var->BackColor = over;
		}
		else var->BackColor = back;
		var->ForeColor = fore;
	}
	tabPage1->BackColor = SystemColors::Control;
	tabPage3->BackColor = back;
	splitContainer->BackColor = SystemColors::Control;
	splitContainer->Panel1->BackColor = back;
	splitContainer->Panel2->BackColor = back;
	cur1Label->ForeColor = Color::Aqua;
}

#pragma endregion
#pragma region Threading

Void MainForm::updatePictures(ProgressBar^ ptr) {
	psPanel->Controls->Remove(ptr);
	pbc--; int i = 0; 
	engine->works = pbc != 0;
	if (isPsPanel) psPanel->Height = 7 + (17 * pbc);
	for each (Control ^ var in psPanel->Controls) {
		newPs.Y = 7 + (17 * i);
		var->Location = newPs;
		i++;
	}
	if (engine->permanent) 
		curPictureBox->Image = engine->getLast();
	else {
		engine->current = engine->count() - 1;
		curPictureBox->Image = engine->getCurrent();
	}
	addLogEntry();
	countLabel->Text = gcnew String("Count: " + engine->count());
	if (curLabel == 1) cur1Label->Text = gcnew String("Cur1: " + (engine->count() - 1));
	else cur2Label->Text = gcnew String("Cur2: " + (engine->count() - 1));
	disableControls(engine->permanent || !engine->works);
}

Void MainForm::addLogEntry() {
	DataGridViewRowCollection^ row = dataGridView->Rows;
	row->Add(row->Count.ToString(), engine->getCurrent(), nullptr, nullptr);
	row[row->Count - 1]->Height =
		int(float(engine->getCurrent()->Height) * (
			float(dataGridView->Columns[1]->Width) /
			float(engine->getCurrent()->Width)));
}

Void MainForm::disableControls() {
	for each (Control^ var in tableLayout->Controls) {
		if (var->Name->Contains("button"))
			safe_cast<Button^>(var)->Enabled = !safe_cast<Button^>(var)->Enabled;
	}
	if (!engine->works) {
		for each (ToolStripMenuItem ^ var in fileItem->DropDownItems) {
			var->Enabled = !var->Enabled;
		}
	}
}

Void MainForm::disableControls(bool val) {
	for each (Control ^ var in tableLayout->Controls) {
		if (var->Name->Contains("button"))
			safe_cast<Button^>(var)->Enabled = val;
	}
	if (!engine->works) {
		for each (ToolStripMenuItem ^ var in fileItem->DropDownItems) {
			var->Enabled = val;
		}
	}
}

Void MainForm::progressBarInc(ProgressBar^ ptr) {
	ptr->Value++;
}

Void MainForm::addProgress(int max) {
	ProgressBar^ pb = gcnew ProgressBar();
	newPs.Y = 7 + (17 * pbc);
	pbc++;
	if (pbc == 16) disableControls();
	pb->Name = pbc.ToString();
	pb->Location = newPs;
	pb->Size = Drawing::Size(psPanel->Width - 4, 10);
	pb->Anchor = System::Windows::Forms::AnchorStyles::Top | 
		System::Windows::Forms::AnchorStyles::Left | 
		System::Windows::Forms::AnchorStyles::Right;
	pb->Maximum = max;
	pb->Value = 0;
	pb->MouseMove += gcnew MouseEventHandler(
		this, &MainForm::psPanel_MouseMove);
	pb->MouseDown += gcnew MouseEventHandler(
		this, &MainForm::psPanel_MouseDown);
	psPanel->Controls->Add(pb);
}

ProgressBar^ MainForm::getLast() {
	return safe_cast<ProgressBar^>(
		psPanel->Controls[psPanel->Controls->Count - 1]);
}

#pragma endregion
#pragma region TableLayout
#pragma region Buttons

Void MainForm::button1Click(Object^, EventArgs^) {
	if (engine->dataEmpty()) return;
	if (!engine->works || engine->permanent) {
		engine->works = true;
		addProgress(engine->getCurrent()->Width);
		engine->preset(gcnew PbarInc(
			this, &MainForm::progressBarInc), 
			getLast());
		engine->doNegative();
		disableControls(engine->permanent);
	}
}

Void MainForm::button2Click(Object^, EventArgs^) {
	if (engine->dataEmpty()) return;
	if (!engine->works || engine->permanent) {
		engine->works = true;
		addProgress(engine->getCurrent()->Width);
		engine->preset(gcnew PbarInc(
			this, &MainForm::progressBarInc),
			getLast());
		engine->doHalftone();
		disableControls(engine->permanent);
	}
}

Void MainForm::button3Click(Object^, EventArgs^) {
	if (engine->dataEmpty()) return;
	if (textBox1->Text == String::Empty || 
		textBox2->Text == String::Empty || 
		textBox3->Text == String::Empty) return;
	if (!engine->works || engine->permanent) {
		engine->works = true;
		addProgress(engine->getCurrent()->Width);
		engine->preset(gcnew PbarInc(
			this, &MainForm::progressBarInc),
			getLast());
		engine->doBinar(
			Convert::ToInt32(textBox1->Text),
			Convert::ToInt32(textBox2->Text),
			Convert::ToInt32(textBox3->Text));
		disableControls(engine->permanent);
	}
}

Void MainForm::button4Click(Object^, EventArgs^) {
	if (engine->dataEmpty()) return;
	if (!engine->works || engine->permanent) {
		engine->works = true;
		addProgress(engine->getCurrent()->Width * 3);
		engine->preset(gcnew PbarInc(
			this, &MainForm::progressBarInc),
			getLast());
		engine->doBinarAdaptive();
		disableControls(engine->permanent);
	}
}

Void MainForm::button5Click(Object^, EventArgs^) {
	if (engine->dataEmpty()) return;
	if (textBox4->Text == String::Empty ||
		textBox5->Text == String::Empty) return;
	if (!engine->works || engine->permanent) {
		double c, g;
		try {
			c = Convert::ToDouble(textBox4->Text);
			g = Convert::ToDouble(textBox5->Text);
		}
		catch (System::FormatException^ exc) {
			delete exc;
			return;
		}
		engine->works = true;
		addProgress(engine->getCurrent()->Width);
		engine->preset(gcnew PbarInc(
			this, &MainForm::progressBarInc),
			getLast());
		engine->doPower(c, g);
		disableControls(engine->permanent);
	}
}

Void MainForm::button6Click(Object^, EventArgs^) {
	if (engine->dataEmpty() || 
		textBox6->Text == String::Empty) return;
	if (engine->dataEmpty()) return;
	if (!engine->works || engine->permanent) {
		engine->works = true;
		addProgress(engine->getCurrent()->Width);
		engine->preset(gcnew PbarInc(
			this, &MainForm::progressBarInc),
			getLast());
		engine->doLBrightness(Convert::ToInt32(textBox6->Text));
		disableControls(engine->permanent);
	}
}

Void MainForm::button7Click(Object^, EventArgs^) {
	if (engine->dataEmpty() || 
		textBox7->Text == String::Empty) return;
	if (engine->dataEmpty()) return;
	if (!engine->works || engine->permanent) {
		engine->works = true;
		addProgress(engine->getCurrent()->Width);
		engine->preset(gcnew PbarInc(
			this, &MainForm::progressBarInc),
			getLast());
		engine->doLContrast(Convert::ToInt32(textBox7->Text));
		disableControls(engine->permanent);
	}
}

Void MainForm::button8Click(Object^, EventArgs^) {
	if (engine->dataEmpty() || 
		textBox8->Text == String::Empty) return;
	if (engine->dataEmpty()) return;
	if (!engine->works || engine->permanent) {
		engine->works = true;
		addProgress(engine->getCurrent()->Width);
		engine->preset(gcnew PbarInc(
			this, &MainForm::progressBarInc),
			getLast());
		engine->doNBrightness(Convert::ToInt32(textBox8->Text));
		disableControls(engine->permanent);
	}
}

Void MainForm::button9Click(Object^, EventArgs^) {
	if (engine->dataEmpty() || 
		textBox9->Text == String::Empty) return;
	if (engine->dataEmpty()) return;
	if (!engine->works || engine->permanent) {
		engine->works = true;
		addProgress(engine->getCurrent()->Width);
		engine->preset(gcnew PbarInc(
			this, &MainForm::progressBarInc),
			getLast());
		engine->doNContrast(Convert::ToInt32(textBox9->Text));
		disableControls(engine->permanent);
	}
}

Void MainForm::button10Click(Object^, EventArgs^) {
	if (engine->dataEmpty()) return;
	if (!engine->works || engine->permanent) {
		engine->works = true;
		addProgress(engine->getCurrent()->Width * 2);
		engine->preset(gcnew PbarInc(
			this, &MainForm::progressBarInc),
			getLast());
		engine->doAutolevels(
			domainUpDown1->SelectedIndex,
			domainUpDown2->SelectedIndex);
		disableControls(engine->permanent);
	}
}

Void MainForm::button11Click(Object^, EventArgs^) {
	if (engine->dataEmpty() || 
		textBox10->Text == String::Empty || 
		textBox11->Text == String::Empty) return;
	if (!engine->works || engine->permanent) {
		engine->works = true;
		addProgress(engine->getCurrent()->Width);
		engine->preset(gcnew PbarInc(
			this, &MainForm::progressBarInc),
			getLast());
		engine->doFrequencyDomain(
			Convert::ToInt32(textBox10->Text), 
			Convert::ToInt32(textBox11->Text));
		disableControls(engine->permanent);
	}
}

Void MainForm::button12Click(Object^, EventArgs^) {
	if (engine->dataEmpty() || 
		comboBox1->Text == "Type" || 
		comboBox2->Text == "Size") return;
	if (!engine->works || engine->permanent) {
		engine->works = true;
		addProgress(engine->getCurrent()->Width);
		engine->preset(gcnew PbarInc(
			this, &MainForm::progressBarInc),
			getLast());
		engine->doFiltration(
			comboBox1->SelectedIndex, 
			comboBox2->SelectedIndex);
		disableControls(engine->permanent);
	}
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
	case 7:	case 8:	case 9: 
	case 29: case 39: case 40:
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
	int val;
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
	case 39:
		if (engine->getCurrent() != nullptr) val = Math::Min(
			engine->getCurrent()->Width, engine->getCurrent()->Height) / 2;
		else val = 0;
		if (temp->Text != String::Empty &&
			Convert::ToInt32(temp->Text) > val) temp->Text = val.ToString();
		if (temp->Text != String::Empty &&
			Convert::ToInt32(temp->Text) == 0) temp->Text = "1";
		break;
	case 40:
		if (temp->Text != String::Empty &&
			Convert::ToInt32(temp->Text) > 16) temp->Text = "16";
		break;
	}
}

Void MainForm::psPanel_MouseMove(Object^ sender, MouseEventArgs^ e) {
	if (e->Location.X < psPanel->Location.X ||
		e->Location.X > psPanel->Location.X + psPanel->Width ||
		e->Location.Y < psPanel->Location.Y ||
		e->Location.Y > psPanel->Location.Y + psPanel->Height) {
		psPanel->Height = 24;
		isPsPanel = false;
	}
}

Void MainForm::psPanel_MouseDown(Object^ sender, MouseEventArgs^ e) {
	if (e->Button == Windows::Forms::MouseButtons::Left &&
		pbc > 1) {
		psPanel->Height = 7 + (17 * pbc);
		isPsPanel = true;
	}
}

Void MainForm::dataGridView_ColumnWidthChanged(Object^ sender, DataGridViewColumnEventArgs^ e) {
	int h = int(float(engine->getCurrent()->Height) * (
		float(dataGridView->Columns[1]->Width) /
		float(engine->getCurrent()->Width)));
	for each (DataGridViewRow^ var in dataGridView->Rows) {
		var->Height = h;
	}
}

#pragma endregion
#pragma endregion
