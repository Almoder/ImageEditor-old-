#include "Dialog.h"

using namespace Lab1;

Void Dialog::textBox1_KeyDown(Object^  sender, KeyEventArgs^  e) {
	switch (e->KeyCode) {
	case Keys::Up:
		this->t = Convert::ToInt32(textBox1->Text);
		textBox3->Focus();
		break;
	case Keys::Down:
		this->t = Convert::ToInt32(textBox1->Text);
		textBox2->Focus();
		break;
	case Keys::Enter:
		switch (type) {
		case 1:
			this->t = Convert::ToInt32(textBox1->Text);
			ptr->dialogBinar(t, b0, b1);
			e->SuppressKeyPress = true;
			break;
		case 2:
			this->c = Convert::ToDouble(textBox1->Text);
			if (Convert::ToDouble(textBox1->Text) * 25.0 >= 100.0) trackBar1->Value = 50;
			else trackBar1->Value = (int)(Convert::ToDouble(textBox1->Text) * 25);
			ptr->dialogPower(c, g);
			e->SuppressKeyPress = true;
			break;
		}
		break;
	case Keys::Escape:
		this->Close();
	}
}

Void Dialog::textBox2_KeyDown(Object^  sender, KeyEventArgs^  e) {
	switch (e->KeyCode) {
	case Keys::Up:
		this->b0 = Convert::ToInt32(textBox2->Text);
		textBox1->Focus();
		break;
	case Keys::Down:
		this->b0 = Convert::ToInt32(textBox2->Text);
		textBox3->Focus();
		break;
	case Keys::Enter:
		switch (type) {
		case 1:
			this->t = Convert::ToInt32(textBox2->Text);
			ptr->dialogBinar(t, b0, b1);
			e->SuppressKeyPress = true;
			break;
		case 2:
			this->g = Convert::ToDouble(textBox2->Text);
			if (Convert::ToDouble(textBox2->Text) * 25.0 >= 100.0) trackBar2->Value = 50;
			else trackBar2->Value = (int)(Convert::ToDouble(textBox1->Text) * 25);
			ptr->dialogPower(c, g);
			e->SuppressKeyPress = true;
			break;
		}
		break;
	case Keys::Escape:
		this->Close();
	}

}

Void Dialog::textBox3_KeyDown(Object^  sender, KeyEventArgs^  e) {
	switch (e->KeyCode) {
	case Keys::Up:
		this->b1 = Convert::ToInt32(textBox3->Text);
		textBox2->Focus();
		break;
	case Keys::Down:
		this->b1 = Convert::ToInt32(textBox3->Text);
		textBox1->Focus();
		break;
	case Keys::Enter:
		this->b1 = Convert::ToInt32(textBox3->Text);
		ptr->dialogBinar(t, b0, b1);
		e->SuppressKeyPress = true;
		break;
	case Keys::Escape:
		this->Close();
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

/*
Void Dialog::textBox2_KeyPress(Object^  sender, KeyPressEventArgs^  e) {
if (!Char::IsControl(e->KeyChar) && !Char::IsDigit(e->KeyChar) && (e->KeyChar != '.')) {
e->Handled = true;
}
}

Void Dialog::textBox3_KeyPress(Object^  sender, KeyPressEventArgs^  e) {
if (!Char::IsControl(e->KeyChar) && !Char::IsDigit(e->KeyChar) && (e->KeyChar != '.')) {
e->Handled = true;
}
}
*/

Void Dialog::trackBar1_ValueChanged(Object^  sender, EventArgs^  e) {
	switch (type) {
	case 1:
		textBox1->Text = trackBar1->Value.ToString();
		this->t = trackBar1->Value;
		ptr->dialogBinar(t, b0, b1);
		break;
	case 2:
		textBox1->Text = Convert::ToString((double)trackBar1->Value / 25.0);
		this->c = (double)trackBar1->Value / 25.0;
		ptr->dialogPower(c, g);
		break;
	}
}

Void Dialog::trackBar2_ValueChanged(Object^  sender, EventArgs^  e) {
	switch (type) {
	case 1:
		textBox2->Text = trackBar2->Value.ToString();
		this->b0 = trackBar2->Value;
		ptr->dialogBinar(t, b0, b1);
		break;
	case 2:
		textBox2->Text = Convert::ToString((double)trackBar2->Value / 25.0);
		this->g = (double)trackBar2->Value / 25.0;
		ptr->dialogPower(c, g);
		break;
	}
}

Void Dialog::trackBar3_ValueChanged(Object^  sender, EventArgs^  e) {
	textBox3->Text = trackBar3->Value.ToString();
	this->b1 = trackBar3->Value;
	ptr->dialogBinar(t, b0, b1);
}

Void Dialog::OnFormClosing(Object^, FormClosingEventArgs^) {
	ptr->bkpPictureBox();
}