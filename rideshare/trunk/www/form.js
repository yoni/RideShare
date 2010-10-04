var email_entered = false;
var password_entered = false;

function setIfEmpty(input, text) {
	if(input.value == '') {
		input.value = text;
		input.style.color = '#7F7F7F';
		input.type = 'text';
		if(input.name == 'emailaddr') {
			email_entered = false;
		} else if(input.name == 'password') {
			password_entered = false;
		}
	}
}

function acceptInput(textbox, startingValue, type) {
	textbox.style.color = 'black';
	if(textbox.name == 'emailaddr') {
		email_entered = true;
	} else if(textbox.name == 'password') {
		password_entered = true;
	}
	if(textbox.value == startingValue) {
		textbox.type = type;
		textbox.value = '';
	}
}

function form_check() {
	if(email_entered == false || password_entered == false) {
		alert('Please fill in all fields');
		return false;
	}
	return true;
}
