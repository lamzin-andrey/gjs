// Пока здесь
function L(s) {
	return s;
}
var Demo = {
	init:function(){
		e('qdjsExeFilePath').innerHTML = Qt.appDir() + '/index.html';
		e('qdjsExeFileCopyPath').innerHTML = Qt.appDir() + '/index.html.copy';
		
		var sep = '/',
			tempFile;
		if (!PHP.file_exists('/usr/bin')) {
			sep = '\\';
		}
		e('tempFolder1').innerHTML = OS.getTempDir() + sep;
		AppEnv.init([this, this.onOldUserData], [this, this.onLastUserData]);
	},
	onOldUserData:function() {
		this.onUserData();
	},
	onLastUserData:function() {
		this.onUserData();
	},
	onUserData:function() {
		var s = e('inpMkdir').value;
		e('inpMkdir').value = s.replace('/user/', '/' + USER + '/');
		
	},
	onClickPosOnCenter: function(){
		var w = 800, h = 600;
		MW.moveTo( (screen.width - w) / 2, (screen.height - h) / 2);
		MW.resizeTo(w, h);
	},
	minimize: function() {
		MW.showNormal();
		MW.minimize();
		
		setTimeout(function() {
			MW.showNormal();
			MW.minimize();
		}, 100);
	},
	runXTerm: function(){
		var o = this,
			cmd = 'xterm';
		if (!PHP.file_exists('/usr')) {
			cmd = 'notepad';
		}
		o.outputIndex = 0;
		try {
			this.xtId = Env.exec(cmd, [o, o.onFinishXT], [o, o.onStdOutXT], [o, o.onStdErrXT]);
		} catch (err) {
			alert(err);
		}
		
	},
	closeXTerm: function(){
		var o = this, cmd = 'kill ' + this.xtId[0];
		
		if (!PHP.file_exists('/usr')) {
			cmd = 'TASKKILL /PID ' + this.xtId[0] + ' /T';
		}
		o.outputIndex = 0;
		this.xtId = jexec(cmd, [o, o.onFinishXT], [o, o.onStdOutXT], [o, o.onStdErrXT]);
	},
	
	runXTerm2: function(){
		var o = this,
			cmd = 'xterm';
		if (!PHP.file_exists('/usr')) {
			cmd = 'notepad';
		}
		o.outputIndex = 2;
		this.xtId = Env.exec(cmd, [o, o.onFinishXT], [o, o.onStdOutXT], [o, o.onStdErrXT]);
		
	},
	closeXTerm2: function(){
		var o = this, cmd = 'kill ' + this.xtId[0];
		
		if (!PHP.file_exists('/usr')) {
			cmd = 'TASKKILL /PID ' + this.xtId[0] + ' /T';
		}
		o.outputIndex = 2;
		this.xtId = Env.exec(cmd, [o, o.onFinishXT], [o, o.onStdOutXT], [o, o.onStdErrXT]);
	},
    checkXTerm2: function() {
		var suffix = '2';
		if (!this.xtId) {
			e('xtStdErr' + suffix).innerHTML += '<div>Proc is not run yet.</div>';
		}
        if (Env.isRun(this.xtId[1])) {
			e('xtStdOut' + suffix).innerHTML += '<div>Proc is run.</div>';
		} else {
			e('xtStdOut' + suffix).innerHTML += '<div>Proc is not run.</div>';
		}
    },
	onFinishXT: function(stdout, stderr) {
		var suffix = '';
		if (this.outputIndex == 2) {
			suffix = '2'
		}
		e('xtStdOut' + suffix).innerHTML += '<div>' + stdout + '</div>';
		e('xtStdErr' + suffix).innerHTML += '<div>' + stderr + '</div>';
	},
	
	onStdOutXT: function(stdout) {
		// e('xtStdOut').innerHTML += '<div>' + stdout + '</div>';
	},
	
	onStdErrXT: function(stdout) {
		// e('xtStdErr').innerHTML += '<div>' + stdout + '</div>';
	},
	runCopyWithArg: function() {
		var o = this,
			qdjsPath = Qt.appDir().replace('default', '') + 'hw',
			nixHeader = '#! /bin/bash',
			ext = PHP.file_exists('/usr') ? 'sh' : 'bat',
			header = PHP.file_exists('/usr') ? nixHeader : '',
			batchFilePath = Qt.appDir() + '/tmp/shell.' + ext,
			n = '\n',
			cmd = header + n + qdjsPath  + ' ' + Qt.appDir() + ' HelloWorld';
		PHP.file_put_contents(batchFilePath, cmd);
		
		jexec(batchFilePath, [o, o.onFinishXT], [o, o.onStdOutXT], [o, o.onStdErr]);
	},
	onkeydown1:function(evt) {
        var trg = e('inpKD1'),	
			jsOut = e('xtStdOut3'),
			qtOut = e('xtStdErr3'),
			o = this;
		setTimeout(function() {
			jsOut.innerHTML += '<div>' + String.fromCharCode(o.decodeKeyId(evt.keyIdentifier)) + '</div>';
			qtOut.innerHTML += '<div>' + Qt.getLastKeyChar() + '</div>';
		}, 100);
	},
	decodeKeyId:function(id) {
		var i, q = '', firstNotZeroFound = 0;
		id = String(id).replace('U+', '');
		// alert(id);
		for (i = 0; i < id.length; i++) {
			if (firstNotZeroFound || id.charAt(i) != '0') {
				q += id.charAt(i);
				firstNotZeroFound = 1;
			}
		}
		// alert(q);
		return parseInt(q, 16);
	},
	onkeydown2:function(evt) {
        var trg = e('inpKD2'),	
			jsOut = e('xtStdOut4'),
			qtOut = e('xtStdErr4'),
			o = this;
		setTimeout(function() {
			jsOut.innerHTML += '<div>' + evt.keyCode + '</div>';
			qtOut.innerHTML += '<div>' + Qt.getLastKeyCode() + '</div>';
		}, 100);
	},
	onkeydown3:function(evt) {
        var trg = e('inpKD3'),
			o = this;
		setTimeout(function() {
			Qt.setTitle(trg.value);
		}, 10);
	},
	onClickLoadFile:function(suff){
		suff = suff ? suff : '';
		this.currentTextFile = Env.openFileDialog('Выберите текстовый файл с расширением txt или js', '', '*.txt *.js');
		e('inpKD5' + suff).value = FS.readfile(this.currentTextFile);
	},
	onClickSaveFile:function(suff){
		suff = suff ? suff : '';
		if (!this.currentTextFile) {
			alert('Надо сначала выбрать текстовый файл');
			return;
		}
		var nB = FS.writefile(this.currentTextFile, e('inpKD5' + suff).value);
		alert('Записано байт: ' + nB);
	},
	onClickSaveFileWithDialog:function(){
		if (!this.currentTextFile) {
			alert(L('Надо сначала выбрать текстовый файл'));
			return;
		}
		var sPath = Env.saveFileDialog('Выберите файл для сохранения', this.currentTextFile, '*.txt *.js');
		if (!sPath) {
			alert(L('Надо выбрать файл для сохранения'));
			return;
		}
		var nB = FS.writefile(sPath, e('inpKD5').value);
		alert('Записано байт: ' + nB);
	},
	checkQdjsExists:function(){
		alert(PHP.file_exists(Qt.appDir() + '/index.html'));
	},
	checkQdjsCopyExists:function(){
		alert(PHP.file_exists(Qt.appDir() + '/index.html.copy'));
	},
	unlink:function() {
		var sep = '/',
			tempFile;
		if (!PHP.file_exists('/usr/bin')) {
			sep = '\\';
		}
		tempFile = OS.getTempDir() + sep + 't.txt'
		e('tempFolder1').innerHTML = OS.getTempDir() + sep;
		return FS.unlink(tempFile);
	},
	isDirChooseFile:function() {
		e('isDirPath').value = Qt.openFileDialog('Выберите файл', '', '*.*');
	},
	isDirChooseDir:function() {
		e('isDirPath').value = Qt.openDirectoryDialog('Выберите каталог', '');
	},
	isDir:function() {
		var s = e('isDirPath').value;
		if (!s || !PHP.file_exists(s)) {
			alert('Файл не выбран или не существует');
			return;
		}
		
		alert(PHP.is_dir(s));
	},
	scandir:function() {
		var s = Qt.openDirectoryDialog(L('Выберите каталог'), ''),
			ls = FS.scandir(s), i, icon = 'exec.png', width = 24, file;
		ls.sort();
		e('xtStdOut5Content').innerHTML = '';
		for (i = 0; i < ls.length; i++) {
			icon = 'exec.png'
			if (FS.isDir(s + '/' + ls[i])) {
				icon = 'folder' + width + '.png';
			}
			file = '<div><img class="filielistitem" width="' + width + '" height="' + width + '" src="' + Qt.appDir() + '/doc/i/' + icon + '"> <span class="filelistitemtext">' + ls[i] + '</span></div>';
			
			e('xtStdOut5Content').innerHTML += file;
		}
	},
	filesize:function(filter){
		filter = filter ? filter : '*.*';
		var s = Qt.openFileDialog(L('Выберите файл'), '', filter);
		if (FS.fileExists(s)) {
			alert(L('Размер файла ') + FS.filesize(s) + ' ' + L('байт'));
		} else {
			alert(L('Надо выбрать файл'));
		}
	},
	filessize:function(filter){
		filter = filter ? filter : '*.*';
		var a = Qt.openFilesDialog(L('Выберите файлы'), '', filter),
			i, s, sum = 0;
		for (i = 0; i < a.length; i++) {
			s = a[i];
			if (FS.fileExists(s)) {
				sum += FS.filesize(s);
			}
		}
		if (a.length > 0) {
			alert(L('Размер файлов в сумме ') + sum + ' ' + L('байт'));
		} else {
			alert(L('Надо выбрать файл'));
		}
	},
	onkeydown4:function(evt) {
        var trg = e('inpKD4'),
			o = this;
		setTimeout(function() {
			Qt.renameMenuItem(2, 0, trg.value);
		}, 10);
	},
	onClickCreateDir:function() {
		alert(FS.mkdir(e('inpMkdir').value));
	},
	browseForPartDir:function() {
		var s = Qt.openDirectoryDialog(L('Выберите каталог'), ''),
			ls, i, icon = 'exec.png', width = 24, file, o = this, fileInfo, title;
		ls = FS.partDir(s, e('inpPartDir').value, e('chPartDirReset').checked);
		ls.sort(function(a, b) {
			var itemA = o.partDirParseFile(a), itemB = o.partDirParseFile(a);
			if ("EOF" == itemA || "EOF" == itemB) {
				return 0;
			}
			if (itemA.name < itemB.name) {
				return -1;
			}
			return 1;
		});
		
		if (e('chPartDirReset').checked || window.partDirPrevPath != s) {
			e('xtStdOut6Content').innerHTML = '';
		}
		window.partDirPrevPath = s;
		for (i = 0; i < ls.length; i++) {
			icon = 'exec.png'
			try {
				fileInfo = o.partDirParseFile(ls[i]);
			} catch(err) {
				alert(err);
			}
			if (fileInfo == "EOF") {
				break;
			}
			// alert(fileInfo.isExec);
			if (fileInfo.isDir) {
				icon = 'folder' + width + '.png';
			}
			title = "Size: " + fileInfo.size + ".\n";
			title += "lastModify timestamp: " + fileInfo.mtime + ".\n";
			title += "Owner: " + fileInfo.owner + ":" + fileInfo.group + ".\n";
			title += (fileInfo.isSymlink ? "Symlink." : "No symlink.") + "\n";
			title += ((fileInfo.isExec === 1) ? "Executable." : " No exec") + "\n";
			title += "Path: " + fileInfo.path + ".\n";
			title += "Code: " + fileInfo.src + ".\n";
			file = '<div title="' + title + '"><img class="filielistitem" width="' + width + '" height="' + width + '" src="' + Qt.appDir() + '/doc/i/' + icon + '"> <span class="filelistitemtext">' + fileInfo.name + '</span></div>';
			
			e('xtStdOut6Content').innerHTML += file;
		}
	},
	partDirParseFile:function(s) {
		return FS.partDirItem(s);
	}
};
