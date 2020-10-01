#include "Dialog.h"

using namespace Lab1;

Dialog::Dialog(MainForm^ ptr, int type) 	{
	InitializeComponent(type);
	t = 0; b0 = 0; b1 = 0;
	c = 1.0; g = 1.0;
	this->ptr = ptr;
	this->type = type;
}

Dialog::~Dialog() {
	ptr->backUpFromPictureBox();
	if (components) {
		delete components;
	}
}

Void Dialog::textBox1_KeyDown(Object^  sender, KeyEventArgs^  e) {
	switch (e->KeyCode) {
	case Keys::Up:
		t = Convert::ToInt32(textBox1->Text);
		textBox3->Focus();
		break;
	case Keys::Down:
		t = Convert::ToInt32(textBox1->Text);
		textBox2->Focus();
		break;
	case Keys::Enter:
		switch (type) {
		case 1:
			t = Convert::ToInt32(textBox1->Text);
			ptr->dialogBinar(t, b0, b1);
			e->SuppressKeyPress = true;
			break;
		case 2:
			c = Convert::ToDouble(textBox1->Text);
			if (Convert::ToDouble(textBox1->Text) * 25.0 >= 100.0) trackBar1->Value = 50;
			else trackBar1->Value = (int)(Convert::ToDouble(textBox1->Text) * 25);
			ptr->dialogPower(c, g);
			e->SuppressKeyPress = true;
			break;
		}
		break;
	case Keys::Escape:
		Close();
	}
}

Void Dialog::textBox2_KeyDown(Object^  sender, KeyEventArgs^  e) {
	switch (e->KeyCode) {
	case Keys::Up:
		b0 = Convert::ToInt32(textBox2->Text);
		textBox1->Focus();
		break;
	case Keys::Down:
		b0 = Convert::ToInt32(textBox2->Text);
		textBox3->Focus();
		break;
	case Keys::Enter:
		switch (type) {
		case 1:
			t = Convert::ToInt32(textBox2->Text);
			ptr->dialogBinar(t, b0, b1);
			e->SuppressKeyPress = true;
			break;
		case 2:
			g = Convert::ToDouble(textBox2->Text);
			if (Convert::ToDouble(textBox2->Text) * 25.0 >= 100.0) trackBar2->Value = 50;
			else trackBar2->Value = (int)(Convert::ToDouble(textBox1->Text) * 25);
			ptr->dialogPower(c, g);
			e->SuppressKeyPress = true;
			break;
		}
		break;
	case Keys::Escape:
		Close();
	}

}

Void Dialog::textBox3_KeyDown(Object^  sender, KeyEventArgs^  e) {
	switch (e->KeyCode) {
	case Keys::Up:
		b1 = Convert::ToInt32(textBox3->Text);
		textBox2->Focus();
		break;
	case Keys::Down:
		b1 = Convert::ToInt32(textBox3->Text);
		textBox1->Focus();
		break;
	case Keys::Enter:
		b1 = Convert::ToInt32(textBox3->Text);
		ptr->dialogBinar(t, b0, b1);
		e->SuppressKeyPress = true;
		break;
	case Keys::Escape:
		Close();
	}
}

Void Dialog::textBox_KeyPress(Object^  sender, KeyPressEventArgs^  e) {
	if (!Char::IsControl(e->KeyChar) && !Char::IsDigit(e->KeyChar) && (e->KeyChar != '.')) {
		e->Handled = true;
	}
	switch (type) {
	case 1:
		trackBar1->Value = Convert::ToInt32(textBox1->Text);
		break;
	case 2:
		trackBar1->Value = (int)(Convert::ToDouble(textBox1->Text) / 25.0);
		break;
	}
}

Void Dialog::trackBar1_ValueChanged(Object^  sender, EventArgs^  e) {
	switch (type) {
	case 1:
		textBox1->Text = trackBar1->Value.ToString();
		t = trackBar1->Value;
		ptr->dialogBinar(t, b0, b1);
		break;
	case 2:
		textBox1->Text = Convert::ToString((double)trackBar1->Value / 25.0);
		c = (double)trackBar1->Value / 25.0;
		ptr->dialogPower(c, g);
		break;
	}
}

Void Dialog::trackBar2_ValueChanged(Object^  sender, EventArgs^  e) {
	switch (type) {
	case 1:
		textBox2->Text = trackBar2->Value.ToString();
		b0 = trackBar2->Value;
		ptr->dialogBinar(t, b0, b1);
		break;
	case 2:
		textBox2->Text = Convert::ToString((double)trackBar2->Value / 25.0);
		g = (double)trackBar2->Value / 25.0;
		ptr->dialogPower(c, g);
		break;
	}
}

Void Dialog::trackBar3_ValueChanged(Object^  sender, EventArgs^  e) {
	textBox3->Text = trackBar3->Value.ToString();
	b1 = trackBar3->Value;
	ptr->dialogBinar(t, b0, b1);
}

Void Dialog::OnFormClosing(Object^, FormClosingEventArgs^) {
	ptr->backUpFromPictureBox();
}