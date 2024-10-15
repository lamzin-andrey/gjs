function SimpleTextEditor() {}
var ClassMembers = SimpleTextEditor.prototype;
ClassMembers.init = function() {
	MW.setTitle(L('Простой редактор текстовых файлов'));
	MW.setIconImage(App.dir() + '/img/icon48.png');
	this.isCurrentFileChange = false;
	this.textarea = document.getElementById('edit1');
	this.setEventListeners();
};

ClassMembers.setEventListeners = function() {
	var o = this;
	this.textarea.oninput = function(event) {
		o.onInput(event);
	}
}

ClassMembers.onInput = function(event) {
	this.isCurrentFileChange = true;
};

ClassMembers.onClickOpenMenuItem = function() {
	if (!this.isCurrentFileChange) {
		try {
			var fileName = Env.openFileDialog(L('Выберите текстовый файл'), '', '*.txt *.js *.cpp *.html');
			if (fileName && FS.fileExists(fileName)) {
				this.currentFileName = fileName;
				this.textarea.value = FS.readfile(fileName);
			}
		} catch(err) {
			alert(err);
		}
	} else {
		if (confirm(L('Файл') + ' ' + this.currentFileName + ' ' + L('изменен. Сохранить изменения перед открытием файла?'))) {
			FS.writefile(this.currentFileName, this.textarea.value);
			this.isCurrentFileChange = false;
			this.onClickOpenMenuItem();
		}
	}
};

ClassMembers.onClickSaveMenuItem = function() {
	FS.writefile(this.currentFileName, this.textarea.value);
};

ClassMembers.onClickQuitMenuItem = function() {
	if (!this.isCurrentFileChange) {
		App.quit();
		return;
	}
	if (confirm(L('Файл') + ' ' + this.currentFileName + ' ' + L('изменен. Сохранить изменения перед выходом?'))) {
		FS.writefile(this.currentFileName, this.textarea.value);
		this.isCurrentFileChange = false;
		this.onClickQuitMenuItem();
	}
};

window.editor = new SimpleTextEditor();
window.addEventListener('load', 
	function() {
		editor.init();
	},
	false
);

function onClickOpenMenuItem() {
	editor.onClickOpenMenuItem();
}
function onClickSaveMenuItem() {
	editor.onClickSaveMenuItem();
}
function onClickExitMenuItem() {
	editor.onClickQuitMenuItem();
}


function L(s) {
	return s;
}
